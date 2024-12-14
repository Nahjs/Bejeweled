#include "chatroom.h"
#include "ui_chatroom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    
    chatClient = new ChatClient(this);
    setupChatConnections();

    // 设置窗口标题
    this->setWindowTitle("聊天室");

    // 如果是游客模式，禁用聊天功能
    if(Login::isGuest) {
        ui->chatInput->setEnabled(false);
        ui->sendButton->setEnabled(false);
        ui->chatDisplay->append("游客模式不能使用聊天功能，请注册登录后使用。");
    }
}

ChatRoom::~ChatRoom()
{
    if(chatClient->isConnected()) {
        chatClient->sendMessage("DSCN", "");
        chatClient->disconnectFromServer();
    }
    delete ui;
}

void ChatRoom::show()
{
    if(!chatClient->isConnected()) {
        chatClient->connectToServer("127.0.0.1", 8888);
    }
    QWidget::show();
}

void ChatRoom::setupChatConnections()
{
    connect(chatClient, &ChatClient::connected, this, &ChatRoom::onChatConnected);
    connect(chatClient, &ChatClient::disconnected, this, &ChatRoom::onChatDisconnected);
    connect(chatClient, &ChatClient::error, this, &ChatRoom::onChatError);
    connect(chatClient, &ChatClient::messageReceived, this, &ChatRoom::handleChatMessage);
    
    // 连接UI控件信号
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatRoom::onSendMessage);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &ChatRoom::onSendMessage);
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