#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class ChatServer : public QObject
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    bool start(int port = 8888);
    void stop();

private slots:
    void handleNewConnection();
    void handleClientDisconnected();
    void handleClientData();

private:
    QTcpServer *m_server;
    QMap<QTcpSocket*, QString> m_clients; // socket -> username

    void broadcast(const QString &type, const QString &message, QTcpSocket *exclude = nullptr);
    void updateUserList();
};

#endif // CHATSERVER_H
