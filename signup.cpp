#include "signup.h"

#include <QLineEdit>
#include <QProgressBar>

#include "login.h"
#include <QSqlError>
#include <QRegularExpression>  // 使用新的正则表达式类

#include "sliderpuzzlewidget.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup),
    useSliderVerification(true),  // 默认使用滑块验证
    inputValidated(false)
{
    ui->setupUi(this);
    
    // 配置密码输入框和基本UI设置
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);                // 设置密码显示模式
    ui->lineEdit_surepasswd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_passwd->setPlaceholderText("6-16位字符，不包含中文");    // 设置占位提示文本
    ui->lineEdit_surepasswd->setPlaceholderText("请再次输入密码");
    
    // 统一设置输入框高度
    ui->lineEdit_username->setFixedHeight(40);
    ui->lineEdit_passwd->setFixedHeight(40);
    ui->lineEdit_surepasswd->setFixedHeight(40);

    // 初始化验证方式选择
    ui->verificationMethodBox->clear();
    ui->verificationMethodBox->addItem("滑块验证");
    ui->verificationMethodBox->addItem("图形验证码");
    
    // 创建验证码控件
    verificationWidget = new Verification(this);
    verificationWidget->setFixedSize(100, 30);
    verificationWidget->setParent(ui->verificationFrame);  // 设置正确的父窗口
    verificationWidget->show();  // 确保显示
    
    // 创建滑块验证控件
    sliderWidget = new SliderPuzzleWidget(this);
    sliderWidget->setGeometry(150, 390, 201, 191);  // 使用verificationFrame的位置和大小
    sliderWidget->hide();
    
    // 设置验证码框架
    if (ui->verificationFrame->layout()) {
        delete ui->verificationFrame->layout();  // 清除可能存在的旧布局
    }
    auto *verifyLayout = new QHBoxLayout(ui->verificationFrame);
    verifyLayout->setContentsMargins(0, 0, 0, 0);
    verifyLayout->addWidget(verificationWidget);
    
    // 将滑块验证控件移到最上层并显示
    sliderWidget->raise();
    sliderWidget->show();  // 默认显示滑块验证
    
    // 初始隐藏图形验证码相关组件
    verificationWidget->hide();
    ui->lineEdit_verification->hide();
    ui->label_verification->hide();
    
    // 设置默认选择为滑块验证
    ui->verificationMethodBox->setCurrentIndex(0);


    // 更新密码输入框连接
    connect(ui->lineEdit_passwd, &QLineEdit::textChanged, this, &Signup::updatePasswordStrength);

    // 密码输入实时验证
    connect(ui->lineEdit_passwd, &QLineEdit::textChanged, this, [this](const QString &text) {
        // 检查密码强度，但不显示提示标签
        QRegularExpression hasLetter("[A-Za-z]");
        QRegularExpression hasNumber("[0-9]");
        QRegularExpression hasSymbol("[^A-Za-z0-9\u4e00-\u9fa5]");
        QRegularExpression hasChinese("[\u4e00-\u9fa5]");
        
        QString placeholderText = "密码要求：6-16位字符，不能包含中文";
        
        if (!text.isEmpty()) {
            if (text.length() < 6 || text.length() > 16) {
                ui->lineEdit_passwd->setStyleSheet("QLineEdit { color: red; }");
            } else if (text.contains(hasChinese)) {
                ui->lineEdit_passwd->setStyleSheet("QLineEdit { color: red; }");
            } else {
                ui->lineEdit_passwd->setStyleSheet("");
            }
        } else {
            ui->lineEdit_passwd->setStyleSheet("");
        }
    });

    // 验证方式切换处理
    connect(ui->verificationMethodBox, &QComboBox::currentIndexChanged,
            this, &Signup::onVerificationMethodChanged);
    
    // 确保验证组件正确初始化
    verificationWidget->hide();
    ui->lineEdit_verification->hide();
    ui->label_verification->hide();
    sliderWidget->show();
    sliderWidget->raise();
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
    useSliderVerification = (index == 0);
    
    // 根据选择的验证方式更新界面
    if (useSliderVerification) {
        // 切换到滑块验证
        verificationWidget->hide();
        ui->lineEdit_verification->hide();
        ui->label_verification->hide();
        sliderWidget->show();
        sliderWidget->raise();
        sliderWidget->reset();
    } else {
        // 切换到图形验证码
        sliderWidget->hide();
        verificationWidget->show();
        ui->lineEdit_verification->show();
        ui->label_verification->show();
        verificationWidget->refreshCode();
    }
}

void Signup::updateVerificationWidget()
{
    // 先隐藏所有验证组件
    verificationWidget->hide();
    ui->lineEdit_verification->hide();
    ui->label_verification->hide();
    sliderWidget->hide();

    qDebug() << "更新验证组件显示";  // 添加调试输出
    
    if (useSliderVerification) {
        qDebug() << "显示滑块验证";  // 添加调试输出
        sliderWidget->show();
        sliderWidget->raise();
        sliderWidget->reset();
    } else {
        qDebug() << "显示图形验证码";  // 添加调试输出
        verificationWidget->show();
        ui->lineEdit_verification->show();
        ui->label_verification->show();
        verificationWidget->refreshCode();
    }
}

bool Signup::validateInput()
{
    // 获取用户输入
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    
    // 验证输入不为空
    if(username.isEmpty() || password.isEmpty() || surepass.isEmpty()) {
        QMessageBox::warning(this, "注册错误", "用户名和密码不能为空！");
        return false;
    }
    
    // 验证密码规则
    QRegularExpression rx("[\u4e00-\u9fa5]");
    if (password.contains(rx)) {
        QMessageBox::warning(this, "注册错误", "密码不能包含中文字符！");
        return false;
    }
    
    // 检查密码长度
    if (password.length() < 6 || password.length() > 16) {
        QMessageBox::warning(this, "注册错误", "密码长度必须在6-16位之间！");
        return false;
    }
    
    if(password != surepass) {
        QMessageBox::warning(this, "注册错误", "两次输入的密码不一致！");
        return false;
    }
    
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM user WHERE username = ?");
    checkQuery.addBindValue(username);
    
    if(checkQuery.exec() && checkQuery.next()) {
        QMessageBox::warning(this, "注册错误", "用户名已存在！");
        return false;
    }
    
    return true;
}

void Signup::showVerificationWidget()
{
    if (useSliderVerification) {
        sliderWidget->show();
        sliderWidget->raise();
        sliderWidget->reset();  // 使用正确的方法名
    } else {
        verificationWidget->show();
        ui->lineEdit_verification->show();
        ui->label_verification->show();
        verificationWidget->refreshCode();  // 使用新的公共方法
    }
}

//注册按钮
void Signup::on_pushButton_2_clicked()
{
    // 验证输入
    if (!validateInput()) {
        return;
    }
    
    // 验证码验证
    bool verificationPassed = false;
    if (useSliderVerification) {
        if (!sliderWidget->isVerified()) {
            QMessageBox::warning(this, "注册错误", "请完成滑块验证！");
            return;
        }
        verificationPassed = true;
    } else {
        QString inputCode = ui->lineEdit_verification->text();
        if (inputCode.isEmpty()) {
            QMessageBox::warning(this, "注册错误", "请输入验证码！");
            return;
        }
        verificationPassed = (inputCode.toLower() == verificationWidget->getVerificationCode().toLower());
        if (!verificationPassed) {
            QMessageBox::warning(this, "注册错误", "验证码错误！");
            verificationWidget->refreshCode();
            return;
        }
    }
    
    // 执行注册
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    
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
        qDebug() << "Database error:" << errorText;
        QMessageBox::warning(this, "注册失败", "数据库错误：" + errorText);
    }
}

void Signup::checkAndShowVerification()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    
    // 检查用户输入
    if(username.isEmpty() || password.isEmpty() || surepass.isEmpty()) {
        QMessageBox::warning(this, "注册错误", "用户名和密码不能为空！");
        return;
    }
    
    if(password != surepass) {
        QMessageBox::warning(this, "注册错误", "两次输入的密码不一致！");
        return;
    }
    
    // 检查用户名是否已存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM user WHERE username = ?");
    checkQuery.addBindValue(username);
    
    if(checkQuery.exec() && checkQuery.next()) {
        QMessageBox::warning(this, "注册错误", "用户名已存在！");
        return;
    }
    
    // 显示对应的验证组件
    if (useSliderVerification) {
        sliderWidget->show();
        sliderWidget->raise();
    } else {
        verificationWidget->show();
        ui->lineEdit_verification->show();
        ui->label_verification->show();
    }
}

/**
 * @brief 更新密码强度显示
 * @param password 当前输入的密码
 * 
 * 密码强度评分规则：
 * - 基础要求(25分)：长度6-16位且不含中文
 * - 包含字母(+25分)：密码中包含英文字母
 * - 包含数字(+25分)：密码中包含数字
 * - 包含特殊符号(+25分)：密码中包含特殊字符
 * 
 * 强度等级显示：
 * - 红色(0-25)：弱密码，仅满足基础要求
 * - 橙色(26-50)：中等，包含字母或数字
 * - 黄色(51-75)：较强，包含字母和数字
 * - 绿色(76-100)：强密码，包含字母、数字和特殊符号
 */
void Signup::updatePasswordStrength(const QString &password)
{
    int strength = 0;
    // 定义正则表达式用于检查密码组成
    QRegularExpression hasLetter("[A-Za-z]");       // 检查是否包含字母
    QRegularExpression hasNumber("[0-9]");          // 检查是否包含数字
    QRegularExpression hasSymbol("[^A-Za-z0-9\u4e00-\u9fa5]");  // 检查是否包含特殊符号
    QRegularExpression hasChinese("[\u4e00-\u9fa5]");  // 检查是否包含中文字符

    // 检查密码是否满足基础要求
    if (password.length() >= 6 && password.length() <= 16) {
        if (!password.contains(hasChinese)) {
            strength += 25;  // 满足基础要求的分数
            
            // 增加额外的强度分数
            if (password.contains(hasLetter)) strength += 25;  // 包含字母
            if (password.contains(hasNumber)) strength += 25;  // 包含数字
            if (password.contains(hasSymbol)) strength += 25;  // 包含特殊符号
        }
    }
    
    // 根据强度设置进度条样式
    QString style;
    if (strength <= 25) {
        style = "QProgressBar::chunk { background-color: red; }";      // 弱密码
    } else if (strength <= 50) {
        style = "QProgressBar::chunk { background-color: orange; }";   // 中等强度
    } else if (strength <= 75) {
        style = "QProgressBar::chunk { background-color: yellow; }";   // 较强
    } else {
        style = "QProgressBar::chunk { background-color: green; }";    // 强密码
    }
    
    // 更新UI显示
    ui->strengthBar->setStyleSheet(style);           // 设置进度条颜色
    ui->strengthBar->setValue(strength);             // 更新进度条值
    
    // 更新密码输入框的视觉提示
    if (!password.isEmpty()) {
        if (password.length() < 6 || password.length() > 16 || password.contains(hasChinese)) {
            // 密码不符合要求时显示红色
            ui->lineEdit_passwd->setStyleSheet("QLineEdit { color: red; }");
        } else {
            // 密码符合要求时恢复正常颜色
            ui->lineEdit_passwd->setStyleSheet("");
        }
    } else {
        // 密码为空时恢复正常颜色
        ui->lineEdit_passwd->setStyleSheet("");
    }
}