//
// Created by 17914 on 24-12-9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ThemeChange.h" resolved

#include "themechange.h"
#include "ui_ThemeChange.h"
#include <QMessageBox>

ThemeChange::ThemeChange(QWidget *parent) :
    QWidget(parent), ui(new Ui::ThemeChange) {
    ui->setupUi(this);

}

ThemeChange::~ThemeChange() {
    delete ui;
}

void ThemeChange::on_ToneButton_clicked() {
    QMessageBox::information(this, "主题切换", "已切换至主题1");
}
