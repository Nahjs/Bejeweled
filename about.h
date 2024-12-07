#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include <QTime>

namespace Ui {
class About;
}

class About : public QMainWindow
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
    QString lastupdatetime;
};

#endif // ABOUT_H
