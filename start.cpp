#include "start.h"
#include "ui_start.h"
#include "setup.h"
#include "rank.h"
#include "propshop.h"
#include "levelmanager.h"

int Start::rows = 8; // 默认行数
int Start::cols = 8; // 默认列数

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
    levelManager = new LevelManager(this); // 初始化关卡管理器
    connect(levelManager, &LevelManager::backToStart, this, &Start::show);

    connect(login, &Login::loginSuccess, this, &Start::onLoginSuccess);
    connect(game, &Mainwindow::gameToStart, this, &Start::doGameToStart);
    connect(rank, SIGNAL(rankClosed()), this, SLOT(onRankClosed()));
    connect(this, &Start::sendPath, game, &Mainwindow::updateGemTheme);

    // 初始化时不显示欢迎信息
    ui->label_welcome->setText("");

    login->show();
    this->hide();

    chatRoom = nullptr;  // 初始化聊天室指针为空

    // 初始化ChatClient
    m_client = new ChatClient(this);
    connect(m_client, &ChatClient::connected, this, [this]() {
        qDebug() << "成功连接到服务器";
    });
    connect(m_client, &ChatClient::error, this, [](const QString& error) {
        qDebug() << "连接错误:" << error;
    });
    
    battle = nullptr;  // 初始化为nullptr
}

Start::~Start()
{
    delete ui;
    if (battle) {
        delete battle;
    }
    delete m_client;
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

// 添加关卡按钮点击处理函数
void Start::on_btn_level_clicked()
{
    if(!Login::isGuest) {
        this->hide();
        levelManager->show();
    } else {
        QMessageBox::warning(this, "游客模式限制",
            "游客模式下只能体验第一关\n"
            "请注册账号以解锁所有关卡！");
        // 游客模式也可以进入，但会在levelManager中限制只能玩第一关
        this->hide();
        levelManager->show();
    }
}

void Start::on_btn_battle_clicked()
{
    if (!m_client->isConnected()) {
        // 尝试连接服务器
        //m_client->connectToServer("localhost", 5371);
         m_client->connectToServer("cn-hk-bgp-4.ofalias.net", 49548); // 线上服务器
    }

    if (!battle) {
        battle = new Battle(m_client, this);
        connect(battle, &Battle::battleToStart, this, &Start::show);
    }

    if (Login::isGuest) {
        QMessageBox::warning(this, "游客模式限制",
            "游客模式下无法使用对战功能\n"
            "请注册账号后体验完整功能！");
        return;
    }

    this->hide();
    battle->show();
}