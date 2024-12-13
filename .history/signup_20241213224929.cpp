#include "signup.h"
#include "login.h"
#include <QSqlError>

#include "sliderpuzzlewidget.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup),
    useSliderVerification(false)
{
    ui->setupUi(this);
    
    // 设置验证方式下拉框
    ui->verificationMethodBox->clear();  // 清空已有选项
    ui->verificationMethodBox->addItem("图形验证码");
    ui->verificationMethodBox->addItem("滑块验证");
    
    // 创建验证码控件
    verificationWidget = new Verification(this);
    verificationWidget->setFixedSize(100, 30);
    verificationWidget->setParent(ui->verificationFrame);  // 设置正确的父窗口
    verificationWidget->show();  // 确保显示
    
    // 创建滑块验证控件
    sliderWidget = new SliderPuzzleWidget(this);
    sliderWidget->setGeometry(170, 390, 201, 191);  // 使用verificationFrame的位置和大小
    sliderWidget->hide();
    
    // 设置验证码框架
    if (ui->verificationFrame->layout()) {
        delete ui->verificationFrame->layout();  // 清除可能存在的旧布局
    }
    auto *verifyLayout = new QHBoxLayout(ui->verificationFrame);
    verifyLayout->setContentsMargins(0, 0, 0, 0);
    verifyLayout->addWidget(verificationWidget);
    
    // 将滑块验证控件移到最上层
    sliderWidget->raise();
    
    // 连接信号槽
    connect(ui->verificationMethodBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &Signup::onVerificationMethodChanged);
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

void Signup::onVerificationMethodChanged(int index)
{
    useSliderVerification = (index == 1);
    updateVerificationWidget();
}

void Signup::updateVerificationWidget()
{
    if (useSliderVerification) {
        verificationWidget->hide();
        ui->lineEdit_verification->hide();
        ui->label_verification->hide();
        sliderWidget->show();
        sliderWidget->raise();  // 确保滑块验证控件在最上层
    } else {
        verificationWidget->show();
        ui->lineEdit_verification->show();
        ui->label_verification->show();
        sliderWidget->hide();
    }
}

//注册按钮
void Signup::on_pushButton_2_clicked()
{
    
    if(password != surepass) {
        QMessageBox::warning(this, "注册错误", "两次输入的密码不一致！");
        return;
    }
    
    // 验证检查
    bool verificationPassed = false;
    if (useSliderVerification) {
        verificationPassed = sliderWidget->isVerified();
        if (!verificationPassed) {
            QMessageBox::warning(this, "注册错误", "请完成滑块验证！");
            return;
        }
    } else {
        QString inputCode = ui->lineEdit_verification->text();
        verificationPassed = (inputCode.toLower() == verificationWidget->getVerificationCode().toLower());
        if (!verificationPassed) {
            QMessageBox::warning(this, "注册错误", "验证码错误！");
            return;
        }
    }
    
    // 验证通过，执行注册
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
}*/