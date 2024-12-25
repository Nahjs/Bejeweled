#include "gamemanager.h"
#include <QTcpSocket>
#include <QDebug>

GameManager::GameManager(QObject* parent) : QObject(parent) {
}

void GameManager::broadcast(const TextMessage& msg) {
    QString serializedMsg = msg.serialize();
    // 广播消息给所有在线玩家
    for(auto it = m_players.begin(); it != m_players.end(); ++it) {
        QTcpSocket* socket = it.key();
        if(socket && socket->isValid() && socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(serializedMsg.toUtf8());
            socket->flush();
        }
    }
}

void GameManager::addPlayer(QTcpSocket* socket, const QString& playerId) {
    if(!m_players.contains(socket)) {
        m_players[socket] = playerId;
        
        // 发送当前玩家列表给新加入的玩家
        TextMessage userListMsg(MessageType::USER_LIST);
        QStringList playerList;
        for(const QString& id : m_players.values()) {
            playerList << id;
        }
        userListMsg.setData(playerList.join(","));
        socket->write(userListMsg.serialize().toUtf8());
        socket->flush();
        
        // 广播新玩家加入消息
        TextMessage joinMsg(MessageType::GAME_JOIN);
        joinMsg.setData(playerId);
        broadcast(joinMsg);
        
        emit playerCountChanged(m_players.size());
    }
}

void GameManager::removePlayer(QTcpSocket* socket) {
    if(m_players.contains(socket)) {
        QString playerId = m_players[socket];
        m_players.remove(socket);
        
        // 广播玩家离开消息
        TextMessage leaveMsg(MessageType::DISC);
        leaveMsg.setData(playerId);
        broadcast(leaveMsg);
        
        emit playerCountChanged(m_players.size());
    }
}

QStringList GameManager::getPlayerList() const {
    return m_players.values();
}

int GameManager::getPlayerCount() const {
    return m_players.size();
}

QString GameManager::getPlayerId(QTcpSocket* socket) const {
    return m_players.value(socket);
}
