#ifndef RANK_H
#define RANK_H

#include <QMainWindow>
#include <crankdao.h>

namespace Ui {
class Rank;
}

class Rank : public QMainWindow
{
    Q_OBJECT

public:
    static Rank * getCRankDlg();
    void showRank();
    ~Rank();

private slots:
   // void on_actionClear_triggered();

private:
    explicit Rank(QWidget *parent = nullptr);
    static Rank * crankdlg;
    Ui::Rank *ui;
    int ranknum;
};
#endif // RANK_H
