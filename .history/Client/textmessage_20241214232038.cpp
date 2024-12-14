#include "textmessage.h"

// 默认构造函数：创建空消息对象
TextMessage::TextMessage(QObject *parent) : QObject(parent)
{
    m_data = "";  // 初始化消息内容为空
    m_type = "";  // 初始化消息类型为空
}

// 带参数的构造函数：创建指定类型和内容的消息
TextMessage::TextMessage(QString type, QString data, QObject *parent) : QObject (parent)
{
    // 去除类型字符串两端的空格并确保长度为4
    m_type = type.trimmed();
    m_type.resize(4, ' ');  // 如果长度不足4，用空格补齐
    m_data = data;
}

QString TextMessage::type()
{
    return m_type;
}

int TextMessage::length()
{
    return m_data.length();
}

QString TextMessage::data()
{
    return m_data;
}

QString TextMessage::serialize() const
{
    // 第1步：将消息内容的长度转换为16进制字符串
    QString len = QString::asprintf("%X", m_data.length());
    
    // 第2步：确保长度字段为4字符，不足则用空格补齐
    len.resize(4, ' ');

    // 第3步：组装完整消息

bool TextMessage::unserialize(QString s)
{
    // 检查消息长度是否至少包含头部(8字符)
    bool ret = (s.length() >= 8);

    if(ret)
    {
        // 提取消息类型和长度
        QString type = s.mid(0, 4);
        QString len = s.mid(4, 4);
        // 将16进制长度转换为整数
        int length = len.toInt(&ret, 16);

        // 验证消息完整性
        ret = ret && ((s.length()-8) == length);

        if(ret)
        {
            // 解析成功，设置消息属性
            m_type = type;
            m_data = s.mid(8, length);
        }
    }

    return ret;
}
