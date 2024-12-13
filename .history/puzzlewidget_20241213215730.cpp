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