#include "battlegame.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <thread>
#include <chrono>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>  // 用于生成唯一ID

BattleGame::BattleGame(ChatClient* client, QWidget *parent) 
    : QWidget(parent), m_client(client), m_hasSelected(false)
{
    // 生成唯一的玩家ID
    m_playerId = QUuid::createUuid().toString();
    
    m_playerMatrix = new NumMatrix();
    m_opponentMatrix = new NumMatrix();
    
    // 设置矩阵大小并初始化
    m_playerMatrix->setMapSize(7, 7);  // 设置7x7的大小
    m_opponentMatrix->setMapSize(7, 7);
    m_playerMatrix->BuildMap(5);  // 初始化玩家矩阵
    
    // 设置游戏运行状态为true
    m_playerMatrix->setgamerunning(true);
    m_gameStarted = true;  // 测试时直接设置为开始状态
    
    m_refreshTimer = new QTimer(this);
    m_playerScore = 0;
    m_opponentScore = 0;
    
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
}

BattleGame::~BattleGame() {
    // 清理动态分配的资源
    delete m_playerMatrix;
    delete m_opponentMatrix;
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

void BattleGame::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    
    // 绘制两个数字矩阵
    drawMatrix(painter, m_playerMatrix, false);
    drawMatrix(painter, m_opponentMatrix, true);
    
    // 绘制选中效果
    if (m_hasSelected) {
        painter.setPen(QPen(Qt::red, 2));
        QPoint pos = boardToScreen(m_selectedX, m_selectedY, false);
        painter.drawRect(pos.x(), pos.y(), CELL_SIZE, CELL_SIZE);
    }
}

void BattleGame::drawMatrix(QPainter& painter, const NumMatrix* matrix, bool isOpponent) {
    int offsetX = isOpponent ? BOARD_SPACING + matrix->MAPCOLNUM * CELL_SIZE : 0;
    
    // 绘制矩阵底色
    painter.fillRect(offsetX + 50, 50, 
                    matrix->MAPCOLNUM * CELL_SIZE, 
                    matrix->MAPROWNUM * CELL_SIZE, 
                    QColor(200, 200, 200));
    
    // 绘制数字
    for(int i = 0; i < matrix->MAPROWNUM; i++) {
        for(int j = 0; j < matrix->MAPCOLNUM; j++) {
            drawNumber(painter, j, i, matrix->GetNum(i, j), isOpponent);
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

void BattleGame::mousePressEvent(QMouseEvent* event) {
    if (!m_gameStarted) {
        qDebug() << "Game not started, ignoring click";
        return;
    }
    
    bool isOpponentBoard;
    QPoint boardPos = screenToBoard(event->x(), event->y(), isOpponentBoard);
    
    if (isOpponentBoard) {
        qDebug() << "Clicked opponent board, ignoring";
        return;
    }
    
    int x = boardPos.x();
    int y = boardPos.y();
    
    qDebug() << "Mouse click at board position:" << x << "," << y;
    
    if (x >= 0 && x < m_playerMatrix->MAPCOLNUM && 
        y >= 0 && y < m_playerMatrix->MAPROWNUM) {
        if (!m_hasSelected) {
            m_selectedX = x;
            m_selectedY = y;
            m_hasSelected = true;
            qDebug() << "Selected first gem at:" << x << "," << y;
        } else {
            qDebug() << "Attempting swap with gem at:" << x << "," << y;
            // 发送交换操作消息
            QJsonObject swapData;
            swapData["fromX"] = m_selectedX;
            swapData["fromY"] = m_selectedY;
            swapData["toX"] = x;
            swapData["toY"] = y;
            QJsonDocument doc(swapData);
            
            TextMessage swapMsg(MessageType::MATRIX_SWAP, QString::fromUtf8(doc.toJson()));
            m_client->sendMessage("SWAP", swapMsg.serialize());
            
            // 尝试本地交换
            if (m_playerMatrix->swap(m_selectedY, m_selectedX, y, x)) {
                // 处理消除和下落
                bool continueChecking = true;
                while (continueChecking) {
                    continueChecking = false;
                    if (m_playerMatrix->eliminate()) {
                        m_playerScore += 10;
                        // 发送分数更新
                        QJsonObject scoreData;
                        scoreData["score"] = m_playerScore;
                        QJsonDocument scoreDoc(scoreData);
                        m_client->sendMessage("SCORE_SYNC", QString::fromUtf8(scoreDoc.toJson()));
                        
                        // 发送消除消息
                        QJsonObject elimData;
                        elimData["playerId"] = m_playerId;
                        QJsonDocument elimDoc(elimData);
                        m_client->sendMessage("MATRIX_ELIM", QString::fromUtf8(elimDoc.toJson()));
                        
                        // 执行下落
                        while (m_playerMatrix->down()) {
                            // 发送下落消息
                            QJsonObject dropData;
                            dropData["playerId"] = m_playerId;
                            QJsonDocument dropDoc(dropData);
                            m_client->sendMessage("MATRIX_DROP", QString::fromUtf8(dropDoc.toJson()));
                            
                            std::this_thread::sleep_for(std::chrono::milliseconds(40));
                            sendMatrixUpdate();
                            continueChecking = true;
                        }
                    }
                }
            }
            m_hasSelected = false;
        }
        update();
    }
}

void BattleGame::onGameMessage(const QString& type, const QString& data) {
    qDebug() << "\n=== Game Message Received ===";
    qDebug() << "Type:" << type;
    qDebug() << "Data:" << data;
    
    if (type == "SYNC") {
        QStringList parts = data.split(',');
        qDebug() << "Received matrix sync message:";
        qDebug() << "Data parts count:" << parts.size();
        
        if (parts.size() >= 2 + m_opponentMatrix->MAPROWNUM * m_opponentMatrix->MAPCOLNUM) {
            // 更新对手分数
            m_opponentScore = parts[0].toInt();
            qDebug() << "Opponent score updated to:" << m_opponentScore;
            
            // 更新对手矩阵
            int index = 1;
            qDebug() << "Updating opponent matrix:";
            for(int i = 0; i < m_opponentMatrix->MAPROWNUM; i++) {
                QString row;
                for(int j = 0; j < m_opponentMatrix->MAPCOLNUM; j++) {
                    int value = parts[index++].toInt();
                    m_opponentMatrix->SetNum(i, j, value);
                    row += QString::number(value) + " ";
                }
                qDebug() << "Row" << i << ":" << row;
            }
            
            m_opponentScoreLabel->setText(QString("Opponent Score: %1").arg(m_opponentScore));
            update();
        } else {
            qDebug() << "ERROR: Invalid matrix data format received";
            qDebug() << "Expected size:" << (2 + m_opponentMatrix->MAPROWNUM * m_opponentMatrix->MAPCOLNUM);
            qDebug() << "Actual size:" << parts.size();
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
            int targetY = parts[2].toInt();
            
            // 执行道具效果动画
            executePropAnimation(propType, targetX, targetY);
        }
    }
    update(); // 重绘画面
}

void BattleGame::processGameState(const QString& data) {
    QStringList parts = data.split(',');
    // 使用 NumMatrix 的尺寸替代 BOARD_SIZE
    if (parts.size() < m_playerMatrix->MAPROWNUM * m_playerMatrix->MAPCOLNUM + 4) return;
    
    m_playerScore = parts[1].toInt();
    m_opponentScore = parts[2].toInt();
    m_gameStarted = !parts[3].toInt();
    
    // 更新分数显示
    m_playerScoreLabel->setText(QString("Your Score: %1").arg(m_playerScore));
    m_opponentScoreLabel->setText(QString("Opponent Score: %1").arg(m_opponentScore));
    
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

void BattleGame::sendMatrixUpdate() 
{
    if (!m_client->isConnected()) {
        qDebug() << "未连接到服务器，延迟发送矩阵更新";
        return;
    }

    QJsonObject obj;
    obj["playerId"] = m_playerId;
    obj["score"] = m_playerScore;
    
    // 将矩阵数据转换为JSON数组
    QJsonArray matrixData;
    for(int i = 0; i < m_playerMatrix->MAPROWNUM; i++) {
        QJsonArray row;
        for(int j = 0; j < m_playerMatrix->MAPCOLNUM; j++) {
            row.append(m_playerMatrix->GetNum(i, j));
        }
        matrixData.append(row);
    }
    obj["matrix"] = matrixData;

    QJsonDocument doc(obj);
    // 使用压缩格式，避免额外的空白字符
    QString message = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    
    m_client->sendMessage("MATRIX_SYNC", message);
    qDebug() << "发送矩阵同步消息:" << message;
}

QPoint BattleGame::boardToScreen(int x, int y, bool isOpponentBoard) {
    int offsetX = isOpponentBoard ? 
        BOARD_SPACING + m_playerMatrix->MAPCOLNUM * CELL_SIZE : 0;
    return QPoint(offsetX + 50 + x * CELL_SIZE, 50 + y * CELL_SIZE);
}

QPoint BattleGame::screenToBoard(int x, int y, bool& isOpponentBoard) {
    x -= 50;
    y -= 50;
    
    if (x >= m_playerMatrix->MAPCOLNUM * CELL_SIZE + BOARD_SPACING) {
        x -= m_playerMatrix->MAPCOLNUM * CELL_SIZE + BOARD_SPACING;
        isOpponentBoard = true;
    } else {
        isOpponentBoard = false;
    }
    
    return QPoint(x / CELL_SIZE, y / CELL_SIZE);
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

    // 尝试解析JSON数据
    if (type == "MATRIX_SYNC") {
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        if (!doc.isNull() && doc.isObject()) {
            QJsonObject obj = doc.object();
            QString senderId = obj["playerId"].toString();
            
            // 只处理其他玩家的矩阵更新
            if (senderId != m_playerId) {
                updateOpponentMatrix(obj);
                qDebug() << "更新对手矩阵 - 来自玩家:" << senderId;
            }
        }
    }
    // ...其他消息处理...
}

void BattleGame::updateOpponentMatrix(const QJsonObject& data)
{
    // 解析对手ID和分数
    QString opponentId = data["playerId"].toString();
    m_opponentScore = data["score"].toInt();
    m_opponentScoreLabel->setText(QString("Opponent Score: %1").arg(m_opponentScore));

    // 更新矩阵数据
    QJsonArray matrix = data["matrix"].toArray();
    if (!matrix.isEmpty()) {
        qDebug() << "更新对手矩阵数据 - 大小:" << matrix.size();
        for(int i = 0; i < matrix.size() && i < m_opponentMatrix->MAPROWNUM; i++) {
            QJsonArray row = matrix[i].toArray();
            for(int j = 0; j < row.size() && j < m_opponentMatrix->MAPCOLNUM; j++) {
                m_opponentMatrix->SetNum(i, j, row[j].toInt());
            }
        }
        update(); // 强制重绘
        qDebug() << "对手矩阵更新完成";
    }
}

void BattleGame::sendGameState() {
    // 将当前游戏状态转换为JSON
    QJsonObject gameState;
    // ... 添加矩阵数据和分数 ...
    
    QJsonDocument doc(gameState);
    QString message = QString::fromUtf8(doc.toJson());
    
    // 发送到服务器
    m_client->sendMessage("matrix_update", message);
}

void BattleGame::executePropAnimation(int propType, int targetX, int targetY, bool isOpponent) {
    // 根据道具类型创建不同的特效动画
    QPoint pos = boardToScreen(targetX, targetY, isOpponent);
    
    switch(static_cast<PropType>(propType)) {
        case PropType::BOOM: {
            // 爆炸效果
            QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
            anim->setDuration(ANIMATION_DURATION);
            anim->setStartValue(QRect(pos.x(), pos.y(), CELL_SIZE, CELL_SIZE));
            anim->setEndValue(QRect(pos.x() - CELL_SIZE, pos.y() - CELL_SIZE, 
                                  CELL_SIZE * 3, CELL_SIZE * 3));
            m_activeAnimations.append(anim);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
            break;
        }
        case PropType::ROW: {
            // 行消除效果
            QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
            anim->setDuration(ANIMATION_DURATION);
            anim->setStartValue(QRect(50, pos.y(), CELL_SIZE * m_playerMatrix->MAPCOLNUM, CELL_SIZE));
            anim->setEndValue(QRect(50, pos.y(), CELL_SIZE * m_playerMatrix->MAPCOLNUM, 0));
            m_activeAnimations.append(anim);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
            break;
        }
        case PropType::COLUMN: {
            // 列消除效果
            QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
            anim->setDuration(ANIMATION_DURATION);
            anim->setStartValue(QRect(pos.x(), 50, CELL_SIZE, CELL_SIZE * m_playerMatrix->MAPROWNUM));
            anim->setEndValue(QRect(pos.x(), 50, 0, CELL_SIZE * m_playerMatrix->MAPROWNUM));
            m_activeAnimations.append(anim);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
            break;
        }
        case PropType::COLOR: {
            // 同色消除效果
            // TODO: 实现同色消除的动画效果
            break;
        }
    }
    
    update();  // 刷新界面
}
