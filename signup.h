#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QComboBox>
#include <QProgressBar>
#include <QVBoxLayout>
#include "ui_signup.h"
#include "Verification.h"        //图像验证头文件
#include "sliderpuzzlewidget.h"  // 滑块验证头文件

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

signals:
    void signupSuccess();    // 注册成功时发射，用于通知其他组件
    void backToLogin();      // 返回登录界面时发射，用于切换视图
    void registerSuccess();   // 注册成功时发射，用于数据库操作完成的通知

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_2_clicked();           // 注册按钮点击处理
    void on_btn_return_clicked();             // 返回按钮点击处理
    void onVerificationMethodChanged(int index); // 验证方式切换处理
    void updateVerificationWidget();          // 更新验证组件的显示状态
    void checkAndShowVerification();          // 检查输入并显示验证组件

private:
    Ui::Signup *ui;
    //QLabel *strengthLabel;    // 添加密码强度显示标签
    //QProgressBar *strengthBar; // 添加密码强度进度条
    Verification *verificationWidget;         // 图形验证码控件
    SliderPuzzleWidget *sliderWidget;         // 滑块验证控件
    bool useSliderVerification;               // 当前使用的验证方式（true为滑块，false为图形验证码）
    bool inputValidated;                      // 输入验证状态标记
    
    bool validateInput();                     // 验证用户输入的合法性
    void showVerificationWidget();            // 显示当前选择的验证组件
    void updatePasswordStrength(const QString &password); // 更新密码强度指示器显示
};

#endif // SIGNUP_H
