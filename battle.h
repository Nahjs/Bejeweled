#ifndef BATTLE_H
#define BATTLE_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QSlider>

#include "battlegame.h"
#include "Client/chatclient.h"
#include "login.h"  // 添加 login.h 头文件

namespace Ui {
class Battle;
}

class Battle : public QMainWindow
{
    Q_OBJECT

public:
    explicit Battle(ChatClient* client, QWidget *parent = nullptr);
    ~Battle();

private slots:
    void onBackButtonClicked();
    void updateOpponentDisplays(const QStringList& players);

    void handleMessage(const QString &type, const QString &data);

    void handleNewPlayer(const QString& playerId, const QString& playerName);
    void handlePlayerLeft(const QString& playerId);

    // 添加音频控制槽函数
    void on_bgmSlider_valueChanged(int value);
    void on_effectSlider_valueChanged(int value);

signals:
    void battleToStart();  // 返回开始界面的信号

private:
    Ui::Battle *ui;
    ChatClient* m_client;
    BattleGame* m_playerGame;
    QMap<QString, BattleGame*> m_opponentGames;  // 键改为用户名而不是UUID
    QMap<QString, QString> m_opponentIds;        // 用户名到UUID的映射
    QLayout* m_opponentsLayout;  // 改为QLayout*以支持不同类型的布局
    
    // 添加音频控制组件
    QWidget* audioWidget;
    QVBoxLayout* verticalLayout_audio;
    QHBoxLayout* horizontalLayout_bgm;
    QHBoxLayout* horizontalLayout_effect;
    QLabel* label_bgm;
    QLabel* label_effect; 
    QSlider* bgmSlider;
    QSlider* effectSlider;

    void setupUI();
    void resizeOpponentDisplays();
    void clearOpponentDisplays();
    int calculateOptimalcolumns();
};

#endif // BATTLE_H
