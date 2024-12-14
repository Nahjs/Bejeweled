#ifndef START_H
#define START_H

#include "about.h"
#include "help.h"
#include "mainwindow.h"
#include "rank.h"
#include "login.h"
#include "mailform.h"
#include "chatroom.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Start; }
QT_END_NAMESPACE

class Start : public QMainWindow
{
    Q_OBJECT

public:
    Start(QWidget *parent = nullptr);
    ~Start();
    Rank *rank;

private slots:
    void on_btn_startToGame_clicked();
    void doGameToStart();

    void on_btn_mainToRank_clicked();

    void on_btn_help_clicked();

    void on_btn_about_clicked();

    //主题设置
    void on_btn_themeChange_clicked();

    void onRankClosed(); // 添加新的槽函数

    void onLoginSuccess(); // 添加处理登录成功的槽函数

  //  void on_btn_sendMail_clicked(); // 添加发送邮件的槽函数

    void onChatConnected();
    void onChatDisconnected();
    void onChatError(const QString& error);
    void onSendMessage();  // 发送聊天消息
    void on_btn_chatRoom_clicked();  // 添加聊天室按钮槽函数

signals:
    void startToGame();

private:
    Ui::Start *ui;
    Mainwindow *game;
    Help *help;
    About *about;
    Login *login; // 添加 Login 实例
    MailForm* mailForm; // 添加 MailForm 实例
    ChatClient *chatClient;  // 聊天客户端
    ChatRoom *chatRoom;  // 添加聊天室实例
    
    void setupChatConnections();  // 设置聊天相关连接
    void handleChatMessage(const QString& type, const QString& message);
#endif // START_H
