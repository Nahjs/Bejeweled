#ifndef START_H
#define START_H

#include <levelmanager.h>

#include "about.h"
#include "help.h"
#include "mainwindow.h"
#include "rank.h"
#include "login.h"
#include "mailform.h"
#include "chatroom.h"
#include <QMainWindow>
#include <propshop.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Start; }
QT_END_NAMESPACE

class Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
    Rank *rank;

private slots:
    void on_btn_startToGame_clicked();
    void doGameToStart();
    void on_btn_mainToRank_clicked();
    void on_btn_help_clicked();
    void on_btn_about_clicked();
    void on_btn_themeChange_clicked();
    void onRankClosed();
    void onLoginSuccess();
    void on_btn_chatRoom_clicked();
    void on_btn_level_clicked();  // 添加关卡模式按钮槽函数

signals:
    void startToGame();
    void sendPath(QString Path);
    public slots:
        void getPath(QString path);
        void getSize(int row,int col);
    void on_btn_propShop_clicked();
private:
    Ui::Start *ui;
    Mainwindow *game;
    Help *help;
    About *about;
    Login *login;
  //  MailForm* mailForm;
    ChatRoom *chatRoom;
    PropShop *propShop;      // 添加商城指针
    LevelManager *levelManager;  // 添加关卡管理器指针
    static int rows;
    static int cols;
};
#endif // START_H
