#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include "textmessage.h"

class MessageProcessor : public QObject {
    Q_OBJECT

public:
    explicit MessageProcessor(QObject* parent = nullptr);
    
    // 消息入队
    void enqueueMessage(TextMessage* message);
    // 处理队列中的所有消息
    void processMessages();
    // 清空队列
    void clear();
    // 获取队列大小
    int queueSize() const;

signals:
    void messageProcessed(TextMessage* message);

private:
    QQueue<TextMessage*> m_messageQueue;
    QMutex m_mutex;
    
    virtual void processMessage(TextMessage* message) = 0;
};

#endif // MESSAGEPROCESSOR_H
