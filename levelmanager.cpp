#include "levelmanager.h"
#include "ui_levelmanager.h"
#include "login.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>

LevelManager::LevelManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelManager)
{
    ui->setupUi(this);
    setWindowTitle("选择关卡");
    
    gameWindow = new Mainwindow(this);
    
    // 修改信号连接
    connect(gameWindow, &Mainwindow::gameToStart, this, &LevelManager::show);
    connect(ui->btn_back, &QPushButton::clicked, this, [this]() {
        this->hide();
        emit backToStart();
    });
    
    // 连接所有关卡按钮的信号
    connect(ui->btn_level_1, &QPushButton::clicked, this, [this](){ loadLevelConfig(1); });
    connect(ui->btn_level_2, &QPushButton::clicked, this, [this](){ loadLevelConfig(2); });
    connect(ui->btn_level_3, &QPushButton::clicked, this, [this](){ loadLevelConfig(3); });
    connect(ui->btn_level_4, &QPushButton::clicked, this, [this](){ loadLevelConfig(4); });
    connect(ui->btn_level_5, &QPushButton::clicked, this, [this](){ loadLevelConfig(5); });
    connect(ui->btn_level_6, &QPushButton::clicked, this, [this](){ loadLevelConfig(6); });
    connect(ui->btn_level_7, &QPushButton::clicked, this, [this](){ loadLevelConfig(7); });
    connect(ui->btn_level_8, &QPushButton::clicked, this, [this](){ loadLevelConfig(8); });
    connect(ui->btn_level_9, &QPushButton::clicked, this, [this](){ loadLevelConfig(9); });
    connect(ui->btn_level_10, &QPushButton::clicked, this, [this](){ loadLevelConfig(10); });
    
    // 连接返回和重置按钮
    connect(ui->btn_back, &QPushButton::clicked, this, &LevelManager::close);
    connect(ui->btn_reset, &QPushButton::clicked, this, &LevelManager::resetProgress);
    
    updateLevelButtonStates();
    // 添加测试账户
    addTestAccount();
}

LevelManager::~LevelManager()
{
    delete ui;
    // gameWindow作为子对象会自动删除
}

void LevelManager::addTestAccount()
{
    QSqlQuery query;

    // 添加测试账户
    query.prepare("INSERT OR IGNORE INTO user (username, password) VALUES (?, ?)");
    query.addBindValue("t");
    query.addBindValue("1");
    if (!query.exec()) {
        qDebug() << "添加测试账户失败:" << query.lastError().text();
        return;
    }

    // 初始化测试账户的关卡进度
    for (int levelId = 1; levelId <= 10; levelId++) {
        query.prepare("INSERT OR IGNORE INTO user_progress (username, level_id, highest_score, stars, completed) "
                      "VALUES (?, ?, 0, 0, 1)");
        query.addBindValue("t");
        query.addBindValue(levelId);
        if (!query.exec()) {
            qDebug() << "初始化测试账户关卡" << levelId << "失败:" << query.lastError().text();
        }
    }

    qDebug() << "测试账户:t，密码为1，\n闯关模式测试完成后请在LevelManager::updateLevelButtonStates取消对关卡按钮的禁用注释";
}

void LevelManager::initDatabase()
{
    // 确保按正确顺序创建表
    QSqlQuery query;
    
    // 1. 先创建关卡配置表
    initLevelTable();
    
    // 1. 先创建关卡配置表
    query.exec("CREATE TABLE IF NOT EXISTS user_progress ("
              "username TEXT, "
              "level_id INTEGER, "
              "highest_score INTEGER DEFAULT 0, "
              "username TEXT, "
              "level_id INTEGER, "
              "highest_score INTEGER DEFAULT 0, "
              "stars INTEGER DEFAULT 0, "
              "completed BOOLEAN DEFAULT 0, "
              "FOREIGN KEY(username) REFERENCES user(username), "
              "FOREIGN KEY(level_id) REFERENCES level_config(level_id), "
              "PRIMARY KEY(username, level_id))");
              
    if(query.lastError().isValid()) {
        qDebug() << "创建进度表时出错:" << query.lastError().text();
    }
}

void LevelManager::initLevelTable()
{
    QSqlQuery query;
    
    // 添加调试输出
    qDebug() << "正在检查关卡配置表...";
    
    // 先显式创建表
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
    
    // 检查表是否为空
    query.exec("SELECT COUNT(*) FROM level_config");
    if(query.next() && query.value(0).toInt() == 0) {
        qDebug() << "关卡配置表为空，开始插入数据...";
        
        // 添加初始关卡数据
        const struct {
            int id, score, time, size, gems, steps;
            QString rules;
        } levels[] = {
            {1, 800, 120, 6, 5, 15, "新手关卡：\n完成一次三消\n达到目标分数"},
            {2, 1500, 100, 6, 6, 12, "完成一次四连消除\n达到目标分数"},
            {3, 2000, 90, 7, 6, 20, "限时挑战：\n90秒内达到目标分数\n完成3次连击"},
            {4, 2500, 120, 7, 6, 15, "特殊任务：\n消除25个红宝石\n使用爆炸道具2次"},
            {5, 3000, 120, 7, 6, 18, "道具大师：\n使用3种不同道具\n完成一次五连消除"},
            {6, 3500, 150, 8, 6, 20, "连击达人：\n完成6连消除\n达成5次连击"},
            {7, 4000, 60, 7, 6, 25, "极限挑战：\n60秒内达到目标分数\n使用所有道具各一次"},
            {8, 5000, 180, 9, 7, 30, "终极试炼：\n大地图挑战\n完成一次七连消除"},
            {9, 6000, 150, 8, 7, 25, "宝石大师：\n消除每种宝石各20个\n使用每种道具2次"},
            {10, 8000, 180, 9, 8, 35, "最终关卡：\n完成所有特殊任务\n达到目标分数"}
        };

        for (const auto& level : levels) {
            query.prepare("INSERT OR IGNORE INTO level_config VALUES (?,?,?,?,?,?,?)");
            query.addBindValue(level.id);
            query.addBindValue(level.score);
            query.addBindValue(level.time);
            query.addBindValue(level.size);
            query.addBindValue(level.gems);
            query.addBindValue(level.rules);
            query.addBindValue(level.steps);
            query.exec();
        }
        
        qDebug() << "关卡数据插入完成";
    } else {
        qDebug() << "关卡配置表已存在且有数据";
    }
}

void LevelManager::initUserProgress(const QString& username)
{
    QSqlQuery query;
    
    // 先检查表是否存在
    if(!query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='user_progress'")) {
        qDebug() << "检查进度表失败:" << query.lastError().text();
        return;
    }
    
    // 确保表存在
    if(!query.next()) {
        initDatabase();
    }
    
    // 删除已有记录
    query.prepare("DELETE FROM user_progress WHERE username = ?");
    query.addBindValue(username);
    query.exec();
    
    // 为用户创建所有关卡的进度记录
    for(int levelId = 1; levelId <= 10; levelId++) {
        query.prepare("INSERT INTO user_progress "
                     "(username, level_id, highest_score, stars, completed) "
                     "VALUES (?, ?, 0, 0, ?)");
        query.addBindValue(username);
        query.addBindValue(levelId);
        query.addBindValue(levelId == 1 ? 1 : 0); // 第一关默认解锁
        
        if(!query.exec()) {
            qDebug() << "初始化关卡" << levelId << "失败："
                     << query.lastError().text()
                     << "\nSQL:" << query.lastQuery()
                     << "\nBound values:"
                     << "\nusername:" << username
                     << "\nlevelId:" << levelId;
        }
    }
}

void LevelManager::resetProgress()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "重置进度",
                                "确定要重置所有关卡进度吗？\n此操作不可恢复！",
                                QMessageBox::Yes|QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("UPDATE user_progress SET highest_score = 0, stars = 0, completed = 0 "
                     "WHERE username = ?");
        query.addBindValue(Login::currentUsername);
        
        if (query.exec()) {
            // 重新初始化第一关
            query.prepare("UPDATE user_progress SET completed = 1 WHERE username = ? AND level_id = 1");
            query.addBindValue(Login::currentUsername);
            query.exec();
            
            updateLevelButtonStates();
            QMessageBox::information(this, "重置成功", "关卡进度已重置！");
        }
    }
}

void LevelManager::updateLevelButtonStates()
{
    // 禁用所有按钮
    QList<QPushButton*> levelButtons = {
        ui->btn_level_1, ui->btn_level_2, ui->btn_level_3, ui->btn_level_4, ui->btn_level_5,
        ui->btn_level_6, ui->btn_level_7, ui->btn_level_8, ui->btn_level_9, ui->btn_level_10
    };

    //待取消禁用
    /*for (auto btn : levelButtons) {
        btn->setEnabled(false);
    }
    
*/

    // 第一关始终开放
    ui->btn_level_1->setEnabled(true);

    // 查询已完成的关卡
    QSqlQuery query;
    query.prepare("SELECT level_id, highest_score, stars FROM user_progress "
                 "WHERE username = ? AND completed = 1");
    query.addBindValue(Login::currentUsername);
    
    if (query.exec()) {
        int totalStars = 0;
        int completedLevels = 0;
        
        while (query.next()) {
            int levelId = query.value(0).toInt();
            int score = query.value(1).toInt();
            int stars = query.value(2).toInt();
            
            // 更新对应关卡按钮和显示
            if (levelId <= 10 && levelId > 0) {
                levelButtons[levelId-1]->setEnabled(true);
                // 如果有下一关，也解锁下一关
                if (levelId < 10) {
                    levelButtons[levelId]->setEnabled(true);
                }
            }
            
            totalStars += stars;
            completedLevels++;
        }
        
        // 更新总进度显示
        ui->label_total_progress->setText(QString("已完成关卡：%1/10").arg(completedLevels));
        ui->label_total_stars->setText(QString("总星数：%1/30").arg(totalStars));
    }

    // 游客模式限制
    if (Login::isGuest) {
        for (int i = 1; i < levelButtons.size(); i++) {
            levelButtons[i]->setEnabled(false);
        }
    }
}

void LevelManager::onLevelButtonClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn) {
        int levelId = btn->property("levelId").toInt();
        loadLevelConfig(levelId);
    }
}

void LevelManager::loadLevelConfig(int levelId)
{
    QSqlQuery query;
    query.prepare("SELECT target_score, time_limit, map_size, gem_types, special_rules, step_limit "
                 "FROM level_config WHERE level_id = ?");
    query.addBindValue(levelId);
    
    if(query.exec() && query.next()) {
        int targetScore = query.value(0).toInt();
        int timeLimit = query.value(1).toInt();
        int mapSize = query.value(2).toInt();
        int gemTypes = query.value(3).toInt();
        QString rules = query.value(4).toString();
        int stepLimit = query.value(5).toInt();
        
        if(QMessageBox::information(this, QString("第%1关").arg(levelId),
            QString("目标分数：%1\n时间限制：%2秒\n特殊规则：%3\n步数限制：%4\n\n是否开始游戏？")
            .arg(targetScore).arg(timeLimit).arg(rules).arg(stepLimit),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            
            startLevel(levelId);
        }
    }
}

void LevelManager::startLevel(int levelId)
{
    if(gameWindow) {
        gameWindow->setLevelMode(true);  // 假设Mainwindow类中有这个方法
        
        QSqlQuery query;
        query.prepare("SELECT target_score, time_limit, map_size, gem_types, step_limit "
                     "FROM level_config WHERE level_id = ?");
        query.addBindValue(levelId);
        
        if(query.exec() && query.next()) {
            int targetScore = query.value(0).toInt();
            int timeLimit = query.value(1).toInt();
            int mapSize = query.value(2).toInt();
            int gemTypes = query.value(3).toInt();
            int stepLimit = query.value(4).toInt();
            
            // 更新参数数量以匹配新的函数签名
            gameWindow->setLevelConfig(levelId, targetScore, timeLimit, mapSize, gemTypes, stepLimit);
            this->hide();
            gameWindow->show();
            gameWindow->Game_start();
            emit levelGameStart();
        }
    }
}

// ... 其余方法的实现 ...

