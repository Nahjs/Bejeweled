#ifndef START_H
#define START_H

#include "about.h"
#include "help.h"
#include "mainwindow.h"
#include "name.h"
#include "rank.h"
#include "login.h"
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

    void doNameConfirm();

    void on_btn_name_clicked();

    void on_btn_help_clicked();

    void on_btn_about_clicked();

    //主题设置
    void on_btn_themeChange_clicked();

    void onRankClosed(); // 添加新的槽函数


public slots:
    void onLoginSuccess(); // 添加处理登录成功的槽函数

signals:
    void startToGame();

private:
    Ui::Start *ui;
    Mainwindow *game;
    Name *name;
    Help *help;
    About *about;
    Login *login; // 添加 Login 实例

};
#endif // START_H
