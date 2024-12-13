#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include <QSqlError>  // 添加这个头文件，虽然已经在 login.h 中包含了，这里为了清晰也可以再加一次

#include <QGraphicsDropShadowEffect>

bool Login::isGuest = false;
QString Login::currentUsername = "";
int Login::guestCounter = 0;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    sqlite_Init(); // 确保数据库初始化

    // 添加游客模式提示标签
    QString guestTip = "游客模式提示：\n"
                      "• 游客模式下的游戏记录不会保存\n"
                      "• 无法查看历史最高分\n"
                      "• 建议注册账号以保存游戏进度！";
    ui->label_guestTip->setText(guestTip);
    ui->label_guestTip->setStyleSheet("QLabel { color:rgb(234, 13, 13); }");
    
    // 为游客登录按钮添加确认对话框
    connect(ui->btn_guest, &QPushButton::clicked, this, [this](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "游客登录",
                                    "是否以游客身份进行游戏？\n"
                                    "• 游客模式下的游戏记录将不会保存\n"
                                    "• 建议注册账号以保存游戏进度\n\n"
                                    "点击\"是\"继续游客登录\n"
                                    "点击\"否\"前往注册账号",
                                    QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes) {
            on_btn_guest_clicked();
        } else {
            this->hide();  // 隐藏登录窗口
            on_btn_signup_clicked();  // 跳转到注册界面
        }
    });
}

Login::~Login()
{
    delete ui;
    QSqlDatabase::database().close();
}

void sqlite_Init()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if(!db.open()) {
        qDebug() << "open error:" << db.lastError().text();
        return;
    }
    
    QSqlQuery query;
    QString createsql = QString("CREATE TABLE IF NOT EXISTS user ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "username TEXT UNIQUE NOT NULL, "
                              "password TEXT NOT NULL, "
                              "highest_score INTEGER DEFAULT 0)");
    
    if(!query.exec(createsql)) {
        qDebug() << "table create error:" << query.lastError().text();
    }

    // 修改排行榜表结构
    QString createLeaderboard = QString("CREATE TABLE IF NOT EXISTS leaderboard ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                      "username TEXT NOT NULL, "
                                      "score INTEGER NOT NULL, "
                                      "game_time DATETIME DEFAULT CURRENT_TIMESTAMP, "
                                      "FOREIGN KEY(username) REFERENCES user(username))");
    
    if(!query.exec(createLeaderboard)) {
        qDebug() << "leaderboard table create error:" << query.lastError().text();
    }
}

void Login::on_btn_signin_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    
    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录错误", "用户名和密码不能为空！");
        return;
    }
    
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    
    if(query.exec()) {
        if(query.next()) {
            currentUsername = username;
            isGuest = false;
            QMessageBox::information(this, "登录成功", "欢迎回来！");
            emit loginSuccess();
            this->hide();
        } else {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        }
    } else {
        // 使用数据库错误文本进行判断
        QString errorText = query.lastError().text();
        if(errorText.contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "登录失败", "用户名已存在！");
        } else {
            QMessageBox::warning(this, "登录失败", "未知错误：" + errorText);
        }
    }
}

void Login::showAndReset()
{
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    this->show();
}

void Login::on_btn_signup_clicked()
{
    Signup *s = new Signup;
    connect(s, &Signup::backToLogin, this, &Login::showAndReset);
    connect(s, &Signup::signupSuccess, s, &Signup::deleteLater);
    s->show();
    this->hide();  // 隐藏而不是关闭登录窗口
}

void Login::on_btn_guest_clicked()
{
    guestCounter++;
    currentUsername = QString("Guest_%1").arg(guestCounter);
    isGuest = true;
    emit loginSuccess();
    this->hide();
}
