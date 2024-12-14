#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "textmessage.h"

class ChatClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatClient(QObject *parent = nullptr);
    ~ChatClient();

    bool connectToServer(const QString& ip, int port);
    void disconnectFromServer();
    bool sendMessage(const QString& type, const QString& data);
    bool isConnected() const;

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString& type, const QString& data);
    void error(const QString& errorMessage);

private slots:
    void handleConnected();
    void handleDisconnected();
    void handleReadyRead();
    void handleError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* m_socket;
    QString m_buffer;
};

#endif // CHATCLIENT_H
