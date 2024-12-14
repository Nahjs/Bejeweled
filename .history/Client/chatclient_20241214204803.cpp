#include "chatclient.h"

ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &ChatClient::handleConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ChatClient::handleDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatClient::handleReadyRead);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &ChatClient::handleError);
}

ChatClient::~ChatClient()
{
    if (m_socket->isOpen()) {
        m_socket->close();
    }
}

bool ChatClient::connectToServer(const QString& ip, int port)
{
    m_socket->connectToHost(ip, port);
    return m_socket->waitForConnected(5000);  // 5秒超时
}

void ChatClient::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

bool ChatClient::sendMessage(const QString& type, const QString& data)
{
    if (!m_socket->isOpen()) return false;

    TextMessage msg(type, data);
    QByteArray rawData = msg.serialize().toUtf8();
    return m_socket->write(rawData) == rawData.size();
}

bool ChatClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

void ChatClient::handleConnected()
{
    emit connected();
}

void ChatClient::handleDisconnected()
{
    emit disconnected();
}

void ChatClient::handleReadyRead()
{
    // 将接收到的数据添加到缓冲区
    m_buffer += QString::fromUtf8(m_socket->readAll());

    // 持续处理缓冲区中的完整消息
    while (m_buffer.length() >= 8) {  // 最小消息长度为8(类型4字节+长度4字节)
        // 解析消息头
        QString type = m_buffer.mid(0, 4);  // 提取消息类型
        bool ok;
        // 提取消息长度(16进制字符串转整数)
        int length = m_buffer.mid(4, 4).trimmed().toInt(&ok, 16);
        
        // 检查长度解析是否成功，以及缓冲区是否包含完整消息
        if (!ok || m_buffer.length() < length + 8) {
            break;  // 数据不完整，等待更多数据
        }

        // 提取消息内容并更新缓冲区
        QString data = m_buffer.mid(8, length);
        m_buffer = m_buffer.mid(length + 8);

        // 发出消息接收信号
        emit messageReceived(type, data);
    }
}

void ChatClient::handleError(QAbstractSocket::SocketError socketError)
{
    emit error(m_socket->errorString());
}
