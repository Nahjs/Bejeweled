#include "setup.h"
#include "ui_setup.h"
#include <mainwindow.h>
#include <QThread>

Setup::Setup(QWidget *parent) :
    QWidget(parent), ui(new Ui::ThemeChange) {
    ui->setupUi(this);
}

Setup::~Setup() {
    delete ui;
}

void Setup::on_ToneButton_clicked() {
    emit themeChanged(":/res/images/a");

    QMessageBox::information(this, "主题切换", "已切换至主题1");
    //图片路径：/res/images/a
}

void Setup::on_TtwoButton_clicked() {
    emit themeChanged(":/res/images/gem");
    QMessageBox::information(this, "主题切换", "已切换至主题2");
    //图片路径：/res/images/b
}

void Setup::on_TthreeButton_clicked() {
    emit themeChanged(":/res/images/c");
    QMessageBox::information(this, "主题切换", "已切换至主题3");
    //图片路径：/res/images/c
}

void Setup::on_TfourButton_clicked() {
    emit themeChanged(":/res/images/fruit");
    QMessageBox::information(this, "主题切换", "已切换至主题4");
    //图片路径：/res/images/d
}

void Setup::on_TfiveButton_clicked() {
    emit themeChanged(":/res/images/fish");
    QMessageBox::information(this, "主题切换", "已切换至主题5");
    //图片路径：/res/images/fish
}

void Setup::on_TsixButton_clicked() {
    emit themeChanged(":/res/images/mine");
    QMessageBox::information(this, "主题切换", "已切换至主题6");
    //图片路径：/res/images/mine
}