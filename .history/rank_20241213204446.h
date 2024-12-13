#ifndef RANK_H
#define RANK_H

#include <QMainWindow>
#include <QString>
#include <QTimer>

typedef struct RankStruct {
    char strName[50];
    int nGrade;
    int nRank;
} Rankstruct;

namespace Ui {
class Rank;
}

class Rank : public QMainWindow {
    Q_OBJECT

public:
    static Rank* getInstance();
    void updateRank();
    int getIndex();
    void insertIndex(int rankIndex);
    void showRank();
    ~Rank();

    void closeEvent(QCloseEvent *event) override;

    static Rankstruct g_rank;
    static Rankstruct* ranks[10];

signals:
    void rankClosed(); // 信号声明

private slots:
    void on_actionClear_triggered();
    void onTimeout();

private:
    explicit Rank(QWidget *parent = nullptr);
    static Rank* instance;
    Ui::Rank *ui;
    
    void loadRankData();
    void saveRankData();
    int getRankCount();
    QTimer *timer;
    void updateTime();
    QString getCurrentDateTime();
};

#endif // RANK_H
