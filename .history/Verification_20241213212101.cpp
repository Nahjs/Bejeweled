#include "Verification.h"
#include <QPainter>
#include <QTime>
#include <QTimer>

verification::verification(QWidget *parent)
    : QWidget(parent), m_verificationCode(QString()), m_codeNum(4)
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    m_verificationCode = getVerificationCodeByRand();
    m_colors = getColors();
}

verification::~verification()
{
}

void verification::sltTimerOut()
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    m_colors = getColors();
    update();
}

QString verification::getVerificationCodeByRand()
{
    QString destCode = QString();
    for (int i = 0; i < m_codeNum; i++) {
        int flag = qrand() % 2;
        if (0 == flag) {