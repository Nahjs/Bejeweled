#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
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
    if(m_socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = (type + "\n" + message + "\n").toUtf8();
        m_socket->write(data);
    }
}

bool ChatClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

// 删除 connected() 和 disconnected() 方法的实现

void ChatClient::onReadyRead()
{
    while(m_socket->canReadLine()) {
        QString line = QString::fromUtf8(m_socket->readLine()).trimmed();
        QString type = line;
        QString message;
        
        if(m_socket->canReadLine()) {
            message = QString::fromUtf8(m_socket->readLine()).trimmed();
        }
        
        emit messageReceived(type, message);
    }
}

void ChatClient::handleError(QAbstractSocket::SocketError socketError)
{
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
