#include "serverhandler.h"
#include <QDebug>

/* 获取所有在线用户的ID
 * @return 返回所有在线用户ID，每个ID之间用'\r'分隔
 */
QString ServerHandler::getOnlineUserId()
{
    QString ret = "";

    // 遍历所有用户节点
    for (int i=0; i<m_nodeList.length(); i++) {
        Node* n = m_nodeList.at(i);
        
        // 如果用户有socket连接（表示在线）
        if (n->socket != nullptr){
            ret += n->id + '\r';
        }
    }

    return ret;
}

/* 向所有在线用户广播消息
 * @param tm: 要广播的消息对象
 */
void ServerHandler::sendToAllOnlineUser(TextMessage &tm)
{
    // 将消息序列化为字节数组
    const QByteArray& ba = tm.serialize().toLatin1();

    // 遍历所有用户节点，向在线用户发送消息
    for (int i=0; i<m_nodeList.length(); i++) {
        Node* n = (m_nodeList.at(i));

        if( n->socket != nullptr){  // 用户在线
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

/* 处理客户端消息的主函数
 * @param obj: 客户端套接字
 * @param message: 收到的消息对象
 */
void ServerHandler::handle(QTcpSocket& obj, TextMessage& message) {
    QMutexLocker locker(&m_mutex); // 自动加锁解锁，保护共享资源

    // 根据消息类型调用相应的处理函数
    if (message.type() == "CONN") {         // 连接请求
        handleConnect(obj, message.data());
    }
    else if (message.type() == "LGIN") {    // 登录请求
        handleLogin(obj, message.data());
    }
    else if (message.type() == "MSGA") {    // 聊天消息
        handleChat(obj, message.data());
    }
    else if (message.type() == "DSCN") {    // 断开连接请求
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
