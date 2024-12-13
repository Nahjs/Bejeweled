#include "login.h"
#include "ui_login.h"
#include "signup.h"

#include <QGraphicsDropShadowEffect>
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    // 初始化数据库连接
    if(!QSqlDatabase::contains()) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("user.db");
        if(!db.open()) {
            qDebug() << "Database open failed:" << db.lastError().text();
        }
    }

}

Login::~Login()
{
    delete ui;
    QSqlDatabase::database().close();
}

void sqlite_Init()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if(!db.open())
    {
        qDebug()<<"open error";
    }
    //create excle
    QString createsql=QString("create table if not exists user(id integer primary key autoincrement,"
                        "username ntext unique not NULL,"
                        "password ntext not NULL)");
    QSqlQuery query;
    if(!query.exec(createsql)){
        qDebug()<<"table create error";
    }
    else{
        qDebug()<<"table create success";
    }
}


void Login::on_btn_signin_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    
    if(query.exec()) {
        if(query.next()) {
            emit loginSuccess();  // 发送登录成功信号
            this->hide();
        } else {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
    }
}

void Login::on_btn_signup_clicked()
{
    this->close();
    Signup *s = new Signup;
    s->show();

}
