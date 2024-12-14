#include "mailform.h"
#include "ui_mailform.h"

MailForm::MailForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailForm)
{
    ui->setupUi(this);
    setWindowTitle("发送邮件");
}

MailForm::~MailForm()
{
    delete ui;
}

void MailForm::on_sendButton_clicked()
{
    QString recipient = ui->recipientEdit->text();
    QString subject = ui->subjectEdit->text();
    QString body = ui->bodyEdit->toPlainText();

    if(recipient.isEmpty() || subject.isEmpty() || body.isEmpty()) {
        QMessageBox::warning(this, "警告", "请填写完整的邮件信息！");
        return;
    }

    QStringList recipients;
    recipients << recipient;

    // 这里使用QQ邮箱SMTP服务器作为示例，您需要替换为实际的服务器信息
    Smtp* smtp = new Smtp("smtp.qq.com", "your-email@qq.com", "your-password",
                         "your-email@qq.com", recipients, subject, body);
    
    connect(smtp, &Smtp::status, [this](const QString &status) {
        QMessageBox::information(this, "提示", status);
    });
}
