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
    void on_btn_themeChange_clicked();
    void onRankClosed();
    void onLoginSuccess();
    void on_btn_chatRoom_clicked();

signals:
    void startToGame();

private:
    Ui::Start *ui;
    Mainwindow *game;
    Help *help;
    About *about;
    Login *login;
    MailForm* mailForm;
    ChatRoom *chatRoom;
};
#endif // START_H
