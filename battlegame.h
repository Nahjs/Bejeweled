#ifndef BATTLEGAME_H
#define BATTLEGAME_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMap>
#include <QMediaPlayer>
#include <QMutex>

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
    static const int ANIMATION_DELAY = 40;  // 动画延迟时间
    
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
    QLabel* m_statusLabel;  // 仅保留状态标签用于显示对手名字
    bool m_isOpponent = false;  // 添加此成员变量
    QTimer* m_updateTimer = nullptr;

    // 新增成员变量
    QString m_playerName;  // 当前玩家名称或对手名称
    QMap<QString, NumMatrix*> m_opponentMatrices;  // 对手名称到矩阵的映射
    QMap<QString, int> m_opponentScores;          // 对手名称到分数的映射

    QPixmap pixmap_gem[8];          // 宝石图片
    QPixmap pixmap_di;              // 选中框图片
    QPixmap disappear1, disappear2, disappear3;  // 消除动画
    QPixmap number[10];             // 数字图片
    QMediaPlayer* greatSound;
    QMediaPlayer* excellentSound;
    QMediaPlayer* amazingSound;
    QMediaPlayer* unbelievableSound;
    QAudioOutput* effectAudioOutput;

    void initSoundEffects();
    void playSoundEffect(QMediaPlayer* effect);
    void updateGemTheme(QString path);
    void drawGemWithEffects(QPainter& painter, int i, int j, int num);
    void setupAudioSystem();
    
    // 动画相关
    int midSituation[8][8];         // 消除动画状态
    bool isSelected[8][8];          // 选中状态
    int addScoreSituation;          // 加分动画状态
    static const int scoreStep = 5;  // 分数动画步长
    static const int scoreOffsetX = 10;  // 分数X偏移
    static const int scoreOffsetY = -20;  // 分数Y偏移

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

public slots:
    void updateBackgroundMusic(float volume);
    void updateMuteState(bool muted);

private:
    int m_totalEliminateCount = 0;  // 添加总消除计数器

    // 修改布局常量
    static constexpr int GAME_AREA_WIDTH = 450;  // 游戏区域固定宽度
    static constexpr int GAME_AREA_HEIGHT = 480; // 游戏区域固定高度
    static constexpr int OFFSET_X = 60;          // 游戏区域X偏移
    static constexpr int OFFSET_Y = 80;         // 游戏区域Y偏移
    static constexpr int SCORE_OFFSET_X = 0;    // 分数显示X偏移
    static constexpr int SCORE_OFFSET_Y = 0;    // 分数显示Y偏移

    int m_cellSize;  // 动态计算的单元格大小

    QPoint point;         // 存储第一次点击的位置
    int focus = 0;        // 点击状态标志
    bool hintUsedThisRound = false;  // 提示使用标志
    
public slots:
    void updateMapSize(int rows, int cols);  // 添加更新地图大小的槽函数

private:
    QMutex m_resourceMutex;            // 资源互斥锁
    QMutex m_updateMutex;              // 更新互斥锁
    QAtomicInt m_animationInProgress;  // 动画状态标志
    bool m_resourcesLoaded = false;     // 资源加载状态标志

    // 添加辅助方法
    bool beginAnimation() {
        if (m_animationInProgress.loadAcquire()) return false;
        m_animationInProgress.storeRelease(true);
        return true;
    }
    
    void endAnimation() {
        m_animationInProgress.storeRelease(false);
    }
    
    void safeUpdate();

    void checkAndLoadResources() {
        QMutexLocker locker(&m_resourceMutex);
        if (!m_resourcesLoaded) {
            updateGemTheme(":/res/images/a");
        }
    }

    // 添加handleComboBonus声明
    void handleComboBonus();
    void handleAnimationStage(int stage, QVector<QPair<int, int>>& eliminatedCells);
};

#endif // BATTLEGAME_H
