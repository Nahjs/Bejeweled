#ifndef MAILFORM_H
#define MAILFORM_H

#include <QDialog>
#include <QMessageBox>
#include "smtp.h"

namespace Ui {
class MailForm;
}

class MailForm : public QDialog
{
    Q_OBJECT

public:
    explicit MailForm(QWidget *parent = nullptr);
    ~MailForm();

private slots:
    void on_sendButton_clicked();

private:
    Ui::MailForm *ui;
};

#endif // MAILFORM_H
