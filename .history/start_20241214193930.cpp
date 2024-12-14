#include "start.h"
#include "ui_start.h"
#include "themechange.h"
#include "rank.h"
#include "themechange.h"
#include "rank.h" 

Start::Start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);
    
    // 创建和初始化所有实例
    game = new Mainwindow(this);
    rank = Rank::getInstance();
    help = new Help(this);
    about = new About(this);
    login = new Login();
    mailForm = new MailForm(this);

    connect(login, &Login::loginSuccess, this, &Start::onLoginSuccess);
    connect(game, SIGNAL(gameToStart()), this, SLOT(doGameToStart()));
    connect(rank, SIGNAL(rankClosed()), this, SLOT(onRankClosed()));
    
    // 初始化时不显示欢迎信息
    ui->label_welcome->setText("");

    login->show();
    this->hide();
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
    // 根据是否是游客显示不同的欢迎信息
    if(Login::isGuest) {
        ui->label_welcome->setText("欢迎您，游客！祝您游戏愉快！");
    } else {
        ui->label_welcome->setText("欢迎回来，" + Login::currentUsername + "！");
    }
    
    this->show();
}

void Start::on_btn_sendMail_clicked()
{
    mailForm->show();
}
