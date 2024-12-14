#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

/*
 * TextMessage类
 * 用于处理服务器和客户端之间传递的消息
 * 每个消息包含两个部分：
 * 1. 类型(type)：4个字符的消息类型标识
 * 2. 数据(data)：实际的消息内容
 */
class TextMessage : public QObject
{
    // 私有成员变量
    QString m_type;    // 消息类型，固定4字符长度
    QString m_data;    // 消息的实际内容

    Q_OBJECT
public:
    /* 默认构造函数
     * 创建一个空的消息对象，类型和内容都为空
     */
    explicit TextMessage(QObject *parent = nullptr);

    /* 带参数的构造函数
     * @param type: 消息类型(4字符)
     * @param data: 消息内容
     * @param parent: 父对象指针(Qt内存管理用)
     */
    TextMessage(QString type, QString data, QObject* parent = nullptr);

    /* 获取消息类型
     * @return 返回4字符的消息类型
     */
    QString type();

    /* 获取消息内容的长度
     * @return 返回消息内容的字符数
     */
    int length();

    /* 获取消息内容
     * @return 返回消息的实际内容
     */
    QString data();

    /* 将消息序列化为字符串
     * 格式：[类型(4字符)][长度(4字符十六进制)][内容]
     * @return 序列化后的字符串
     */
    QString serialize();

    /* 从字符串反序列化消息
     * @param s: 要解析的字符串
     * @return 解析成功返回true，失败返回false
     */
    bool unserialize(QString s);

signals:    // Qt信号机制，当前类不使用

public slots:    // Qt槽机制，当前类不使用
};

#endif // TEXTMESSAGE_H
