#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include "textmessage.h"

class MessageHandler : public QObject {
    Q_OBJECT
    
public:
    explicit MessageHandler(QObject* parent = nullptr);
    virtual ~MessageHandler() = default;
    
    // 主消息处理入口
    virtual void handleMessage(QTcpSocket& socket, TextMessage& message) = 0;

protected:
    // 基础消息处理方法
    virtual void handleConnect(QTcpSocket& socket, const QString& data) = 0;
    virtual void handleLogin(QTcpSocket& socket, const QString& data) = 0;
    virtual void handleChat(QTcpSocket& socket, const QString& data) = 0;
    virtual void handleDisconnect(QTcpSocket& socket) = 0;
    virtual void handleGameAction(QTcpSocket& socket, const QString& data) = 0;
};

#endif // MESSAGEHANDLER_H
