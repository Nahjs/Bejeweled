#pragma once
#include <QObject>
#include <QTcpSocket>
#include "../common/include/textmessage.h"

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    void connectToServer(const QString &host, int port);
    void disconnectFromServer();
    void sendMessage(const QString &type, const QString &message);
    void sendMatchRequest(int desiredPlayers);
    void sendMatchCancel();
    bool isConnected() const;

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString& type, const QString& data);
    void error(const QString& errorMessage);
    void matchFound(const QString& data);
    void matchFull(const QString& data);
    void matchCancelled(const QString& data);
    void matchWaiting(const QString& data);
    void matchFailed(const QString& data);
    void battleStarted(const QString& opponentName);  // 添加新的信号声明

private slots:
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void handleError(QAbstractSocket::SocketError socketError);
    void handleServerMessage(const QString &type, const QString &data);

    void handleMessage(const QString &type, const QString &data);

    void sendBattleRequest();

    void onDisconnected();

private:
    QTcpSocket* m_socket;
    QString m_host;
    int m_port;
    QString m_buffer;
    QString m_username;
};
