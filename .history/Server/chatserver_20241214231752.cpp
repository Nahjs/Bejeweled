#include "chatserver.h"
#include <QDebug>

// 构造函数：初始化聊天服务器
ChatServer::ChatServer(QObject *parent) : QTcpServer(parent)
{
}

// 启动服务器函数
// port: 服务器要监听的端口号
// 返回值: 是否成功启动服务器
bool ChatServer::startServer(quint16 port)
{
    // QHostAddress::Any表示监听所有可用的网络接口
    if(!listen(QHostAddress::Any, port)) {
        qDebug() << "服务器启动失败。错误信息:" << errorString();
        return false;
    }
    qDebug() << "服务器成功启动，正在监听端口:" << port;
    return true;
}

// 处理新的客户端连接
// socketDescriptor: 新连接的套接字描述符
void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    // 为新客户端创建一个套接字对象
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        // 连接信号和槽，用于处理客户端的消息和断开连接
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::handleReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleDisconnected);
        qDebug() << "新客户端连接，IP地址:" << clientSocket->peerAddress().toString();
    } else {
        delete clientSocket;
    }
}

// 处理客户端发来的消息
void ChatServer::handleReadyRead()
{
    // 获取发送消息的客户端套接字
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    // 循环读取消息直到没有更多数据
    while(clientSocket->canReadLine()) {
        // 读取消息类型和内容（每条消息由两行组成）
        QString type = QString::fromUtf8(clientSocket->readLine()).trimmed();
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        
        qDebug() << "收到消息 - 类型:" << type << "内容:" << message;

        // 处理登录消息
        if(type == "LGIN") {
            QStringList parts = message.split("\r");
            if(parts.size() >= 1) {
                QString username = parts[0];
                clients[clientSocket] = username; // 保存用户信息
                qDebug() << "用户登录:" << username;
                broadcastMessage("MSGA", username + " 加入了聊天室");
                sendUserList(); // 更新在线用户列表
            }
        }
        // 处理普通聊天消息
        else if(type == "MSGA") {
            QString username = clients.value(clientSocket);
            if(!username.isEmpty()) {
                qDebug() << "转发来自" << username << "的消息:" << message;
                broadcastMessage("MSGA", username + ": " + message);
            }
        }
    }
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
