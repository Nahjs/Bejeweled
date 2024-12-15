#include "setup.h"
#include "ui_setup.h"

Setup::Setup(QWidget *parent) :
    QWidget(parent), ui(new Ui::ThemeChange) {
    ui->setupUi(this);
}

Setup::~Setup() {
    delete ui;
}

void Setup::on_ToneButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题1");
    emit themeChanged(":/res/images/a");
}

void Setup::on_TtwoButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题2");
    emit themeChanged(":/res/images/b");
}

void Setup::on_TthreeButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题3");
    emit themeChanged(":/res/images/c");
}

void Setup::on_TfourButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题4");
    emit themeChanged(":/res/images/d");
}

void Setup::on_TfiveButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题5");
    emit themeChanged(":/res/images/fish");
}

void Setup::on_TsixButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题6");
    emit themeChanged(":/res/images/mine");
}