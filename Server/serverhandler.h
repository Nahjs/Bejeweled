#pragma once
#include <QObject>
#include <QTcpSocket>

#include "gamemanager.h"
#include "messagetypes.h"
#include "messagedata.h"  // 确保只包含一次

class ServerHandler : public QObject {
    Q_OBJECT
public:
    // ...existing code...
    void handleMessage(QTcpSocket& socket, const TextMessage& msg);
    // ...existing code...

private slots:
    void handleMatrixSync(QTcpSocket& socket, const QString& data);
    void handleSwap(QTcpSocket& socket, const SwapData& swap);
    void handlePropUse(QTcpSocket& socket, const PropData& prop);
    
private:
    GameManager* m_gameManager;
    // ...existing code...
};
