#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent) : QObject(parent)
{
    m_server = new QTcpServer(this);
}

bool ChatServer::start(int port)
{
    if (!m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server failed to start. Error:" << m_server->errorString();
        return false;
    }
    
    connect(m_server, &QTcpServer::newConnection, this, &ChatServer::handleNewConnection);
    qDebug() << "Server is listening on port" << port;
    return true;
}

void ChatServer::stop()
{
    m_server->close();
}

void ChatServer::handleNewConnection()
{
    QTcpSocket *clientSocket = m_server->nextPendingConnection();
    
    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::handleClientData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleClientDisconnected);
    
    qDebug() << "New client connected";
}

void ChatServer::handleClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;
    
    QString username = m_clients.value(clientSocket);
    m_clients.remove(clientSocket);
    
    broadcast("MSGA", username + " 离开了聊天室");
    updateUserList();
    
    clientSocket->deleteLater();
}

void ChatServer::handleClientData()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    while (clientSocket->canReadLine()) {
        QString line = QString::fromUtf8(clientSocket->readLine()).trimmed();
        QString type = line;
        
        if (!clientSocket->canReadLine()) break;
        QString data = QString::fromUtf8(clientSocket->readLine()).trimmed();
        
        if (type == "LGIN") {
            QStringList loginData = data.split('\
