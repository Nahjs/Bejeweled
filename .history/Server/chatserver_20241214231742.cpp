#include "chatserver.h"
#include <QDebug>

// 构造函数：初始化聊天服务器
ChatServer::ChatServer(QObject *parent) : QTcpServer(parent)
{
}

// 启动服务器函数
    if(!listen(QHostAddress::Any, port)) {
        qDebug() << "Server failed to start. Error:" << errorString();
        return false;
    }
    qDebug() << "Server is running on port" << port;
    return true;
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::handleReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleDisconnected);
        qDebug() << "New client connected from:" << clientSocket->peerAddress().toString();
    } else {
        delete clientSocket;
    }
}

void ChatServer::handleReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    while(clientSocket->canReadLine()) {
        QString type = QString::fromUtf8(clientSocket->readLine()).trimmed();
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        
        qDebug() << "Received message - Type:" << type << "Message:" << message;

        if(type == "LGIN") {
            QStringList parts = message.split("\r");
            if(parts.size() >= 1) {
                QString username = parts[0];
                clients[clientSocket] = username;
                qDebug() << "User logged in:" << username;
                broadcastMessage("MSGA", username + " 加入了聊天室");
                sendUserList();
            }
        }
        else if(type == "MSGA") {
            QString username = clients.value(clientSocket);
            if(!username.isEmpty()) {
                qDebug() << "Broadcasting message from" << username << ":" << message;
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
    qDebug() << "Broadcasting:" << type << message;
    
    for(QTcpSocket* socket : clients.keys()) {
        if(socket != exclude && socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(data);
            socket->flush();
        }
    }
}

void ChatServer::sendUserList()
{
    QString userList = clients.values().join("\r");
    broadcastMessage("USER", userList);
}
