#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "numMatrix.h"
//#include "cconfiglogic.h"
//#include "cmenudlg.h"
//#include "cranklogic.h"
//#include "cthemedlg.h"
//#include "cmusicplayer.h"
#include <string.h>
#include <QDebug>
#include <QTimer>
#include <thread>
#include <chrono>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QCloseEvent>

#include "cranklogic.h"
#include "rank.h"

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

    void Music();
    void Game_over(bool saveRank = true); //时间耗尽时游戏结束，如果中途退出并保存记录，saverank则设置为false

signals:
    void gameToStart();
    void gameToMenu();
    //void clicked();//鼠标点击信号

private slots:
    void on_btn_gameToStart_clicked();
    void doStartToGame();
    void doMenuToGame();
    void on_btn_gameToMenu_clicked();
    void do_theme_background_change(QString);
    void do_theme_gem_change(QString);
   // void do_music_background_change(QString);
    void on_pushButton_stop_clicked();
    void update_timebar(); //每隔一秒更新时间条的槽函数
    void Game_start();
    void on_pushButton_continue_clicked();
    void on_pushButton_restart_clicked();
    void do_btn_hint();//点击提示
    void paintEvent(QPaintEvent *event);//自定义绘制操作
    void closeEvent(QCloseEvent *event);//在窗口关闭时执行清理工作

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_row_clicked();

    void on_pushButton_col_clicked();

    void on_pushButton_color_clicked();
    void on_pushButton_boom_clicked();

private:
    Ui::Mainwindow *ui;
    QTimer *timer;//定时器
    QImage *image_stop;
    QImage *image_gameover ;
    QLabel *label_image=new QLabel(this); //存放暂停图片的容器
   // CMenuDlg *menu = new CMenuDlg(this);
   // CThemeDlg *theme = new CThemeDlg();
    NumMatrix *numMatrix = new NumMatrix();
    QPoint point;//鼠标位置
    QPoint point1;
    QPoint point2;
    QPixmap pixmap_gem[8];//存宝石图片
    QPixmap pixmap_di;//储存被选中框
    QPixmap number[10];//分数图片
    QPixmap disappear1;
    QPixmap disappear2;
    QPixmap disappear3;//消除泡泡的过程
    //QPixmap circle;//圆圈
    QPixmap addscore;//加分
    int mouseflag;
    int focus;
    int focus_x;
    int focus_y;
    int eliminateNumber = 0;
    int isSelected[8][8];//是否选中（0/1）
    int midSituation[8][8];//消除中间过程（1，2，3，对应三张图片）
    std::string string_grade;//分数转成string类型
    int addScoreSituation=-1;//加分情况的状态（0-9）
    int totaltime=60; //时间
    QString gemtype; //宝石类型，其值为"gem","fish","mine",默认值为"gem"
    int music = 1;
    int eli_music=0;
  //  CMusicPlayer *mus = new CMusicPlayer;
    //CMusicPlayer *mus1 = new CMusicPlayer;
    CRankLogic * ranklogic = new CRankLogic();
    Rank* rankInstance;

    bool props=false,boom=false,color=false,row=false,col=false; //判断是否选择道具

     int cellSize ;//每个单元格的大小
     int offsetX ;
     int offsetY ;//绘制时的偏移量
     int scoreOffsetX ;
     int scoreOffsetY ;//分数显示的偏移量。
     int scoreStep ;//分数动画的步长
    int t;//动画持续时间

protected:
    void mousePressEvent(QMouseEvent *event);
    QPoint mousePos;//鼠标位置a

};

#endif // MAINWINDOW_H
