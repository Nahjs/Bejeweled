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
    QString type() const;
    
    /* 获取消息的内容
     * @return 返回消息的实际内容
     */
    QString data() const;
    
    /* 将消息对象转换为可以传输的字符串格式
     * 转换格式为：[类型(4字符)][长度(4字符十六进制)][数据内容]
     * @return 返回格式化后的完整消息字符串
     */
    QString serialize() const;
    
#endif // TEXTMESSAGE_H
