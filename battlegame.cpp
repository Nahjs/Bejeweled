#include "battlegame.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <thread>
#include <chrono>
#include <QApplication>
#include <QAudioOutput>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QThread>
#include <QUuid>  // 用于生成唯一ID

#include "login.h"
#include "setup.h"

BattleGame::BattleGame(ChatClient* client, QString playerName, QWidget *parent) 
    : QWidget(parent), m_client(client), m_hasSelected(false), m_playerName(playerName)
{
    // 生成唯一的玩家ID
    m_playerId = QUuid::createUuid().toString();
    
    m_playerMatrix = new NumMatrix();
    // 移除 m_opponentMatrix 的初始化
    
    // 设置矩阵大小并初始化
    m_playerMatrix->setMapSize(7, 7);  // 设置7x7的大小
    m_playerMatrix->BuildMap(5);  // 初始化玩家矩阵
 
    
    // 设置游戏运行状态为true
    m_playerMatrix->setgamerunning(true);
    m_gameStarted = true;  // 测试时直接设置为开始状态？匹配机制？
    
    m_refreshTimer = new QTimer(this);
    m_playerScore = 0;
    // 移除 m_opponentScore = 0; 不再需要
    
    // 设置定时器，50ms刷新一次
    connect(m_refreshTimer, &QTimer::timeout, this, &BattleGame::onRefreshTimeout);
    m_refreshTimer->start(50);
    
    // 连接游戏消息处理
    connect(m_client, &ChatClient::messageReceived, this, &BattleGame::handleMessage);
    connect(m_client, &ChatClient::connected, this, [this]() {
        // 连接成功后立即发送初始矩阵状态
        QTimer::singleShot(100, this, [this]() {
            sendMatrixUpdate();
        });
    });
    
    initUI();
    
    // 发送开始游戏请求和初始矩阵状态
    m_client->sendMessage("GAME", "");
    sendMatrixUpdate();  // 发送初始矩阵状态

    qDebug() << "Game initialized with matrix size:" << m_playerMatrix->MAPROWNUM << "x" << m_playerMatrix->MAPCOLNUM;

    // 创建定时器，每200ms发送一次矩阵更新
  /*  m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &BattleGame::sendMatrixUpdate);
    m_updateTimer->start(200);*/

    // 初始化图片资源
    updateGemTheme(":/res/images/a");
    pixmap_di.load(":/res/images/select.png");
    disappear1.load(":/res/images/tx1.png");
    disappear2.load(":/res/images/tx2.png");
    disappear3.load(":/res/images/tx3.png");

    for(int i = 0; i < 10; i++) {
        QString path = ":/res/images/number" + QString::number(i) + ".png";
        number[i].load(path);
    }

    // 初始化动画状态数组
    memset(midSituation, 0, sizeof(midSituation));
    memset(isSelected, 0, sizeof(isSelected));
    addScoreSituation = 0;

    // 初始化音效系统
    setupAudioSystem();
    initSoundEffects();

    // 设置固定大小
    setMinimumWidth(GAME_AREA_WIDTH + 2 * OFFSET_X);
    setMinimumHeight(GAME_AREA_HEIGHT + OFFSET_Y + SCORE_OFFSET_Y);
    
    // 计算初始单元格大小
    m_cellSize = GAME_AREA_WIDTH / m_playerMatrix->MAPCOLNUM;
}

// 修改析构函数确保清理所有动画
BattleGame::~BattleGame() {
    // 停止并删除所有活跃的动画
    while (!m_activeAnimations.isEmpty()) {
        QPropertyAnimation* animation = m_activeAnimations.takeFirst();
        animation->stop();
        delete animation;
    }

    // ...existing cleanup code...
    // 清理动态分配的资源
    delete m_playerMatrix;
    // 清理所有对手矩阵
    qDeleteAll(m_opponentMatrices);
    m_opponentMatrices.clear();
    delete m_refreshTimer;

    // 清理所有活跃的动画
    for(QPropertyAnimation* animation : m_activeAnimations) {
        animation->stop();
        delete animation;
    }
    m_activeAnimations.clear();
}

void BattleGame::initUI() {
    setMinimumSize(800, 400);
    
    // 只保留状态标签用于显示对手名字
    m_statusLabel = new QLabel(this);
    m_statusLabel->setStyleSheet("QLabel { color: black; font-size: 14px; }");
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->move(350, 10);
}

void BattleGame::paintEvent(QPaintEvent* event) {
    if (!m_resourcesLoaded) {
        checkAndLoadResources();
        if (!m_resourcesLoaded) {
            QPainter painter(this);
            painter.fillRect(rect(), Qt::lightGray);
            painter.drawText(rect(), Qt::AlignCenter, "加载资源中...");
            return;
        }
    }

    static bool painting = false;
    if (painting) return;
    
    painting = true;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 使用新的布局参数
    NumMatrix* matrix = m_isOpponent ? m_opponentMatrices[m_playerName] : m_playerMatrix;
    if (!matrix) {
        painting = false;
        return;
    }

    // 计算实际绘制位置
    int offsetX = OFFSET_X;
    int offsetY = OFFSET_Y;
    
    if (m_isOpponent) {
        // 对手的矩阵使用较小的显示尺寸
        m_cellSize = std::min(200 / matrix->MAPCOLNUM, 200 / matrix->MAPROWNUM);
        offsetX = (width() - matrix->MAPCOLNUM * m_cellSize) / 2;
        offsetY = (height() - matrix->MAPROWNUM * m_cellSize) / 2;
    }

    // 绘制底色背景
  /*  painter.fillRect(offsetX, offsetY,
                    matrix->MAPCOLNUM * m_cellSize,
                    matrix->MAPROWNUM * m_cellSize,
                    QColor(200, 200, 200));
*/
    // 修改宝石绘制逻辑
    for (int i = 0; i < matrix->MAPROWNUM; i++) {
        for (int j = 0; j < matrix->MAPCOLNUM; j++) {
            int num = matrix->GetNum(i, j);
            if (num <= 0 || num > 8) continue;
            
            QRect destRect(
                offsetX + j * m_cellSize,
                offsetY + i * m_cellSize,
                m_cellSize - 2,
                m_cellSize - 2
            );
            
            // 直接绘制原始图片
            if (!pixmap_gem[num - 1].isNull()) {
                painter.drawPixmap(destRect, pixmap_gem[num - 1]);
            }

            // 绘制选中框
            if (isSelected[i][j] && !pixmap_di.isNull()) {
                painter.drawPixmap(destRect, pixmap_di);
            }

            // 绘制消除动画效果
            if (midSituation[i][j] > 0) {
                const QPixmap* effectPixmap = nullptr;
                switch(midSituation[i][j]) {
                    case 1: effectPixmap = &disappear1; break;
                    case 2: effectPixmap = &disappear2; break;
                    case 3: effectPixmap = &disappear3; break;
                }
                
                if (effectPixmap && !effectPixmap->isNull()) {
                    painter.drawPixmap(destRect, *effectPixmap);
                    
                    if (midSituation[i][j] == 3) {
                        // 加分动画
                        if (addScoreSituation >= 0 && addScoreSituation <= 9) {
                            int x = scoreOffsetX + j * m_cellSize + (addScoreSituation + 1) * scoreStep;
                            int y = scoreOffsetY + i * m_cellSize - (addScoreSituation + 1) * scoreStep;
                            // 只在确认数字图片存在时绘制
                            if (!number[1].isNull()) {
                                painter.drawPixmap(x, y, 10, 20, number[1]);
                                if (!number[0].isNull()) {
                                    painter.drawPixmap(x + 20, y, 10, 20, number[0]);
                                }
                            }
                        }
                        midSituation[i][j] = 0;
                    }
                }
            }
        }
    }

    // 绘制计分板
    QString scoreStr = m_isOpponent ? 
        QString::number(m_opponentScores[m_playerName]) : 
        QString::number(m_playerScore);

    // 绘制分数时检查图片有效性
    for (int i = 0; i < scoreStr.length(); i++) {
        int digit = scoreStr[i].digitValue();
        if (digit >= 0 && digit < 10 && !number[digit].isNull()) {
            painter.drawPixmap(200 + i * 25, 0, 25, 50, number[digit]);
        }
    }

    // 如果是对手实例，绘制玩家名称
    if (m_isOpponent) {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, m_playerName);
    }
    
    painting = false;
}

void BattleGame::drawMatrix(QPainter& painter, const NumMatrix* matrix, bool) {
    // 移除对手矩阵的偏移量，始终在中心绘制
    int offsetX = (width() - matrix->MAPCOLNUM * CELL_SIZE) / 2;
    int offsetY = (height() - matrix->MAPROWNUM * CELL_SIZE) / 2;

    // 绘制矩阵底色
    painter.fillRect(offsetX, offsetY,
                    matrix->MAPCOLNUM * CELL_SIZE,
                    matrix->MAPROWNUM * CELL_SIZE,
                    QColor(200, 200, 200));

    // 绘制数字
    for(int i = 0; i < matrix->MAPROWNUM; i++) {
        for(int j = 0; j < matrix->MAPCOLNUM; j++) {
            drawNumber(painter, j, i, matrix->GetNum(i, j), false);
        }
    }
}

void BattleGame::drawNumber(QPainter& painter, int x, int y, int number, bool isOpponent) {
    QPoint pos = boardToScreen(x, y, isOpponent);

    // 根据数字选择不同的显示样式
    QColor color;
    switch(number) {
        case 1: color = Qt::red; break;
        case 2: color = Qt::blue; break;
        case 3: color = Qt::green; break;
        case 4: color = Qt::yellow; break;
        case 5: color = Qt::magenta; break;
        default: return;
    }

    // 绘制数字背景
    painter.fillRect(pos.x(), pos.y(), CELL_SIZE-2, CELL_SIZE-2, color);

    // 绘制数字
    painter.setPen(Qt::white);
    painter.drawText(QRect(pos.x(), pos.y(), CELL_SIZE, CELL_SIZE),
                    Qt::AlignCenter, QString::number(number));
}

QPoint BattleGame::screenToBoard(int x, int y, bool& isOpponentBoard) {
    int offsetX = m_isOpponent ? (width() - m_playerMatrix->MAPCOLNUM * m_cellSize) / 2 : OFFSET_X;
    int offsetY = m_isOpponent ? (height() - m_playerMatrix->MAPROWNUM * m_cellSize) / 2 : OFFSET_Y;
    
    int relX = x - offsetX;
    int relY = y - offsetY;
    
    if (relX < 0 || relY < 0 || 
        relX >= m_playerMatrix->MAPCOLNUM * m_cellSize || 
        relY >= m_playerMatrix->MAPROWNUM * m_cellSize) {
        return QPoint(-1, -1);
    }
    
    return QPoint(relX / m_cellSize, relY / m_cellSize);
}

void BattleGame::mousePressEvent(QMouseEvent* event) {
    if (!m_gameStarted || m_animationInProgress.loadAcquire()) {
        return;
    }

    // 计算点击位置（使用新的布局参数）
    int xx = event->pos().x() - OFFSET_X;
    int yy = event->pos().y() - OFFSET_Y;

    // 修改坐标计算方式
    int focus_y = xx / m_cellSize;
    int focus_x = yy / m_cellSize;

    qDebug() << "Raw coordinates:" << xx << "," << yy;
    qDebug() << "Cell size:" << m_cellSize;
    qDebug() << "Matrix size:" << m_playerMatrix->MAPROWNUM << "x" << m_playerMatrix->MAPCOLNUM;

    // 检查边界
    if(focus_x < 0 || focus_x >= m_playerMatrix->MAPROWNUM ||
       focus_y < 0 || focus_y >= m_playerMatrix->MAPCOLNUM) {
        qDebug() << "Out of bounds click";
        return;
    }

    qDebug() << "Click at matrix position:" << focus_x << "," << focus_y;

    // 处理第一次点击
    if(focus == 0) {
        memset(isSelected, 0, sizeof(isSelected));
        point.setX(focus_x);
        point.setY(focus_y);
        isSelected[focus_x][focus_y] = true;
        qDebug() << "First click - Selected position:" << focus_x << "," << focus_y;
        focus = 1;
        update();
        return;
    }

    // 处理第二次点击
    int x = point.x();
    int y = point.y();
    
    // 检查是否相邻
    if ((focus_x == x && abs(focus_y - y) == 1) ||
        (focus_y == y && abs(focus_x - x) == 1)) {
        
        qDebug() << "Attempting swap between (" << x << "," << y << ") and ("
                 << focus_x << "," << focus_y << ")";
        
        // 尝试交换
        if (m_playerMatrix->swap(x, y, focus_x, focus_y)) {
            qDebug() << "Swap successful, handling elimination";
            handleEliminationAndDrop();
        } else {
            qDebug() << "Swap failed - no valid elimination possible";
        }
        
        focus = 0;  // 重置选中状态
    } else {
        // 不相邻，更新选中位置
        memset(isSelected, 0, sizeof(isSelected));
        point.setX(focus_x);
        point.setY(focus_y);
        isSelected[focus_x][focus_y] = true;
        focus = 1;
        qDebug() << "Not adjacent - new selection at:" << focus_x << "," << focus_y;
    }

    // 发送更新到服务器
    sendMatrixUpdate();
    update();
}

void BattleGame::onGameMessage(const QString& type, const QString& data) {
    qDebug() << "\n=== Game Message Received ===";
    qDebug() << "Type:" << type;
    qDebug() << "Data:" << data;

    if (type == "SYNC") {
        QStringList parts = data.split(',');
        qDebug() << "Received matrix sync message:";
        qDebug() << "Data parts count:" << parts.size();

        // 首先尝试解析为 JSON
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QString username = obj["username"].toString();
            
            if (!m_opponentMatrices.contains(username)) {
                return;
            }
            NumMatrix* matrix = m_opponentMatrices[username];
            
            if (obj.contains("matrix") && obj["matrix"].isArray()) {
                QJsonArray jsonMatrix = obj["matrix"].toArray();
                // 更新矩阵数据
                updateOpponentMatrix(obj);
            }
        } else {
            // 如果不是 JSON 格式，使用旧的分割字符串方式处理
            if (!m_opponentMatrices.contains(m_playerName)) {
                return;
            }
            NumMatrix* matrix = m_opponentMatrices[m_playerName];
            
            if (parts.size() >= 2 + matrix->MAPROWNUM * matrix->MAPCOLNUM) {
                // 更新对手分数
                m_opponentScores[m_playerName] = parts[0].toInt();
                qDebug() << "Opponent score updated to:" << m_opponentScores[m_playerName];

                // 更新对手矩阵
                int index = 1;
                qDebug() << "Updating opponent matrix:";
                for(int i = 0; i < matrix->MAPROWNUM; i++) {
                    QString row;
                    for(int j = 0; j < matrix->MAPCOLNUM; j++) {
                        int value = parts[index++].toInt();
                        matrix->SetNum(i, j, value);
                        row += QString::number(value) + " ";
                    }
                    qDebug() << "Row" << i << ":" << row;
                }

                updateScoreDisplay(m_playerName, m_opponentScores[m_playerName]);
                update();
            }
        }
    }
    // ...existing code...
    else if (type == "SWAP") {
        // 处理交换消息
        QStringList parts = data.split(',');
        if (parts.size() >= 4) {
            int fromX = parts[0].toInt();
            int fromY = parts[1].toInt();
            int toX = parts[2].toInt();
            int toY = parts[3].toInt();

            // 执行本地交换
            if (m_playerMatrix->swap(fromY, fromX, toY, toX)) {
                // 处理消除和下落
                bool hasChanges = false;
                while (m_playerMatrix->eliminate()) {
                    m_playerMatrix->down();
                    hasChanges = true;
                }
                update();
            }
        }
    }
    else if (type == "PROP_USE") {
        // 处理道具使用消息
        QStringList parts = data.split(',');
        if (parts.size() >= 3) {
            int propType = parts[0].toInt();
            int targetX = parts[1].toInt();
            // 执行道具效果动画
            int targetY = parts[2].toInt();
            
            // 执行道具效果动画
          //  executePropAnimation(propType, targetX, targetY);
        }
    }
    update(); // 重绘画面
}

void BattleGame::processGameState(const QString& data) {
    QStringList parts = data.split(',');
    // 使用 NumMatrix 的尺寸替代 BOARD_SIZE
    if (parts.size() < m_playerMatrix->MAPROWNUM * m_playerMatrix->MAPCOLNUM + 4) return;
    
    m_playerScore = parts[1].toInt();
    // 更新特定对手的分数
    if (m_isOpponent && m_opponentMatrices.contains(m_playerName)) {
        m_opponentScores[m_playerName] = parts[2].toInt();
        updateScoreDisplay(m_playerName, m_opponentScores[m_playerName]);
    }
    m_gameStarted = !parts[3].toInt();
    
    // 更新分数显示
    m_playerScoreLabel->setText(QString("Your Score: %1").arg(m_playerScore));
    
    // 不再需要这行，因为分数显示已经在updateScoreDisplay中处理
    // m_opponentScoreLabel->setText(QString("Opponent Score: %1").arg(m_opponentScore));
    
    // 更新矩阵数据
    int index = 4;
    for(int i = 0; i < m_playerMatrix->MAPROWNUM; i++) {
        for(int j = 0; j < m_playerMatrix->MAPCOLNUM; j++) {
            m_playerMatrix->SetNum(i, j, parts[index].toInt());
            index++;
        }
    }
}

void BattleGame::sendMove(int fromX, int fromY, int toX, int toY) {
    QString moveData = QString("%1 %2 %3 %4").arg(fromX).arg(fromY).arg(toX).arg(toY);
    m_client->sendMessage("MOVE", moveData);
}

QJsonArray BattleGame::MatrixToJson(NumMatrix* matrix) 
{
    QJsonArray jsonMatrix;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        QJsonArray row;
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            row.append(matrix->GetNum(i, j));
        }
        jsonMatrix.append(row);
    }
    return jsonMatrix;
}

void BattleGame::sendMatrixUpdate() 
{
    if (m_isOpponent) return;  // 对手实例不发送更新

    QJsonObject data;
    data["matrix"] = MatrixToJson(m_playerMatrix);  // 使用玩家矩阵
    data["username"] = Login::currentUsername;
    data["playerId"] = m_playerId;
    data["score"] = m_playerScore;  // 使用现有的分数变量
    data["timestamp"] = QDateTime::currentMSecsSinceEpoch();

    QJsonDocument doc(data);
    QString jsonStr = doc.toJson(QJsonDocument::Compact);
    m_client->sendMessage("MATRIX_SYNC", jsonStr);
}

QPoint BattleGame::boardToScreen(int x, int y, bool isOpponentBoard) {
    int offsetX = isOpponentBoard ? 
        (width() - m_playerMatrix->MAPCOLNUM * m_cellSize) / 2 : OFFSET_X;
    int offsetY = isOpponentBoard ? 
        (height() - m_playerMatrix->MAPROWNUM * m_cellSize) / 2 : OFFSET_Y;
    
    return QPoint(
        offsetX + x * m_cellSize,
        offsetY + y * m_cellSize
    );
}
/*
void BattleGame::handleEliminationAndDrop() {
    static QMutex animationMutex;
    QMutexLocker locker(&animationMutex);

    // 检查状态
    if (!m_resourcesLoaded || !m_playerMatrix || m_animationInProgress.loadAcquire()) {
        return;
    }

    m_animationInProgress.storeRelease(true);
    m_totalEliminateCount = 0;

    try {
        bool hasMoreEliminations;
        do {
            hasMoreEliminations = false;

            // 执行一次消除循环
            if (m_playerMatrix->eliminate(false)) {
                int eliminateNumber = 0;
                QVector<QPair<int, int>> eliminatedCells;

                {
                    QMutexLocker matrixLocker(&m_resourceMutex);
                    memset(midSituation, 0, sizeof(midSituation));

                    // 收集需要消除的位置
                    for (int i = 0; i < m_playerMatrix->MAPROWNUM; i++) {
                        for (int j = 0; j < m_playerMatrix->MAPCOLNUM; j++) {
                            if (m_playerMatrix->GetNum(i, j) == 0) {
                                eliminateNumber++;
                                eliminatedCells.append({i, j});
                                midSituation[i][j] = 1;
                            }
                        }
                    }
                }

                if (eliminateNumber > 0) {
                    m_totalEliminateCount += eliminateNumber;
                    m_playerScore += eliminateNumber * 10;

                    // 执行消除动画
                    for (int stage = 1; stage <= 3 && !eliminatedCells.isEmpty(); stage++) {
                        handleAnimationStage(stage, eliminatedCells);
                        QThread::msleep(ANIMATION_DELAY);  // 延迟以实现平滑动画效果
                    }

                    // 执行下落
                    bool hasDropped;
                    do {
                        {
                            QMutexLocker matrixLocker(&m_resourceMutex);
                            hasDropped = m_playerMatrix->down();
                        }

                        if (hasDropped) {
                            safeUpdate();
                            QThread::msleep(ANIMATION_DELAY);  // 延迟以实现平滑动画效果
                        }
                    } while (hasDropped);

                    hasMoreEliminations = m_playerMatrix->checkmap();
                }
            }
        } while (hasMoreEliminations);

        // 所有消除完成后处理连消奖励
        if (m_totalEliminateCount >= 5) {
            handleComboBonus();
        }

        // 所有操作完成后才发送一次更新
        QTimer::singleShot(100, this, [this]() {
            sendMatrixUpdate();
        });

    } catch (const std::exception& e) {
        qDebug() << "Exception in handleEliminationAndDrop:" << e.what();
    }

    m_animationInProgress.storeRelease(false);
}
*/

void BattleGame::handleEliminationAndDrop()
{
    const int ANIMATION_DELAY = 50;
    bool hasMoreEliminations;
    int eliminateNumber = 0;
    do {
        hasMoreEliminations = false;


        // 第一步：检查并标记需要消除的宝石
        {
            QMutexLocker locker(&m_resourceMutex);
            if (m_playerMatrix->eliminate(false)) {
                for (int i = 0; i < m_playerMatrix->MAPROWNUM; i++) {
                    for (int j = 0; j < m_playerMatrix->MAPCOLNUM; j++) {
                        if (m_playerMatrix->GetNum(i, j) == 0) {
                            eliminateNumber++;
                            midSituation[i][j] = 1;
                        }
                    }
                }
                hasMoreEliminations = true;
            }
        }

        if (eliminateNumber > 0) {
            m_playerScore += eliminateNumber * 1;//对战模式一个一分

            // 三阶段消除动画
            for (int stage = 1; stage <= 3; stage++) {
                {
                    for (int i = 0; i < m_playerMatrix->MAPROWNUM; i++) {
                        for (int j = 0; j < m_playerMatrix->MAPCOLNUM; j++) {
                            if (m_playerMatrix->GetNum(i, j) == 0) {
                                midSituation[i][j] = stage;
                            }
                        }
                    }
                }
                update();
                this->repaint();
                QThread::msleep(ANIMATION_DELAY);
            }

            // 处理下落效果
            bool hasDropped;
            do {
                hasDropped = false;
                {
                    hasDropped = m_playerMatrix->down();
                }
                if (hasDropped) {
                    update();
                    this->repaint();
                    QThread::msleep(ANIMATION_DELAY);
                }
            } while (hasDropped);
        }
    } while (hasMoreEliminations);

    // 下落动画
    while (m_playerMatrix->down()) {
        this->repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    m_hasSelected = false;
    update();  // 重绘以清除选中效果

    //音效
    if (eliminateNumber >= 5) {
        if (eliminateNumber == 5) {
          //  m_playerScore += 50;
            playSoundEffect(greatSound);
        }
        else if (eliminateNumber <= 8) {
           // m_playerScore += 100;
            playSoundEffect(excellentSound);
        }
        else if (eliminateNumber <= 11) {
           // m_playerScore += 200;
            playSoundEffect(amazingSound);
        }
        else {
           // m_playerScore += 500;
            playSoundEffect(unbelievableSound);
        }
    }
    // 发送更新
    QTimer::singleShot(100, this, [this]() {
        sendMatrixUpdate();
    });
}

void BattleGame::handleAnimationStage(int stage, QVector<QPair<int, int>>& eliminatedCells) {
    QMutexLocker matrixLocker(&m_resourceMutex);
    
    for (const auto& cell : eliminatedCells) {
        if (m_playerMatrix->GetNum(cell.first, cell.second) == 0) {
            midSituation[cell.first][cell.second] = stage;
        }
    }
    
    safeUpdate();
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    QThread::msleep(ANIMATION_DELAY);
}

void BattleGame::handleComboBonus() {
    QMutexLocker locker(&m_resourceMutex);
    
    int bonusScore = 0;
    QMediaPlayer* soundEffect = nullptr;

    if (m_totalEliminateCount == 5) {
        bonusScore = 50;
        soundEffect = greatSound;
    } else if (m_totalEliminateCount <= 8) {
        bonusScore = 100;
        soundEffect = excellentSound;
    } else if (m_totalEliminateCount <= 11) {
        bonusScore = 200;
        soundEffect = amazingSound;
    } else {
        bonusScore = 500;
        soundEffect = unbelievableSound;
    }

    if (bonusScore > 0) {
        m_playerScore += bonusScore;
        addScoreSituation = 9;
        
        // 使用定时器延迟播放音效
        if (soundEffect) {
            QTimer::singleShot(0, this, [this, soundEffect]() {
                playSoundEffect(soundEffect);
            });
        }
        
        // 使用定时器延迟更新分数显示
        QTimer::singleShot(0, this, [this]() {
            updateScore();
        });
    }
}

// 修改update方法，添加更多的状态检查
void BattleGame::safeUpdate() {
    if (!m_resourcesLoaded || m_animationInProgress.loadAcquire()) {
        return;
    }
    
    QMutexLocker locker(&m_updateMutex);
    update();
}

void BattleGame::updateScore() {
    // 更新UI上的分数标签
    m_playerScoreLabel->setText(QString("Your Score: %1").arg(m_playerScore));
    
    // 触发重绘,确保分数动画显示
    addScoreSituation = 0;  // 重置分数动画状态
    
    // 发送分数更新
    QJsonObject scoreData;
    scoreData["score"] = m_playerScore;
    QJsonDocument scoreDoc(scoreData);
    m_client->sendMessage("SCORE_SYNC", QString::fromUtf8(scoreDoc.toJson()));
    
    update();  // 触发重绘
}

void BattleGame::onRefreshTimeout() {
    if (m_gameStarted) {
        if (addScoreSituation > 0) {
            addScoreSituation--;
            update();  // 更新分数动画
        }
        update();
    }
}

void BattleGame::executeSwapAnimation(int fromX, int fromY, int toX, int toY) {
    auto* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(40);
    animation->setStartValue(boardToScreen(fromX, fromY, false));
    animation->setEndValue(boardToScreen(toX, toY, false));
    
    // 实际执行交换
    int temp = m_playerMatrix->GetNum(fromY, fromX);
    m_playerMatrix->SetNum(fromY, fromX, m_playerMatrix->GetNum(toY, toX));
    m_playerMatrix->SetNum(toY, toX, temp);
    
    // 将动画添加到活跃动画列表中
    m_activeAnimations.append(animation);
    
    // 连接动画完成信号，在完成时清理
    connect(animation, &QPropertyAnimation::finished, this, [this, animation]() {
        m_activeAnimations.removeOne(animation);
        animation->deleteLater();
    });
    
    animation->start();
}



void BattleGame::handleMessage(const QString& type, const QString& data) 
{
    qDebug() << "收到服务器消息 - 类型:" << type << "内容:" << data;

    // 尝试解析JSON格式
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (!doc.isNull()) {
        if (type == "SCORE_SYNC") {
            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                if (obj.contains("score") && obj.contains("username")) {
                    QString username = obj["username"].toString();
                    if (m_opponentMatrices.contains(username)) {
                        m_opponentScores[username] = obj["score"].toInt();
                        updateScoreDisplay(username, m_opponentScores[username]);
                        update();
                    }
                }
            }
        }
        else if (type == "MATRIX_SYNC") {
            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                QString senderId = obj["playerId"].toString();
                if (senderId != m_playerId) {
                    updateOpponentMatrix(obj);
                }
            }
        }
        else if (type == "PLAYER_JOIN" || type == "PLAYER_LEFT") {
            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                // 处理玩家加入/离开的逻辑...
            }
        }
    } else {
        qDebug() << "无效的JSON数据:" << data;
    }
}

void BattleGame::updateOpponentMatrix(const QJsonObject& data)
{
    if (!m_isOpponent) return;

    QString username = data["username"].toString();
    if (username.isEmpty()) {
        qDebug() << "Invalid username in matrix update";
        return;
    }

    // 确保对手矩阵存在
    NumMatrix* matrix = nullptr;
    if (!m_opponentMatrices.contains(username)) {
        // 创建新的矩阵
        matrix = new NumMatrix();
        matrix->setMapSize(7, 7);
        m_opponentMatrices[username] = matrix;
        m_opponentScores[username] = 0;
        qDebug() << "Created new matrix for opponent:" << username;
    } else {
        matrix = m_opponentMatrices[username];
    }

    // 安全检查
    if (!matrix) {
        qDebug() << "Matrix is null for opponent:" << username;
        return;
    }

    // 获取分数
    int newScore = data["score"].toInt();
    m_opponentScores[username] = newScore;

    // 更新矩阵数据
    QJsonArray jsonMatrix = data["matrix"].toArray();
    if (jsonMatrix.size() != matrix->MAPROWNUM) {
        qDebug() << "Matrix size mismatch. Expected:" << matrix->MAPROWNUM 
                 << "Got:" << jsonMatrix.size();
        return;
    }

    try {
        for (int i = 0; i < matrix->MAPROWNUM; ++i) {
            QJsonArray row = jsonMatrix[i].toArray();
            if (row.size() != matrix->MAPCOLNUM) {
                qDebug() << "Row size mismatch at row" << i;
                continue;
            }
            for (int j = 0; j < matrix->MAPCOLNUM; ++j) {
                matrix->SetNum(i, j, row[j].toInt());
            }
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception during matrix update:" << e.what();
        return;
    }
    
    // 更新显示
    updateScoreDisplay(username, newScore);
    update();
    qDebug() << "Successfully updated matrix for:" << username;
}

void BattleGame::updateScoreDisplay(const QString& playerName, int score) {
    if (playerName.isEmpty()) return;
    
    if (m_isOpponent) {
        if (m_statusLabel) {
            QString displayText = tr("%1: %2").arg(playerName).arg(score);
            m_statusLabel->setText(displayText);
        }
    }
    update();
}

void BattleGame::setIsOpponent(bool isOpponent, const QString& opponentName) 
{ 
    if (opponentName.isEmpty()) {
        qDebug() << "Empty opponent name!";
        return;
    }

    m_isOpponent = isOpponent;
    m_playerName = opponentName;

    if (m_isOpponent) {
        try {
            // 为新对手创建矩阵
            if (!m_opponentMatrices.contains(opponentName)) {
                NumMatrix* matrix = new NumMatrix();
                if (!matrix->setMapSize(7, 7)) {
                    qDebug() << "Failed to set matrix size for:" << opponentName;
                    delete matrix;
                    return;
                }
                m_opponentMatrices[opponentName] = matrix;
                m_opponentScores[opponentName] = 0;
            }

            // 更新状态标签
            if (m_statusLabel) {
                m_statusLabel->setText(opponentName);
            }

            qDebug() << "Successfully set up opponent:" << opponentName;
        } catch (const std::exception& e) {
            qDebug() << "Exception in setIsOpponent:" << e.what();
            return;
        }
    }

    update();
    qDebug() << "Set opponent mode:" << m_isOpponent << "Name:" << opponentName;
}

void BattleGame::drawGems(QPainter& painter)
{
    NumMatrix* matrix = m_isOpponent ? m_opponentMatrices[m_playerName] : m_playerMatrix;
    if (!matrix) return;
    
    // 计算绘制的起始位置，使棋盘居中
    int offsetX = (width() - matrix->MAPCOLNUM * CELL_SIZE) / 2;
    int offsetY = (height() - matrix->MAPROWNUM * CELL_SIZE) / 2;
    
    // 如果是对手实例，绘制玩家名称
    if (m_isOpponent) {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter,
                        m_playerName);
    }
    
    // 绘制宝石
    for (int i = 0; i < matrix->MAPROWNUM; ++i) {
        for (int j = 0; j < matrix->MAPCOLNUM; ++j) {
            int gemType = matrix->GetNum(i, j);
            QRect gemRect(
                offsetX + j * CELL_SIZE,  // x坐标
                offsetY + i * CELL_SIZE,  // y坐标
                CELL_SIZE - 2,            // 宽度（留出边距）
                CELL_SIZE - 2             // 高度（留出边距）
            );
            
            // 根据宝石类型选择颜色
            QColor gemColor;
            switch (gemType) {
                case 1: gemColor = Qt::red; break;
                case 2: gemColor = Qt::blue; break;
                case 3: gemColor = Qt::green; break;
                case 4: gemColor = Qt::yellow; break;
                case 5: gemColor = Qt::magenta; break;
                default: gemColor = Qt::gray;
            }
            
            // 绘制宝石
            painter.setBrush(gemColor);
            painter.setPen(Qt::black);
            painter.drawEllipse(gemRect);
        }
    }
    
    // 如果是对手实例，绘制分数
    if (m_isOpponent && m_opponentScores.contains(m_playerName)) {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 12));
        painter.drawText(rect(), Qt::AlignBottom | Qt::AlignRight,
            tr("%1的分数: %2").arg(m_playerName).arg(m_opponentScores[m_playerName]));
    }
}

void BattleGame::updateGemTheme(QString path) {
    QMutexLocker locker(&m_resourceMutex);
    QString actualPrefix = ":/res/images/";

    // 清理现有资源
    for (int i = 0; i < 8; ++i) {
        pixmap_gem[i] = QPixmap();
    }
    pixmap_di = QPixmap();
    disappear1 = QPixmap();
    disappear2 = QPixmap();
    disappear3 = QPixmap();
    for (int i = 0; i < 10; ++i) {
        number[i] = QPixmap();
    }

    bool loadSuccess = true;
    
    // 加载所有资源
    for (int i = 0; i < 8; ++i) {
        QString gemPath = actualPrefix + "a" + QString::number(i + 1) + ".png";
        if (!pixmap_gem[i].load(gemPath)) {
            qDebug() << "Failed to load gem:" << gemPath;
            loadSuccess = false;
        }
    }

    if (!pixmap_di.load(actualPrefix + "select.png")) {
        qDebug() << "Failed to load select frame";
        loadSuccess = false;
    }

    if (!disappear1.load(actualPrefix + "tx1.png") ||
        !disappear2.load(actualPrefix + "tx2.png") ||
        !disappear3.load(actualPrefix + "tx3.png")) {
        qDebug() << "Failed to load effect images";
        loadSuccess = false;
    }

    for (int i = 0; i < 10; ++i) {
        QString numPath = actualPrefix + "number" + QString::number(i) + ".png";
        if (!number[i].load(numPath)) {
            qDebug() << "Failed to load number:" << numPath;
            loadSuccess = false;
        }
    }

    m_resourcesLoaded = loadSuccess;
    if (!loadSuccess) {
        QMessageBox::critical(this, "错误", "部分资源加载失败，请检查资源文件！");
    }
}

void BattleGame::drawGemWithEffects(QPainter& painter, int i, int j, int num) {
    if (!m_resourcesLoaded) return;
    
    QPoint pos = boardToScreen(j, i, false);
    
    // 防御性检查
    if (num <= 0 || num > 8 || pixmap_gem[num - 1].isNull()) {
        qDebug() << "无效的宝石编号或空图片:" << num << "在位置" << i << "," << j;
        // 绘制占位符
        painter.fillRect(QRect(pos.x(), pos.y(), m_cellSize, m_cellSize), Qt::gray);
        painter.setPen(Qt::black);
        painter.drawText(QRect(pos.x(), pos.y(), m_cellSize, m_cellSize), 
                        Qt::AlignCenter, QString::number(num));
        return;
    }

    // 绘制宝石
    painter.drawPixmap(pos.x(), pos.y(), m_cellSize, m_cellSize, pixmap_gem[num - 1]);

    // 绘制选择框
    if (isSelected[i][j] && !pixmap_di.isNull()) {
        painter.drawPixmap(pos.x(), pos.y(), m_cellSize, m_cellSize, pixmap_di);
    }

    // 绘制特效
    if (midSituation[i][j] > 0) {
        const QPixmap* effect = nullptr;
        switch(midSituation[i][j]) {
            case 1: effect = &disappear1; break;
            case 2: effect = &disappear2; break;
            case 3: effect = &disappear3; break;
        }
        
        if (effect && !effect->isNull()) {
            painter.drawPixmap(pos.x(), pos.y(), m_cellSize, m_cellSize, *effect);
        }
    }
}

void BattleGame::setupAudioSystem() {
    effectAudioOutput = new QAudioOutput(this);
    effectAudioOutput->setVolume(0.5f);
}

void BattleGame::initSoundEffects() {
    // 初始化音效播放器
    greatSound = new QMediaPlayer(this);
    excellentSound = new QMediaPlayer(this);
    amazingSound = new QMediaPlayer(this);
    unbelievableSound = new QMediaPlayer(this);
    
    // 设置音频输出
    greatSound->setAudioOutput(new QAudioOutput(this));
    excellentSound->setAudioOutput(new QAudioOutput(this));
    amazingSound->setAudioOutput(new QAudioOutput(this));
    unbelievableSound->setAudioOutput(new QAudioOutput(this));
    
    // 设置音源
    greatSound->setSource(QUrl("qrc:/res/audio/great.mp3"));
    excellentSound->setSource(QUrl("qrc:/res/audio/excellent.mp3"));
    amazingSound->setSource(QUrl("qrc:/res/audio/amazing.mp3"));
    unbelievableSound->setSource(QUrl("qrc:/res/audio/unbelievable.mp3"));
}

void BattleGame::playSoundEffect(QMediaPlayer* effect) {
    if (!effect || !effectAudioOutput) return;
    
    if (effect->playbackState() == QMediaPlayer::PlayingState) {
        effect->setPosition(0);
    }
    effect->play();
}

void BattleGame::updateBackgroundMusic(float volume) {
    // 如果使用了Setup类中的静态音频输出
    if (Setup::audioOutput) {
        Setup::audioOutput->setVolume(volume);
    }
    
    // 同时更新特效音量
    if (effectAudioOutput) {
        effectAudioOutput->setVolume(volume);
    }
}

void BattleGame::updateMuteState(bool muted) {
    // 如果使用了Setup类中的静态音频输出
    if (Setup::audioOutput) {
        Setup::audioOutput->setMuted(muted);
    }

    
    // 同时更新特效静音状态
    if (effectAudioOutput) {
        effectAudioOutput->setMuted(muted);
    }
    
    // 更新所有音效播放器的静音状态
    if (greatSound) greatSound->audioOutput()->setMuted(muted);
    if (excellentSound) excellentSound->audioOutput()->setMuted(muted);
    if (amazingSound) amazingSound->audioOutput()->setMuted(muted);
    if (unbelievableSound) unbelievableSound->audioOutput()->setMuted(muted);
}

void BattleGame::updateMapSize(int rows, int cols) {
    if (m_playerMatrix && m_playerMatrix->setMapSize(rows, cols)) {
        // 重新计算单元格大小
        m_cellSize = GAME_AREA_WIDTH / cols;
        m_playerMatrix->BuildMap(5);  // 重新生成地图
        update();
    }
}


