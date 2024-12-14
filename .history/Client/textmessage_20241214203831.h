#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

class TextMessage : public QObject
{
    Q_OBJECT
public:
    explicit TextMessage(QObject *parent = nullptr);
    TextMessage(const QString& type, const QString& data, QObject *parent = nullptr);

    QString type() const;
    QString data() const;
    QString serialize() const;
    bool unserialize(const QString& msg);

private:
    QString m_type;  // 4字符消息类型
    QString m_data;  // 消息内容
};

#endif // TEXTMESSAGE_H
