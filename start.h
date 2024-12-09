#ifndef START_H
#define START_H

#include "about.h"
#include "help.h"
#include "rank.h"
#include "name.h"
#include "mainwindow.h"

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
signals:
    void startToGame();

private:
    Ui::Start *ui;
    Mainwindow *game;
    Name *name;
    Help *help;
    About *about;

};
#endif // START_H
