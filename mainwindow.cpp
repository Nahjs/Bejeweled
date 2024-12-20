#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QCloseEvent>
#include <QDebug>
#include <chrono>
#include <thread>
#include <string>

#include "mainwindow.h"

#include <QMessageBox>
#include <QThread>
#include "login.h"
#include "ui_mainwindow.h"
#include"setup.h"
#include "Rank.h"
#include <QDrag>
#include <QFile>
#include <QMimeData>
// 主窗口构造函数
Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);

    // 初始化游戏数据结构
    initArrays();  // 初始化选中状态和消除动画状态数组
    numMatrix = new NumMatrix();  // 创建游戏核心逻辑对象

    // 初始化定时器
    timer = new QTimer(this);

    // 信号槽连接
    connect(parent, SIGNAL(startToGame()), this, SLOT(doStartToGame()));  // 开始游戏信号
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timebar()));  // 定时器更新进度条
    connect(this,SIGNAL(gameToMenu()),this,SLOT(on_pushButton_stop_clicked())); // 进入菜单时暂停游戏
    connect(ui->pushButton_hint,SIGNAL(clicked()),this,SLOT(do_btn_hint())); // 提示按钮

    // 初始化游戏状态变量
    focus = 0;  // 选中状态标记

    // 计算游戏界面布局参数
    cellSize = 450/NumMatrix::MAPCOLNUM;  // 单个宝石大小
    offsetX = 60;  // 游戏区域X偏移
    offsetY = 100; // 游戏区域Y偏移
    scoreOffsetX = 75;  // 分数显示X偏移
    scoreOffsetY = 40;  // 分数显示Y偏移
    scoreStep = 1;  // 分数动画步长
    t = 40;  // 动画时间间隔(毫秒)

    // 初始化提示点坐标
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            numMatrix->point[i][j]=-1;
        }
    }
    int i;
    QString path;
    for(i=0;i<8;i++)
    {
        path = ":/res/images/a"  + QString::number(i+1,10) + ".png";//宝石图片
        if (!pixmap_gem[i].load(path)) {
            qDebug() << "Failed to load gem image for index:" << i; // Log an error if the image fails to load
        }
        pixmap_gem[i].load(path);
    }
    for(i=0;i<10;i++)
    {
        path = ":/res/images/number" + QString::number(i,10) + ".png";//得分数图片
        number[i].load(path);
    }
    pixmap_di.load(":/res/images/select.png");//被选中显示
    disappear1.load(":/res/images/tx1.png");
    disappear2.load(":/res/images/tx2.png");
    disappear3.load(":/res/images/tx3.png");//三消的动画过程

    //道具按钮
   /* this->ui->pushButton_boom->setCheckable(true);
    this->ui->pushButton_col->setCheckable(true);
    this->ui->pushButton_row->setCheckable(true);
    this->ui->pushButton_color->setCheckable(true);
*/
    ui->pushButton_boom->setEnabled(g_props_boom > 0);
    ui->pushButton_col->setEnabled(g_props_col > 0);
    ui->pushButton_row->setEnabled(g_props_row > 0);
    ui->pushButton_color->setEnabled(g_props_color > 0);

    image_stop = new QImage(":/res/images/stop.png"); //游戏暂停的图片
    image_gameover = new QImage(":/res/images/gameover.png"); //游戏结束的图片

    //音乐按钮图片
    QIcon icoOn(":/res/images/musicOn.png");
    QIcon icoOff(":/res/images/musicOff.png");
    ui->pushButton->setIcon(icoOn);
    ui->pushButton_2->setIcon(icoOff);
    ui->pushButton->setIconSize(QSize(50,50));
    ui->pushButton->setFlat(true);
    ui->pushButton_2->setIconSize(QSize(50,50));
    ui->pushButton_2->setFlat(true);


    /*由开始界面发送信号给该游戏界面启动游戏，要不就加入下面这行代码，在main.cpp中直接创建game的实例进入游戏
    Game_start();
*/
    rankInstance = Rank::getInstance();

    // 设置接受拖放
    setAcceptDrops(true);
    
    // 为道具按钮启用拖放
    ui->pushButton_boom->setMouseTracking(true);
    ui->pushButton_row->setMouseTracking(true);
    ui->pushButton_col->setMouseTracking(true);
    ui->pushButton_color->setMouseTracking(true);

    setupAudioConnections();
    
    // 开始播放背景音乐
    if (Setup::backgroundMusic) {
        Setup::backgroundMusic->play();
    }
    
    initSoundEffects();//初始化音效
}

Mainwindow::~Mainwindow()
{
    cleanupArrays();
     delete numMatrix;  // 确保删除 numMatrix
    delete ui;
    delete effectAudioOutput;
    delete greatSound;
    delete excellentSound;
    delete amazingSound;
    delete unbelievableSound;
}

// 主窗口的实现文件，包含游戏的核心逻辑和界面交互
void Mainwindow::paintEvent(QPaintEvent *event) {
    // 重写绘制事件，负责绘制游戏界面的所有元素
    QPainter painter(this);
    int num;

    // 设置固定的游戏区域偏移量
    offsetX = 60;  // 左边距
    offsetY = 100; // 上边距

    // 遍历地图绘制所有宝石
    for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
        for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
            num = numMatrix->m_aMap[i][j];
            
            // 绘制基本宝石图像
            painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                             cellSize, cellSize, pixmap_gem[num - 1]);

            // 绘制选中状态的特效
            if (isSelected[i][j] == 1) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                                 cellSize, cellSize, pixmap_di);
                isSelected[i][j] = 0;
            }

            // 绘制提示框
            if (i == numMatrix->point[0][0] && j == numMatrix->point[0][1]) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                                 cellSize, cellSize, pixmap_di);
                numMatrix->point[0][0] = numMatrix->point[0][1] = -1;
            }
            if (i == numMatrix->point[1][0] && j == numMatrix->point[1][1]) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                                 cellSize, cellSize, pixmap_di);
                numMatrix->point[1][0] = numMatrix->point[1][1] = -1;
            }

            // 绘制消除动画效果（三个阶段）
            if (midSituation[i][j] == 1) {
                // 第一阶段动画
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                                 cellSize, cellSize, disappear1);
            } else if (midSituation[i][j] == 2) {
                // 第二阶段动画
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                                 cellSize, cellSize, disappear2);
            } else if (midSituation[i][j] == 3) {
                // 第三阶段动画及分数显示
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize,
                                 cellSize, cellSize, disappear3);

                // 加分动画
                if (addScoreSituation >= 0 && addScoreSituation <= 9) {
                    int x = scoreOffsetX + j * cellSize + (addScoreSituation + 1) * scoreStep;
                    int y = scoreOffsetY + i * cellSize - (addScoreSituation + 1) * scoreStep;
                    painter.drawPixmap(x, y, 10, 20, number[1]);
                    painter.drawPixmap(x + 20, y, 10, 20, number[0]);
                }

                midSituation[i][j] = 0;
            }
        }
    }

    // 绘制计分板
    for (int i = 0; i < string_grade.length(); i++) {
        painter.drawPixmap(600 + i * 25, 30, 25, 50, number[string_grade[i] - '0']);
    }

    // 播放消除音效
    if (eli_music == 1) {
        // mus1->Music_eliminate();
        eli_music = 0;
    }
}

void Mainwindow::closeEvent(QCloseEvent *event)
{
    // 只在游戏进行中时显示提示
    if (ui->progressBar_time->value() > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认退出",
            "现在退出游戏将不会保存任何记录和获得的道具，确定要退出吗？",
            QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) {
            emit gameToStart();
            Game_over(false);
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        emit gameToStart();
        Game_over(false);
        event->accept();
    }
}

//鼠标点击事件
void Mainwindow::mousePressEvent(QMouseEvent *event) {
    int eli_number = 0;  // 累计消除的宝石数量
    mouseflag = 1;

    // 计算点击位置
    int xx = event->position().x() - offsetX;
    int yy = event->position().y() - offsetY;

    focus_y = xx / cellSize;
    focus_x = yy / cellSize;

    // 检查边界
    if(focus_x < 0 || focus_x >= NumMatrix::MAPROWNUM ||
       focus_y < 0 || focus_y >= NumMatrix::MAPCOLNUM) {
        return;
    }

    // 处理第一次点击
    if(focus == 0) {
        point.setX(focus_x);
        point.setY(focus_y);
        isSelected[focus_x][focus_y] = 1;
        focus = 1;
        this->repaint();
        return;
    }

    // 处理道具使用
    if(props) {
        if(boom) {
            this->ui->pushButton_boom->setChecked(false);
            numMatrix->propsEliminate(1, focus_x, focus_y);
            ui->label_boom->setText(QString::number(g_props_boom));
            props = false;
            boom = false;
        }
        else if(row) {
            this->ui->pushButton_row->setChecked(false);
            numMatrix->propsEliminate(2,focus_x,focus_y);
            ui->label_row->setText(QString::number(g_props_row));
            props=false;
            row=false;
        }
        else if(col) {
            this->ui->pushButton_col->setChecked(false);
            numMatrix->propsEliminate(3,focus_x,focus_y);
            ui->label_col->setText(QString::number(g_props_col));
            props=false;
            col=false;
        }
        else if(color) {
            this->ui->pushButton_color->setChecked(false);
            numMatrix->propsEliminate(4,focus_x,focus_y);
            ui->label_color->setText(QString::number(g_props_color));
            props=false;
            color=false;
        }

        // 处理消除效果
        do {
            eliminateNumber = 0;
            for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
                for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
                    if (numMatrix->m_aMap[i][j] == 0) {
                        eliminateNumber++; // 这个是0的个数 消除数
                        midSituation[i][j] = 1; // 状态1
                    }
                }
            }
            eli_number += eliminateNumber;
            Rank::g_rank.nGrade += eliminateNumber * 5; // 使用道具后，每消除一个，分数+5
            string_grade = std::to_string(Rank::g_rank.nGrade);

            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
                for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
                    if (numMatrix->m_aMap[i][j] == 0) {
                        midSituation[i][j] = 2; // 状态2
                    }
                }
            }
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
                for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
                    if (numMatrix->m_aMap[i][j] == 0) {
                        midSituation[i][j] = 3; // 状态3
                    }
                }
            }
            ui->label_boom->setText(QString::number(g_props_boom));
            ui->label_row->setText(QString::number(g_props_row));
            ui->label_col->setText(QString::number(g_props_col));
            ui->label_color->setText(QString::number(g_props_color));
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            while (numMatrix->down()) {
                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));
            }
        } while (numMatrix->eliminate());
    }
    // 处理普通点击
    else {
        int x = point.x();
        int y = point.y();
        isSelected[focus_x][focus_y] = 1;
        this->repaint();

        // 处理相邻交换
        if ((focus_x == x && (focus_y == y - 1 || focus_y == y + 1)) ||
            (focus_y == y && (focus_x == x - 1 || focus_x == x + 1))) {

            // 交换动画
            point1.setX(focus_x);
            point1.setY(focus_y);
            focus = 0;

            // 执行交换
            int temp = numMatrix->m_aMap[x][y];
            numMatrix->m_aMap[x][y] = numMatrix->m_aMap[focus_x][focus_y];
            numMatrix->m_aMap[focus_x][focus_y] = temp;

            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(t));

            // 首先检查是否可以消除
            bool canEliminate = numMatrix->eliminate(true);

            if (!canEliminate) {
                // 不能消除，换回来
                temp = numMatrix->m_aMap[x][y];
                numMatrix->m_aMap[x][y] = numMatrix->m_aMap[focus_x][focus_y];
                numMatrix->m_aMap[focus_x][focus_y] = temp;
                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));
                return;
            }

            // 可以消除，执行实际消除操作
            while (true) {
                if (!numMatrix->eliminate(false)) {
                    break;
                }

                eliminateNumber = 0;
                // 第一阶段动画
                for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
                    for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
                        if (numMatrix->m_aMap[i][j] == 0) {
                            eliminateNumber++;
                            midSituation[i][j] = 1;
                        }
                    }
                }
                eli_number += eliminateNumber;
                // 添加分数：普通消除每个宝石10分
                Rank::g_rank.nGrade += eliminateNumber * 10;
                string_grade = std::to_string(Rank::g_rank.nGrade);

                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));

                // 第二阶段动画
                for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
                    for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
                        if (numMatrix->m_aMap[i][j] == 0) {
                            midSituation[i][j] = 2;
                        }
                    }
                }
                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));

                // 第三阶段动画
                for (int i = 0; i < NumMatrix::MAPROWNUM; i++) {
                    for (int j = 0; j < NumMatrix::MAPCOLNUM; j++) {
                        if (numMatrix->m_aMap[i][j] == 0) {
                            midSituation[i][j] = 3;
                        }
                    }
                }
                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));

                // 更新道具显示
                ui->label_boom->setText(QString::number(g_props_boom));
                ui->label_row->setText(QString::number(g_props_row));
                ui->label_col->setText(QString::number(g_props_col));
                ui->label_color->setText(QString::number(g_props_color));

                // 更新按钮状态
                ui->pushButton_boom->setEnabled(g_props_boom > 0);
                ui->pushButton_col->setEnabled(g_props_col > 0);
                ui->pushButton_row->setEnabled(g_props_row > 0);
                ui->pushButton_color->setEnabled(g_props_color > 0);

                // 如果有激活的道具但数量为0，取消激活状态
                if(props) {
                    if(boom && g_props_boom <= 0) {
                        props = false;
                        boom = false;
                        ui->pushButton_boom->setChecked(false);
                    }
                    if(row && g_props_row <= 0) {
                        props = false;
                        row = false;
                        ui->pushButton_row->setChecked(false);
                    }
                    if(col && g_props_col <= 0) {
                        props = false;
                        col = false;
                        ui->pushButton_col->setChecked(false);
                    }
                    if(color && g_props_color <= 0) {
                        props = false;
                        color = false;
                        ui->pushButton_color->setChecked(false);
                    }
                }

                // 下落动画
                while (numMatrix->down()) {
                    this->repaint();
                    std::this_thread::sleep_for(std::chrono::milliseconds(t));
                }
            }

            hintUsedThisRound = false;
        } else {
            point.setX(focus_x);
            point.setY(focus_y);
            focus = 1; // 修改：重置选中状态
        }
    }

    // 确保音效和奖励分数逻辑正确执行
    if(eli_number >= 5) {
        eli_music = 1;  // 触发音效

        // 连消奖励
        if(eli_number == 5) {
            //Rank::g_rank.nGrade += 50;  // 五连奖励
            playSoundEffect(greatSound);
        } else if(eli_number > 5 && eli_number <= 8) {
           // Rank::g_rank.nGrade += 100;  // 六七八连奖励
            playSoundEffect(excellentSound);
        } else if(eli_number > 8 && eli_number <= 11) {
           // Rank::g_rank.nGrade += 200;  // 九十十一连奖励
            playSoundEffect(amazingSound);
        } else if(eli_number > 11) {
           // Rank::g_rank.nGrade += 500;  // 十一连以上特别奖励
            playSoundEffect(unbelievableSound);
            // 更新时间奖励
            int time = ui->progressBar_time->value() + 5;
            if(time > 60) time = 60;
            ui->progressBar_time->setValue(time);
        }

        // 更新分数显示
        string_grade = std::to_string(Rank::g_rank.nGrade);
        this->repaint();
    }

    // 处理等级提升
    if(Rank::g_rank.nGrade / 1000 != g_spc - 5) {
        if(g_spc) {
            g_spc++;
            numMatrix->BuildMap(g_spc);
            ui->progressBar_time->setValue(60);
            this->repaint();
        }
    }

    // 处理无解情况
    if(!numMatrix->hint()) {
        numMatrix->BuildMap(g_spc);
        this->repaint();
    } else {
        numMatrix->point[0][0] = -1;
        numMatrix->point[0][1] = -1;
        numMatrix->point[1][0] = -1;
        numMatrix->point[1][1] = -1;
    }
}

void Mainwindow::do_btn_hint(){
    if (hintUsedThisRound) {
        QMessageBox::warning(this, "提示", "本回合已经使用过提示功能！");
        return;
    }
    
    hintUsedThisRound = true;
    numMatrix->hint();
    Rank::g_rank.nGrade -= 30;
    string_grade = std::to_string(Rank::g_rank.nGrade);
    this->repaint();
}

void Mainwindow::on_btn_gameToStart_clicked()
{
    // 只在游戏进行中时显示提示
    if (ui->progressBar_time->value() > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认返回",
            "返回主界面将不会保存任何记录和获得的道具，确定要返回吗？",
            QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) {
            this->hide();
            Game_over(false);
            emit gameToStart();
        }
    } else {
        this->hide();
        Game_over(false);
        emit gameToStart();
    }
}

void Mainwindow::doStartToGame()
{
    this->show();
  //  this->setDisabled(false);
    this->Game_start();
}

void Mainwindow::on_btn_gameToMenu_clicked()
{
    // 只在游戏进行中时显示提示
    if (ui->progressBar_time->value() > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认返回菜单",
            "返回菜单将不会保存当前游戏进度，确定要返回吗？",
            QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) {
            emit gameToMenu();
        }
    } else {
        emit gameToMenu();
    }
}

void Mainwindow::doMenuToGame(){
    this->show();
}

void Mainwindow::Music(){
   // QMediaPlayer *music = new QMediaPlayer();
    //music=new QMediaPlayer;
   // connect(music,SIGNAL(positionChanged(qint64)),this,SLOT(postitionChanged(qint64)));
   // music->setMedia(QUrl::fromLocalFile("bgm.mp3"));
    //music->setVolume(20);
  //  music->play();
}

void Mainwindow::do_theme_background_change(QString path){
    // 保留为空实现，以后可以扩展
}

/*
void CGameDlg::do_music_background_change(QString path)
{
    mus->Music_switch(path);
}
*/

void Mainwindow::update_timebar(){
    int CurrentValue=ui->progressBar_time->value();
    CurrentValue--;
    if(CurrentValue>(totaltime/2)&&CurrentValue<=totaltime){
        ui->progressBar_time->setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0) }");
        ui->progressBar_time->setAlignment(Qt::AlignCenter);
    }
    if(CurrentValue>(totaltime/6)&&CurrentValue<=(totaltime/2)){
        ui->progressBar_time->setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 255, 0) }");
        ui->progressBar_time->setAlignment(Qt::AlignCenter);
    }
    if(CurrentValue<=(totaltime/6)){
        ui->progressBar_time->setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 0, 0) }");
        ui->progressBar_time->setAlignment(Qt::AlignCenter);
    }
  /*  if(CurrentValue>4)
      //  mus->Music_last_4sOFF();
   // if(CurrentValue==4)
        //mus->Music_last_4sON();*/
    if (CurrentValue<=0){
        Game_over(true);
    }
    ui->progressBar_time->setValue(CurrentValue);
}

//游戏开始
void Mainwindow::Game_start(){

     // 重置数组状态
    for(int i = 0; i < NumMatrix::MAX_MAP_SIZE; i++) {
        for(int j = 0; j < NumMatrix::MAX_MAP_SIZE; j++) {
            isSelected[i][j] = 0;
            midSituation[i][j] = 0;
        }
    }

    // 重新计算单元格大小
    cellSize = 450/NumMatrix::MAPCOLNUM;

    // 初始化游戏区域大小
    int screenWidth = 450;  // 游戏区域固定宽度
    cellSize = screenWidth / NumMatrix::MAPCOLNUM;  // 根据列数计算单元格大小

    // 保证最小单元格大小
    if(cellSize < 30) {  // 设置最小单元格大小
        cellSize = 30;
    }

    // 根据单元格大小调整偏移量
    offsetX = 60;
    offsetY = 100;

    timer->start(1000); //每一秒更新一次timerbar

    numMatrix->setgamerunning(true); //初始设置游戏处于运行状态
    g_spc=5;
    
    // 从数据库加载用户道具数量
    if(!Login::isGuest) {
        QSqlQuery query;
        query.prepare("SELECT coins, props_boom, props_row, props_col, props_color FROM user WHERE username = ?");
        query.addBindValue(Login::currentUsername);
        
        if(query.exec() && query.next()) {
            g_coins = query.value(0).toInt();
            g_props_boom = query.value(1).toInt();
            g_props_row = query.value(2).toInt();
            g_props_col = query.value(3).toInt();
            g_props_color = query.value(4).toInt();
        }
    } else {
        // 游客模式使用默认值
        g_coins = 100;
        g_props_boom = 2;
        g_props_color = 2;
        g_props_row = 2;
        g_props_col = 2;
    }

    // 更新UI显示
    updatePropsUI();
    
    numMatrix->BuildMap(g_spc);  //初始化游戏地图
    Rank::g_rank.nGrade = 0;  // 修改这里
    string_grade="";
    this->repaint();

    ui->progressBar_time->setMaximum(totaltime);
    ui->progressBar_time->setValue(totaltime);

    ui->pushButton_continue->hide(); //初始时"继续游戏"按钮不可见
    ui->pushButton_restart->hide();  //初始时"重新开始"按钮不可见
    ui->pushButton_stop->show(); //初始时"暂停游戏"按钮可见
    ui->pushButton_continue->setEnabled(false); //初始时"继续游戏"按钮不可用
    ui->pushButton_restart->setEnabled(false); //初始时"重新开始"按钮不可用
    ui->pushButton_stop->setEnabled(true); //初始时"暂停游戏"按钮可用
    label_image->hide(); //初始时暂停游戏以及结束的图片都隐藏

    props=false;
    boom=false;
    color=false;
    row=false;
    col=false;
    hintUsedThisRound = false; // 游戏开始时重置提示按钮使用状态

    // 连接道具变化信号
    connect(numMatrix, &NumMatrix::propsChanged, this, &Mainwindow::updatePropsUI);
    
    // 确保游戏开始时背景音乐播放
    if (Setup::backgroundMusic) {
        qDebug() << "Starting background music in game...";
        if (Setup::backgroundMusic->playbackState() != QMediaPlayer::PlayingState) {
            Setup::backgroundMusic->play();
            qDebug() << "Background music playback state:" << Setup::backgroundMusic->playbackState();
        }
    }
    
    // 初始化并开始播放背景音乐
    initAudioSettings();
    if (Setup::backgroundMusic) {
        Setup::backgroundMusic->play();
        qDebug() << "Background music started in Game_start()";
    }
}

//时间耗尽，游戏结束
void Mainwindow::Game_over(bool saveRank) {
    timer->stop();
    label_image->setGeometry(offsetX,offsetY,500,500);
    label_image->setPixmap(QPixmap::fromImage(*image_gameover));
    label_image->show();
    label_image->setPixmap(QPixmap::fromImage(*image_gameover));
    numMatrix->setgamerunning(false);
    
    if(ui->progressBar_time->value()==0&&!Login::isGuest) {
        // 计算获得的金币数（每100分1个金币）
        int coinsEarned = Rank::g_rank.nGrade / 100;
        if(coinsEarned > 0) {
            g_coins += coinsEarned;
            
            // 更新显示并保存数据
            updatePropsUI();

            // 显示获得金币的消息
            QMessageBox::information(this, "游戏结束",
                QString("游戏结束!\n你的分数: %1\n奖励金币: %2\n当前金币: %3")
                .arg(Rank::g_rank.nGrade)
                .arg(coinsEarned)
                .arg(g_coins));
        }

        // 保存分数到排行榜
        if(Rank::g_rank.nGrade > 0) {
            QSqlQuery query;
            query.prepare("INSERT INTO leaderboard (username, score) VALUES (?, ?)");
            query.addBindValue(Login::currentUsername);
            query.addBindValue(Rank::g_rank.nGrade);
            query.exec();
        }
    }
    
    ui->pushButton_stop->hide();
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_continue->hide();
    ui->pushButton_continue->setEnabled(false);
    ui->pushButton_restart->show();
    ui->pushButton_restart->setEnabled(true);
}

void Mainwindow::on_pushButton_stop_clicked()
{
    timer->stop();
    label_image->setGeometry(offsetX,offsetY-60,450,570);
    label_image->setPixmap(QPixmap::fromImage(*image_stop));
    label_image->show();
    numMatrix->setgamerunning(false);
    ui->pushButton_stop->hide();
    ui->pushButton_continue->show();
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_continue->setEnabled(true);
    //mus->gameSound->setVolume(0);
    
    // 暂停时可以选择暂停音乐
    if (Setup::backgroundMusic) {
        Setup::backgroundMusic->pause();
        qDebug() << "Background music paused";
    }
}

void Mainwindow::on_pushButton_continue_clicked()
{
    timer->start();
    label_image->hide();
    numMatrix->setgamerunning(true);
    ui->pushButton_stop->show();
    ui->pushButton_continue->hide();
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_continue->setEnabled(false);
    //mus->gameSound->setVolume(10);
    
    // 继续游戏时恢复音乐
    if (Setup::backgroundMusic) {
        Setup::backgroundMusic->play();
        qDebug() << "Background music resumed";
    }
}

void Mainwindow::on_pushButton_restart_clicked()
{
    timer->start();
    label_image->hide();
    ui->progressBar_time->setMaximum(totaltime);
    ui->progressBar_time->setValue(totaltime);
    ui->progressBar_time->setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0) }");
    ui->progressBar_time->setAlignment(Qt::AlignCenter);

    // 重新生成地图
    g_spc = 5;
    
    // 从数据库加载道具数量
    if(!Login::isGuest) {
        QSqlQuery query;
        query.prepare("SELECT props_boom, props_row, props_col, props_color FROM user WHERE username = ?");
        query.addBindValue(Login::currentUsername);
        
        if(query.exec() && query.next()) {
            g_props_boom = query.value(0).toInt();
            g_props_row = query.value(1).toInt();
            g_props_col = query.value(2).toInt();
            g_props_color = query.value(3).toInt();
        }
    } else {
        // 游客模式使用默认值
        g_props_boom = 2;
        g_props_row = 2;
        g_props_col = 2;
        g_props_color = 2;
    }

    numMatrix->BuildMap(g_spc);
    numMatrix->setgamerunning(true);
    Rank::g_rank.nGrade = 0;
    string_grade = "";
    this->repaint();

    ui->pushButton_restart->hide();
    ui->pushButton_restart->setEnabled(false);
    ui->pushButton_stop->show();
    ui->pushButton_stop->setEnabled(true);

    props = false;
    boom = false;
    color = false;
    row = false;
    col = false;
    updatePropsUI();
}

//音乐开
void Mainwindow::on_pushButton_clicked()
{
    if (Setup::audioOutput) {
        Setup::volume = 1.0f;
        Setup::audioOutput->setVolume(Setup::volume);
        Setup::audioOutput->setMuted(false);
        Setup::isMuted = false;
        qDebug() << "Music unmuted - Volume:" << Setup::audioOutput->volume();
    }
}

//音乐关
void Mainwindow::on_pushButton_2_clicked()
{
    if (Setup::audioOutput) {
        Setup::audioOutput->setMuted(true);
        Setup::isMuted = true;
        qDebug() << "Music muted";
    }
}



/*
道具
*/

//消除地图中竖直上的宝石
void Mainwindow::on_pushButton_row_clicked()
{
    if(g_props_row == 0 || (props && !row))
    {
        this->ui->pushButton_row->setChecked(false);
        return;
    }
    if(row == true){
        props = false;
        row = false;
        this->ui->pushButton_row->setChecked(false);
    }
    else if(!props && !row){
        props=true;
        row=true;
    }
}

//消除地图中水平上的宝石
void Mainwindow::on_pushButton_col_clicked()
{
    if(g_props_col == 0 || (props && !col))
    {
        this->ui->pushButton_col->setChecked(false);
        return;
    }
    if(col == true){
        props = false;
        col = false;
        this->ui->pushButton_col->setChecked(false);
    }
    else if(!props && !col){
        props=true;
        col=true;
    }
}

//消除地图中相同颜色的宝石
void Mainwindow::on_pushButton_color_clicked()
{
    if(g_props_color == 0 || (props && !color))
    {
        this->ui->pushButton_color->setChecked(false);
        return;
    }
    if(color){
        props = false;
        color = false;
        this->ui->pushButton_color->setChecked(false);
    }
    else if(!props && !color){
        props=true;
        color=true;
        this->ui->pushButton_color->setChecked(true);
    }
}

//产生爆炸，消除3*3范围的宝石
void Mainwindow::on_pushButton_boom_clicked()
{
    if(g_props_boom == 0 || (props && !boom))
    {
        this->ui->pushButton_boom->setChecked(false);
        return;
    }
    if(boom == true){
        props = false;
        boom = false;
        this->ui->pushButton_boom->setChecked(false);
    }
    else if(!props && !boom){
        props=true;
        boom=true;
        this->ui->pushButton_boom->setChecked(true);
    }
}

/*void Mainwindow::closeFromRank()
{
    // 只在游戏进行中时显示提示
    if (ui->progressBar_time->value() > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认返回",
            "返回将不会保存任何记录和获得的道具，确定要返回吗？",
            QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) {
            this->hide();
            Game_over(false);
            emit gameToStart();
        }
    } else {
        this->hide();
        Game_over(false);
        emit gameToStart();
    }
}
*/

void Mainwindow::initArrays() {
    // 分配动态数组空间
    isSelected = new int*[NumMatrix::MAX_MAP_SIZE];
    midSituation = new int*[NumMatrix::MAX_MAP_SIZE];

    // 先分配所有行
    for(int i = 0; i < NumMatrix::MAX_MAP_SIZE; i++) {
        isSelected[i] = new int[NumMatrix::MAX_MAP_SIZE]();  // 使用()初始化为0
        midSituation[i] = new int[NumMatrix::MAX_MAP_SIZE]();
    }
}

void Mainwindow::cleanupArrays() {
    // 释放动态数组
    if(isSelected) {
        for(int i = 0; i < NumMatrix::MAX_MAP_SIZE; i++) {
            delete[] isSelected[i];
        }
        delete[] isSelected;
    }

    if(midSituation) {
        for(int i = 0; i < NumMatrix::MAX_MAP_SIZE; i++) {
            delete[] midSituation[i];
        }
        delete[] midSituation;
    }

}

void Mainwindow::updatePropsUI() {
    // 更新UI显示
    ui->label_boom->setText(QString::number(g_props_boom));
    ui->label_row->setText(QString::number(g_props_row));
    ui->label_col->setText(QString::number(g_props_col));
    ui->label_color->setText(QString::number(g_props_color));

    // 更新按钮状态
    ui->pushButton_boom->setEnabled(g_props_boom > 0);
    ui->pushButton_col->setEnabled(g_props_col > 0);
    ui->pushButton_row->setEnabled(g_props_row > 0);
    ui->pushButton_color->setEnabled(g_props_color > 0);
    
    // 更新数据库，字段顺序要与表结构一致
    if(ui->progressBar_time->value()==0&&!Login::isGuest && Login::currentUsername.length() > 0) {
        QSqlQuery query;
        query.prepare("UPDATE user SET highest_score = GREATEST(highest_score, ?) "
                     "coins = ?,"
                     "props_boom = ?, "
                     "props_row = ?, "
                     "props_col = ?, "
                     "props_color = ? "
                     "WHERE username = ?");

        query.addBindValue(Rank::g_rank.nGrade);    // highest_score
        query.addBindValue(g_coins);                // coins
        query.addBindValue(g_props_boom);           // props_boom
        query.addBindValue(g_props_row);            // props_row
        query.addBindValue(g_props_col);            // props_col
        query.addBindValue(g_props_color);          // props_color
        query.addBindValue(Login::currentUsername); // username

        if(!query.exec()) {
            qDebug() << "Failed to update user data:" << query.lastError().text()
                     << "\nSQL:" << query.lastQuery()
                     << "\nBound values:" 
                     << "\nhighest_score:" << Rank::g_rank.nGrade
                     << "\ncoins:" << g_coins
                     << "\nprops_boom:" << g_props_boom
                     << "\nprops_row:" << g_props_row
                     << "\nprops_col:" << g_props_col
                     << "\nprops_color:" << g_props_color
                     << "\nusername:" << Login::currentUsername;
        }
    }
}

void Mainwindow::updateGemTheme(QString path) {
    for (int i = 0; i < 8; ++i) {
        QString gemPath = path + QString::number(i + 1) + ".png";
        if (!pixmap_gem[i].load(gemPath)) {
            qDebug() << "Failed to load gem image:" << gemPath;
        }
    }
    this->repaint(); // 重新绘制界面
}

void Mainwindow::setupAudioConnections() {
    if (Setup::backgroundMusic) {
        // 监控播放器错误
        connect(Setup::backgroundMusic, &QMediaPlayer::errorOccurred,
                this, [](QMediaPlayer::Error error, const QString &errorString) {
            qDebug() << "Background music error:" << error << errorString;
        });
        
        // 监控播放状态变化
        connect(Setup::backgroundMusic, &QMediaPlayer::playbackStateChanged,
                this, [](QMediaPlayer::PlaybackState state) {
            qDebug() << "Background music state changed to:" << state;
        });
        
        // 监控媒体状态变化
        connect(Setup::backgroundMusic, &QMediaPlayer::mediaStatusChanged,
                this, [](QMediaPlayer::MediaStatus status) {
            qDebug() << "Background music media status:" << status;
        });
    }
}

void Mainwindow::updateBackgroundMusic(float volume) {    if (Setup::audioOutput) {        Setup::audioOutput->setVolume(volume);    }
}

void Mainwindow::updateMuteState(bool muted) {
    if (Setup::audioOutput) {
        Setup::audioOutput->setMuted(muted);
    }
}

void Mainwindow::initSoundEffects() {
    qDebug() << "Initializing sound effects...";
    
    // 创建音效专用的音频输出
    effectAudioOutput = new QAudioOutput(this);
    effectAudioOutput->setVolume(0.5f);
    qDebug() << "Effect audio output volume:" << effectAudioOutput->volume();
    
    // 初始化音效播放器
    greatSound = new QMediaPlayer(this);
    excellentSound = new QMediaPlayer(this);
    amazingSound = new QMediaPlayer(this);
    unbelievableSound = new QMediaPlayer(this);
    
    // 设置音频文件路径
    QUrl greatUrl("qrc:/res/audio/great.mp3");
    QUrl excellentUrl("qrc:/res/audio/excellent.mp3");
    QUrl amazingUrl("qrc:/res/audio/amazing.mp3");
    QUrl unbelievableUrl("qrc:/res/audio/unbelievable.mp3");
    
    // 检查URL是否有效
    qDebug() << "Great sound URL is valid:" << greatUrl.isValid();
    qDebug() << "Excellent sound URL is valid:" << excellentUrl.isValid();
    qDebug() << "Amazing sound URL is valid:" << amazingUrl.isValid();
    qDebug() << "Unbelievable sound URL is valid:" << unbelievableUrl.isValid();
    
    // 设置音频输出和音源
    greatSound->setAudioOutput(new QAudioOutput(this));
    excellentSound->setAudioOutput(new QAudioOutput(this));
    amazingSound->setAudioOutput(new QAudioOutput(this));
    unbelievableSound->setAudioOutput(new QAudioOutput(this));
    
    greatSound->setSource(greatUrl);
    excellentSound->setSource(excellentUrl);
    amazingSound->setSource(amazingUrl);
    unbelievableSound->setSource(unbelievableUrl);
    
    // 添加错误处理
    auto handleError = [](QMediaPlayer *player, const QString &name) {
        connect(player, &QMediaPlayer::errorOccurred,
                [name](QMediaPlayer::Error error, const QString &errorString) {
            qDebug() << name << "error:" << error << errorString;
        });
    };
    
    handleError(greatSound, "Great sound");
    handleError(excellentSound, "Excellent sound");
    handleError(amazingSound, "Amazing sound");
    handleError(unbelievableSound, "Unbelievable sound");
}

void Mainwindow::playSoundEffect(QMediaPlayer* effect) {
    if (!effect) {
        qDebug() << "Sound effect player is null!";
        return;
    }
    
    if (Setup::isMuted) {
        qDebug() << "Sound effects are muted";
        return;
    }
    
    qDebug() << "Playing sound effect...";
    qDebug() << "Current playback state:" << effect->playbackState();
    qDebug() << "Current media status:" << effect->mediaStatus();
    qDebug() << "Current source:" << effect->source().toString();
    
    if (effect->playbackState() == QMediaPlayer::PlayingState) {
        qDebug() << "Resetting sound effect position";
        effect->setPosition(0);
    }
    
    effect->play();
    qDebug() << "Play command sent to sound effect";
    
    // 监控播放状态
    connect(effect, &QMediaPlayer::playbackStateChanged,
            this, [](QMediaPlayer::PlaybackState state) {
        qDebug() << "Sound effect playback state changed to:" << state;
    });
    
    // 监控错误
    connect(effect, &QMediaPlayer::errorOccurred,
            this, [](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "Sound effect error:" << error << errorString;
    });
}

void Mainwindow::initAudioSettings() {
    qDebug() << "\n=== Audio System Reset ===";

    // 强制重新初始化播放器
    if (Setup::backgroundMusic) {
        Setup::backgroundMusic->stop();
        delete Setup::backgroundMusic;
        delete Setup::audioOutput;
    }

    Setup::backgroundMusic = new QMediaPlayer(this);
    Setup::audioOutput = new QAudioOutput(this);
    Setup::backgroundMusic->setAudioOutput(Setup::audioOutput);

    // 资源检查
    QUrl musicUrl("qrc:/res/audio/bgm.mp3");
    qDebug() << "Resource check:"
             << "\nURL:" << musicUrl.toString()
             << "\nValid:" << musicUrl.isValid()
             << "\nFile exists:" << QFile::exists(":/res/audio/bgm.mp3");

    Setup::backgroundMusic->setSource(musicUrl);
    Setup::audioOutput->setVolume(Setup::volume);

    // 媒体状态监控
    connect(Setup::backgroundMusic, &QMediaPlayer::mediaStatusChanged,
            this, [](QMediaPlayer::MediaStatus status) {
        qDebug() << "Media status:" << status;
        if (status == QMediaPlayer::LoadedMedia) {
            Setup::backgroundMusic->play();
        }
    });

    // 错误处理
    connect(Setup::backgroundMusic, &QMediaPlayer::errorOccurred,
            this, [](QMediaPlayer::Error error) {
        qDebug() << "Media error:" << error
                 << "\nDetails:" << Setup::backgroundMusic->errorString();
    });

    // 播放状态监控
    connect(Setup::backgroundMusic, &QMediaPlayer::playbackStateChanged,
            this, [](QMediaPlayer::PlaybackState state) {
        qDebug() << "Playback state:" << state;
        if (state == QMediaPlayer::StoppedState) {
            Setup::backgroundMusic->play();
        }
    });

    Setup::backgroundMusic->play();

    // 滑块初始化
    ui->bgmSlider->setRange(0, 100);
    ui->bgmSlider->setValue(Setup::volume * 100);
    ui->effectSlider->setRange(0, 100);
    ui->effectSlider->setValue(effectAudioOutput->volume() * 100);

    qDebug() << "=== Audio System Initialized ===\n";
}

void Mainwindow::on_bgmSlider_valueChanged(int value) {
    if (Setup::audioOutput) {
        Setup::volume = value / 100.0f;
        Setup::audioOutput->setVolume(Setup::volume);
        qDebug() << "Background music volume changed to:" << Setup::volume;
    }
}

void Mainwindow::on_effectSlider_valueChanged(int value) {
    if (effectAudioOutput) {
        float volume = value / 100.0f;
        effectAudioOutput->setVolume(volume);
        qDebug() << "Sound effect volume changed to:" << volume;
    }
}
