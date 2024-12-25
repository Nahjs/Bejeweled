#include "../include/textmessage.h"
#include <QStringList>

TextMessage::TextMessage() : 
    m_type(MessageType::MSGA),
    m_data()
{
}

TextMessage::TextMessage(MessageType type, const QString& data) : 
    m_type(type),
    m_data(data)
{
}

QString TextMessage::serialize() const {
    return QString("%1|%2").arg(static_cast<int>(m_type)).arg(m_data);
}

bool TextMessage::unserialize(const QString& str) {
    QStringList parts = str.split('|');
    if (parts.size() != 2) {
        return false;
    }
    
    bool ok;
    int typeVal = parts[0].toInt(&ok);
    if (!ok) {
        return false;
    }
    
    m_type = static_cast<MessageType>(typeVal);
    m_data = parts[1];
    return true;
}
