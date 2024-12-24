#include "chatserver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "textmessage.h"

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
    QTcpSocket *clientSocket = new QTcpSocket(this);
    
    if(clientSocket->setSocketDescriptor(socketDescriptor)) {
        // 设置保持连接选项
        clientSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
        
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::handleReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleDisconnected);
        connect(clientSocket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError error) {
            QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
            qDebug() << "客户端连接错误:" << error << (socket ? socket->errorString() : "");
        });

        clients.append(clientSocket);  // 使用 clients 而不是 m_clients
        
        qDebug() << "\n=== 新客户端连接 ===";
        qDebug() << "IP地址:" << clientSocket->peerAddress().toString();
        qDebug() << "当前连接数:" << clients.size();
        qDebug() << "===================\n";
    } else {
        qDebug() << "客户端连接失败:" << clientSocket->errorString();
        delete clientSocket;
    }
}

/* 处理收到的客户端消息
 * 当客户端发送消息时会触发此函数
 */
void ChatServer::handleReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    QByteArray data = clientSocket->readAll();
    QString message = QString::fromUtf8(data);
    qDebug() << "收到客户端数据:" << data.size() << "字节";
    qDebug() << "原始数据:" << message;

    TextMessage textMsg;
    if(textMsg.unserialize(message)) {
        qDebug() << "解析消息成功 - 类型:" << static_cast<int>(textMsg.type()) 
                << "内容:" << textMsg.data();
        
        // 广播消息给其他客户端
        broadcastMessage(textMsg.type(), textMsg.data(), clientSocket);
    } else {
        qDebug() << "消息解析失败，无效的消息格式";
    }
}

/* 处理客户端断开连接
 * 当客户端断开连接时会触发此函数
 */
void ChatServer::handleDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;

    QString username = usernames.value(clientSocket);
    if(!username.isEmpty()) {
        broadcastMessage(MessageType::CHAT_ALL, username + " 离开了游戏");
    }

    clients.removeOne(clientSocket);
    usernames.remove(clientSocket);
    clientSocket->deleteLater();
    
    sendUserList();
}

/* 广播消息给所有客户端
 * @param type: 消息类型
 * @param message: 消息内容
 * @param exclude: 要排除的客户端（可选）
 */
void ChatServer::broadcastMessage(MessageType type, const QString& data, QTcpSocket* exclude)
{
    TextMessage message(type, data);
    QByteArray serialized = message.serialize().toUtf8();
    
    qDebug() << "广播消息 - 类型:" << static_cast<int>(type) 
             << "大小:" << serialized.size() << "字节";

    for(QTcpSocket* client : clients) {
        if(client != exclude && client->state() == QAbstractSocket::ConnectedState) {
            qint64 written = client->write(serialized);
            client->flush();
            qDebug() << "发送给客户端" << client->peerAddress().toString() 
                    << "写入字节数:" << written;
        }
    }
}

/* 发送用户列表给所有客户端
 * 用户列表以\r分隔
 */
void ChatServer::sendUserList()
{
    QString userList = usernames.values().join("\r");
    broadcastMessage(MessageType::USER_LIST, userList);
}

// 添加新的处理函数
void ChatServer::handleBattleRequest(QTcpSocket* client, const QString& data)
{
    // 解析对战请求数据
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();
    
    QString playerId = obj["playerId"].toString();
    int score = obj["score"].toInt();
    
    // 广播对战请求给其他客户端
    broadcastMessage(MessageType::BATTLE_REQ, data, client);
    qDebug() << "玩家" << playerId << "请求对战";
}

void ChatServer::handleBattleJoin(QTcpSocket* client, const QString& data)
{
    // 解析加入对战数据
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();
    
    QString playerId = obj["playerId"].toString();
    QString targetId = obj["targetId"].toString();
    
    // 发送对战开始消息给双方
    broadcastMessage(MessageType::BATTLE_START, data);
    qDebug() << "玩家" << playerId << "加入了与" << targetId << "的对战";
}

void ChatServer::handlePropUse(QTcpSocket* client, const QString& data)
{
    // 解析道具使用数据
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();
    
    int propType = obj["propType"].toInt();
    int targetX = obj["x"].toInt();
    int targetY = obj["y"].toInt();
    
    // 转发道具使用消息给其他客户端
    broadcastMessage(MessageType::PROP_USE, data, client);
    // 修改枚举输出方式
    qDebug() << "玩家使用道具:" << propType 
             << "位置:" << targetX << "," << targetY;
}

// 删除重复的 broadcastMessage 函数，只保留 MessageType 版本
