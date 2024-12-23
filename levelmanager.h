#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QDialog>
#include <QPushButton>
#include <QList>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class LevelManager;
}

class LevelManager : public QDialog {
    Q_OBJECT
    
public:
    explicit LevelManager(QWidget *parent = nullptr);
    ~LevelManager();

    void addTestAccount();

    // 数据库初始化
    static void initDatabase();
    static void updateProgress(const QString& username, int levelId, int score, int stars);
    static bool isLevelUnlocked(const QString& username, int levelId);
    static void initUserProgress(const QString& username); // 新增：初始化用户关卡进度

    // 关卡配置
    struct LevelConfig {
        int levelId;
        int targetScore;
        int timeLimit;
        int mapSize;
        int gemTypes;
        int stepLimit;
        QString specialRules;
    };

signals:
    void backToStart();       // 返回主界面信号
    void levelGameStart();    // 确保只有这一个游戏开始信号

private slots:
    void onLevelButtonClicked();
    void resetProgress();  // 新增：重置进度函数

private:
    // UI相关
    void createLevelButtons();
    void updateLevelButtonStates();
    void loadLevelConfig(int levelId);
    void startLevel(int levelId);

    // 数据库操作
    static void initLevelTable();
    static void initProgressTable();
    
private:
    Ui::LevelManager *ui;
    QList<QPushButton*> levelButtons;
    Mainwindow* gameWindow;

    QTimer *updateTimer;
};

#endif // LEVELMANAGER_H
