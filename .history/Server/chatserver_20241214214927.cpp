#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent)
{
}

bool ChatServer::startServer(quint16 port)
{
    if(!listen(QHostAddress::Any, port)) {
        qDebug() << "Server failed to start. Error:" << errorString();
        return false;
    }
    qDebug() << "Server is running on port" << port;
    return true;
}

void ChatServer::handleNewConnection()
{
    QTcpSocket *clientSocket = nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::handleReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleDisconnected);
    
    qDebug() << "New client connected";
}

void ChatServer::handleReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    while(clientSocket->canReadLine()) {
        QString line = QString::fromUtf8(clientSocket->readLine()).trimmed();
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        
        if(line == "LGIN") {
            QStringList parts = message.split("\r");
            if(parts.size() >= 1) {
                QString username = parts[0];
                clients[clientSocket] = username;
                sendUserList();
                broadcastMessage("MSGA", username + " 加入了聊天室", clientSocket);
            }
        }
        else if(line == "MSGA") {
            QString username = clients.value(clientSocket);
            if(!username.isEmpty()) {
                broadcastMessage("MSGA", username + ": " + message);
            }
        }
    }
}

void ChatServer::handleDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    QString username = clients.value(clientSocket);
    if(!username.isEmpty()) {
        broadcastMessage("MSGA", username + " 离开了聊天室", clientSocket);
    }

    clients.remove(clientSocket);
    clientSocket->deleteLater();
    sendUserList();
}

void ChatServer::broadcastMessage(const QString& type, const QString& message, QTcpSocket* exclude)
{
    QByteArray data = (type + "\n" + message + "\n").toUtf8();
    for(QTcpSocket* socket : clients.keys()) {
        if(socket != exclude) {
            socket->write(data);
        }
    }
}

void ChatServer::sendUserList()
{
    QString userList = clients.values().join("\r");
    broadcastMessage("USER", userList);
}
