#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "../common/include/textmessage.h"  // 使用相对路径包含头文件

/*
 * ChatClient类实现了客户端与服务器之间的网络通信功能
 * 主要功能：
 * 1. 建立和管理与服务器的TCP连接
 * 2. 发送消息到服务器
 * 3. 接收和处理服务器发来的消息
 * 4. 处理各种网络事件和错误
 */
class ChatClient : public QObject
{
    Q_OBJECT

public:
    /* 构造函数：初始化网络通信组件
     * 创建TCP套接字并设置信号槽连接
     */
    explicit ChatClient(QObject *parent = nullptr);
    
    /* 析构函数：清理资源
     * 如果连接还存在，会关闭连接
     */
    ~ChatClient();

    /* 连接到指定的服务器
     * @param host: 服务器的IP地址或域名
     * @param port: 服务器监听的端口号
     */
    void connectToServer(const QString &host, int port);

    /* 主动断开与服务器的连接
     * 会触发disconnected信号
     */
    void disconnectFromServer();

    /* 发送消息到服务器
     * @param type: 消息类型标识（4字符）
     * @param message: 要发送的消息内容
     */
    void sendMessage(const QString &type, const QString &message);

    void processMessage();

    /* 检查当前是否已连接到服务器
     * @return 如果已连接返回true，否则返回false
     */
    bool isConnected() const;

signals:
    // 当成功连接到服务器时触发此信号
    void connected();
    // 当与服务器断开连接时触发此信号
    void disconnected();
    // 当收到服务器消息时触发此信号
    void messageReceived(const QString& type, const QString& data);
    // 当发生网络错误时触发此信号
    void error(const QString& errorMessage);

private slots:
    // 处理套接字有新数据可读的事件
    void onReadyRead();
    // 处理网络错误事件
    void handleError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* m_socket;  // 管理网络连接的套接字对象
    QString m_buffer;      // 用于存储接收到的数据的缓冲区
};

#endif // CHATCLIENT_H
