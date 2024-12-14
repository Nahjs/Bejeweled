#include "start.h"
#include "ui_start.h"
#include "themechange.h"
#include "rank.h"
#include "themechange.h"
#include "rank.h"
#include "chatclient.h"

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

    connect(login, &Login::loginSuccess, this, &Start::onLoginSuccess);
    connect(game, SIGNAL(gameToStart()), this, SLOT(doGameToStart()));
    connect(rank, SIGNAL(rankClosed()), this, SLOT(onRankClosed()));

    // 初始化聊天客户端
    chatClient = new ChatClient(this);
    setupChatConnections();
    
    // 如果是游客模式，禁用聊天功能
    if(Login::isGuest) {
        ui->chatInput->setEnabled(false);
        ui->sendButton->setEnabled(false);
        ui->chatDisplay->append("游客模式不能使用聊天功能，请注册登录后使用。");
    }

    // 初始化时不显示欢迎信息
    ui->label_welcome->setText("");

    login->show();
    this->hide();
}

Start::~Start()
{
    delete ui;
}

void Start::setupChatConnections()
{
    // 连接聊天客户端信号
    connect(chatClient, &ChatClient::connected, this, &Start::onChatConnected);
    connect(chatClient, &ChatClient::disconnected, this, &Start::onChatDisconnected);
    connect(chatClient, &ChatClient::error, this, &Start::onChatError);
    connect(chatClient, &ChatClient::messageReceived, this, &Start::handleChatMessage);
    
    // 连接发送按钮
    connect(ui->sendButton, &QPushButton::clicked, this, &Start::onSendMessage);
    
    // 连接回车发送
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &Start::onSendMessage);
    
    // 尝试连接到聊天服务器
    chatClient->connectToServer("127.0.0.1", 8888);  // 使用相同的服务器端口
}

void Start::onChatConnected()
{
    ui->chatDisplay->append("已连接到聊天服务器");
    // 发送登录消息
    if(!Login::isGuest) {
        chatClient->sendMessage("LGIN", Login::currentUsername + "\r" + "password");
    }
}

void Start::onChatDisconnected()
{
    ui->chatDisplay->append("与聊天服务器断开连接");
}

void Start::onChatError(const QString& error)
{
    ui->chatDisplay->append("错误: " + error);
}

void Start::handleChatMessage(const QString& type, const QString& message)
{
    if(type == "MSGA") {
        appendChatMessage(message);
    }
    else if(type == "USER") {
        // 更新在线用户列表
        QStringList users = message.split('\r', QString::SkipEmptyParts);
        ui->userList->clear();
        ui->userList->addItems(users);
    }
}

void Start::appendChatMessage(const QString& message)
{
    ui->chatDisplay->append(message);
}

void Start::onSendMessage()
{
    if(Login::isGuest) {
        QMessageBox::warning(this, "提示", "游客模式不能发送消息，请注册登录后使用。");
        return;
    }
    
    QString message = ui->chatInput->text().trimmed();
    if(!message.isEmpty()) {
        chatClient->sendMessage("MSGA", message);
        ui->chatInput->clear();
    }
}

void Start::on_btn_startToGame_clicked()
{
    this->hide();
    emit startToGame();
}