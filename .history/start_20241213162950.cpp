#include "start.h"

#include <Login/ui_login.h>

#include "ui_start.h"
#include "themechange.h"
#include "rank.h" 

Start::Start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);
    
    // 创建登录窗口
    login = new Login();
    connect(login, &Login::loginSuccess, this, &Start::onLoginSuccess);
    login->show();
    this->hide();

    game = new Mainwindow(this);
    rank =  Rank::getInstance();
    name = new Name(this);
    help = new Help(this);
    about = new About(this);

    connect(game, SIGNAL(gameToStart()), this, SLOT(doGameToStart()));
    connect(name, SIGNAL(nameConfirm()), this, SLOT(doNameConfirm()));
    ui->label_welcome->setText("请告知你的大名：");

    // 连接排行榜关闭信号
    connect(rank, SIGNAL(rankClosed()), this, SLOT(onRankClosed()));
}

Start::~Start()
{
    delete ui;
}


void Start::on_btn_startToGame_clicked()
{
    this->hide();
    emit startToGame();
}

void Start::doGameToStart()
{
    this->show();
}

void Start::on_btn_mainToRank_clicked()
{
    Rank::getInstance()->showRank();
}

void Start::doNameConfirm()
{
    this->ui->label_welcome->setText(" " + QString::fromStdString(Rank::g_rank.strName)+"，你终于来了 ！");
}

void Start::on_btn_name_clicked()
{
    name->show();
}

void Start::on_btn_help_clicked()
{
    help->show();
}

void Start::on_btn_about_clicked()
{
    about->show();
}

//主题设置
void Start::on_btn_themeChange_clicked()
{
    ThemeChange *themeChangeDlg = new ThemeChange; // 注意这里没有指定父窗口，所以它会创建一个新窗口
    themeChangeDlg->setAttribute(Qt::WA_DeleteOnClose); // 当窗口关闭时，自动删除对象
    themeChangeDlg->show();
}

void Start::onRankClosed()
{
    this->show(); // 显示开始界面
}

void Start::onLoginSuccess()
{
    this->show();
}
