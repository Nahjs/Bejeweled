#include "name.h"
#include "ui_name.h"

Name::Name(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Name)
{
    ui->setupUi(this);
}

Name::~Name()
{
    delete ui;
}

void Name::on_btn_confirm_clicked()
{
    memset(g_rank.strName, 0, sizeof (char) * 50);
    strcpy(g_rank.strName, ui->lineEdit_name->text().toLatin1().toStdString().c_str());
    this->close();
    emit nameConfirm();
}

//void CNameDlg::closeEvent(QCloseEvent *event)
//{
//    event->ignore();
//    on_btn_confirm_clicked();
//}
