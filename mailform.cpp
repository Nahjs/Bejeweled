#include "mailform.h"
#include "ui_mailform.h"

/**
 * @brief 构造函数：初始化邮件发送窗口
 * @param parent 父窗口指针
 */
MailForm::MailForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailForm)
{
    ui->setupUi(this);
    setWindowTitle("发送邮件");
}

/**
 * @brief 析构函数：清理资源
 */
MailForm::~MailForm()
{
    delete ui;
}

/**
 * @brief 发送按钮点击事件处理
 * 验证输入数据的完整性，创建SMTP对象发送邮件
 */
void MailForm::on_sendButton_clicked()
{
    // 获取用户输入的邮件信息
    QString recipient = ui->recipientEdit->text();
    QString subject = ui->subjectEdit->text();
    QString body = ui->bodyEdit->toPlainText();

    // 验证输入数据的完整性
    if(recipient.isEmpty() || subject.isEmpty() || body.isEmpty()) {
        QMessageBox::warning(this, "警告", "请填写完整的邮件信息！");
        return;
    }

    // 准备收件人列表
    QStringList recipients;
    recipients << recipient;

    // 创建SMTP对象并发送邮件
    // 注意：需要替换为实际的SMTP服务器信息和账号密码
    Smtp* smtp = new Smtp("smtp.qq.com", "your-email@qq.com", "your-password",
                         "your-email@qq.com", recipients, subject, body);

    // 连接状态信号，显示发送结果
    connect(smtp, &Smtp::status, [this](const QString &status) {
        QMessageBox::information(this, "提示", status);
    });
}
