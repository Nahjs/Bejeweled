#include "signup.h"
#include "login.h"
#include <QSqlError>
#include "ui_signup.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    
    // 创建验证码控件
    verificationWidget = new verification(this);
    // 设置验证码控件的固定大小
    verificationWidget->setFixedSize(100, 30);
    
    // 将验证码控件添加到Frame中
    QHBoxLayout* layout = new QHBoxLayout(ui->verificationFrame);
    layout->setContentsMargins(5, 5, 5, 5); // 设置上下左右边距都为5
    layout->addWidget(verificationWidget);
    ui->verificationFrame->setLayout(layout);
}

Signup::~Signup()
{
    delete ui;
}

//返回登录按钮
void Signup::on_btn_return_clicked()
{
    emit backToLogin();
    this->close();
}

//注册按钮
void Signup::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    QString inputCode = ui->lineEdit_verification->text(); // 需要在UI中添加验证码输入框
    
    if(username.isEmpty() || password.isEmpty() || surepass.isEmpty() || inputCode.isEmpty()) {
        QMessageBox::warning(this, "注册错误", "所有字段都必须填写！");
        return;
    }
    
    // 验证码校验
    if(inputCode.toLower() != verificationWidget->getVerificationCode().toLower()) {
        QMessageBox::warning(this, "注册错误", "验证码错误！");
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
        emit signupSuccess();
        emit backToLogin();
        this->close();
    } else {
        // 使用数据库错误文本进行判断
        QString errorText = query.lastError().text();
        if(errorText.contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "注册失败", "用户名已存在！");
        } else {
            QMessageBox::warning(this, "注册失败", "未知错误：" + errorText);
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