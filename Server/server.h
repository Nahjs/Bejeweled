#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QQueue>
#include <QTimer>
#include "messagetypes.h"
#include "messagedata.h"
#include "textmessage.h"

struct ClientInfo {
    QTcpSocket* socket;
    QString id;
    QString username;
    qint64 timestamp;

    bool operator==(const ClientInfo& other) const {
        return id == other.id;
    }
};

struct PendingMatch {
    ClientInfo client;
    int desiredPlayerCount;
};

class Server : public QTcpServer {
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void handleMessage(QTcpSocket& socket, const QString& type, const QString& data);  // 修改函数签名

    void handleLogin(QTcpSocket &socket, const QString &data);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void handleReadyRead();

    void sendPlayerList(QTcpSocket &socket);

    void handleDisconnected();
    void handleSwap(QTcpSocket& socket, const SwapData& swap);
    void handlePropUse(QTcpSocket& socket, const PropData& prop);

    void handleMatchRequest(QTcpSocket &socket, const QString &data);

    void handleMatrixSync(QTcpSocket& socket, const QString& data);
    void handleMatchRequest(const ClientInfo& client, int desiredPlayers);
    void handleMatchCancel(const ClientInfo& client);

    void handleMatchCancel(QTcpSocket &socket, const QString &data);

    void handleGameEnd(QTcpSocket& socket, const QString& data);
    void handleSurrender(QTcpSocket& socket, const QString& data);
    void handleBattleStart(QTcpSocket& socket, const QString& data);
    void handleBattleEnd(QTcpSocket& socket, const QString& data);
    void handleChatAll(QTcpSocket& socket, const QString& data);
    void checkMatchQueue();

private:
    void broadcastMessage(MessageType type, const QString& data, QTcpSocket* exclude = nullptr);
    void sendUserList();
    void attemptMatch();
    void startMatch(QList<PendingMatch>& players);
    void sendMessage(const ClientInfo& client, MessageType type, const QString& data);

    QMap<QTcpSocket*, QString> m_players;
    QMap<QTcpSocket*, QString> m_playerNames;
    QQueue<PendingMatch> m_matchQueue;
    QMap<QString, QList<QString>> m_gameRooms;
    QTimer* m_matchTimer;
    QList<QTcpSocket*> clients;
    QMap<QTcpSocket*, QString> usernames;
    QMap<QString, QString> battlePairs;
    QMap<QTcpSocket*, QString> playerIds;
    QVector<ClientInfo> currentMatch;
    int desiredPlayerCount;
    QVector<PendingMatch> pendingMatches;

    static constexpr int MIN_PLAYERS = 2;
    static constexpr int MAX_PLAYERS = 4;
    static constexpr int MATCH_TIMEOUT = 30000;

    // 房间管理
    QMap<QString, RoomInfo> m_rooms;
    QMap<QTcpSocket*, QString> m_playerRooms;  // 玩家-房间映射
    
    void handleRoomCreate(QTcpSocket& socket, const QString& data);
    void handleRoomJoin(QTcpSocket& socket, const QString& data);
    void handleRoomLeave(QTcpSocket& socket, const QString& data);
    void handleRoomReady(QTcpSocket& socket, const QString& data);
    void handleRoomStart(QTcpSocket& socket, const QString& data);
    
    void broadcastRoomList();
    void broadcastRoomInfo(const QString& roomId);
    void checkRoomStart(const QString& roomId);

    static constexpr int HEARTBEAT_TIMEOUT = 60000; // 60秒超时

    // 添加新的消息处理函数
    void handleMessage(MessageType type, const QString& data, QTcpSocket* socket);

    QString messageTypeToString(MessageType type);

    // 添加对战状态跟踪
    struct BattleSession {
        QString hostId;
        QString guestId;
        bool isActive;
        QDateTime startTime;
    };
    QMap<QString, BattleSession> m_battleSessions;
};
