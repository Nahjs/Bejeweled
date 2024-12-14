#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "textmessage.h"

// ChatClient类：负责处理与服务器的所有通信
class ChatClient : public QObject
{
    Q_OBJECT

public:
    // 构造函数：创建并初始化聊天客户端
    explicit ChatClient(QObject *parent = nullptr);
    // 析构函数：清理资源
    ~ChatClient();

    // 连接到聊天服务器
    // host: 服务器IP地址
    // port: 服务器端口号
    void connectToServer(const QString &host, int port);

    // 断开与服务器的连接
    void disconnectFromServer();

    // 向服务器发送消息
    // type: 消息类型（如"MSGA"表示聊天消息，"LGIN"表示登录消息）
    // message: 要发送的消息内容
    void sendMessage(const QString &type, const QString &message);

    // 检查是否与服务器保持连接
    bool isConnected() const;

signals:
    // 当成功连接到服务器时触发此信号
    void connected();
    // 当与服务器断开连接时触发此信号
    void disconnected();
    // 当收到服务器消息时触发此信号
    void messageReceived(const QString& type, const QString& data);
    // 当发生错误时触发此信号
    void error(const QString& errorMessage);

private slots:

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
