#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>  // 添加这个头文件
#include <QMessageBox>
#include <QDebug>

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

public slots:
    void showAndReset();  // 添加显示并重置输入的槽函数

private:
    QSqlDatabase db; // 添加数据库成员变量

signals:  // 修改为正确的signals部分
    void loginSuccess();

private slots:
    void on_btn_signin_clicked();
    void on_btn_signup_clicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
