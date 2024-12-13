#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QComboBox>
#include <QVBoxLayout>
#include "ui_signup.h"
#include "Verification.h"
#include "sliderpuzzlewidget.h"  // 添加滑块验证头文件

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
    void onVerificationMethodChanged(int index);
    void updateVerificationWidget();

    void checkAndShowVerification();

private:
    Ui::Signup *ui;
    Verification *verificationWidget;  // 添加验证码控件
    SliderPuzzleWidget *sliderWidget;
    bool useSliderVerification;  // 标记当前使用的验证方式
    bool inputValidated;  // 新增：标记输入是否已验证
    
    bool validateInput();  // 新增：验证输入合法性
    void showVerificationWidget();  // 新增：显示验证组件
};

#endif // SIGNUP_H
