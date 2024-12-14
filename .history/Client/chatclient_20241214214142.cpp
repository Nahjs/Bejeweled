#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(socket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &ChatClient::handleError);
}

ChatClient::~ChatClient()
{
    if (socket->isOpen()) {
        socket->close();
    }
}

void ChatClient::connectToServer(const QString &host, int port)
{
    socket->connectToHost(host, port);
}

void ChatClient::disconnectFromServer()
{
    socket->disconnectFromHost();
}

void ChatClient::sendMessage(const QString &type, const QString &message)
{
    if(socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = (type + "\n" + message + "\n").toUtf8();
        socket->write(data);
    }
}

bool ChatClient::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void ChatClient::connected()
{
    emit connected();
}

void ChatClient::disconnected()
{
    emit disconnected();
}

void ChatClient::onReadyRead()
{
    while(socket->canReadLine()) {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        QString type = line;
        QString message;
        
        if(socket->canReadLine()) {
            message = QString::fromUtf8(socket->readLine()).trimmed();
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
            emit error("发生错误: " + socket->errorString());
    }
}
