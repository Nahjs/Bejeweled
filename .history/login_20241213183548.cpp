#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include <QSqlError>  // 添加这个头文件，虽然已经在 login.h 中包含了，这里为了清晰也可以再加一次

#include <QGraphicsDropShadowEffect>
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    sqlite_Init(); // 确保数据库初始化
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
                              "password TEXT NOT NULL)");
    
    if(!query.exec(createsql)) {
        qDebug() << "table create error:" << query.lastError().text();
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
            QMessageBox::information(this, "登录成功", "欢迎回来！");
            emit loginSuccess();
            this->hide();
        } else {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        QMessageBox::warning(this, "错误", "数据库查询失败！");
    }
}

void Login::on_btn_signup_clicked()
{
    this->close();
    Signup *s = new Signup;
    s->show();

}
