#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "ui_signup.h"
#include "Verification.h"  // 添加验证码头文件

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

signals:
    void signupSuccess();  // 添加注册成功信号
    void backToLogin();    // 添加返回登录信号

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_2_clicked();
    void on_btn_return_clicked();
    void on_btnSwitchVerification_clicked();  // 添加切换验证方式槽函数

private:
    Ui::Signup *ui;
    Verification *verificationWidget;  // 添加验证码控件
    SliderPuzzleWidget *sliderPuzzleWidget;  // 添加滑块拼图控件
    bool useSliderVerification;  // 标记当前使用的验证方式
    
    void switchVerificationMethod();  // 切换验证方式
    bool checkVerification();         // 验证检查
};

#endif // SIGNUP_H
