#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include "chatclient.h"
#include <QMessageBox>

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();

private slots:
    void onChatConnected();
    void onChatDisconnected();
    void onChatError(const QString& error);
    void onSendMessage();
    void handleChatMessage(const QString& type, const QString& message);

private:
    Ui::ChatRoom *ui;
    ChatClient *chatClient;
    
    void setupChatConnections();
    void appendChatMessage(const QString& message);
};

#endif // CHATROOM_H
