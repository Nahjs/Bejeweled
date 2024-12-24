#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include "messagetypes.h"  // 确保包含消息类型定义

/*
 * 聊天服务器类
 * 负责管理所有客户端连接和消息转发
 */
class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);

    /* 启动服务器
     * @param port: 服务器监听的端口号
     * @return 启动是否成功
     */
    bool startServer(quint16 port);

protected:
    /* 处理新的客户端连接请求
     * @param socketDescriptor: 新连接的套接字描述符
     */
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    // 处理客户端发来的数据
    void handleReadyRead();
    // 处理客户端断开连接
    void handleDisconnected();

private:
    /* 广播消息给所有客户端
     * @param type: 消息类型
     * @param message: 消息内容
     * @param exclude: 不需要发送消息的客户端（可选）
     */
    void broadcastMessage(MessageType type, const QString& message, QTcpSocket* exclude = nullptr);

    // 向所有客户端发送在线用户列表
    void sendUserList();

    // 存储所有已连接的客户端
    QList<QTcpSocket*> clients;
    // 存储所有已连接客户端的用户名
    QMap<QTcpSocket*, QString> usernames;

    void handleBattleRequest(QTcpSocket* client, const QString& data);
    void handleBattleJoin(QTcpSocket* client, const QString& data);
    void handlePropUse(QTcpSocket* client, const QString& data);

    // 存储对战配对信息
    QMap<QString, QString> battlePairs;  // playerId -> opponentId
    // 存储客户端ID映射
    QMap<QTcpSocket*, QString> playerIds;
};

#endif // CHATSERVER_H
