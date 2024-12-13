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
    
    // 创建并设置验证方式选择下拉框
    auto *verificationMethodBox = new QComboBox(this);
    verificationMethodBox->addItem("图形验证码");
    verificationMethodBox->addItem("滑块验证");
    
    // 创建一个水平布局放置验证方式选择
    auto *methodLayout = new QHBoxLayout();
    methodLayout->addWidget(new QLabel("验证方式:", this));
    methodLayout->addWidget(verificationMethodBox);
    methodLayout->addStretch();
    
    // 获取验证码输入框所在的布局
    QWidget* parent = ui->lineEdit_verification->parentWidget();
    QLayout* parentLayout = parent->layout();
    if (QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(parentLayout)) {
        // 在验证码输入框上方插入选择框
        int index = vLayout->indexOf(ui->lineEdit_verification);
        vLayout->insertLayout(index, methodLayout);
        
        // 创建验证码控件
        verificationWidget = new Verification(this);
        verificationWidget->setFixedSize(100, 30);
        
        // 创建滑块验证控件
        sliderWidget = new SliderPuzzleWidget(this);
        sliderWidget->hide();
        
        // 创建验证框架并设置布局
        auto *verificationFrame = new QFrame(this);
        auto *verifyLayout = new QHBoxLayout(verificationFrame);
        verifyLayout->setContentsMargins(5, 5, 5, 5);
        verifyLayout->addWidget(verificationWidget);
        verifyLayout->addWidget(sliderWidget);
        
        // 将验证框架添加到布局中
        vLayout->insertWidget(index + 1, verificationFrame);
    }
    
    // 连接信号槽
    connect(verificationMethodBox, &QComboBox::currentIndexChanged, 
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
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    
    if(username.isEmpty() || password.isEmpty() || surepass.isEmpty()) {
        QMessageBox::warning(this, "注册错误", "用户名和密码不能为空！");
        return;
    }
    
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
}
*/