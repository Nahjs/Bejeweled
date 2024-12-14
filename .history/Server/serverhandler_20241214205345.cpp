#include "serverhandler.h"
#include <QDebug>

QString ServerHandler::getOnlineUserId()
{
    QString ret = "";

    for (int i=0; i<m_nodeList.length(); i++) {

        Node* n = m_nodeList.at(i);

        if (n->socket != nullptr){
            ret += n->id + '\r';
        }

    }

    return ret;
}

void ServerHandler::sendToAllOnlineUser(TextMessage &tm)
{
    const QByteArray& ba = tm.serialize().toLatin1();

    for (int i=0; i<m_nodeList.length(); i++) {
        Node* n = (m_nodeList.at(i));

        if( n->socket != nullptr){
            n->socket->write(ba);
        }

    }
}

ServerHandler::ServerHandler() {
    qDebug() << "ServerHandler initialized";
}

ServerHandler::~ServerHandler() {
    // 清理资源
    qDeleteAll(m_nodeList);
    m_nodeList.clear();
}

void ServerHandler::handle(QTcpSocket& obj, TextMessage& message) {
    QMutexLocker locker(&m_mutex); // 自动加锁解锁

    if (message.type() == "CONN") {
        handleConnect(obj, message.data());
    }
    else if (message.type() == "LGIN") {
        handleLogin(obj, message.data());
    }
    else if (message.type() == "MSGA") {
        handleChat(obj, message.data());
    }
    else if (message.type() == "DSCN") {
        handleDisconnect(obj);
    }
}

void ServerHandler::handleConnect(QTcpSocket& socket, const QString& data) {
    qDebug() << "New connection from:" << data;
    // 发送欢迎消息
    TextMessage welcome("MSGA", "Welcome to the chat room!");
    socket.write(welcome.serialize().toLatin1());
}

void ServerHandler::handleLogin(QTcpSocket& socket, const QString& data) {
    QString id = data.section('\r', 0, 0);
    QString pwd = data.section('\r', 1, 1);
    QString result = "";

    int index = -1;

    for (int i = 0; i < m_nodeList.length(); i++) {
        if (id == m_nodeList.at(i)->id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        Node* newNode = new Node();

        if (newNode != nullptr) {
            newNode->id = id;
            newNode->pwd = pwd;
            newNode->socket = &socket;

            m_nodeList.append(newNode);
            result = "LIOK";
        }
        else {
            result = "LIER";
        }
    }
    else {
        Node* n = m_nodeList.at(index);

        if (pwd == n->pwd) {
            n->socket = &socket;
            result = "LIOK";
        }
        else {
            result = "LIER";
        }
    }

    socket.write(TextMessage(result, id).serialize().toLatin1());

    // 登录成功后广播在线用户列表
    if (result == "LIOK") {
        TextMessage tm("USER", getOnlineUserId());
        sendToAllOnlineUser(tm);
    }
}

void ServerHandler::handleChat(QTcpSocket& socket, const QString& data) {
    Node* sender = findNodeBySocket(&socket);
    if (sender) {
        QString message = QString("%1: %2").arg(sender->id).arg(data);
        TextMessage tm("MSGA", message);
        sendToAllOnlineUser(tm);
    }
}

void ServerHandler::handleDisconnect(QTcpSocket& socket) {
    Node* node = findNodeBySocket(&socket);
    if (node) {
        node->socket = nullptr;
        node->inGame = false;
        
        // 广播用户离线消息
        TextMessage tm("USER", getOnlineUserId());
        sendToAllOnlineUser(tm);
    }
}

Node* ServerHandler::findNodeBySocket(QTcpSocket* socket) {
    for (int i = 0; i < m_nodeList.length(); i++) {
        if (m_nodeList.at(i)->socket == socket) {
            return m_nodeList.at(i);
        }
    }
    return nullptr;
}
