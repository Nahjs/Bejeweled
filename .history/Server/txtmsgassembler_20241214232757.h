#ifndef TXTMSGASSEMBLER_H
#define TXTMSGASSEMBLER_H

#include <QObject>
#include <QQueue>
#include <QSharedPointer>
#include "textmessage.h"

/*
 * 消息组装器类
 * 用于将接收到的零散数据重新组装成完整的消息对象
 */
class TxtMsgAssembler : public QObject
{
    // 成员变量
    QQueue<char> m_queue;      // 字符队列，用于存储接收到的数据
    QString m_type;            // 当前正在处理的消息类型
    int m_length;              // 当前消息的长度
    QString m_data;            // 当前消息的数据内容

    // 私有辅助方法
    void clear();              // 清空当前消息的处理状态
    QString fetch(int n);      // 从队列中获取指定数量的字符
    bool makeTypeAndLength();  // 解析消息类型和长度
    TextMessage* makeMessage(); // 生成消息对象

public:
    explicit TxtMsgAssembler(QObject* parent = nullptr);

    /* 将新接收到的数据加入处理队列
     * @param data: 新接收到的数据
     * @param len: 数据长度
     */
    void prepare(const char* data, int len);

    /* 组装消息（带新数据）
     * @param data: 新数据
     * @param len: 数据长度
     * @return 如果可以组装成完整消息则返回消息对象，否则返回nullptr
     */
    QSharedPointer<TextMessage> assemble(const char* data, int len);

    /* 尝试从已有数据组装消息
     * @return 如果可以组装成完整消息则返回消息对象，否则返回nullptr
     */
    QSharedPointer<TextMessage> assemble();

    /* 重置组装器状态
     * 清空所有缓存的数据和处理状态
     */
    void reset();
};

#endif // TXTMSGASSEMBLER_H
