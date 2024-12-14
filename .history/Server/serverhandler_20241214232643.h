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
 * 服务器消息处理器类
 * 实现具体的消息处理逻辑，包括用户管理和消息转发
 */
class ServerHandler : public TxtMsgHandler {
    /*
     * 用户节点结构
     * 存储每个连接用户的相关信息
     */
    struct Node {
        QString id;         // 用户ID
        QString pwd;        // 用户密码
        QTcpSocket* socket; // 用户socket连接
        bool inGame;        // 游戏状态
        
        Node() : id(""), pwd(""), socket(nullptr), inGame(false) {}
    };

private:
    QList<Node*> m_nodeList;     // 用户节点列表
    QMutex m_mutex;              // 互斥锁保护共享资源
    QMap<QString, QString> m_gameRooms; // 游戏房间映射

    // 实现基类的纯虚函数
    void handleConnect(QTcpSocket& socket, const QString& data) override;
    void handleLogin(QTcpSocket& socket, const QString& data) override;
    void handleChat(QTcpSocket& socket, const QString& data) override;
    void handleDisconnect(QTcpSocket& socket) override;

    // 辅助函数
    QString getOnlineUserId();
    void handle(QTcpSocket& obj, TextMessage& message) override;
};

#endif // SERVERHANDLER_H
