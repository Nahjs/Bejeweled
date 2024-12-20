#include "propshop.h"
#include "ui_propshop.h"
#include "login.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

PropShop::PropShop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropShop)
{
    ui->setupUi(this);
    setWindowTitle("道具商城");
    
    // 加载用户金币
    loadUserCoins();
    
    // 更新显示
    updateDisplay();
}

PropShop::~PropShop()
{
    delete ui;
}

// 道具商店的实现文件，包含购买道具和界面更新的具体逻辑
void PropShop::loadUserCoins()
{
    if(!Login::isGuest) {
        // 从数据库加载用户的金币和道具数量
        QSqlQuery query;
        query.prepare("SELECT coins, props_boom, props_row, props_col, props_color FROM user WHERE username = ?");
        query.addBindValue(Login::currentUsername);
        
        if(query.exec() && query.next()) {
            g_coins = query.value(0).toInt();
            g_props_boom = query.value(1).toInt();
            g_props_row = query.value(2).toInt();
            g_props_col = query.value(3).toInt();
            g_props_color = query.value(4).toInt();
        }
    } else {
        // 游客模式使用内存中的默认值
        // g_coins和道具数量保持当前值
    }
}

void PropShop::updateDisplay()
{
    // 更新金币显示
    ui->label_coins->setText(QString("当前金币: %1").arg(g_coins));
    
    // 更新道具数量显示
    ui->label_boom_count->setText(QString("拥有数量: %1").arg(g_props_boom));
    ui->label_row_count->setText(QString("拥有数量: %1").arg(g_props_row));
    ui->label_col_count->setText(QString("拥有数量: %1").arg(g_props_col));
    ui->label_color_count->setText(QString("拥有数量: %1").arg(g_props_color));
    
    // 更新价格显示
    ui->label_boom_price->setText(QString("价格: %1金币").arg(PRICE_BOOM));
    ui->label_row_price->setText(QString("价格: %1金币").arg(PRICE_ROW));
    ui->label_col_price->setText(QString("价格: %1金币").arg(PRICE_COL));
    ui->label_color_price->setText(QString("价格: %1金币").arg(PRICE_COLOR));
}

// 通用的道具购买逻辑
bool PropShop::buyProp(int price, int& propCount, const QString& propName)
{
    if(g_coins < price) {
        QMessageBox::warning(this, "购买失败", "金币不足!");
        return false;
    }
    
    // 扣除金币并增加道具数量
    g_coins -= price;
    propCount++;
    updateDatabase();
    updateDisplay();
    
    QMessageBox::information(this, "购买成功", 
        QString("成功购买%1!").arg(propName));
    return true;
}

void PropShop::updateDatabase()
{
    if(!Login::isGuest) {
        QSqlQuery query;
        query.prepare("UPDATE user SET coins = ?, props_boom = ?, props_row = ?, "
                     "props_col = ?, props_color = ? WHERE username = ?");
        query.addBindValue(g_coins);
        query.addBindValue(g_props_boom);
        query.addBindValue(g_props_row);
        query.addBindValue(g_props_col);
        query.addBindValue(g_props_color);
        query.addBindValue(Login::currentUsername);
        
        if(!query.exec()) {
            qDebug() << "Failed to update props:" << query.lastError() 
                     << "\nSQL:" << query.lastQuery()
                     << "\nValues:" << g_coins << g_props_boom << g_props_row 
                     << g_props_col << g_props_color << Login::currentUsername;
        }
    }
    // 游客模式不需要更新数据库，直接使用内存中的值
}

void PropShop::on_btn_buyBoom_clicked()
{
    buyProp(PRICE_BOOM, g_props_boom, "爆炸道具");
}

void PropShop::on_btn_buyRow_clicked()
{
    buyProp(PRICE_ROW, g_props_row, "行消除道具");
}

void PropShop::on_btn_buyCol_clicked()
{
    buyProp(PRICE_COL, g_props_col, "列消除道具");
}

void PropShop::on_btn_buyColor_clicked()
{
    buyProp(PRICE_COLOR, g_props_color, "同色消除道具");
}
