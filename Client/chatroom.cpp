#include "chatroom.h"
#include "signup.h"
#include "ui_chatroom.h"

#include <QCloseEvent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom),
    client(new Client(this))
{
    ui->setupUi(this);

    setupChatConnections();

    if(Login::isGuest) {
        ui->chatInput->setEnabled(false);
        ui->sendButton->setEnabled(false);
        ui->chatDisplay->append("游客模式不能使用聊天功能，请注册登录后使用。");
    }

    ui->registerButton->setVisible(Login::isGuest);
    setWindowTitle("聊天室 - " + Login::currentUsername);
}

ChatRoom::~ChatRoom() {
    if(client) {
        client->disconnectFromServer();
        delete client;
    }
    delete ui;
}

void ChatRoom::setClient(Client *client) {
    if (this->client) {
        this->client->disconnectFromServer();
        delete this->client;
    }
    this->client = client;
    setupChatConnections();
}

void ChatRoom::closeEvent(QCloseEvent *event) {
    if(client && client->isConnected()) {
        // 发送离开消息
        QJsonObject leaveMsg;
        leaveMsg["username"] = Login::currentUsername;
        leaveMsg["type"] = "LEAVE";
        QJsonDocument doc(leaveMsg);
        client->sendMessage("LEAVE", doc.toJson(QJsonDocument::Compact));
        
        // 等待消息发送完成
        QTimer::singleShot(100, this, [this]() {
            client->disconnectFromServer();
        });
    }
    event->accept();
}

void ChatRoom::setupChatConnections() {
    connect(client, &Client::connected, this, &ChatRoom::onChatConnected);
    connect(client, &Client::disconnected, this, &ChatRoom::onChatDisconnected);
    connect(client, &Client::error, this, &ChatRoom::onChatError);
    connect(client, &Client::messageReceived, this, &ChatRoom::handleChatMessage);

    connect(ui->sendButton, &QPushButton::clicked, this, &ChatRoom::onSendMessage);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &ChatRoom::onSendMessage);

    qDebug() << "\n=== 设置聊天连接 ===";
    connect(client, &Client::connected, this, [this]() {
        if(!Login::isGuest) {
            QJsonObject loginData;
            loginData["username"] = Login::currentUsername;
            loginData["password"] = "password"; // 实际应用中应该使用真实密码
            QJsonDocument doc(loginData);
            client->sendMessage("LOGIN", doc.toJson(QJsonDocument::Compact));
        }
    });
    
    qDebug() << "正在连接到聊天服务器...";
    client->connectToServer("127.0.0.1", 5371);
    qDebug() << "===================\n";
}

void ChatRoom::onChatConnected() {
    if(!Login::isGuest) {
        QJsonObject loginData;
        loginData["username"] = Login::currentUsername;
        loginData["password"] = "password";
        QJsonDocument doc(loginData);
        QString loginMessage = doc.toJson(QJsonDocument::Compact);
        qDebug() << "发送登录请求:" << loginMessage;
        client->sendMessage("LOGIN", loginMessage);
    }
}

void ChatRoom::onChatDisconnected() {
    ui->userList->clear();
    ui->chatInput->setEnabled(false);
    ui->sendButton->setEnabled(false);
}

void ChatRoom::onChatError(const QString& error) {
    ui->chatDisplay->append("错误: " + error);
}

void ChatRoom::handleChatMessage(const QString& type, const QString& message) {
    qDebug() << "收到消息 - 类型:" << type << "完整内容:" << message;
    
    if(type == "CHAT_ALL") {
        if(message.contains("加入了聊天室") || 
           message.contains("离开了聊天室") || 
           message.contains(": ")) {
            appendChatMessage(message);
        }
    }
    else if(type == "USER") {
        qDebug() << "收到用户列表更新消息:" << message;
        
        QJsonValue messageValue;
        QJsonDocument messageDoc = QJsonDocument::fromJson(message.toUtf8());
        
        if (messageDoc.isArray()) {
            // 如果消息本身就是一个JSON数组
            messageValue = QJsonValue(messageDoc.array());
        } else {
            // 如果消息是一个对象，尝试获取其中的数组
            QJsonObject messageObj = messageDoc.object();
            messageValue = messageObj["message"];
        }
        
        QStringList users;
        if (messageValue.isArray()) {
            QJsonArray userArray = messageValue.toArray();
            qDebug() << "解析到的用户数组:" << userArray;
            
            for (const QJsonValue& value : userArray) {
                if (value.isString()) {
                    users.append(value.toString());
                }
            }
        }
        
        qDebug() << "最终用户列表:" << users;
        
        if (!users.isEmpty()) {
            ui->userList->clear();
            ui->userList->addItems(users);
            qDebug() << "更新UI列表完成，共" << ui->userList->count() << "个用户";
            
            // 确保所有项目可见
            for(int i = 0; i < ui->userList->count(); ++i) {
                QListWidgetItem* item = ui->userList->item(i);
                item->setHidden(false);
                qDebug() << "用户" << i << ":" << item->text();
            }
            
            ui->userList->viewport()->update();
        } else {
            qDebug() << "警告: 未能解析出有效的用户列表";
            qDebug() << "原始消息内容:" << message;
        }
    }
    else if(type == "LOGIN") {
        if(message == "success") {
            qDebug() << "登录成功";
            ui->chatInput->setEnabled(true);
            ui->sendButton->setEnabled(true);
        } else {
            ui->chatDisplay->append("登录失败: " + message);
            qDebug() << "登录失败:" << message;
        }
    }
}

void ChatRoom::appendChatMessage(const QString& message) {
    ui->chatDisplay->append(message);
}

void ChatRoom::onSendMessage() {
    if(Login::isGuest) {
        QMessageBox::warning(this, "提示", "游客模式不能发送消息，请注册登录后使用。");
        return;
    }

    QString message = ui->chatInput->text().trimmed();
    if(!message.isEmpty()) {
        // 添加用户名到消息中
        QString formattedMessage = Login::currentUsername + ": " + message;
        qDebug() << "发送聊天消息:" << message;
        client->sendMessage("CHAT_ALL", formattedMessage);
        ui->chatInput->clear();
        // 在本地显示自己发送的消息
        ui->chatDisplay->append("我: " + message);
    }
}

void ChatRoom::on_registerButton_clicked() {
    Signup *signUp = new Signup();
    connect(signUp, &Signup::registerSuccess, this, &ChatRoom::onRegisterSuccess);
    signUp->show();
}

void ChatRoom::onRegisterSuccess() {
    ui->chatInput->setEnabled(true);
    ui->sendButton->setEnabled(true);
    ui->registerButton->hide();
    ui->chatDisplay->append("注册成功！现在您可以参与聊天了。");

    setWindowTitle("聊天室 - " + Login::currentUsername);

    if(client && client->isConnected()) {
        client->sendMessage("LOGIN", Login::currentUsername + "\r" + "password");
    }
}
