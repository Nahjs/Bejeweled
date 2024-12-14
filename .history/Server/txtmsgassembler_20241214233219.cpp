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
QSharedPointer<TextMessage> TxtMsgAssembler::assemble()
{
    TextMessage* ret = nullptr;
    bool tryMakeMsg = false;

    // 如果还没有解析消息类型，先尝试解析
    if( m_type == "" )
    {
        tryMakeMsg = makeTypeAndLength();
    }
    else
    {
        tryMakeMsg = true;
    }

    // 如果可以尝试组装消息
    if( tryMakeMsg )
    {
        ret = makeMessage();
    }

    // 如果成功组装了消息，清空处理状态
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

/* 解析消息类型和长度
 * @return: 解析成功返回true，失败返回false
 */
bool TxtMsgAssembler::makeTypeAndLength()
{
    // 检查队列中是否有足够的数据（至少8个字符）
    bool ret = (m_queue.length() >= 8);

    if( ret )
    {
        QString len = "";
        
        // 获取4字符的消息类型
        m_type = fetch(4);
        
        // 获取4字符的长度字段
        len = fetch(4);
        
        // 将16进制的长度转换为整数
        m_length = len.trimmed().toInt(&ret, 16);

        // 如果转换失败，清空处理状态
        if( !ret )
        {
            clear();
        }
    }

    return ret;
}

/* 根据已解析的类型和长度组装消息
 * @return: 成功返回消息对象，失败返回nullptr
 */
TextMessage* TxtMsgAssembler::makeMessage()
{
    TextMessage* ret = nullptr;

    if( m_type != "" )
    {
        // 计算还需要多少数据
        int needed = m_length - m_data.length();
        // 确定本次可以获取多少数据
        int n = (needed <= m_queue.length()) ? needed : m_queue.length();

        m_data += fetch(n);

        if( m_length == m_data.length() )
        {
            ret = new TextMessage(m_type, m_data);
        }
    }

    return ret;
}

/* 重置消息组装器状态
 * 清空当前消息的处理状态和队列
 */
void TxtMsgAssembler::reset()
{
    clear();
    m_queue.clear();
}
