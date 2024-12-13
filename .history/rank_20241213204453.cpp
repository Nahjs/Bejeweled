#include "rank.h"
#include "ui_rank.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include <QLabel>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QDateTime>

Rank* Rank::instance = nullptr;
Rankstruct Rank::g_rank;
Rankstruct* Rank::ranks[10] = {nullptr};

Rank* Rank::getInstance() 
{
    if(instance == nullptr)
        instance = new Rank;
    return instance;
}

Rank::Rank(QWidget *parent) : QMainWindow(parent), ui(new Ui::Rank) 
{
    ui->setupUi(this);
    for(int i = 0; i < 10; i++) {
        ranks[i] = new Rankstruct();
    }
    loadRankData();
    
    // 初始化定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(1000); // 每秒更新一次
    updateTime(); // 立即更新一次时间显示
}

void Rank::loadRankData() 
{
        file.close();
    }
}

void Rank::saveRankData() 
{
    QFile file("rank.txt");
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        for(int i = 0; i < 10; i++) {
            out.writeRawData(ranks[i]->strName, 50);
            out << ranks[i]->nGrade;
        }
        file.close();
    }
}

int Rank::getRankCount() 
{
    int count = 0;
    for(int i = 0; i < 10 && ranks[i]->nGrade > 0; i++) {
        count++;
    }
    return count;
}

void Rank::updateRank() 
{
    loadRankData();
    showRank();
}

int Rank::getIndex() 
{
    int length = getRankCount();
    if(length == 0) return 0;
    
    for(int i = length - 1; i >= 0; i--) {
        if(g_rank.nGrade < ranks[i]->nGrade)
            return i + 1;
    }
    return 0;
}

void Rank::insertIndex(int rankIndex) 
{
    if(rankIndex == 10 || g_rank.strName[0] == 0)
        return;

    int length = getRankCount();
    for(int i = 0; i < length; i++) {
        if(!strcmp(g_rank.strName, ranks[i]->strName)) {
            if(g_rank.nGrade <= ranks[i]->nGrade)
                return;
            else
                break;
        }
    }

    for(int i = 9; i > rankIndex; i--) {
        if(ranks[i-1]->nGrade > 0) {
            *ranks[i] = *ranks[i-1];
        }
    }
    
    ranks[rankIndex]->nGrade = g_rank.nGrade;
    strcpy(ranks[rankIndex]->strName, g_rank.strName);
    
    saveRankData();
    showRank();
}

void Rank::showRank() {
    QSqlQuery query;
    // 获取所有用户的最高分（非游客）
    query.prepare("SELECT username, MAX(score) as highest_score FROM leaderboard "
                 "GROUP BY username ORDER BY highest_score DESC LIMIT 10");
    
    if(query.exec()) {
        int row = 1;
        while(query.next() && row <= 10) {
            QString nameLabel = QString("label_%1").arg(row*3 - 2);
            QString scoreLabel = QString("label_%1").arg(row*3);
            
            QLabel* nameLabelWidget = findChild<QLabel*>(nameLabel);
            QLabel* scoreLabelWidget = findChild<QLabel*>(scoreLabel);
            
            if(nameLabelWidget) {
                nameLabelWidget->setText(query.value("username").toString());
            }
            if(scoreLabelWidget) {
                scoreLabelWidget->setText(query.value("highest_score").toString());
            }
            row++;
        }
        
        // 清空剩余的标签
        while(row <= 10) {
            QString nameLabel = QString("label_%1").arg(row*3 - 2);
            QString scoreLabel = QString("label_%1").arg(row*3);
            
            QLabel* nameLabelWidget = findChild<QLabel*>(nameLabel);
            QLabel* scoreLabelWidget = findChild<QLabel*>(scoreLabel);
            
            if(nameLabelWidget) nameLabelWidget->setText("");
            if(scoreLabelWidget) scoreLabelWidget->setText("");
            row++;
        }
    }
    
    this->show();
}

void Rank::on_actionClear_triggered() 
{
    for(int i = 0; i < 10; i++) {
        ranks[i]->nGrade = 0;
        ranks[i]->strName[0] = '-';
        ranks[i]->strName[1] = '\0';
    }
    saveRankData();
    showRank();
}

Rank::~Rank() 
{
    for(int i = 0; i < 10; i++) {
        delete ranks[i];
    }
    delete ui;
}

void Rank::closeEvent(QCloseEvent *event)
{
    emit rankClosed();
    event->accept();
    this->hide(); // 使用hide()而不是close()
}
