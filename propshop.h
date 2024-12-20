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

// 道具商店的头文件，定义了道具商店界面的类结构
class PropShop : public QDialog
{
    Q_OBJECT

public:
    explicit PropShop(QWidget *parent = nullptr);
    ~PropShop();
    void updateDisplay();  // 更新商店界面显示
    void loadUserCoins(); // 从数据库加载用户金币数据

private slots:
    // 各种道具购买按钮的槽函数
    void on_btn_buyBoom_clicked();
    void on_btn_buyRow_clicked();
    void on_btn_buyCol_clicked();
    void on_btn_buyColor_clicked();

private:
    Ui::PropShop *ui;
    bool buyProp(int price, int& propCount, const QString& propName); // 通用的道具购买逻辑
    void updateDatabase();  // 将道具数量和金币更新到数据库
};

#endif // PROPSHOP_H
