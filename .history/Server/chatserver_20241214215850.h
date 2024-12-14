#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);
    bool startServer(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;  // 添加这一行

private slots:
    void handleReadyRead();
    void handleDisconnected();

private:
    QMap<QTcpSocket*, QString> clients; // 套接字-用户名映射
    void broadcastMessage(const QString& type, const QString& message, QTcpSocket* exclude = nullptr);
    void sendUserList();
};
