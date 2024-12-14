#include "textmessage.h"

// 创建空消息对象，初始化类型和数据为空字符串
TextMessage::TextMessage(QObject *parent) : QObject(parent)
{
    m_data = "";
    m_type = "";
}

/*
 * 创建指定类型和内容的消息对象
 * 会自动处理消息类型的长度，确保是4个字符
 */
TextMessage::TextMessage(QString type, QString data, QObject *parent) : QObject (parent)
{
    // 去除类型字符串两端的空白字符
    m_type = type.trimmed();
    // 确保类型exactly是4个字符，不足补空格
    m_type.resize(4, ' ') ;
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

/*
 * 序列化消息
 * 将消息长度转换为16进制字符串
 * 确保长度字段为4字符，不足补空格
 * 返回完整的消息格式：类型(4字符) + 长度(4字符) + 数据
 */
QString TextMessage::serialize() const
{
    // 将消息长度转换为16进制字符串
    QString len = QString::asprintf("%X", m_data.length());
    
    // 确保长度字段为4字符，不足补空格
    len.resize(4, ' ');

    // 返回完整的消息格式：类型(4字符) + 长度(4字符) + 数据
    return m_type + len + m_data;
}

/*
 * 反序列化消息
 * 检查消息长度是否至少包含头部(8字符)
 * 提取消息类型和长度
 * 将16进制长度转换为整数
 * 验证消息完整性
 * 解析成功，设置消息属性
 */
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
