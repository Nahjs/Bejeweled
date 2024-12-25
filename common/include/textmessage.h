#pragma once

#include <QString>
#include "messagetypes.h"

class TextMessage {
public:
    TextMessage();
    TextMessage(MessageType type, const QString& data = QString());

    MessageType type() const { return m_type; }
    QString data() const { return m_data; }
    void setData(const QString& data) { m_data = data; }
    void setType(MessageType type) { m_type = type; }

    QString serialize() const;
    bool unserialize(const QString& str);

private:
    MessageType m_type;
    QString m_data;
};
