#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

// 消息封装类，用于处理客户端和服务器之间的通信消息
class TextMessage : public QObject
{
    Q_OBJECT
public:
    // 默认构造函数
    explicit TextMessage(QObject *parent = nullptr);
    
    // 带参数的构造函数
    // @param type 消息类型(4字符)
    // @param data 消息内容
    // @param parent 父对象指针
    TextMessage(const QString& type, const QString& data, QObject *parent = nullptr);

    // 获取消息类型
    // @return 消息类型
    QString type() const;
    
    // 获取消息内容
    // @return 消息内容
    QString data() const;
    
    // 序列化消息为字符串
    // @return 序列化后的消息字符串
    QString serialize() const;
    
    // 从字符串反序列化消息