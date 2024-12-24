#include "chatclient.h"
#include <QDebug>
#include <QTimer>

// 构造函数：初始化网络通信组件
ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
    // 创建TCP套接字对象
    m_socket = new QTcpSocket(this);

    // 设置信号和槽的连接
    // 当成功连接到服务器时
    connect(m_socket, &QTcpSocket::connected, this, &ChatClient::connected);
    // 当与服务器断开连接时
    connect(m_socket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    // 当有新数据可读时
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    // 当发生网络错误时
    connect(m_socket, &QTcpSocket::errorOccurred, this, &ChatClient::handleError);
}

ChatClient::~ChatClient()
{
    if (m_socket->isOpen()) {
        m_socket->close();
    }
}

void ChatClient::connectToServer(const QString &host, int port)
{
    // 添加连接超时处理
    QTimer::singleShot(5000, this, [this]() {
        if(m_socket->state() != QAbstractSocket::ConnectedState) {
            emit error("连接超时");
            m_socket->abort();
        }
    });

    // 设置保持连接选项
    m_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    
    qDebug() << "正在连接到服务器:" << host << "端口:" << port;
    m_socket->connectToHost(host, port);
}

void ChatClient::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

void ChatClient::sendMessage(const QString& type, const QString& message)
{
    if(m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "未连接到服务器，无法发送消息";
        return;
    }

    TextMessage textMsg;
    // 将字符串消息类型转换为枚举
    if (type == "MATRIX_SYNC") textMsg.setType(MessageType::MATRIX_SYNC);
    else if (type == "SWAP") textMsg.setType(MessageType::MATRIX_SWAP);
    else if (type == "SCORE_SYNC") textMsg.setType(MessageType::SCORE_SYNC);
    else if (type == "MATRIX_ELIM") textMsg.setType(MessageType::MATRIX_ELIM);
    else if (type == "MATRIX_DROP") textMsg.setType(MessageType::MATRIX_DROP);
    else if (type == "PROP_USE") textMsg.setType(MessageType::PROP_USE);
    else if (type == "PROP_SYNC") textMsg.setType(MessageType::PROP_SYNC);
    else if (type == "GAME") textMsg.setType(MessageType::GAME_REQ);
    else textMsg.setType(MessageType::MSGA);
    
    textMsg.setData(message);
    QString serialized = textMsg.serialize() + "\n";  // 添加换行符确保消息分割

    qDebug() << "发送消息 - 类型:" << type << "序列化数据:" << serialized;
    
    m_socket->write(serialized.toUtf8());
    m_socket->flush();
}

void ChatClient::processMessage()
{
    QByteArray data = m_socket->readAll();
    QDataStream stream(data);
    QString type, message;
    stream >> type >> message;
    
    // 发出信号通知界面更新
    emit messageReceived(type, message);
}

bool ChatClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

// 删除 connected() 和 disconnected() 方法的实现

void ChatClient::onReadyRead()
{
    while (m_socket->canReadLine()) {  // 使用 canReadLine() 确保数据完整
        QByteArray data = m_socket->readLine();
        QString message = QString::fromUtf8(data).trimmed();  // 移除可能的换行符
        
        TextMessage textMsg;
        if(textMsg.unserialize(message)) {
            qDebug() << "收到消息 - 类型:" << static_cast<int>(textMsg.type()) 
                    << "内容:" << textMsg.data();
                    
            // 消息类型转换为字符串
            QString typeStr;
            switch(textMsg.type()) {
                case MessageType::MATRIX_SYNC:
                    typeStr = "MATRIX_SYNC";
                    break;
                case MessageType::SCORE_SYNC:
                    typeStr = "SCORE_SYNC";
                    break;
                case MessageType::MATRIX_SWAP:
                    typeStr = "SWAP";
                    break;
                // ... 其他类型转换
                default:
                    typeStr = QString::number(static_cast<int>(textMsg.type()));
            }
            
            emit messageReceived(typeStr, textMsg.data());
        } else {
            qDebug() << "消息解析失败:" << message;
        }
    }
}

void ChatClient::handleError(QAbstractSocket::SocketError socketError)
{
    // 根据不同的错误类型发出相应的错误信息
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            emit error("服务器关闭了连接");
            break;
        case QAbstractSocket::HostNotFoundError:
            emit error("找不到服务器");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            emit error("连接被拒绝");
            break;
        default:
            emit error("发生错误: " + m_socket->errorString());
    }
}
