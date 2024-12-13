#include "rank.h"
#include "ui_rank.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include <QLabel>

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
}

void Rank::loadRankData() 
{
    QFile file("rank.dat");
    if(file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        for(int i = 0; i < 10; i++) {
            in.readRawData(ranks[i]->strName, 50);
            in >> ranks[i]->nGrade;
        }
        file.close();
    }
}

void Rank::saveRankData() 
{
    QFile file("rank.dat");
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

void Rank::showRank() 
{
    QString name;
    QString grade;
    int length = getRankCount();

    for(int i = 1; i <= 10; i++) {
        QString nameLabel = QString("label_%1").arg(i*3 - 2);
        QString scoreLabel = QString("label_%1").arg(i*3);
        QLabel* nameLabelWidget = findChild<QLabel*>(nameLabel);
        QLabel* scoreLabelWidget = findChild<QLabel*>(scoreLabel);
        
        if(i <= length) {
            name = QString::fromLatin1(ranks[i-1]->strName);
            grade = QString::number(ranks[i-1]->nGrade);
        } else {
            name = "";
            grade = "";
        }
        
        if(nameLabelWidget) nameLabelWidget->setText(name);
        if(scoreLabelWidget) scoreLabelWidget->setText(grade);
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
