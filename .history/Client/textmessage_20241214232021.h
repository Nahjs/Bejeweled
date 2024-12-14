#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

/*
 * TextMessage类用于处理客户端和服务器之间的通信消息
 * 每个消息包含两个主要部分：
 * 1. 类型(type)：固定4个字符长度的消息类型标识
 * 2. 数据(data)：实际传输的消息内容
 */
class TextMessage : public QObject
{
    Q_OBJECT
public:
    // 创建一个空的消息对象，type和data都被初始化为空字符串
    explicit TextMessage(QObject *parent = nullptr);
    
    /* 创建一个带有指定类型和内容的消息对象
     * @param type: 消息类型，必须是4个字符（不足会自动补空格）
     * @param data: 要传输的实际消息内容
     * @param parent: Qt对象树中的父对象指针，用于内存管理
     */
    TextMessage(const QString& type, const QString& data, QObject *parent = nullptr);

    /* 获取消息的类型
     * @return 返回4字符的消息类型
     */
    // @return 序列化后的消息字符串
    QString serialize() const;
    
    // 从字符串反序列化消息
    // @param msg 要反序列化的消息字符串
    // @return 反序列化是否成功
    bool unserialize(const QString& msg);

private:
    QString m_type;  // 消息类型(4字符)
    QString m_data;  // 消息内容
};

#endif // TEXTMESSAGE_H
