#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QWidget>

class Verification : public QWidget
{
    Q_OBJECT
public:
    enum class BackgroundStyle {
        E_DOT
    };

    explicit Verification(QWidget *parent = nullptr);
    ~Verification();
    QString getVerificationCode() const { return m_verificationCode; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void sltTimerOut();

private:
    QString getVerificationCodeByRand();
    Qt::GlobalColor* getColors();
    void paintDot(QPainter* painter);

private:
    QString m_verificationCode;
    int m_codeNum;
    Qt::GlobalColor* m_colors;
    BackgroundStyle m_bstyle = BackgroundStyle::E_DOT;
};

#endif // VERIFICATION_H
