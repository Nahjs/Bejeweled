#include "battle.h"
#include "ui_battle.h"
#include <QMessageBox>
#include <QGridLayout>
#include <cmath>
#include <QJsonDocument>
#include <QJsonObject>

Battle::Battle(ChatClient* client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Battle)
    , m_client(client)
{
    ui->setupUi(this);
    setupUI();

    // 连接服务器消息处理
    connect(m_client, &ChatClient::messageReceived, this, [this](const QString& type, const QString& data) {
        if (type == "PLAYER_JOIN") {
            QStringList parts = data.split(",");
            if (parts.size() >= 2) {
                handleNewPlayer(parts[0], parts[1]);
                // 新玩家加入时，发送当前玩家的矩阵信息
                if (m_playerGame) {
                    m_playerGame->sendMatrixUpdate();
                }
            }
        }
        else if (type == "PLAYER_LEFT") {
            handlePlayerLeft(data);
        }
        else {
            handleMessage(type, data);

        }
    });

    // 修改连接方式，使用QAction的triggered信号
    connect(ui->backButton, &QAction::triggered, this, &Battle::onBackButtonClicked);
}

Battle::~Battle()
{
    clearOpponentDisplays();
    delete ui;
}

void Battle::setupUI()
{
    // 使用登录用户名
    ui->playerInfoLabel->setText(tr("当前玩家: %1").arg(Login::currentUsername));
    
    // 设置左侧玩家界面的固定大小
    ui->leftPanel->setFixedWidth(580);
    
    // 创建玩家游戏界面时传入当前用户名
    m_playerGame = new BattleGame(m_client, Login::currentUsername, this);
    m_playerGame->setFixedSize(550, 550);
    ui->playerContainer->layout()->addWidget(m_playerGame);

    // 初始化对手容器的布局
    QGridLayout* opponentsLayout = new QGridLayout(ui->opponentsContainer);
    opponentsLayout->setSpacing(10);
    opponentsLayout->setContentsMargins(10, 10, 10, 10);
    opponentsLayout->setAlignment(Qt::AlignCenter);
    ui->opponentsContainer->setLayout(opponentsLayout);
    m_opponentsLayout = opponentsLayout;
    
    qDebug() << "战斗界面初始化完成";
}

void Battle::handleNewPlayer(const QString& playerId, const QString& playerName)
{
    if (playerName == Login::currentUsername) {
        qDebug() << "忽略自己的游戏实例:" << playerName;
        return;
    }

    // 使用用户名检查是否已存在
    if (m_opponentGames.contains(playerName)) {
        qDebug() << "已存在的玩家实例:" << playerName;
        return;
    }

    qDebug() << "创建新对手游戏实例:" << playerName << "ID:" << playerId;

    // 创建并初始化对手游戏实例，传入对手用户名
    BattleGame* opponentGame = new BattleGame(m_client, playerName, ui->opponentsContainer);
    opponentGame->setIsOpponent(true, playerName);
    opponentGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    opponentGame->setMinimumSize(200, 200);
    
    // 使用用户名作为key存储游戏实例
    m_opponentGames[playerName] = opponentGame;
    m_opponentIds[playerName] = playerId;  // 保存ID映射以便需要时查询

    // 新玩家加入时，发送自己的矩阵信息
    QTimer::singleShot(200, this, [this]() {
        if (m_playerGame) {
            m_playerGame->sendMatrixUpdate();
        }
    });

    // 更新布局
    resizeOpponentDisplays();

    // 更新对手信息显示
    ui->opponentsInfoLabel->setText(tr("当前对手数: %1").arg(m_opponentGames.size()));
    
    qDebug() << "当前对手总数:" << m_opponentGames.size();
}

void Battle::handlePlayerLeft(const QString& playerId)
{
    // 通过ID反查用户名
    QString username;
    for (auto it = m_opponentIds.begin(); it != m_opponentIds.end(); ++it) {
        if (it.value() == playerId) {
            username = it.key();
            break;
        }
    }

    if (!username.isEmpty() && m_opponentGames.contains(username)) {
        delete m_opponentGames[username];
        m_opponentGames.remove(username);
        m_opponentIds.remove(username);
        resizeOpponentDisplays();
        
        qDebug() << "玩家离开:" << username << "(" << playerId << ")";
    }
}

void Battle::resizeOpponentDisplays()
{
    int count = m_opponentGames.size();
    if (count == 0) return;

    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->opponentsContainer->layout());
    if (!gridLayout) return;

    // 不再限制最大显示数量，根据实际对手数量计算行列
    int rows = (count + 1) / 2;  // 向上取整
    int cols = (count > 1) ? 2 : 1;

    qDebug() << "调整布局 - 对手数量:" << count << "行数:" << rows << "列数:" << cols;

    // 清理现有布局但保留widget
    QList<BattleGame*> widgets;
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widgets.append(qobject_cast<BattleGame*>(widget));
            widget->hide();  // 临时隐藏以避免闪烁
        }
        delete item;
    }

    // 计算每个格子的大小
    int totalWidth = ui->opponentsContainer->width();
    int totalHeight = ui->opponentsContainer->height();
    int cellWidth = (totalWidth - (cols + 1) * 10) / cols;
    int cellHeight = (totalHeight - (rows + 1) * 10) / rows;

    // 重新布局所有对手游戏界面
    int index = 0;
    for (auto it = m_opponentGames.begin(); it != m_opponentGames.end(); ++it) {
        int row = index / cols;
        int col = index % cols;
        BattleGame* game = it.value();
        
        game->setFixedSize(cellWidth, cellHeight);
        gridLayout->addWidget(game, row, col);
        game->show();  // 显示widget
        
        qDebug() << "放置对手" << index + 1 
                 << "在位置(" << row << "," << col << ")"
                 << "大小:" << cellWidth << "x" << cellHeight;
        
        index++;
    }

    // 强制布局更新
    gridLayout->activate();
    ui->opponentsContainer->updateGeometry();
    ui->opponentsContainer->update();
}

void Battle::clearOpponentDisplays()
{
    for (auto game : m_opponentGames) {
        delete game;
    }
    m_opponentGames.clear();
    m_opponentIds.clear();  // 同时清理ID映射
}

void Battle::onBackButtonClicked()
{
    // 弹出确认对话框
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("确认返回"),
        tr("确定要退出对战模式吗？"),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        emit battleToStart();
        this->close();
    }
}

void Battle::updateOpponentDisplays(const QStringList& players)
{
    // 清理现有显示
    clearOpponentDisplays();
    
    // 为每个玩家创建显示
    for (const QString& player : players) {
        QStringList parts = player.split(":");
        if (parts.size() >= 2) {
            handleNewPlayer(parts[0], parts[1]);
        }
    }
}

void Battle::handleMessage(const QString& type, const QString& data)
{
    if (type == "MATRIX_SYNC") {
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QString username = obj["username"].toString();
            QString playerId = obj["playerId"].toString();
            qint64 timestamp = obj["timestamp"].toVariant().toLongLong();
            
            if (username == Login::currentUsername) {
                return;  // 忽略自己的消息
            }

            static QMap<QString, qint64> lastUpdateTimes;
            
            // 使用用户名作为key检查更新
            if (!lastUpdateTimes.contains(username) || 
                timestamp > lastUpdateTimes[username]) {
                
                // 如果是新玩家，创建实例
                if (!m_opponentGames.contains(username)) {
                    handleNewPlayer(playerId, username);
                }
                
                // 使用用户名获取对应的游戏实例
                if (m_opponentGames.contains(username)) {
                    m_opponentGames[username]->updateOpponentMatrix(obj);
                    lastUpdateTimes[username] = timestamp;
                    qDebug() << "更新玩家" << username << "的矩阵 时间戳:" << timestamp;
                }
            }
        }
    }
    // ...existing code...
}
