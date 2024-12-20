#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// 数据库初始化函数声明
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

    // 数据库相关函数
    bool initDatabase();  // 初始化数据库连接
    bool registerUser(const QString &username, const QString &password);  // 注册新用户

    // 静态成员变量，用于在整个应用程序中共享登录状态
    static bool isGuest;          // 标记是否为游客模式
    static QString currentUsername;  // 记录当前登录用户名
    static int guestCounter;        // 游客计数器，用于区分不同游客

public slots:
    void showAndReset();  // 显示登录窗口并重置输入框

signals:
    void loginSuccess();  // 登录成功信号，用于通知其他组件

private slots:
    void on_btn_signin_clicked();   // 登录按钮点击处理
    void on_btn_signup_clicked();   // 注册按钮点击处理
    void on_btn_guest_clicked();    // 游客登录按钮点击处理

private:
    QSqlDatabase db;    // 数据库连接对象
    Ui::Login *ui;      // UI界面对象
};

#endif // LOGIN_H
