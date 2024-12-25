#pragma once

#include <QString>
#include <QVector>
#include <QList>

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
    MATCH = 43,     // 消除结果
    REFILL = 44,    // 填充新方块
    DROP = 45,      // 方块下落
    CHAIN = 46,     // 连锁反应
    FAIL = 47,      // 无效移动
    
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
    
    // 对战结果消息 (90-99)
    BATTLE_WIN = 90,   // 对战胜利
    BATTLE_LOSE = 91,  // 对战失败
    BATTLE_DRAW = 92   // 对战平局
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
