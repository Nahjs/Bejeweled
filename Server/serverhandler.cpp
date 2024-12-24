// ...existing code...

#include "serverhandler.h"

#include <QTcpSocket>

#include "messagetypes.h"
#include "numMatrix.h"
#include "textmessage.h"

void ServerHandler::handleSwap(QTcpSocket& socket, const SwapData& swap) {
    TextMessage msg(MessageType::MATRIX_SWAP, QString("%1,%2,%3,%4")
        .arg(swap.fromRow)
        .arg(swap.fromCol)
        .arg(swap.toRow)
        .arg(swap.toCol));
    
    m_gameManager->broadcast(msg);
}

void ServerHandler::handlePropUse(QTcpSocket& socket, const PropData& prop) {
    TextMessage msg(MessageType::PROP_USE, QString("%1,%2,%3")
        .arg(static_cast<int>(prop.type))
        .arg(prop.targetRow)
        .arg(prop.targetCol));
    
    m_gameManager->broadcast(msg);
}

void ServerHandler::handleMatrixSync(QTcpSocket& socket, const QString& data) {
    QString playerId = m_gameManager->getPlayerId(&socket);
    qDebug() << "\n=== Matrix Sync Event ===";
    qDebug() << "From player:" << playerId;
    
    // 检查数据格式
    QStringList parts = data.split(',');
    qDebug() << "Received data parts:" << parts.size();
    
    if (parts.size() < 1 + NumMatrix::MAPROWNUM * NumMatrix::MAPCOLNUM) {
        qDebug() << "ERROR: Invalid matrix sync data format";
        qDebug() << "Expected minimum size:" 
                 << (1 + NumMatrix::MAPROWNUM * NumMatrix::MAPCOLNUM);
        qDebug() << "Actual size:" << parts.size();
        return;
    }

    // 记录玩家分数
    qDebug() << "Player score:" << parts[0];

    // 记录矩阵数据
    qDebug() << "Matrix data:";
    int index = 1;
    for(int i = 0; i < NumMatrix::MAPROWNUM; i++) {
        QString row;
        for(int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
            row += parts[index++] + " ";
        }
        qDebug() << "Row" << i << ":" << row;
    }

    // 创建同步消息
    TextMessage msg(MessageType::MATRIX_SYNC);
    msg.setData(data);
    
    // 广播给其他玩家
    int broadcastCount = 0;
    for(auto it = m_gameManager->getPlayers().begin(); it != m_gameManager->getPlayers().end(); ++it) {
        QTcpSocket* playerSocket = it.key();
        if(playerSocket != &socket) {
            QString targetId = m_gameManager->getPlayerId(playerSocket);
            qDebug() << "Broadcasting to player:" << targetId;
            playerSocket->write(msg.serialize().toUtf8());
            playerSocket->flush();
            broadcastCount++;
        }
    }
    
    qDebug() << "Broadcast complete. Sent to" << broadcastCount << "players";
    qDebug() << "=== End Matrix Sync ===\n";
}

void ServerHandler::handleMessage(QTcpSocket& socket, const TextMessage& msg) {
    switch (msg.type()) {
        case MessageType::MATRIX_SYNC:
            handleMatrixSync(socket, msg.data());
            break;
        // ...existing code...
    }
}
