#include "server.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "numMatrix.h"

Server::Server(QObject *parent) : QTcpServer(parent), desiredPlayerCount(2) {
    m_matchTimer = new QTimer(this);
    m_matchTimer->setInterval(1000);
    connect(m_matchTimer, &QTimer::timeout, this, &Server::checkMatchQueue);
    m_matchTimer->start();
    

}

bool Server::startServer(quint16 port) {
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "服务器启动失败。错误信息:" << errorString();
        return false;
    }
    qDebug() << "服务器正在监听端口:" << port;
    return true;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        // 优化KeepAlive设置
        clientSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::handleReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &Server::handleDisconnected);
        connect(clientSocket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError error) {
            QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
            qDebug() << "客户端连接错误:" << error << (socket ? socket->errorString() : "");
        });

        clients.append(clientSocket);
        
        // 发送连接确认消息
        QJsonObject response;
        response["type"] = "CONN";
        response["message"] = "连接成功";
        QJsonDocument doc(response);
        clientSocket->write(doc.toJson(QJsonDocument::Compact) + "\n");
        clientSocket->flush();
        
        qDebug() << "\n=== 新客户端连接 ===";
        qDebug() << "Socket描述符:" << socketDescriptor;
        qDebug() << "IP地址:" << clientSocket->peerAddress().toString();
        qDebug() << "端口:" << clientSocket->peerPort();
        qDebug() << "当前连接数:" << clients.size();
        qDebug() << "Socket状态:" << clientSocket->state();
        qDebug() << "===================\n";
        

    } else {
        qDebug() << "客户端连接失败:" << clientSocket->errorString();
        delete clientSocket;
    }
}

void Server::handleReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray data = clientSocket->readAll();
    qDebug() << "\n=== 收到客户端消息 ===";
    qDebug() << "来自:" << clientSocket->peerAddress().toString();
    qDebug() << "原始数据:" << data;

    TextMessage msg;
    if (msg.unserialize(QString::fromUtf8(data))) {
        handleMessage(msg.type(), msg.data(), clientSocket);
    } else {
        // 尝试解析为JSON格式
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject json = doc.object();
            QString type = json["type"].toString();
            QString content = json["message"].toString();

            // 分别处理聊天室和对战消息
            if (type == "CHAT_ALL" || type == "LOGIN") {
                // 聊天室消息直接使用原有处理方式
                handleMessage(*clientSocket, type, content);
            } 
            else if (type == "MATRIX_SYNC") {
                // 对战模式的矩阵同步消息
                handleMatrixSync(*clientSocket, content);
            }
            else if (type == "PLAYER_LIST") {
                // 处理玩家列表请求
               // sendPlayerList(*clientSocket);
            }
            else {
                // 其他消息按原有方式处理
                handleMessage(*clientSocket, type, content);
            }
        }
    }
    qDebug() << "===================\n";
}

void Server::sendPlayerList(QTcpSocket& socket) {
    QJsonArray playerList;
    for (auto it = usernames.begin(); it != usernames.end(); ++it) {
        QJsonObject player;
        player["username"] = it.value();
        player["playerId"] = playerIds[it.key()];
        playerList.append(player);
    }
                
    QJsonObject response;
    response["type"] = "PLAYER_LIST";
    response["message"] = playerList;
    QJsonDocument doc(response);
    socket.write(doc.toJson() + "\n");
    socket.flush();
}

void Server::handleDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QString username = usernames.value(clientSocket);
    if (!username.isEmpty()) {
        qDebug() << "用户断开连接:" << username;
        
        // 发送用户离开消息
        QJsonObject leaveMsg;
        leaveMsg["type"] = "CHAT_ALL";
        leaveMsg["message"] = username + " 离开了聊天室";
        QJsonDocument doc(leaveMsg);
        QByteArray messageData = doc.toJson(QJsonDocument::Compact) + "\n";
        
        // 向其他用户广播离开消息
        for (QTcpSocket* client : clients) {
            if (client != clientSocket && client->state() == QAbstractSocket::ConnectedState) {
                client->write(messageData);
                client->flush();
            }
        }

        // 清理用户数据
        clients.removeOne(clientSocket);
        usernames.remove(clientSocket);
        m_players.remove(clientSocket);
        
        // 更新并广播新的用户列表
        sendUserList();
    }


    
    clientSocket->deleteLater();
}

void Server::broadcastMessage(MessageType type, const QString& data, QTcpSocket* exclude) {
    if (type == MessageType::MATRIX_SYNC) {
        return;
    }

    TextMessage message(type, data);
    QByteArray serialized = message.serialize().toUtf8();
    qDebug() << "广播消息 - 类型:" << static_cast<int>(type);

    for (QTcpSocket* client : clients) {
        if (client != exclude && client->state() == QAbstractSocket::ConnectedState) {
            client->write(serialized);
            client->flush();
        }
    }
}

void Server::sendUserList() {
    qDebug() << "准备发送用户列表更新";
    qDebug() << "当前用户列表:" << usernames.values();
    
    QJsonObject userListMsg;
    userListMsg["type"] = "USER";
    
    // 先构造一个标准的JSON数组
    QJsonArray userArray;
    for (const auto& name : usernames.values()) {
        userArray.append(QJsonValue(name));
    }
    
    // 将数组直接设置为message字段的值
    userListMsg["message"] = userArray;
    
    QJsonDocument doc(userListMsg);
    QByteArray messageData = doc.toJson(QJsonDocument::Compact) + "\n";
    
    qDebug() << "发送用户列表消息:" << QString::fromUtf8(messageData);
    qDebug() << "用户数组内容:" << userArray;
    
    for (QTcpSocket* client : clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(messageData);
            client->flush();
        }
    }
}

void Server::handleMessage(QTcpSocket& socket, const QString& type, const QString& data) {
    if (type == "MATRIX_SYNC") {
        handleMatrixSync(socket, data);
    }
    else if (type == "MATCH_REQUEST") {
        handleMatchRequest(socket, data);
    }
    else if (type == "MATCH_CANCEL") {
        handleMatchCancel(socket, data);
    }
    else if (type == "GAME_END") {
        handleGameEnd(socket, data);
    }
    else if (type == "SURRENDER") {
        handleSurrender(socket, data);
    }
    else if (type == "BATTLE_START") {
        handleBattleStart(socket, data);
    }
    else if (type == "BATTLE_END") {
        handleBattleEnd(socket, data);
    }
    else if (type == "CHAT_ALL") {
        handleChatAll(socket, data);
    }
    else if (type == "LOGIN") {
        handleLogin(socket, data);
    }
}

void Server::handleMessage(MessageType type, const QString& data, QTcpSocket* socket) {
    switch (type) {
        case MessageType::BATTLE_REQ:
            handleBattleStart(*socket, data);
            break;
        case MessageType::MATRIX_SYNC:
            handleMatrixSync(*socket, data);
            break;
        case MessageType::MATCH_REQUEST:
            handleMatchRequest(*socket, data);
            break;
        default:
            // 保持原有的基于字符串的消息处理方式
            handleMessage(*socket, messageTypeToString(type), data);
            break;
    }
}

QString Server::messageTypeToString(MessageType type) {
    switch (type) {
        case MessageType::BATTLE_REQ: return "BATTLE_REQ";
        case MessageType::MATRIX_SYNC: return "MATRIX_SYNC";
        case MessageType::MATCH_REQUEST: return "MATCH_REQUEST";
        // ...添加其他需要的类型
        default: return QString::number(static_cast<int>(type));
    }
}

void Server::handleLogin(QTcpSocket& socket, const QString& data) {
    qDebug() << "处理登录消息:" << data;
    
    // 解析嵌套的JSON数据
    QJsonDocument innerDoc = QJsonDocument::fromJson(data.toUtf8());
    if (!innerDoc.isObject()) {
        qDebug() << "登录数据格式错误";
        return;
    }
    
    QJsonObject loginData = innerDoc.object();
    QString username = loginData["username"].toString();
    QString password = loginData["password"].toString();
    
    qDebug() << "用户尝试登录:" << username;
    
    // 存储用户信息
    usernames[&socket] = username;
    m_players[&socket] = username;
    
    // 发送登录成功响应
    QJsonObject response;
    response["type"] = "LOGIN";
    response["message"] = "success";
    QJsonDocument responseDoc(response);
    socket.write(responseDoc.toJson(QJsonDocument::Compact) + "\n");
    socket.flush();
    
    qDebug() << "用户登录成功:" << username;
    
    // 广播在线用户列表
    sendUserList();  // 使用统一的用户列表发送方法
}

void Server::handleMatrixSync(QTcpSocket& socket, const QString& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (!doc.isObject()) {
        qDebug() << "Invalid matrix sync data format";
        return;
    }

    QJsonObject json = doc.object();
    json["timestamp"] = QDateTime::currentMSecsSinceEpoch();
    
    // 广播同步消息给其他玩家
    QJsonDocument outDoc(json);
    QString syncData = outDoc.toJson(QJsonDocument::Compact);
    
    for(QTcpSocket* client : clients) {
        if(client != &socket && client->state() == QAbstractSocket::ConnectedState) {
            QJsonObject response;
            response["type"] = "MATRIX_SYNC";
            response["message"] = syncData;
            QJsonDocument responseDoc(response);
            client->write(responseDoc.toJson(QJsonDocument::Compact) + "\n");
            client->flush();
        }
    }
}

void Server::handleSwap(QTcpSocket& socket, const SwapData& swap) {
    // ...existing code...
}

void Server::handlePropUse(QTcpSocket& socket, const PropData& prop) {
    // ...existing code...
}

void Server::handleMatchRequest(QTcpSocket& socket, const QString& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        int desiredPlayers = obj["desiredPlayers"].toInt(2);
        ClientInfo client;
        client.socket = &socket;
        client.id = obj["playerId"].toString();
        client.username = obj["username"].toString();
        client.timestamp = QDateTime::currentMSecsSinceEpoch();
        handleMatchRequest(client, desiredPlayers);
    }
}

void Server::handleMatchCancel(QTcpSocket& socket, const QString& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        ClientInfo client;
        client.socket = &socket;
        client.id = obj["playerId"].toString();
        client.username = obj["username"].toString();
        handleMatchCancel(client);
    }
}

void Server::handleMatchRequest(const ClientInfo& client, int desiredPlayers) {
    if (std::find(currentMatch.begin(), currentMatch.end(), client) != currentMatch.end()) {
        sendMessage(client, MessageType::MATCH_STATUS, "已在匹配队列中");
        return;
    }

    pendingMatches.append({client, desiredPlayers});
    sendMessage(client, MessageType::MATCH_STATUS, "已加入匹配队列");
    attemptMatch();
}

void Server::handleMatchCancel(const ClientInfo& client) {
    auto it = std::find_if(pendingMatches.begin(), pendingMatches.end(),
                           [&client](const PendingMatch& pm) { return pm.client.id == client.id; });
    if (it != pendingMatches.end()) {
        pendingMatches.erase(it);
        sendMessage(client, MessageType::MATCH_STATUS, "已取消匹配请求");
    }
}

void Server::attemptMatch() {
    for (int i = 0; i < pendingMatches.size(); ++i) {
        int desired = pendingMatches[i].desiredPlayerCount;
        std::vector<ClientInfo> matchedClients;
        matchedClients.push_back(pendingMatches[i].client);

        for (int j = i + 1; j < pendingMatches.size(); ++j) {
            if (pendingMatches[j].desiredPlayerCount == desired) {
                matchedClients.push_back(pendingMatches[j].client);
                if (matchedClients.size() == desired) {
                    break;
                }
            }
        }

        if (matchedClients.size() == desired) {
            QJsonObject matchInfo;
            QJsonArray players;
            for (const auto& cl : matchedClients) {
                players.append(cl.username);
            }
            matchInfo["state"] = "matched";
            matchInfo["players"] = players;

            for (const auto& cl : matchedClients) {
                sendMessage(cl, MessageType::MATCH_STATUS, QJsonDocument(matchInfo).toJson(QJsonDocument::Compact));
            }

            for (const auto& cl : matchedClients) {
                auto it = std::find_if(pendingMatches.begin(), pendingMatches.end(),
                                       [&cl](const PendingMatch& pm) { return pm.client.id == cl.id; });
                if (it != pendingMatches.end()) {
                    pendingMatches.erase(it);
                }
            }

            attemptMatch();
            break;
        }
    }
}

void Server::checkMatchQueue() {
    if (pendingMatches.isEmpty()) return;

    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    QList<PendingMatch> matchedPlayers;

    while (!pendingMatches.isEmpty()) {
        PendingMatch& firstReq = pendingMatches.first();
        if (currentTime - firstReq.client.timestamp > MATCH_TIMEOUT) {
            QJsonObject response;
            response["state"] = "failed";
            response["reason"] = "匹配超时";
            QJsonDocument doc(response);
            TextMessage msg(MessageType::MATCH_STATUS, QString::fromUtf8(doc.toJson()));
            firstReq.client.socket->write(msg.serialize().toUtf8());
            pendingMatches.takeFirst();
            continue;
        }
        break;
    }

    if (pendingMatches.size() >= MIN_PLAYERS) {
        int matchCount = qMin(pendingMatches.size(), MAX_PLAYERS);
        for (int i = 0; i < matchCount; i++) {
            matchedPlayers.append(pendingMatches.takeFirst());
        }
        startMatch(matchedPlayers);
    }
}

void Server::startMatch(QList<PendingMatch>& players) {
    QJsonArray playerArray;
    QStringList playerIds;
    
    for (const PendingMatch& player : players) {
        playerArray.append(player.client.username);
        playerIds.append(player.client.id);
    }
    
    m_gameRooms[playerIds.first()] = playerIds;

    QJsonObject matchResult;
    matchResult["state"] = "matched";
    matchResult["players"] = playerArray;
    QJsonDocument doc(matchResult);
    TextMessage msg(MessageType::MATCH_STATUS, QString::fromUtf8(doc.toJson()));

    for (const PendingMatch& player : players) {
        player.client.socket->write(msg.serialize().toUtf8());
    }
    
    qDebug() << "成功匹配" << players.size() << "名玩家";
    qDebug() << "玩家列表:" << playerIds.join(", ");
}

void Server::handleGameEnd(QTcpSocket& socket, const QString& data) {
    // 处理游戏结束逻辑
    qDebug() << "Game ended by player:" << socket.peerAddress().toString();
    // ...existing code...
}

void Server::handleSurrender(QTcpSocket& socket, const QString& data) {
    // 处理认输逻辑
    qDebug() << "Player surrendered:" << socket.peerAddress().toString();
    // ...existing code...
}

void Server::handleBattleStart(QTcpSocket& socket, const QString& data) {
    // 处理对战开始逻辑
    qDebug() << "Battle started by player:" << socket.peerAddress().toString();
    // ...existing code...
}

void Server::handleBattleEnd(QTcpSocket& socket, const QString& data) {
    // 处理对战结束逻辑
    qDebug() << "Battle ended by player:" << socket.peerAddress().toString();
    // ...existing code...
}

void Server::handleChatAll(QTcpSocket& socket, const QString& data) {
    qDebug() << "处理群聊消息:" << data;
    
    // 构建JSON消息
    QJsonObject chatMsg;
    chatMsg["type"] = "CHAT_ALL";
    chatMsg["message"] = data;
    QJsonDocument doc(chatMsg);
    QByteArray messageData = doc.toJson(QJsonDocument::Compact) + "\n";
    
    qDebug() << "广播聊天消息:" << messageData;
    
    // 广播给所有其他客户端
    for(QTcpSocket* client : clients) {
        if(client != &socket && client->state() == QAbstractSocket::ConnectedState) {
            qDebug() << "转发消息给:" << client->peerAddress().toString();
            client->write(messageData);
            client->flush();
        }
    }
}

void Server::sendMessage(const ClientInfo& client, MessageType type, const QString& data) {
    TextMessage msg(type, data);
    client.socket->write(msg.serialize().toUtf8());
    client.socket->flush();
}

void Server::handleRoomCreate(QTcpSocket& socket, const QString& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    QString hostName = usernames[&socket];
    QString roomId = QUuid::createUuid().toString();
    
    RoomInfo room;
    room.roomId = roomId;
    room.hostName = hostName;
    room.maxPlayers = obj["maxPlayers"].toInt();
    room.players.append(hostName);
    room.isPlaying = false;
    
    m_rooms[roomId] = room;
    m_playerRooms[&socket] = roomId;
    
    // 通知创建成功
    QJsonObject response;
    response["roomId"] = roomId;
    broadcastRoomList();
    broadcastRoomInfo(roomId);
}

void Server::handleRoomJoin(QTcpSocket& socket, const QString& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (!doc.isObject()) return;
    
    QString roomId = doc.object()["roomId"].toString();
    if (!m_rooms.contains(roomId)) return;
    
    RoomInfo& room = m_rooms[roomId];
    if (room.isPlaying || room.players.size() >= room.maxPlayers) return;
    
    QString playerName = usernames[&socket];
    room.players.append(playerName);
    m_playerRooms[&socket] = roomId;
    
    broadcastRoomInfo(roomId);
}

void Server::broadcastRoomList() {
    QJsonObject response;
    response["type"] = "ROOM_LIST";
    
    QJsonArray roomsArray;
    for (const auto& room : m_rooms) {
        QJsonObject roomObj;
        roomObj["roomId"] = room.roomId;
        roomObj["hostName"] = room.hostName;
        roomObj["maxPlayers"] = room.maxPlayers;
        roomObj["currentPlayers"] = room.players.size();
        roomObj["isPlaying"] = room.isPlaying;
        roomsArray.append(roomObj);
    }
    
    response["message"] = roomsArray;
    QJsonDocument doc(response);
    QByteArray messageData = doc.toJson(QJsonDocument::Compact) + "\n";
    
    qDebug() << "广播房间列表:" << QString::fromUtf8(messageData);
    
    // 发送给所有客户端
    for (QTcpSocket* client : clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(messageData);
            client->flush();
        }
    }
}

void Server::broadcastRoomInfo(const QString& roomId) {
    if (!m_rooms.contains(roomId)) return;
    
    const RoomInfo& room = m_rooms[roomId];
    QJsonObject response;
    response["type"] = "ROOM_INFO";
    
    QJsonObject roomInfo;
    roomInfo["roomId"] = room.roomId;
    roomInfo["hostName"] = room.hostName;
    roomInfo["maxPlayers"] = room.maxPlayers;
    roomInfo["isPlaying"] = room.isPlaying;
    
    QJsonArray playersArray;
    QJsonObject readyStatus;
    for (const QString& player : room.players) {
        playersArray.append(player);
        readyStatus[player] = room.readyStatus.value(player, false);
    }
    roomInfo["players"] = playersArray;
    roomInfo["readyStatus"] = readyStatus;
    
    response["message"] = roomInfo;
    QJsonDocument doc(response);
    QByteArray messageData = doc.toJson(QJsonDocument::Compact) + "\n";
    
    qDebug() << "广播房间信息:" << QString::fromUtf8(messageData);
    
    // 发送给房间内的所有玩家
    for (const QString& playerName : room.players) {
        for (QTcpSocket* client : clients) {
            if (usernames[client] == playerName && 
                client->state() == QAbstractSocket::ConnectedState) {
                client->write(messageData);
                client->flush();
                break;
            }
        }
    }
}

void Server::checkRoomStart(const QString& roomId) {
    if (!m_rooms.contains(roomId)) return;
    
    RoomInfo& room = m_rooms[roomId];
    if (room.isPlaying) return;
    
    // 检查是否所有玩家都准备好了
    bool allReady = true;
    for (const QString& player : room.players) {
        if (player != room.hostName && !room.readyStatus.value(player, false)) {
            allReady = false;
            break;
        }
    }
    
    if (allReady) {
        room.isPlaying = true;
        QJsonObject startMsg;
        startMsg["type"] = "ROOM_START";
        startMsg["message"] = room.roomId;
        QJsonDocument doc(startMsg);
        QByteArray messageData = doc.toJson(QJsonDocument::Compact) + "\n";
        
        // 通知房间内所有玩家游戏开始
        for (const QString& playerName : room.players) {
            for (QTcpSocket* client : clients) {
                if (usernames[client] == playerName && 
                    client->state() == QAbstractSocket::ConnectedState) {
                    client->write(messageData);
                    client->flush();
                    break;
                }
            }
        }
        
        broadcastRoomList(); // 更新大厅显示
    }
}

// 添加其他房间相关的处理函数...
