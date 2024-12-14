#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include "txtmsghandler.h"
#include "textmessage.h"
#include <QList>
#include <QMap>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMutex>

/*
 * 服务器消息处理类
 * 实现具体的消息处理逻辑，包括用户管理和消息转发
 */
class ServerHandler : public TxtMsgHandler {
    /* 用户节点结构
     * 存储每个用户的相关信息
     */
    struct Node {
        QString id;         // 用户唯一标识
        QString pwd;        // 用户密码
        QTcpSocket* socket; // 用户的网络连接
        bool inGame;        // 用户是否在游戏中
        
        Node() : id(""), pwd(""), socket(nullptr), inGame(false) {}
    };

private:
    QList<Node*> m_nodeList;      // 存储所有用户节点的列表
    QMutex m_mutex;               // 用于保护共享资源的互斥锁
    QMap<QString, QString> m_gameRooms; // 游戏房间信息

    // 实现基类要求的消息处理方法
    void handleConnect(QTcpSocket& socket, const QString& data) override;
    void handleLogin(QTcpSocket& socket, const QString& data) override;
    void handleChat(QTcpSocket& socket, const QString& data) override;
    void handleDisconnect(QTcpSocket& socket) override;

    /* 辅助方法 */
    // 获取所有在线用户的ID列表
    QString getOnlineUserId();
    // 向所有在线用户广播消息
    void sendToAllOnlineUser(TextMessage& tm);
    // 根据套接字查找用户节点
    Node* findNodeBySocket(QTcpSocket* socket);
    // 根据用户ID查找用户节点
    Node* findNodeById(const QString& id);

public:
    ServerHandler();
    ~ServerHandler();
    // 处理收到的消息
    void handle(QTcpSocket& obj, TextMessage& message) override;
};

#endif // SERVERHANDLER_H
