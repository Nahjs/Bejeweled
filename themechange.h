//
// Created by 17914 on 24-12-9.
//

#ifndef THEMECHANGE_H
#define THEMECHANGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ThemeChange; }
QT_END_NAMESPACE

class ThemeChange : public QWidget {
Q_OBJECT

public:
    explicit ThemeChange(QWidget *parent = nullptr);
    ~ThemeChange() override;

private slots:
    void on_ToneButton_clicked();

private:
    Ui::ThemeChange *ui;
};


#endif //THEMECHANGE_H
