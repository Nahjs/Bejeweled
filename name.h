#ifndef CNAMEDLG_H
#define CNAMEDLG_H

#include <QMainWindow>
#include <QCloseEvent>
#include <Global.h>

namespace Ui {
class Name;
}

class Name : public QMainWindow
{
    Q_OBJECT

public:
    explicit Name(QWidget *parent = nullptr);
    ~Name();

signals:
    void nameConfirm();

private slots:
    void on_btn_confirm_clicked();

private:
//    void closeEvent(QCloseEvent *event);
    Ui::Name *ui;
};

#endif // CNAMEDLG_H
