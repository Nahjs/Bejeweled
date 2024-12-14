#include "chatclient.h"
#include <QDebug>

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
    m_socket->connectToHost(host, port);
}

void ChatClient::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

void ChatClient::sendMessage(const QString &type, const QString &message)
{
    // 检查是否已连接到服务器
    if(m_socket->state() == QAbstractSocket::ConnectedState) {
        // 构造消息格式：类型和消息内容之间用换行符分隔
        QByteArray data = (type + "\n" + message + "\n").toUtf8();
        // 输出调试信息
        qDebug() << "正在发送消息 - 类型:" << type << "内容:" << message;
        // 发送数据
        m_socket->write(data);
        // 确保数据立即发送
        m_socket->flush();
    } else {
        qDebug() << "无法发送消息 - 未连接到服务器";
    }
}

bool ChatClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

// 删除 connected() 和 disconnected() 方法的实现

void ChatClient::onReadyRead()
{
    // 只要还有完整的行可以读取就继续处理
    while(m_socket->canReadLine()) {
        // 读取消息类型（第一行）
        QString type = QString::fromUtf8(m_socket->readLine()).trimmed();
        QString message;
        
        // 读取消息内容（第二行）
        if(m_socket->canReadLine()) {
            message = QString::fromUtf8(m_socket->readLine()).trimmed();
        }
        
        // 输出调试信息
        qDebug() << "收到消息 - 类型:" << type << "内容:" << message;
        // 发出消息接收信号
        emit messageReceived(type, message);
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
