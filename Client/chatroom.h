#pragma once
#include <QWidget>
#include "client.h"
#include <QMessageBox>
#include "login.h"

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget {
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
    void setClient(Client *client);  // 添加设置客户端的方法

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onChatConnected();
    void onChatDisconnected();
    void onChatError(const QString& error);
    void onSendMessage();
    void handleChatMessage(const QString& type, const QString& message);
    void on_registerButton_clicked();
    void onRegisterSuccess();

private:
    Ui::ChatRoom *ui;
    Client *client;

    void setupChatConnections();
    void appendChatMessage(const QString& message);
};
