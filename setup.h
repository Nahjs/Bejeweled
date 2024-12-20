#ifndef THEMECHANGE_H
#define THEMECHANGE_H

#include <QWidget>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
    class ThemeChange;
}

class Setup : public QWidget {
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = nullptr);
    ~Setup() override;

    static QMediaPlayer* backgroundMusic;
    static QAudioOutput* audioOutput;
    static float volume;
    static bool isMuted;

signals:
    void themeChanged(QString path);
    void sizeChanged(int row,int size);
    void volumeChanged(float volume);
    void muteStateChanged(bool muted);

private slots:
    void on_ToneButton_clicked();
    void on_TtwoButton_clicked();
    void on_TthreeButton_clicked();
    void on_TfourButton_clicked();
    void on_TfiveButton_clicked();
    void on_TsixButton_clicked();
    void on_musicSetButton_clicked();
    void on_sizeSetButton_clicked();
    void on_volumeSlider_valueChanged(int value);
    void on_muteButton_clicked();

private:
    Ui::ThemeChange *ui;
    void initAudioControls();
};

#endif // THEMECHANGE_H