#include "setup.h"
#include "ui_setup.h"
#include <mainwindow.h>
#include <QThread>

// 静态成员初始化
QMediaPlayer* Setup::backgroundMusic = new QMediaPlayer;
QAudioOutput* Setup::audioOutput = new QAudioOutput;
float Setup::volume = 1.0f;
bool Setup::isMuted = false;

Setup::Setup(QWidget *parent) :
    QWidget(parent), ui(new Ui::ThemeChange) {
    ui->setupUi(this);
    QPixmap pixmap1(":/res/images/a1");
    QPixmap scaledPixmap1 = pixmap1.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label1->setPixmap(scaledPixmap1);
    ui->label_2->setPixmap(QPixmap(":/res/images/gem1"));
    QPixmap pixmap(":/res/images/c1");
    QPixmap scaledPixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_3->setPixmap(scaledPixmap);
    ui->label_4->setPixmap(QPixmap(":/res/images/fruit1"));
    ui->label_5->setPixmap(QPixmap(":/res/images/fish1"));
    ui->label_6->setPixmap(QPixmap(":/res/images/mine1"));

    initAudioControls();
}

Setup::~Setup() {
    delete ui;
}

void Setup::on_ToneButton_clicked() {
    emit themeChanged(":/res/images/a");

    QMessageBox::information(this, "主题切换", "已切换至主题1");
    //图片路径：/res/images/a
}

void Setup::on_TtwoButton_clicked() {
    emit themeChanged(":/res/images/gem");
    QMessageBox::information(this, "主题切换", "已切换至主题2");
    //图片路径：/res/images/b
}

void Setup::on_TthreeButton_clicked() {
    emit themeChanged(":/res/images/c");
    QMessageBox::information(this, "主题切换", "已切换至主题3");
    //图片路径：/res/images/c
}

void Setup::on_TfourButton_clicked() {
    emit themeChanged(":/res/images/fruit");
    QMessageBox::information(this, "主题切换", "已切换至主题4");
    //图片路径：/res/images/d
}

void Setup::on_TfiveButton_clicked() {
    emit themeChanged(":/res/images/fish");
    QMessageBox::information(this, "主题切换", "已切换至主题5");
    //图片路径：/res/images/fish
}

void Setup::on_TsixButton_clicked() {
    emit themeChanged(":/res/images/mine");
    QMessageBox::information(this, "主题切换", "已切换至主题6");
    //图片路径：/res/images/mine
}

void Setup::on_musicSetButton_clicked() {

}

void Setup::on_sizeSetButton_clicked() {
    // 获取用户输入的行和列值
    QString rowText = ui->rowLineEdit->text(); // 假设输入行值的 QLineEdit 对象名为 rowLineEdit
    QString colText = ui->colLineEdit->text(); // 假设输入列值的 QLineEdit 对象名为 colLineEdit

    // 转换为整型
    bool rowOk, colOk;
    int row = rowText.toInt(&rowOk);
    int col = colText.toInt(&colOk);

    // 检查输入是否为有效的整数
    if (!rowOk || !colOk) {
        QMessageBox::warning(this, "输入错误", "请输入有效的整数值！");
        return;
    }

    // 检查是否为正整数
    if (row <= 0 || col <= 0) {
        QMessageBox::warning(this, "输入错误", "行和列的值必须为正整数！");
        return;
    }

    // 提示用户界面修改后将重启游戏
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this,
                                  "注意",
                                  "界面大小的修改会改变游戏难度，请确认是否继续！",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return; // 用户选择取消，不发送信号
    }

    // 输出行和列值，发送信号
    QMessageBox::information(this, "成功", QString("行: %1, 列: %2").arg(row).arg(col));
    qDebug() << "发送行列信号：" << row << col;
    emit sizeChanged(row, col);
}

void Setup::initAudioControls() {
    // 只初始化UI控件,不初始化背景音乐
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(volume * 100);
    ui->muteButton->setChecked(isMuted);
    ui->muteButton->setText(isMuted ? "取消静音" : "静音");
}

void Setup::on_volumeSlider_valueChanged(int value) {
    volume = value / 100.0f;
    audioOutput->setVolume(volume);
    emit volumeChanged(volume);
}

void Setup::on_muteButton_clicked() {
    isMuted = !isMuted;
    audioOutput->setMuted(isMuted);
    ui->muteButton->setText(isMuted ? "取消静音" : "静音");
    emit muteStateChanged(isMuted);
}
