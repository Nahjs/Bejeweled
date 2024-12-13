#include "signup.h"
#include "ui_signup.h"
#include "login.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

//返回登录按钮
void Signup::on_btn_return_clicked()
{
    Login *w = new Login;
    w->show();
    this->close();
}

//注册按钮
void Signup::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    
    if(username.isEmpty() || password.isEmpty() || surepass.isEmpty()) {
        QMessageBox::warning(this, "注册错误", "所有字段都必须填写！");
        return;
    }
    
    if(password != surepass) {
        QMessageBox::warning(this, "注册错误", "两次输入的密码不一致！");
        return;
    }
    
    QSqlQuery query;
    query.prepare("INSERT INTO user (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    
    if(query.exec()) {
        QMessageBox::information(this, "注册成功", "账号注册成功，请返回登录！");
        Login *w = new Login;
        w->show();
        this->close();
    } else {
        if(query.lastError().type() == QSqlError::ConstraintViolation) {
            QMessageBox::warning(this, "注册失败", "用户名已存在！");
        } else {
            QMessageBox::warning(this, "注册失败", "未知错误：" + query.lastError().text());
        }
    }
}
/*
void Signup::on_btn_confirm_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    
    QSqlQuery query;
    query.prepare("INSERT INTO user (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    
    if(query.exec()) {
        QMessageBox::information(this, "注册成功", "账号注册成功！");
        this->close();
    } else {
        QMessageBox::warning(this, "注册失败", "用户名已存在！");
    }
}
*/