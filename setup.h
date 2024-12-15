#ifndef THEMECHANGE_H
#define THEMECHANGE_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
    class ThemeChange;
}

class Setup : public QWidget {
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = nullptr);
    ~Setup() override;

    signals:
        void themeChanged(const QString &themePath);

    private slots:
        void on_ToneButton_clicked();
    void on_TtwoButton_clicked();
    void on_TthreeButton_clicked();
    void on_TfourButton_clicked();
    void on_TfiveButton_clicked();
    void on_TsixButton_clicked();

private:
    Ui::ThemeChange *ui;
};

#endif // THEMECHANGE_H