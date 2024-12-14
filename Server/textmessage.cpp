#include "textmessage.h"

/* 默认构造函数
 * 创建一个空的消息对象
 */
TextMessage::TextMessage(QObject *parent) : QObject(parent)
{
    m_data = "";    // 初始化消息内容为空
    m_type = "";    // 初始化消息类型为空
}

/* 带参数的构造函数
 * @param type: 消息类型，会被处理成固定4字符长度
 * @param data: 消息内容
 * @param parent: 父对象指针
 */
TextMessage::TextMessage(QString type, QString data, QObject *parent) : QObject (parent)
{
    m_type = type.trimmed();        // 去除类型字符串两端的空格
    m_type.resize(4, ' ');          // 确保类型为4字符长度，不足补空格
    m_data = data;                  // 设置消息内容
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

/* 序列化消息为字符串
 * 格式：[类型(4字符)][长度(4字符十六进制)][内容]
 * 示例：'CHAT', '000A', 'Hello'
 */
QString TextMessage::serialize()
{
    // 将消息内容长度转换为16进制字符串
    QString len = QString::asprintf("%X", m_data.length());

    // 确保长度字段为4字符
    len.resize(4, ' ');

    // 组合完整消息
    return m_type + len + m_data;
}

/* 从字符串解析消息
 * @param s: 要解析的字符串
 * @return: 解析成功返回true，失败返回false
 */
bool TextMessage::unserialize(QString s)
{
    // 检查消息长度是否至少包含类型和长度字段(8字符)
    bool ret = (s.length() >= 8);

    if(ret)
    {
        // 提取消息类型(前4字符)和长度字段(接下来4字符)
        QString type = s.mid(0, 4);
        QString len = s.mid(4, 4);
        // 将16进制长度转换为整数
        int length = len.toInt(&ret, 16);

        // 验证消息完整性：剩余内容长度应等于length
        ret = ret && ((s.length() - 8) == length);

        if(ret)
        {
            // 解析成功，设置消息属性
            m_type = type;
            m_data = s.mid(8, length);    // 提取消息内容
        }
    }

    return ret;    // 返回解析结果
}
