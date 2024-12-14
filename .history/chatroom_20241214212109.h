#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include <QMessageBox>
#include "chatclient.h"
#include "login.h"

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
    void show();  // 重写show方法以处理显示前的连接逻辑

private slots:
    void onChatConnected();
    void onChatDisconnected();
    void onChatError(const QString& error);
    void onSendMessage();
    void handleChatMessage(const QString& type, const QString& message);

private:
    Ui::ChatRoom *ui;