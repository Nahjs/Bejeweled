#ifndef TXTMSGHANDLER_H
#define TXTMSGHANDLER_H

#include <QTcpSocket>
#include "textmessage.h"

// 定义消息类型枚举
enum class MessageType {
    CONNECT = 0,    // 连接消息
    LOGIN,          // 登录消息
    CHAT,           // 聊天消息
    DISCONNECT,     // 断开连接
    GAME_START,     // 游戏开始
    GAME_ACTION,    // 游戏动作
    GAME_END        // 游戏结束
};

class TxtMsgHandler {
public:
    virtual void handle(QTcpSocket&, TextMessage&) = 0;
    virtual ~TxtMsgHandler() = default;
protected:
    // 定义处理各类消息的纯虚函数
    virtual void handleConnect(QTcpSocket& socket, const QString& data) = 0;
    virtual void handleLogin(QTcpSocket& socket, const QString& data) = 0;
    virtual void handleChat(QTcpSocket& socket, const QString& data) = 0;
    virtual void handleDisconnect(QTcpSocket& socket) = 0;
};

#endif // TXTMSGHANDLER_H

