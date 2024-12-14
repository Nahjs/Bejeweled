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
    // 格式：[类型(4字符)][长度(4字符)][内容]
    // 例如：'CHAT', '000A', 'Hello'
    return m_type + len + m_data;
}

bool TextMessage::unserialize(QString s)
{
    // 第1步：检查消息基本长度
    // 消息至少要包含类型(4字符)和长度(4字符)
    bool ret = (s.length() >= 8);

    if(ret)
    {
        // 第2步：解析消息头
        QString type = s.mid(0, 4);         // 提取类型字段
        QString len = s.mid(4, 4);          // 提取长度字段
        int length = len.toInt(&ret, 16);   // 将16进制长度转换为整数

        // 第3步：验证消息完整性
        // 实际数据长度必须等于长度字段指定的长度
        ret = ret && ((s.length()-8) == length);

        if(ret)
        {
            // 第4步：提取消息内容
            m_type = type;
            m_data = s.mid(8, length);  // 从第9个字符开始提取指定长度的内容
        }
    }

    return ret;  // 返回解析结果：成功为true，失败为false
}
