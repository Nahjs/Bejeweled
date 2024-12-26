#pragma once

#include <QString>
#include <QVector>
#include <QList>
#include <QMap>  // 添加这行以支持QMap

enum class MessageType {
    MSGA,

    // 系统消息 (0-9)
    CONN = 0,   // 连接请求
    DISC = 1,   // 断开连接
    PING = 2,   // 心跳检测
    PONG = 3,   // 心跳响应
    ERROR = 4,  // 错误消息
    
    // 用户消息 (10-19)
    LOGIN = 10,     // 登录请求
    LOGOUT = 11,    // 登出请求
    USER_LIST = 12, // 用户列表更新
    LOGIN_OK = 13,  // 登录成功
    LOGIN_FAIL = 14,// 登录失败
    
    // 聊天消息 (20-29)
    CHAT_ALL = 20,  // 群聊消息
    CHAT_PRIV = 21, // 私聊消息
    
    // 游戏基础消息 (30-39)
    GAME_REQ = 30,  // 请求游戏
    GAME_JOIN = 31, // 加入游戏
    GAME_READY = 32,// 准备开始
    GAME_START = 33,// 游戏开始
    GAME_OVER = 34, // 游戏结束
    GAME_QUIT = 35, // 退出游戏
    
    // 游戏操作消息 (40-49)
    SWAP = 40,      // 交换方块
    MOVE = 41,      // 移动确认/结果
    PROP_USE = 42,  // 使用道具
    
    // 游戏状态消息 (50-59)
    SYNC = 50,      // 状态同步
    SCORE = 51,     // 分数更新
    PROP_UPDATE = 52,// 道具更新

    // 对战游戏消息 (60-69)
    BATTLE_REQ = 60,   // 请求对战
    BATTLE_JOIN = 61,  // 加入对战
    BATTLE_START = 62, // 对战开始
    BATTLE_END = 63,   // 对战结束
    
    // 对战状态消息 (70-79)
    MATRIX_SYNC = 70,  // 矩阵同步
    SCORE_SYNC = 71,   // 分数同步
    COMBO_SYNC = 72,   // 连击同步
    PROP_SYNC = 73,    // 道具同步
    
    // 对战操作消息 (80-89)
    MATRIX_SWAP = 80,  // 矩阵交换
    MATRIX_ELIM = 81,  // 矩阵消除
    MATRIX_DROP = 82,  // 矩阵下落
    PROP_TRIGGER = 83, // 道具触发
    
    MATCH_REQUEST,   // 请求匹配
    MATCH_CANCEL,    // 取消匹配
    MATCH_STATUS,    // 匹配状态

    GAME_END,        // 游戏结束
    SURRENDER,       // 认输

    // 房间相关消息 (90-99)
    ROOM_CREATE = 90,    // 创建房间
    ROOM_JOIN = 91,      // 加入房间
    ROOM_LEAVE = 92,     // 离开房间
    ROOM_LIST = 93,      // 房间列表
    ROOM_INFO = 94,      // 房间信息
    ROOM_START = 95,     // 房主开始游戏
    ROOM_READY = 96,     // 玩家准备
    ROOM_UPDATE = 97,    // 房间状态更新
};

// 定义道具类型
enum class PropType {
    BOOM = 1,    // 爆炸道具(3x3范围)
    ROW = 2,     // 行消除
    COLUMN = 3,  // 列消除
    COLOR = 4    // 同色消除
};

// 定义消息数据结构
struct BattleData {
    QString playerId;     // 玩家ID
    int score;           // 当前分数
    QVector<QVector<int>> matrix;  // 矩阵数据
};

// 添加房间数据结构
struct RoomInfo {
    QString roomId;
    QString hostName;
    QStringList players;
    QMap<QString, bool> readyStatus;
    int maxPlayers;
    bool isPlaying;
};
