#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "textmessage.h"

/*
 * ChatClient类实现了客户端与服务器之间的网络通信功能
 * 主要功能：
 * 1. 建立和管理与服务器的TCP连接
 * 2. 发送消息到服务器
public:
    // 构造函数，初始化聊天客户端
    explicit ChatClient(QObject *parent = nullptr);
    ~ChatClient();

    // 连接到指定IP和端口的服务器
    // @param ip 服务器IP地址
    // @param port 服务器端口
    // @return 连接是否成功
    void connectToServer(const QString &host, int port);

    // 断开与服务器的连接
    void disconnectFromServer();

    // 发送消息到服务器
    // @param type 消息类型(4字符)
    // @param data 消息内容
    // @return 发送是否成功
    void sendMessage(const QString &type, const QString &message);

    // 检查是否已连接到服务器
    // @return 连接状态
    bool isConnected() const;

signals:
    // 成功连接到服务器时发出
    void connected();
    // 与服务器断开连接时发出
    void disconnected();
    // 收到服务器消息时发出
    void messageReceived(const QString& type, const QString& data);
    // 发生错误时发出
    void error(const QString& errorMessage);

private slots:
    // 处理接收数据事件
    void onReadyRead();
    // 处理网络错误事件
    void handleError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* m_socket;  // 底层套接字连接
    QString m_buffer;      // 接收数据缓冲区
};

#endif // CHATCLIENT_H
