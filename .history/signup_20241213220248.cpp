#include "signup.h"
#include "login.h"
#include <QSqlError>
#include "ui_signup.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup),
    useSliderVerification(false)
{
    ui->setupUi(this);
    
    // 添加验证方式选择下拉框
    QComboBox* verificationMethodBox = new QComboBox(this);
    verificationMethodBox->addItem("图形验证码");
    verificationMethodBox->addItem("滑块验证");
    ui->verticalLayout->insertWidget(2, verificationMethodBox);  // 插入到适当位置
    
    // 创建验证码控件
    verificationWidget = new Verification(this);
    verificationWidget->setFixedSize(100, 30);
    
    // 创建滑块验证控件
    sliderWidget = new SliderPuzzleWidget(this);
    sliderWidget->hide();  // 初始隐藏
    
    // 添加到布局
    QHBoxLayout* layout = new QHBoxLayout(ui->verificationFrame);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(verificationWidget);
    layout->addWidget(sliderWidget);
    ui->verificationFrame->setLayout(layout);
    
    // 连接信号槽
    connect(verificationMethodBox, SIGNAL(currentIndexChanged(int)), 
            this, SLOT(onVerificationMethodChanged(int)));
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