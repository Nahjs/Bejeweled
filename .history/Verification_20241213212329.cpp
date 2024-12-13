#include "Verification.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QRandomGenerator>  // 添加这个头文件

Verification::Verification(QWidget *parent)
    : QWidget(parent), m_verificationCode(QString()), m_codeNum(4)
{
    m_verificationCode = getVerificationCodeByRand();
    m_colors = getColors();
}

Verification::~Verification()
{
}

void Verification::sltTimerOut()
{
    m_colors = getColors();
    update();
}

QString Verification::getVerificationCodeByRand()
{
    QString destCode = QString();
    for (int i = 0; i < m_codeNum; i++) {
        int flag = QRandomGenerator::global()->bounded(2);  // 替换 qrand() % 2
        if (0 == flag) {
            int c = '0' + QRandomGenerator::global()->bounded(10);  // 替换 qrand() % 10
            destCode += static_cast<QChar>(c);
        }
        else {
            int c = (QRandomGenerator::global()->bounded(2)) ? 'a' : 'A';  // 替换 qrand() % 2
            destCode += static_cast<QChar>(c + QRandomGenerator::global()->bounded(26));  // 替换 qrand() % 26
        }
    }
    return destCode;
}

Qt::GlobalColor* Verification::getColors()
{
    static Qt::GlobalColor colors[4];
    for (int i = 0; i < 4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>(2 + QRandomGenerator::global()->bounded(16));  // 替换 qrand() % 16
    }
    return colors;
}

void Verification::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    //填充验证码绘制矩形
    painter.fillRect(0, 0, 100, 30, QColor(255, 250, 240));
    painter.setFont(QFont("Comic Sans MS", 12));

    //绘制验证码
    //绘制验证码
    for (int i = 0; i < m_codeNum; i++)
    {
        painter.setPen(m_colors[i]);
        painter.drawText(25 * i, 0, 25, 30, Qt::AlignCenter, QString(m_verificationCode[i]));
    }

    //绘制噪点
    if (m_bstyle == BackgroundStyle::E_DOT)
        paintDot(&painter);
}

void Verification::paintDot(QPainter* painter)
{
    if (Q_NULLPTR == painter)
        return;

    //绘制噪点
    for (int i = 0; i < 150; i++)
    {
        painter->setPen(m_colors[i % 4]);
        painter->drawPoint(qrand() % 99, qrand() % 29);
    }
}

void Verification::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_verificationCode = getVerificationCodeByRand();
    m_colors = getColors();
    update();
    QWidget::mouseDoubleClickEvent(event);
}
