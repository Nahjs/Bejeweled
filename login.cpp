#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include <QSqlError>  // 添加这个头文件，虽然已经在 login.h 中包含了，这里为了清晰也可以再加一次

#include <QGraphicsDropShadowEffect>

#include "levelmanager.h"

// 静态成员变量初始化
bool Login::isGuest = false;
QString Login::currentUsername = "";
int Login::guestCounter = 0;

Login::Login(QWidget *parent) : QMainWindow(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
    sqlite_Init(); // 确保数据库初始化

    // 设置游客模式提示信息
    QString guestTip = "游客模式提示：\n"
                      "• 游客模式下的游戏记录不会保存\n"
                      "• 无法查看历史最高分\n"
                      "• 建议注册账号以保存游戏进度！";
    ui->label_guestTip->setText(guestTip);
    ui->label_guestTip->setStyleSheet("QLabel { color:rgb(234, 13, 13); }");
    
    // 游客登录确认对话框设置
    connect(ui->btn_guest, &QPushButton::clicked, this, [this](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "游客登录",
                                    "是否以游客身份进行游戏？\n"
                                    "• 游客模式下的游戏记录将不会保存\n"
                                    "• 建议注册账号以保存游戏进度\n\n"
                                    "点击\"是\"继续游客登录\n"
                                    "点击\"否\"前往注册账号",
                                    QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes) {
            on_btn_guest_clicked();
        } else {
            this->hide();  // 隐藏登录窗口
            on_btn_signup_clicked();  // 跳转到注册界面
        }
    });
}

Login::~Login()
{
    delete ui;
    QSqlDatabase::database().close();
}

// 数据库初始化函数
void sqlite_Init()
{
    // 移除可能存在的旧连接
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    
    // 创建新的数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    
    // 打开数据库连接
    if(!db.open()) {
        qDebug() << "数据库连接失败:" << db.lastError().text();
        return;
    }
    
    QSqlQuery query;
    
    // 1. 先创建关卡配置表
    if(!query.exec("CREATE TABLE IF NOT EXISTS level_config ("
              "level_id INTEGER PRIMARY KEY, "
              "target_score INTEGER, "
              "time_limit INTEGER, "
              "map_size INTEGER, "
              "gem_types INTEGER, "
              "special_rules TEXT, "
              "step_limit INTEGER)")) {
        qDebug() << "创建关卡配置表失败:" << query.lastError().text();
        return;
    }
    
    // 检查并填充关卡数据
    query.exec("SELECT COUNT(*) FROM level_config");
    if(query.next() && query.value(0).toInt() == 0) {
        // 插入关卡配置数据
        const struct {
            int id, score, time, size, gems, steps;
            QString rules;
        } levels[] = {
            {1, 100, 120, 6, 5, 5, "新手教程：\n- 达到100分\n- 完成一次三消\n- 使用一次道具"},
            {2, 400, 100, 7, 6, 10, "进阶挑战：\n- 完成一次四连消除\n- 达到500分"},
            {3, 400, 90, 7, 6, 20, "限时挑战：\n- 完成一次四连消除\n- 达到800"},
            {4, 400, 120, 8, 6, 15, "特殊任务：\n- 消除25个红宝石\n- 使用2次道具"},
            {5, 500, 120, 8, 7, 18, "道具大师：\n- 使用3种道具\n- 完成五连消除"},
            {6, 600, 150, 9, 7, 20, "连击达人：\n- 完成一次六连消除\n- 达到3500分"},
            {7, 700, 60, 9, 7, 25, "极限挑战：\n- 60秒内达到4000分\n- 连击8次"},
            {8, 800, 180, 10, 8, 30, "终极试炼：\n- 完成七连消除\n- 达到5000分"},
            {9, 900, 150, 11, 8, 25, "宝石大师：\n- 各种宝石消除20个\n- 达到6000分"},
            {10, 1000, 180, 12, 8, 35, "最终关卡：\n- 完成所有任务\n- 达到8000分"}
        };

        for(const auto& level : levels) {
            query.prepare("INSERT INTO level_config VALUES (?,?,?,?,?,?,?)");
            query.addBindValue(level.id);
            query.addBindValue(level.score);
            query.addBindValue(level.time);
            query.addBindValue(level.size);
            query.addBindValue(level.gems);
            query.addBindValue(level.rules);
            query.addBindValue(level.steps);
            
            if(!query.exec()) {
                qDebug() << "插入关卡" << level.id << "配置失败:" 
                         << query.lastError().text();
            }
        }
    }
    
    // 2. 再创建其他表
    
    // 创建用户表，包含所有需要的字段
    QString createTableSQL = 
        "CREATE TABLE IF NOT EXISTS user ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "  // 自增主键
        "username TEXT UNIQUE NOT NULL, "         // 用户名（唯一）
        "password TEXT NOT NULL, "                // 密码
        "highest_score INTEGER DEFAULT 0, "       // 最高分
        "coins INTEGER DEFAULT 100, "             // 金币数量
        "props_boom INTEGER DEFAULT 0, "          // 爆炸道具数量
        "props_row INTEGER DEFAULT 0, "           // 行消除道具数量
        "props_col INTEGER DEFAULT 0, "           // 列消除道具数量
        "props_color INTEGER DEFAULT 0"           // 颜色道具数量
        ")";
    
    // 创建排行榜表
    QString createLeaderboard = 
        "CREATE TABLE IF NOT EXISTS leaderboard ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "score INTEGER NOT NULL, "
        "game_time DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "FOREIGN KEY(username) REFERENCES user(username)"
        ")";
    
    // 创建关卡进度表
    QString createProgressTable = 
        "CREATE TABLE IF NOT EXISTS user_progress ("
        "username TEXT, "
        "level_id INTEGER, "
        "highest_score INTEGER DEFAULT 0, "
        "stars INTEGER DEFAULT 0, "
        "completed BOOLEAN DEFAULT 0, "
        "FOREIGN KEY(username) REFERENCES user(username), "
        "FOREIGN KEY(level_id) REFERENCES level_config(level_id), "
        "PRIMARY KEY(username, level_id))";
        
    if(!query.exec(createProgressTable)) {
        qDebug() << "关卡进度表创建失败:" << query.lastError().text();
    }
    
    // 执行表创建
    if(!query.exec(createTableSQL)) {
        qDebug() << "用户表创建失败:" << query.lastError().text();
    }
    if(!query.exec(createLeaderboard)) {
        qDebug() << "排行榜表创建失败:" << query.lastError().text();
    }
}

// 删除重复的initDatabase函数，因为功能已经合并到sqlite_Init中

bool Login::registerUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    // 包含所有字段的插入语句
    query.prepare("INSERT INTO user (username, password, highest_score, coins, "
                 "props_boom, props_row, props_col, props_color) "
                 "VALUES (?, ?, 0, 100, 0, 0, 0, 0)");
    query.addBindValue(username);
    query.addBindValue(password);
    
    return query.exec();
}

void Login::on_btn_signin_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    
    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录错误", "用户名和密码不能为空！");
        return;
    }
    
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    
    if(query.exec()) {
        if(query.next()) {
            currentUsername = username;
            isGuest = false;
            
            // 确保关卡配置和进度表都已创建
            QSqlQuery checkQuery;
            checkQuery.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='level_config'");
            if(!checkQuery.next()) {
                sqlite_Init(); // 如果表不存在，重新初始化数据库
            }
            
            // 初始化用户的关卡进度
            LevelManager::initUserProgress(username);
            
            QMessageBox::information(this, "登录成功", "欢迎回来！");
            emit loginSuccess();
            this->hide();
        } else {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        }
    } else {
        // 使用数据库错误文本进行判断
        QString errorText = query.lastError().text();
        if(errorText.contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "登录失败", "用户名已存在！");
        } else {
            QMessageBox::warning(this, "登录失败", "未知错误：" + errorText);
        }
    }
}

void Login::showAndReset()
{
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    this->show();
}

void Login::on_btn_signup_clicked()
{
    Signup *s = new Signup;
    connect(s, &Signup::backToLogin, this, &Login::showAndReset);
    connect(s, &Signup::signupSuccess, s, &Signup::deleteLater);
    s->show();
    this->hide();  // 隐藏而不是关闭登录窗口
}

void Login::on_btn_guest_clicked()
{
    guestCounter++;
    currentUsername = QString("Guest_%1").arg(guestCounter);
    isGuest = true;
    
    // 为游客创建临时关卡进度
    LevelManager::initUserProgress(currentUsername);
    
    emit loginSuccess();
    this->hide();
}
