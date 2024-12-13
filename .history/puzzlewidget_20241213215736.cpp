#include "puzzlewidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QTime>
#include <QTimer>

const int squarewidth = 46;
const int squareradius = 20;

PuzzleWidget::PuzzleWidget(QWidget *parent)
    : QWidget(parent)
    , m_value(0)
    , m_offsetPoint(0, 0)
{
    srand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

PuzzleWidget::~PuzzleWidget()
{
}

void PuzzleWidget::setPixmap(const QString& pixmap)
{
    m_pixmap = pixmap;
    QTimer::singleShot(10, this, SLOT(onUpdatePixmap()));
}

void PuzzleWidget::onUpdatePixmap()
{
    m_offsetPoint.rx() = qBound(0, rand() % this->width() + squarewidth + squareradius, 
                               this->width() - squarewidth - squareradius);
    m_offsetPoint.ry() = qBound(0, rand() % this->height() + squarewidth + squareradius, 
                               this->height() - squarewidth - squareradius);
    update();
}

void PuzzleWidget::setValue(int value)
{
    m_value = qBound(0, value, this->width() - squarewidth - squareradius + m_offsetPoint.x());
    update();
}