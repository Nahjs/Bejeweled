#ifndef BATTLEGAME_H
#define BATTLEGAME_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMap>
#include "nummatrix.h"
#include "Client/chatclient.h"

class BattleGame : public QWidget
{
    Q_OBJECT
public:
    explicit BattleGame(ChatClient* client, QString playerName = "", QWidget *parent = nullptr);
    ~BattleGame();

    void sendMatrixUpdate();
    void setIsOpponent(bool isOpponent, const QString& opponentName = "");
    void updateOpponentMatrix(const QJsonObject& data);
    QString getPlayerName() const { return m_playerName; }

private:
    static const int CELL_SIZE = 40;
    static const int BOARD_SPACING = 20;
    static const int ANIMATION_DURATION = 300;
    static const int MATRIX_SIZE = 7;  // 添加矩阵大小常量
    
    enum class PropType {
        BOOM,
        ROW,
        COLUMN,
        COLOR
    };

    ChatClient* m_client;
    NumMatrix* m_playerMatrix;
    QString m_playerId;
    bool m_hasSelected;
    int m_selectedX;
    int m_selectedY;
    QTimer* m_refreshTimer;
    bool m_gameStarted;
    int m_playerScore;
    QList<QPropertyAnimation*> m_activeAnimations;
    QLabel* m_playerScoreLabel;
    QLabel* m_opponentScoreLabel;
    QLabel* m_statusLabel;
    bool m_isOpponent = false;  // 添加此成员变量
    QTimer* m_updateTimer = nullptr;

    // 新增成员变量
    QString m_playerName;  // 当前玩家名称或对手名称
    QMap<QString, NumMatrix*> m_opponentMatrices;  // 对手名称到矩阵的映射
    QMap<QString, int> m_opponentScores;          // 对手名称到分数的映射
    QMap<QString, QLabel*> m_scoreLabels;         // 对手名称到分数标签的映射

    void initUI();
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void drawMatrix(QPainter& painter, const NumMatrix* matrix, bool isOpponent);
    void drawNumber(QPainter& painter, int x, int y, int number, bool isOpponent);
    QPoint boardToScreen(int x, int y, bool isOpponentBoard);

    void handleEliminationAndDrop();

    QPoint screenToBoard(int x, int y, bool& isOpponentBoard);
    void executeSwapAnimation(int fromX, int fromY, int toX, int toY);
   // void executePropAnimation(int propType, int targetX, int targetY, bool isOpponent = false);
    void sendMove(int fromX, int fromY, int toX, int toY);
    void sendGameState();
    void processGameState(const QString& data);
    void drawGems(QPainter& painter);

    // 辅助函数声明
    QJsonArray MatrixToJson(NumMatrix* matrix);

private slots:
    void updateScore();
    void updateScoreDisplay(const QString& playerName, int score);

    void onRefreshTimeout();
    void handleMessage(const QString& type, const QString& data);
    void onGameMessage(const QString& type, const QString& data);
};

#endif // BATTLEGAME_H
