#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

// 前向声明
class Signup;
class Start;

void sqlite_Init();

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginSuccess(); // 添加登录成功信号

private slots:
    void on_btn_signin_clicked();

    void on_btn_signup_clicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
