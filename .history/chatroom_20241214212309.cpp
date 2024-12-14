#include "chatroom.h"
#include "ui_chatroom.h"
#include "login.h"

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

    setWindowTitle("聊天室 - " + Login::currentUsername);
}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::setupChatConnections()
{
    connect(chatClient, &ChatClient::connected, this, &ChatRoom::onChatConnected);
    connect(chatClient, &ChatClient::disconnected, this, &ChatRoom::onChatDisconnected);
    connect(chatClient, &ChatClient::error, this, &ChatRoom::onChatError);
    connect(chatClient, &ChatClient::messageReceived, this, &ChatRoom::handleChatMessage);
    
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatRoom::onSendMessage);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &ChatRoom::onSendMessage);
    
    // 连接到聊天服务器
    chatClient->connectToServer("127.0.0.1", 8888);
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
        QStringList users = message.split('\r', QString::SkipEmptyParts);
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
