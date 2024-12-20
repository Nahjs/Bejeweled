#include "start.h"
#include "ui_start.h"
#include "setup.h"
#include "rank.h"
#include "propshop.h"

int Start::rows = 12; // 默认行数
int Start::cols = 12; // 默认列数

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
    propShop = new PropShop(this); // 初始化道具商城

    connect(login, &Login::loginSuccess, this, &Start::onLoginSuccess);
    connect(game, &Mainwindow::gameToStart, this, &Start::doGameToStart);
    connect(rank, SIGNAL(rankClosed()), this, SLOT(onRankClosed()));
    connect(this, &Start::sendPath, game, &Mainwindow::updateGemTheme);

    // 初始化时不显示欢迎信息
    ui->label_welcome->setText("");

    login->show();
    this->hide();

    chatRoom = nullptr;  // 初始化聊天室指针为空
}

Start::~Start()
{
    delete ui;
}

void Start::on_btn_startToGame_clicked()
{

    // 设置地图大小
    if (game && game->getNumMatrix()) {
        game->getNumMatrix()->setMapSize(rows, cols);
    }
    
    this->hide();
    game->Game_start(); 
    emit startToGame();
}

void Start::on_btn_propShop_clicked()
{
    if(!Login::isGuest) {
            // 先刷新当前游戏的道具数据到数据库
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE user SET coins = ?, props_boom = ?, props_row = ?, "
                              "props_col = ?, props_color = ? WHERE username = ?");
            updateQuery.addBindValue(g_coins);
            updateQuery.addBindValue(g_props_boom);
            updateQuery.addBindValue(g_props_row);
            updateQuery.addBindValue(g_props_col);
            updateQuery.addBindValue(g_props_color);
            updateQuery.addBindValue(Login::currentUsername);

            if(!updateQuery.exec()) {
                qDebug() << "Failed to update props before opening shop:" << updateQuery.lastError();
            }
        propShop->loadUserCoins(); // 刷新金币数据
        propShop->updateDisplay(); // 更新界面显示
        propShop->show();
    }
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

void Start::on_btn_themeChange_clicked()
{
    Setup *themeChangeDlg = new Setup;
    themeChangeDlg->setAttribute(Qt::WA_DeleteOnClose);
    themeChangeDlg->show();
    connect(themeChangeDlg, &Setup::themeChanged, this, &Start::getPath);
    connect(themeChangeDlg, &Setup::sizeChanged, this, &Start::getSize);
}

void Start::onRankClosed()
{
    this->show();
}

void Start::onLoginSuccess()
{
    // 登录成功后更新欢迎信息
    if(Login::isGuest) {
        ui->label_welcome->setText("欢迎您，游客！祝您游戏愉快！");
    } else {
        ui->label_welcome->setText("欢迎回来，" + Login::currentUsername + "！");
    }

    this->show();
}

void Start::on_btn_chatRoom_clicked()
{
    if (!chatRoom) {
        chatRoom = new ChatRoom();
        connect(chatRoom, &ChatRoom::destroyed, [this]() {
            chatRoom = nullptr;
        });
    }
    chatRoom->show();
    chatRoom->activateWindow();
}

void Start::doGameToStart() {
    this->show();
}

void Start::getPath(QString path) {
    emit sendPath(path);
}

void Start::getSize(int row,int col) {
    // 更新游戏地图的行列数设置
    qDebug() << "接收到用户设置的行列值：" << row << col;
    rows = row;
    cols = col;
}