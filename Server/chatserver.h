#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

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
    // 存储所有已连接的客户端, key是套接字指针, value是用户名
    QMap<QTcpSocket*, QString> clients;

    /* 向所有客户端广播消息
     * @param type: 消息类型
     * @param message: 消息内容
     * @param exclude: 不需要发送消息的客户端（可选）
     */
    void broadcastMessage(const QString& type, const QString& message, QTcpSocket* exclude = nullptr);

    // 向所有客户端发送在线用户列表
    void sendUserList();
};

#endif // CHATSERVER_H
