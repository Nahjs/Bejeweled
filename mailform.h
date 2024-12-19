#ifndef MAILFORM_H
#define MAILFORM_H

#include <QDialog>
#include <QMessageBox>
#include "smtp.h"

namespace Ui {
    class MailForm;
}

/**
 * @brief 邮件发送窗口类
 * 提供邮件发送的图形界面，包含收件人、主题、正文等输入框
 */
class MailForm : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit MailForm(QWidget *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~MailForm();

    private slots:
        /**
         * @brief 发送按钮点击处理函数
         * 收集用户输入的邮件信息并调用SMTP类发送邮件
         */
        void on_sendButton_clicked();

private:
    Ui::MailForm *ui;    // UI界面对象指针
};

#endif // MAILFORM_H
