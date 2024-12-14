#include "txtmsgassembler.h"

/* 消息组装器构造函数
 * 用于创建新的消息组装器实例
 */
TxtMsgAssembler::TxtMsgAssembler(QObject* parent) : QObject(parent)
{
}

/* 清空当前消息的处理状态
 * 重置类型、长度和数据，但不清空队列
 */
void TxtMsgAssembler::clear()
{
    m_type = "";     // 清空消息类型
    m_length = 0;    // 重置消息长度
    m_data = "";     // 清空消息数据
}

/* 从队列中获取指定数量的字符
 * @param n: 要获取的字符数量
 * @return: 获取到的字符串
 */
QString TxtMsgAssembler::fetch(int n)
{
    QString ret = "";
    // 从队列头部依次取出n个字符
    for(int i=0; i<n; i++)
    {
        ret += m_queue.dequeue();
    }
    return ret;
}

/* 将新接收到的数据放入处理队列
 * @param data: 新接收到的数据
 * @param len: 数据长度
 */
void TxtMsgAssembler::prepare(const char* data, int len)
{
    if( data != nullptr )
    {
        // 将数据逐字符放入队列
        for(int i=0; i<len; i++)
        {
            m_queue.enqueue(data[i]);
        }
    }
}

/* 尝试从已有数据组装消息
 * @return: 如果可以组装成完整消息则返回消息对象，否则返回nullptr
 */
        ret = makeMessage();
    }

    if( ret != nullptr )
    {
        clear();
    }

    return QSharedPointer<TextMessage>(ret);
}

QSharedPointer<TextMessage> TxtMsgAssembler::assemble(const char* data, int len)
{
    prepare(data, len);

    return assemble();
}

bool TxtMsgAssembler::makeTypeAndLength()
{
    bool ret = (m_queue.length() >= 8);

    if( ret )
    {
        QString len = "";

        m_type = fetch(4);

        len = fetch(4);

        m_length = len.trimmed().toInt(&ret, 16);

        if( !ret )
        {
            clear();
        }
    }

    return ret;
}

TextMessage* TxtMsgAssembler::makeMessage()
{
    TextMessage* ret = nullptr;

    if( m_type != "" )
    {
        int needed = m_length - m_data.length();
        int n = (needed <= m_queue.length()) ? needed : m_queue.length();

        m_data += fetch(n);

        if( m_length == m_data.length() )
        {
            ret = new TextMessage(m_type, m_data);
        }
    }

    return ret;
}

void TxtMsgAssembler::reset()
{
    clear();
    m_queue.clear();
}
