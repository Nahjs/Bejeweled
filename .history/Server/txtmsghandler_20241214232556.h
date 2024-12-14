#ifndef TXTMSGHANDLER_H
#define TXTMSGHANDLER_H

#include <QTcpSocket>
#include "textmessage.h"

/*
 * 消息类型枚举
 * 用于标识不同类型的网络消息
 */
enum class MessageType {
    CONNECT = 0,    // 建立连接请求
    LOGIN,          // 用户登录请求
    CHAT,           // 聊天消息
    DISCONNECT,     // 断开连接请求
    GAME_START,     // 开始游戏请求
    GAME_ACTION,    // 游戏操作消息
    GAME_END        // 游戏结束消息
};

/*
 * 文本消息处理器接口类
 * 定义了处理各种网络消息的标准接口
 */
class TxtMsgHandler {
public:
    // 主要的消息处理入口
};

#endif // TXTMSGHANDLER_H

