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
    m_buffer += QString::fromUtf8(m_socket->readAll());

    while (m_buffer.length() >= 8) {
        // 解析消息头
        QString type = m_buffer.mid(0, 4);
        bool ok;
        int length = m_buffer.mid(4, 4).trimmed().toInt(&ok, 16);
        
        if (!ok || m_buffer.length() < length + 8) {
            break;  // 数据不完整，等待更多数据
        }

        // 提取完整消息
        QString data = m_buffer.mid(8, length);
        m_buffer = m_buffer.mid(length + 8);

        emit messageReceived(type, data);
    }
}

void ChatClient::handleError(QAbstractSocket::SocketError socketError)
{
    emit error(m_socket->errorString());
}
