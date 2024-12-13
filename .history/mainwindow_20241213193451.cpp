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

#include "Global.h"
#include "ui_mainwindow.h"
#include "Rank.h" // Add this line to include the Rank header file

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(parent, SIGNAL(startToGame()), this, SLOT(doStartToGame()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timebar()));
   // connect(menu,SIGNAL(menuToGame()),this,SLOT(doMenuToGame()));
  //  connect(menu,SIGNAL(game_them_background_change(QString)),this,SLOT(do_theme_background_change(QString)));
  //  connect(menu,SIGNAL(game_themee_gem_change(QString)),this,SLOT(do_theme_gem_change(QString)));
  //  connect(menu,SIGNAL(game_music_background_change(QString)),this,SLOT(do_music_background_change(QString)));
     connect(this,SIGNAL(gameToMenu()),this,SLOT(on_pushButton_stop_clicked())); //当点击“菜单”进入menu界面时，游戏自动暂停
    connect(ui->pushButton_hint,SIGNAL(clicked()),this,SLOT(do_btn_hint()));

    focus=0;
   // gemtype="c";
     cellSize = 450/MAPCOLNUM;
     offsetX = 60;
    offsetY = 100;
     scoreOffsetX = 75;
     scoreOffsetY = 40;
     scoreStep = 1;
    t=40;//动画时间

    for (int i = 0; i < MAPROWNUM; i++) {
        for (int j = 0; j < MAPCOLNUM; j++) {
            isSelected[i][j] = 0; // 初始化为未被选中
            midSituation[i][j] = 0; // 状态为0
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            numMatrix->point[i][j]=-1;
        }
    }
    QString path;
    int i;
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
    disappear3.load(":/res/images/tx3.png");

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
    if(music==1){
       // mus->MusicOn();
    }else{
     //   mus->MusicOff();
    }

    /*由开始界面发送信号给该游戏界面启动游戏，要不就加入下面这行代码，在main.cpp中直接创建game的实例进入游戏
    Game_start();
*/
    rankInstance = Rank::getInstance();
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int num;

    for (int i = 0; i < MAPROWNUM; i++) {
        for (int j = 0; j < MAPCOLNUM; j++) {
            num = numMatrix->m_aMap[i][j];
            painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, pixmap_gem[num - 1]);//绘制宝石
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, pixmap_gem[num - 1]);


            if (isSelected[i][j] == 1) { // 被选中的框
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, pixmap_di);
                isSelected[i][j] = 0;
            }

            if (i == numMatrix->point[0][0] && j == numMatrix->point[0][1]) { // 提示的框
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, pixmap_di);
                numMatrix->point[0][0] = numMatrix->point[0][1] = -1; // 初始化
            }
            if (i == numMatrix->point[1][0] && j == numMatrix->point[1][1]) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, pixmap_di);
                numMatrix->point[1][0] = numMatrix->point[1][1] = -1; // 初始化
            }

            //绘制消失动画
            if (midSituation[i][j] == 1) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, disappear1);
            } else if (midSituation[i][j] == 2) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, disappear2);
            } else if (midSituation[i][j] == 3) {
                painter.drawPixmap(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, disappear3);

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
        painter.drawPixmap(600+i * 25, 30, 25, 50, number[string_grade[i] - '0']);
    }

    // 播放消除音效
    if (eli_music == 1) {
        // mus1->Music_eliminate();
        eli_music = 0;
    }
}

void Mainwindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit gameToStart();
    Game_over(false);
}

//鼠标点击事件
void Mainwindow::mousePressEvent(QMouseEvent *event){
    int eli_number=0;//累计消除的宝石数量
    mouseflag=1;

    QPainter painter(this);

    int xx;
    int yy;
  // xx = event->x() - offsetX;
    xx = event->position().x() - offsetX;
    yy = event->position().y() - offsetY;

    focus_y = xx / cellSize;
    focus_x = yy / cellSize; // 把点击的坐标翻译成了宝石矩阵的行列号，便于下面访问算法

    if(focus_x >= MAPROWNUM || focus_y >= MAPCOLNUM) return;

        // 处理第一次点击
        if(focus==0){
            point.setX(focus_x);
            point.setY(focus_y);//存下了第一次点击的横纵坐标（换算后的，可以直接用来访问矩阵）
            isSelected[focus_x][focus_y]=1;
            focus=1;
            this->repaint();//进行重绘
        }

        //有道具激活
        if(props){
            if(boom){
                this->ui->pushButton_boom->setChecked(false);
                numMatrix->propsEliminate(1,focus_x,focus_y);
                ui->label_boom->setText(QString::number(g_props_boom));
                props=false;
                boom=false;
            }
            else if(row){
                this->ui->pushButton_row->setChecked(false);
                numMatrix->propsEliminate(2,focus_x,focus_y);
                ui->label_row->setText(QString::number(g_props_row));
                props=false;
                row=false;
            }
            else if(col){
                this->ui->pushButton_col->setChecked(false);
                numMatrix->propsEliminate(3,focus_x,focus_y);
                ui->label_col->setText(QString::number(g_props_col));
                props=false;
                col=false;
            }
            else if(color){
                this->ui->pushButton_color->setChecked(false);
                numMatrix->propsEliminate(4,focus_x,focus_y);
                ui->label_color->setText(QString::number(g_props_color));
                props=false;
                color=false;
            }


               do {
               // eli_music = 1;
                eliminateNumber = 0;
                for (int i = 0; i < MAPROWNUM; i++) {
                    for (int j = 0; j < MAPCOLNUM; j++) {
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
                for (int i = 0; i < MAPROWNUM; i++) {
                    for (int j = 0; j < MAPCOLNUM; j++) {
                        if (numMatrix->m_aMap[i][j] == 0) {
                            midSituation[i][j] = 2; // 状态2
                        }
                    }
                }
                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));
                for (int i = 0; i < MAPROWNUM; i++) {
                    for (int j = 0; j < MAPCOLNUM; j++) {
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
        } else {
            int x = point.x();
            int y = point.y(); // 取得第一次点击的横纵坐标与新的坐标相比较
            isSelected[focus_x][focus_y] = 1;
            this->repaint();

            if ((focus_x == x && (focus_y == y - 1 || focus_y == y + 1)) || (focus_y == y && (focus_x == x - 1 || focus_x == x + 1))) { // 相邻情况（上下左右）
                point1.setX(focus_x);
                point1.setY(focus_y); // 把第二次的坐标也存下了，便于后面访问
                focus = 0; // 标志

                int temp;
                temp = numMatrix->m_aMap[x][y];
                numMatrix->m_aMap[x][y] = numMatrix->m_aMap[focus_x][focus_y];
                numMatrix->m_aMap[focus_x][focus_y] = temp;
                this->repaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(t));
                if (!numMatrix->eliminate(true)) { // 点的两个不能交换
                    // 换回来
                    int temp1;
                    temp1 = numMatrix->m_aMap[x][y];
                    numMatrix->m_aMap[x][y] = numMatrix->m_aMap[focus_x][focus_y];
                    numMatrix->m_aMap[focus_x][focus_y] = temp1;
                    this->repaint();
                    std::this_thread::sleep_for(std::chrono::milliseconds(t));
                }
                while (numMatrix->eliminate()) {
                    eli_music = 1;
                    eliminateNumber = 0;
                    for (int i = 0; i < MAPROWNUM; i++) {
                        for (int j = 0; j < MAPCOLNUM; j++) {
                            if (numMatrix->m_aMap[i][j] == 0) {
                                eliminateNumber++; // 这个是0的个数 消除数
                                midSituation[i][j] = 1; // 状态1
                            }
                        }
                    }
                    eli_number += eliminateNumber;
                    Rank::g_rank.nGrade += eliminateNumber * 10; // 分数增加
                    string_grade = std::to_string(Rank::g_rank.nGrade);

                    this->repaint();
                    std::this_thread::sleep_for(std::chrono::milliseconds(t));
                    for (int i = 0; i < MAPROWNUM; i++) {
                        for (int j = 0; j < MAPCOLNUM; j++) {
                            if (numMatrix->m_aMap[i][j] == 0) {
                                midSituation[i][j] = 2; // 状态2
                            }
                        }
                    }
                    this->repaint();
                    std::this_thread::sleep_for(std::chrono::milliseconds(t));
                    for (int i = 0; i < MAPROWNUM; i++) {
                        for (int j = 0; j < MAPCOLNUM; j++) {
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
                    for (int k = 0; k < 10; k++) {
                        addScoreSituation = k;
                        this->repaint();
                        std::this_thread::sleep_for(std::chrono::milliseconds(t));
                    }

                    while (numMatrix->down()) {
                        this->repaint();
                        std::this_thread::sleep_for(std::chrono::milliseconds(t));
                    }
                }
            } else {
                point.setX(focus_x);
                point.setY(focus_y);
            }
        }
        //连消的音效播放
        if(eli_number==5){//五连消
            //mus1->Music_great();
        }
        if(eli_number>5&&eli_number<=7){ //6、7连消
            //mus1->Music_excellent();
        }
        if(eli_number>7&&eli_number<=9){ //8、9连消
            //mus1->Music_amazing();
        }
        if(eli_number>9){//时间奖励，连续消去10个及以上的宝石，时间加5秒
            //mus1->Music_unbelievable();
            int time = ui->progressBar_time->value()+5;//+(int)(eli_number/2);
            if(time > 60)
                time = 60;
            ui->progressBar_time->setValue(time);
        }
        if(Rank::g_rank.nGrade / 1000 != g_spc - 5)//确定等级，每超过1000分宝石种类加1
        {
            //ui->progressBar_time->setValue(60);
            if(g_spc){
                g_spc++;
                numMatrix->BuildMap(g_spc);
                ui->progressBar_time->setValue(60);
                this->repaint();
            }
        }
        if(!numMatrix->hint())//当前整个地图没有可以交换产生三连->重新构图
        {
            numMatrix->BuildMap(g_spc);
            this->repaint();
        }
        else//复原因为调用hint而改变的提示框位置
        {
            numMatrix->point[0][0] = -1;
            numMatrix->point[0][1] = -1;
            numMatrix->point[1][0] = -1;
            numMatrix->point[1][1] = -1;
        }

}



void Mainwindow::do_btn_hint(){
    // 检查是否有足够的分数
    if(Rank::g_rank.nGrade < 30) {
        QMessageBox::warning(this, "提示", "分数不足30分，无法使用提示功能！");
        return;
    }
    
    // 禁用提示按钮，防止连续点击
    ui->pushButton_hint->setEnabled(false);
    
    numMatrix->hint();
    Rank::g_rank.nGrade -= 30;
    string_grade = std::to_string(Rank::g_rank.nGrade);
    this->repaint();
    
    // 2秒后重新启用提示按钮
    QTimer::singleShot(2000, this, [this](){
        ui->pushButton_hint->setEnabled(true);
    });
}

void Mainwindow::on_btn_gameToStart_clicked()
{
    this->hide();
    Game_over(false);      //当点击“返回”进入开始界面时，游戏结束，成绩无效？
    emit gameToStart();
}

void Mainwindow::doStartToGame()
{
    this->show();
  //  this->setDisabled(false);
    this->Game_start();
}

void Mainwindow::on_btn_gameToMenu_clicked()
{
    emit gameToMenu();
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
    this->setStyleSheet("#CGameDlg{border-image:url("+path+");}");
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
    if (CurrentValue<=0){
        Game_over(true);
    }
    ui->progressBar_time->setValue(CurrentValue);
}

//游戏开始
void Mainwindow::Game_start(){
    timer->start(1000); //每一秒更新一次timerbar
   // gemtype="gem"; //默认宝石类型

    numMatrix->setgamerunning(true); //初始设置游戏处于运行状态
    g_spc=5;
    g_props_boom = 1;
    g_props_color = 1;
    g_props_row = 1;
    g_props_col = 1;
    numMatrix->BuildMap(g_spc);  //初始化游戏地图
    Rank::g_rank.nGrade = 0;  // 修改这里
    string_grade="";
    this->repaint();

    ui->progressBar_time->setMaximum(totaltime);
    ui->progressBar_time->setValue(totaltime);
    ui->progressBar_time->setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0) }");
    ui->progressBar_time->setAlignment(Qt::AlignCenter);

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
    ui->label_boom->setText(QString::number(g_props_boom));
    ui->label_color->setText(QString::number(g_props_color));
    ui->label_row->setText(QString::number(g_props_row));
    ui->label_col->setText(QString::number(g_props_col));
}

//时间耗尽，游戏结束
void Mainwindow::Game_over(bool saveRank){
    timer->stop();
    label_image->setGeometry(offsetX,offsetY,500,500);
    label_image->setPixmap(QPixmap::fromImage(*image_gameover));
    label_image->show();
    numMatrix->setgamerunning(false);
    
    // 保存分数到排行榜
    if(saveRank && Rank::g_rank.nGrade > 0) {
        rankInstance->insertIndex(rankInstance->getIndex());
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

}

void Mainwindow::on_pushButton_restart_clicked()
{
    timer->start();
    label_image->hide();
    ui->progressBar_time->setMaximum(totaltime);
    ui->progressBar_time->setValue(totaltime);
    ui->progressBar_time->setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0) }");
    ui->progressBar_time->setAlignment(Qt::AlignCenter);

    //重新生成地图，待完成
    g_spc=5;
    g_props_boom = 1;
    g_props_color = 1;
    g_props_row = 1;
    g_props_col = 1;
    numMatrix->BuildMap(g_spc);
    numMatrix->setgamerunning(true);
    Rank::g_rank.nGrade=0;
    string_grade="";
    this->repaint();

    ui->pushButton_restart->hide();
    ui->pushButton_restart->setEnabled(false);
    ui->pushButton_stop->show();
    ui->pushButton_stop->setEnabled(true);

    props=false;
    boom=false;
    color=false;
    row=false;
    col=false;
    ui->label_boom->setText(QString::number(g_props_boom));
    ui->label_color->setText(QString::number(g_props_color));
    ui->label_row->setText(QString::number(g_props_row));
    ui->label_col->setText(QString::number(g_props_col));

}

//音乐开
void Mainwindow::on_pushButton_clicked()
{
    music = 1;
    //mus->gameSound->setVolume(10);
}

//音乐关
void Mainwindow::on_pushButton_2_clicked()
{
    music = 0;
    //mus->gameSound->setVolume(0);
}



//************* 道具部分 ***************


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
void Mainwindow::closeFromRank()
{
    this->hide();
    Game_over(false);
    emit gameToStart();
}
