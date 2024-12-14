#include "chatserver.h"
#include <QDebug>

// 构造函数：初始化聊天服务器
ChatServer::ChatServer(QObject *parent) : QTcpServer(parent)
{
}

/* 启动服务器
 * @param port: 要监听的端口号
 * @return: 启动成功返回true，失败返回false
 */
bool ChatServer::startServer(quint16 port)
{
    // 尝试在指定端口上启动服务器，允许来自任何IP地址的连接
    if(!listen(QHostAddress::Any, port)) {
        qDebug() << "服务器启动失败。错误信息:" << errorString();
        return false;
    }
    qDebug() << "服务器正在监听端口:" << port;
    return true;
}

/* 处理新的客户端连接
 * 当有新客户端连接时，Qt框架会自动调用这个函数
 * @param socketDescriptor: 新连接的套接字描述符
 */
void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    // 为新客户端创建套接字对象
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        // 连接成功，设置信号槽
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::handleReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleDisconnected);
        qDebug() << "新客户端连接，IP地址:" << clientSocket->peerAddress().toString();
    } else {
        delete clientSocket;  // 连接失败，清理资源
    }
}

/* 处理收到的客户端消息
 * 当客户端发送消息时会触发此函数
 */
void ChatServer::handleReadyRead()
{
    // 获取发送消息的客户端套接字
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    // 持续读取消息直到没有完整的行
    while(clientSocket->canReadLine()) {
        // 读取消息类型和内容
        QString type = QString::fromUtf8(clientSocket->readLine()).trimmed();
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        
        qDebug() << "收到消息 - 类型:" << type << "内容:" << message;

        // 根据消息类型处理
        if(type == "LGIN") {  // 登录消息
            QStringList parts = message.split("\r");
            if(parts.size() >= 1) {
                QString username = parts[0];
                clients[clientSocket] = username;
                qDebug() << "User logged in:" << username;
                broadcastMessage("MSGA", username + " 加入了聊天室");
                sendUserList();
            }
        }
        else if(type == "MSGA") {  // 聊天消息
            QString username = clients.value(clientSocket);
            if(!username.isEmpty()) {
                qDebug() << "Broadcasting message from" << username << ":" << message;
                broadcastMessage("MSGA", username + ": " + message);
            }
        }
    }
}

/* 处理客户端断开连接
 * 当客户端断开连接时会触发此函数
 */
void ChatServer::handleDisconnected()
{
    // 获取断开连接的客户端套接字
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    // 获取客户端用户名
    QString username = clients.value(clientSocket);
    if(!username.isEmpty()) {
        // 广播用户离开消息
        broadcastMessage("MSGA", username + " 离开了聊天室", clientSocket);
    }

    // 从客户端列表中移除该客户端
    clients.remove(clientSocket);
    clientSocket->deleteLater();
    sendUserList();
}

/* 广播消息给所有客户端
 * @param type: 消息类型
 * @param message: 消息内容
 * @param exclude: 要排除的客户端（可选）
 */
void ChatServer::broadcastMessage(const QString& type, const QString& message, QTcpSocket* exclude)
{
    QByteArray data = (type + "\n" + message + "\n").toUtf8();
    qDebug() << "Broadcasting:" << type << message;
    
    // 向所有连接的客户端发送消息，排除指定的客户端
    for(QTcpSocket* socket : clients.keys()) {
        if(socket != exclude && socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(data);
            socket->flush();
        }
    }
}

/* 发送用户列表给所有客户端
 * 用户列表以\r分隔
 */
void ChatServer::sendUserList()
{
    QString userList = clients.values().join("\r");
    broadcastMessage("USER", userList);
}
