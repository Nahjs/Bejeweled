#include "textmessage.h"

TextMessage::TextMessage(QObject *parent) : QObject(parent)
{
    m_data = "";
    m_type = "";
}

TextMessage::TextMessage(QString type, QString data, QObject *parent) : QObject (parent)
{
    m_type = type.trimmed();
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

QString TextMessage::serialize() const
{
    // 将消息长度转换为16进制字符串
    QString len = QString::asprintf("%X", m_data.length());
    
    // 确保长度字段为4字符，不足补空格
    len.resize(4, ' ');

    // 返回完整的消息格式：类型(4字符) + 长度(4字符) + 数据
    return m_type + len + m_data;
}

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
