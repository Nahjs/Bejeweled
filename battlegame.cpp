#include "battlegame.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <thread>
#include <chrono>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>  // 用于生成唯一ID

#include "login.h"

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
}

BattleGame::~BattleGame() {
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
    
    m_playerScoreLabel = new QLabel("Your Score: 0", this);
    m_playerScoreLabel->move(50, 10);
    
    m_opponentScoreLabel = new QLabel("Opponent Score: 0", this);
    m_opponentScoreLabel->move(450, 10);
    
    m_statusLabel = new QLabel("Waiting for opponent...", this);
    m_statusLabel->move(350, 350);
}

void BattleGame::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制背景
    painter.fillRect(rect(), Qt::white);
    
    // 绘制宝石
    drawGems(painter);
    
    // 绘制选中框
    if (m_hasSelected) {
        QPoint pos = boardToScreen(m_selectedX, m_selectedY, false);
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(pos.x(), pos.y(), CELL_SIZE, CELL_SIZE);
    }
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
    // 计算棋盘区域的起始位置
    int offsetX = (width() - m_playerMatrix->MAPCOLNUM * CELL_SIZE) / 2;
    int offsetY = (height() - m_playerMatrix->MAPROWNUM * CELL_SIZE) / 2;
    
    // 转换为相对于棋盘左上角的坐标
    int relX = x - offsetX;
    int relY = y - offsetY;
    
    // 验证点击是否在棋盘范围内
    if (relX < 0 || relY < 0 || 
        relX >= m_playerMatrix->MAPCOLNUM * CELL_SIZE || 
        relY >= m_playerMatrix->MAPROWNUM * CELL_SIZE) {
        return QPoint(-1, -1);
    }
    
    // 计算对应的棋盘格子位置
    int boardX = relX / CELL_SIZE;
    int boardY = relY / CELL_SIZE;
    
    isOpponentBoard = false;  // 当前版本不考虑对手棋盘
    return QPoint(boardX, boardY);
}

void BattleGame::mousePressEvent(QMouseEvent* event) {
    if (!m_gameStarted) {
        qDebug() << "Game not started, ignoring click";
        return;
    }

    bool isOpponentBoard;
    QPoint boardPos = screenToBoard(event->pos().x(), event->pos().y(), isOpponentBoard);
    
    if (boardPos.x() < 0 || boardPos.y() < 0) {
        qDebug() << "Invalid click position";
        return;
    }

    qDebug() << "Mouse click at board position:" << boardPos.x() << "," << boardPos.y();

    if (!m_hasSelected) {
        m_selectedX = boardPos.x();
        m_selectedY = boardPos.y();
        m_hasSelected = true;
        qDebug() << "First selection at:" << m_selectedX << "," << m_selectedY;
    } else {
        // 确保交换的是相邻的宝石
        if ((std::abs(boardPos.x() - m_selectedX) == 1 && boardPos.y() == m_selectedY) ||
            (std::abs(boardPos.y() - m_selectedY) == 1 && boardPos.x() == m_selectedX)) {
            
            // 注意：swap函数参数顺序是(row1, col1, row2, col2)
            if (m_playerMatrix->swap(m_selectedY, m_selectedX, boardPos.y(), boardPos.x())) {
                handleEliminationAndDrop();
            }
        }
        m_hasSelected = false;
    }
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

QPoint BattleGame::boardToScreen(int x, int y, bool) {
    // 计算棋盘区域的起始位置
    int offsetX = (width() - m_playerMatrix->MAPCOLNUM * CELL_SIZE) / 2;
    int offsetY = (height() - m_playerMatrix->MAPROWNUM * CELL_SIZE) / 2;
    
    // 转换为屏幕坐标
    return QPoint(
        offsetX + x * CELL_SIZE,
        offsetY + y * CELL_SIZE
    );
}

void BattleGame::handleEliminationAndDrop() {
    bool continueChecking = true;
    while (continueChecking) {
        continueChecking = false;
        if (m_playerMatrix->eliminate()) {
            m_playerScore += 10;
            updateScore();
            
            // 执行下落
            while (m_playerMatrix->down()) {
                update();
                QApplication::processEvents();  // 允许界面更新
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            
            // 继续检查是否还有可以消除的
            continueChecking = true;
        }
    }
    
    // 发送更新到服务器
    sendMatrixUpdate();
}

void BattleGame::updateScore() {
    m_playerScoreLabel->setText(QString("Your Score: %1").arg(m_playerScore));
    
    // 发送分数更新
    QJsonObject scoreData;
    scoreData["score"] = m_playerScore;
    QJsonDocument scoreDoc(scoreData);
    m_client->sendMessage("SCORE_SYNC", QString::fromUtf8(scoreDoc.toJson()));
}

void BattleGame::onRefreshTimeout() {
    if (m_gameStarted) {
        // 更新动画状态
 //       updateAnimations();
        update();  // 触发重绘
    }
}

void BattleGame::executeSwapAnimation(int fromX, int fromY, int toX, int toY) {
    // 创建动画效果
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300); // 300ms的动画时长
    animation->setStartValue(boardToScreen(fromX, fromY, false));
    animation->setEndValue(boardToScreen(toX, toY, false));
    
    // 实际执行交换
    int temp = m_playerMatrix->GetNum(fromY, fromX);
    m_playerMatrix->SetNum(fromY, fromX, m_playerMatrix->GetNum(toY, toX));
    m_playerMatrix->SetNum(toY, toX, temp);
    
    animation->start(QAbstractAnimation::DeleteWhenStopped);
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
    int score = data["score"].toInt();
    
    // 确保对手矩阵存在
    if (!m_opponentMatrices.contains(username)) {
        setIsOpponent(true, username);
    }
    
    // 更新对手矩阵数据
    NumMatrix* matrix = m_opponentMatrices[username];
    QJsonArray jsonMatrix = data["matrix"].toArray();
    for (int i = 0; i < matrix->MAPROWNUM; ++i) {
        QJsonArray row = jsonMatrix[i].toArray();
        for (int j = 0; j < matrix->MAPCOLNUM; ++j) {
            matrix->SetNum(i, j, row[j].toInt());
        }
    }
    
    // 更新分数
    m_opponentScores[username] = score;
    updateScoreDisplay(username, score);
    
    update();
}

void BattleGame::updateScoreDisplay(const QString& playerName, int score)
{
    if (m_scoreLabels.contains(playerName)) {
        m_scoreLabels[playerName]->setText(
            tr("%1的分数: %2").arg(playerName).arg(score)
        );
    }
}

void BattleGame::setIsOpponent(bool isOpponent, const QString& opponentName) 
{ 
    m_isOpponent = isOpponent;
    if (m_isOpponent) {
        m_playerName = opponentName;
        // 为新对手创建矩阵
        if (!m_opponentMatrices.contains(opponentName)) {
            NumMatrix* matrix = new NumMatrix();
            matrix->setMapSize(7, 7);
            m_opponentMatrices[opponentName] = matrix;
            
            // 创建分数标签
            QLabel* scoreLabel = new QLabel(this);
            scoreLabel->setStyleSheet("QLabel { color: black; font-size: 12px; }");
            m_scoreLabels[opponentName] = scoreLabel;
            m_opponentScores[opponentName] = 0;
            updateScoreDisplay(opponentName, 0);
        }
    }
    update();
    qDebug() << "设置对手模式:" << m_isOpponent << "对手名称:" << opponentName;
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
