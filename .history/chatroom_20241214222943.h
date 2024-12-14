#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include "Client/chatclient.h"
#include <QMessageBox>
#include "login.h"
//另外用到了哪些技术，怎么实现的，期间遇到过哪些难题
namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();

protected:
    void closeEvent(QCloseEvent *event) override;  // 添加这一行

private slots:
    void onChatConnected();
    void onChatDisconnected();
    void onChatError(const QString& error);
    void onSendMessage();
    void handleChatMessage(const QString& type, const QString& message);
    void on_registerButton_clicked();  // 添加注册按钮槽函数
    void onRegisterSuccess();  // 添加注册成功处理函数

private:
    Ui::ChatRoom *ui;
    ChatClient *chatClient;
    
    void setupChatConnections();
    void appendChatMessage(const QString& message);
};

#endif // CHATROOM_H
