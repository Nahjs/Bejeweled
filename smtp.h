#ifndef SMTP_H
#define SMTP_H

#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

/**
 * @brief SMTP邮件发送类
 * 实现了基本的SMTP协议，用于发送电子邮件
 */
class Smtp : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param serverName SMTP服务器地址
     * @param username 邮箱账号
     * @param password 邮箱密码
     * @param from 发件人地址
     * @param to 收件人地址列表
     * @param subject 邮件主题
     * @param body 邮件正文
     */
    Smtp(const QString &serverName, const QString &username, const QString &password,
         const QString &from, const QStringList &to, const QString &subject, const QString &body);
    ~Smtp();

signals:
    // 发送状态信号
    void status(const QString &);

private slots:
    // 连接状态变化处理
    void stateChanged(QAbstractSocket::SocketState socketState);
    // 错误处理
    void errorReceived(QAbstractSocket::SocketError socketError);
    // 断开连接处理
    void disconnected();
    // 建立连接处理
    void connected();
    // 接收数据处理
    void readyRead();

private:
    QString message;      // 完整的邮件内容
    QTextStream *t;      // 用于socket数据流操作
    QTcpSocket *socket;  // TCP套接字
    QString from;        // 发件人地址
    QString rcpt;        // 当前收件人地址
    QString response;    // 服务器响应内容
    QString user;        // 用户名
    QString pass;        // 密码
    QString server;      // 服务器地址
    int x;              // 当前处理的收件人索引
    QStringList recips; // 收件人列表
    
    // SMTP协议状态枚举
    enum States {
        Init,   // 初始状态
        Auth,   // 认证
        User,   // 用户名
        Pass,   // 密码
        Mail,   // 发件人
        Rcpt,   // 收件人
        Data,   // 数据准备
        Body,   // 邮件内容
        Quit,   // 结束会话
        Close   // 关闭连接
    };
    int state;          // 当前状态
};

#endif
