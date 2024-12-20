#ifndef PROPSHOP_H
#define PROPSHOP_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "prop.h"

namespace Ui {
class PropShop;
}

class PropShop : public QDialog
{
    Q_OBJECT

public:
    explicit PropShop(QWidget *parent = nullptr);
    ~PropShop();
    void updateDisplay();  // 更新显示
    void loadUserCoins(); // 加载用户金币

private slots:
    void on_btn_buyBoom_clicked();
    void on_btn_buyRow_clicked();
    void on_btn_buyCol_clicked();
    void on_btn_buyColor_clicked();

private:
    Ui::PropShop *ui;
    bool buyProp(int price, int& propCount, const QString& propName);
    void updateDatabase();  // 更新数据库中的道具数量和金币
};

#endif // PROPSHOP_H
