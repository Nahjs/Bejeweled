#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QMap>
#include "textmessage.h"
#include "messagedata.h"

class QTcpSocket;

class GameManager : public QObject {
    Q_OBJECT

public:
    explicit GameManager(QObject* parent = nullptr);
    void broadcast(const TextMessage& msg);
    void addPlayer(QTcpSocket* socket, const QString& playerId);
    void removePlayer(QTcpSocket* socket);
    QStringList getPlayerList() const;
    int getPlayerCount() const;
    QString getPlayerId(QTcpSocket* socket) const;
    const QMap<QTcpSocket*, QString>& getPlayers() const { return m_players; }

signals:
    void playerCountChanged(int count);
    void gameStateChanged();

private:
    QMap<QTcpSocket*, QString> m_players;  // 在线玩家
};

#endif // GAMEMANAGER_H
