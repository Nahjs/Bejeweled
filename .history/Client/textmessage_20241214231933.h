#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

/*
 * TextMessage类用于处理客户端和服务器之间的通信消息
 * 每个消息包含两个主要部分：
 * 1. 类型(type)：固定4个字符的消息类型标识
 * 2. 数据(data)：实际传输的消息内容
 */
class TextMessage : public QObject
{
    Q_OBJECT
public:
    // 创建一个空的消息对象
    explicit TextMessage(QObject *parent = nullptr);
    
    /*
     * 创建一个带有类型和数据的消息对象
     * @param type 消息类型，将自动调整为4个字符（不足补空格）
     * @param data 消息的实际内容
     * @param parent Qt对象树中的父对象
     */
    TextMessage(const QString& type, const QString& data, QObject *parent = nullptr);

    /*
     * 获取消息的类型标识
     * @return 4字符的消息类型
     */
    QString type() const;
    
    /*
     * 获取消息的实际内容
     * @return 消息内容字符串
     */
    QString data() const;
    
    /*
     * 将消息对象转换为可传输的字符串格式
     * 格式为：[类型(4字符)][长度(4字符十六进制)][数据内容]
     * @return 格式化后的完整消息字符串
     */