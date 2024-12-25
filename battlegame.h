#ifndef BATTLEGAME_H
#define BATTLEGAME_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "numMatrix.h"
#include "Client/chatclient.h"
#include <QPropertyAnimation>

class BattleGame : public QWidget {
    Q_OBJECT

public:
    explicit BattleGame(ChatClient* client, QWidget *parent = nullptr);
    ~BattleGame();

private:
    static const int CELL_SIZE = 40;  // 每个宝石的大小
    static const int BOARD_SPACING = 100;  // 两个矩阵之间的间距
    
    ChatClient* m_client;
    NumMatrix* m_playerMatrix;    // 玩家的数字矩阵
    NumMatrix* m_opponentMatrix;  // 对手的数字矩阵
    QString m_playerId;  // 添加玩家ID
    QTimer* m_refreshTimer;      // 刷新定时器
    
    int m_playerScore;
    int m_opponentScore;
    bool m_gameStarted;
    bool m_isMyTurn;
    
    // UI元素
    QLabel* m_playerScoreLabel;
    QLabel* m_opponentScoreLabel;
    QLabel* m_statusLabel;
    
    // 选中的宝石位置
    int m_selectedX;
    int m_selectedY;
    bool m_hasSelected;

    QList<QPropertyAnimation*> m_activeAnimations;
    
    void executeSwapAnimation(int fromX, int fromY, int toX, int toY);
    void executePropAnimation(int propType, int targetX, int targetY, bool isOpponent = false);  // 添加 isOpponent 参数

    void handleMessage(const QString &type, const QString &data);

    void updateOpponentMatrix(const QJsonObject &data);

    void sendGameState();

    void createExplosionEffect(int x, int y);
    void createRowClearEffect(int row);
    void updateAnimations();
    
    // 动画相关的属性
    const int ANIMATION_DURATION = 300;  // 动画持续时间(ms)
    const int REFRESH_INTERVAL = 16;     // 刷新间隔(约60fps)

    void initUI();
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void processGameState(const QString& data);
    void sendMove(int fromX, int fromY, int toX, int toY);
    void sendMatrixUpdate();  // 发送矩阵更新到服务器
    QPoint boardToScreen(int x, int y, bool isOpponentBoard);
    QPoint screenToBoard(int x, int y, bool& isOpponentBoard);
    void drawGem(QPainter& painter, int x, int y, int type, bool isOpponent);
    void drawBoard(QPainter& painter, const NumMatrix* board, bool isOpponent);
    void drawNumber(QPainter& painter, int x, int y, int number, bool isOpponent);
    void drawMatrix(QPainter& painter, const NumMatrix* matrix, bool isOpponent);

private slots:
    void onGameMessage(const QString& type, const QString& data);
    void onRefreshTimeout();
};

#endif // BATTLEGAME_H
