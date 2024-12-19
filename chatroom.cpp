#include "chatroom.h"
#include "signup.h"

#include <QCloseEvent>
#include <QLineEdit>
#include <QPushButton>

#include "ui_chatroom.h"


ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    
    // 初始化聊天客户端
    chatClient = new ChatClient(this);
    setupChatConnections();
    
    // 如果是游客模式，禁用聊天功能
    if(Login::isGuest) {
        ui->chatInput->setEnabled(false);
        ui->sendButton->setEnabled(false);
        ui->chatDisplay->append("游客模式不能使用聊天功能，请注册登录后使用。");
    }

    // 如果是游客模式，显示注册按钮，否则隐藏
    ui->registerButton->setVisible(Login::isGuest);

    setWindowTitle("聊天室 - " + Login::currentUsername);
}

ChatRoom::~ChatRoom()
{
    if(chatClient) {
        chatClient->disconnectFromServer();
        delete chatClient;
    }
    delete ui;
}

void ChatRoom::closeEvent(QCloseEvent *event)
{
    if(chatClient && chatClient->isConnected()) {
        chatClient->disconnectFromServer();
    }
    event->accept();
}

void ChatRoom::setupChatConnections()
{
    connect(chatClient, &ChatClient::connected, this, &ChatRoom::onChatConnected);
    connect(chatClient, &ChatClient::disconnected, this, &ChatRoom::onChatDisconnected);
    connect(chatClient, &ChatClient::error, this, &ChatRoom::onChatError);
    connect(chatClient, &ChatClient::messageReceived, this, &ChatRoom::handleChatMessage);
    
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatRoom::onSendMessage);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &ChatRoom::onSendMessage);
    

    //chatClient->connectToServer("127.0.0.1", 8888);
    // 连接到聊天服务器
    chatClient->connectToServer("cn-hk-bgp-4.ofalias.net", 26493);
}

void ChatRoom::onChatConnected()
{
    ui->chatDisplay->append("已连接到聊天服务器");
    if(!Login::isGuest) {
        chatClient->sendMessage("LGIN", Login::currentUsername + "\r" + "password");
    }
}

void ChatRoom::onChatDisconnected()
{
    ui->chatDisplay->append("与聊天服务器断开连接");
}

void ChatRoom::onChatError(const QString& error)
{
    ui->chatDisplay->append("错误: " + error);
}

void ChatRoom::handleChatMessage(const QString& type, const QString& message)
{
    if(type == "MSGA") {
        appendChatMessage(message);
    }
    else if(type == "USER") {
        QStringList users = message.split('\r', Qt::SkipEmptyParts);
        ui->userList->clear();
        ui->userList->addItems(users);
    }
}

void ChatRoom::appendChatMessage(const QString& message)
{
    ui->chatDisplay->append(message);
}

void ChatRoom::onSendMessage()
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

void ChatRoom::on_registerButton_clicked()
{
    Signup *signUp = new Signup();
    connect(signUp, &Signup::registerSuccess, this, &ChatRoom::onRegisterSuccess);
    signUp->show();
}

void ChatRoom::onRegisterSuccess()
{
    // 注册成功后启用聊天功能
    ui->chatInput->setEnabled(true);
    ui->sendButton->setEnabled(true);
    ui->registerButton->hide();
    ui->chatDisplay->append("注册成功！现在您可以参与聊天了。");
    
    // 更新窗口标题
    setWindowTitle("聊天室 - " + Login::currentUsername);
    
    // 连接到聊天服务器
    if(chatClient && chatClient->isConnected()) {
        chatClient->sendMessage("LGIN", Login::currentUsername + "\r" + "password");
    }
}
