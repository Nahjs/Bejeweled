#include "../include/messageprocessor.h"
#include <QMutexLocker>

MessageProcessor::MessageProcessor(QObject* parent) : QObject(parent) {
}

void MessageProcessor::enqueueMessage(TextMessage* message) {
    QMutexLocker locker(&m_mutex);
    
    // 根据优先级插入消息
    auto it = m_messageQueue.begin();
    while (it != m_messageQueue.end()) {
        if (*message < **it) {
            break;
        }
        ++it;
    }
    m_messageQueue.insert(it, message);
}

void MessageProcessor::processMessages() {
    QMutexLocker locker(&m_mutex);
    
    while (!m_messageQueue.isEmpty()) {
        TextMessage* message = m_messageQueue.dequeue();
        processMessage(message);
        emit messageProcessed(message);
    }
}

void MessageProcessor::clear() {
    QMutexLocker locker(&m_mutex);
    
    qDeleteAll(m_messageQueue);
    m_messageQueue.clear();
}

int MessageProcessor::queueSize() const {
    QMutexLocker locker(&m_mutex);
    return m_messageQueue.size();
}
