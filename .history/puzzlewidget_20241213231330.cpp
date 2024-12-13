#include "puzzlewidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QTime>
#include <QTimer>
#include <QRandomGenerator>

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
    if (width() <= 0 || height() <= 0) {
        return;  // 防止尺寸无效时的计算
    }
    
    // 计算有效的范围
    int maxX = qMax(0, width() - squarewidth - squareradius);
    int maxY = qMax(0, height() - squarewidth - squareradius);
    
    // 将可用区域划分为多个部分，确保拼图块可以出现在不同位置
    int xSection = maxX / 3;
    int ySection = maxY / 2;
    
    // 使用 QRandomGenerator 生成随机数
    int section = QRandomGenerator::global()->bounded(6); // 总共有 3x2=6 个区域
    
    // 根据选中的区域计算基准位置
    
    // 根据选中的区域计算基准位置
    int baseX = (section % 3) * xSection;
    int baseY = (section / 3) * ySection;
    
    // 在选中的区域内随机生成具体位置
    m_offsetPoint.rx() = qBound(0, baseX + (qrand() % xSection), maxX);
    m_offsetPoint.ry() = qBound(0, baseY + (qrand() % ySection), maxY);
    
    update();
}

void PuzzleWidget::setValue(int value)
{
    int maxValue = qMax(0, this->width() - squarewidth - squareradius + m_offsetPoint.x());
    m_value = qBound(0, value, maxValue);
    update();
}

void PuzzleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    
    // 绘制背景
    QPainterPath clippath;
    clippath.addRoundedRect(this->rect(), 4, 4);
    painter.setClipPath(clippath);
    const QPixmap& pixmap = QPixmap(m_pixmap).scaled(this->width(), this->height(), 
                                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    // 创建拼图形状
    QPainterPath cutoutpath;
    cutoutpath.setFillRule(Qt::WindingFill);
    QRect rect(m_offsetPoint, QSize(squarewidth, squarewidth));
    cutoutpath.addRoundedRect(rect, 2, 2);
    cutoutpath.addEllipse(rect.center().x() - squareradius / 2, 
                         rect.top() - squareradius + 6, squareradius, squareradius);
    
    // 创建凹槽
    QPainterPath subellipseparh;
    subellipseparh.addEllipse(rect.right() - squareradius + 6, 
                             rect.center().y() - squareradius / 2, squareradius, squareradius);
    cutoutpath -= subellipseparh;

    // 绘制拼图区域阴影
    painter.setPen(QPen(QColor(80, 80, 80), 1));
    painter.setBrush(QColor(100, 100, 100, 220));
    painter.drawPath(cutoutpath);

    // 绘制移动的拼图块
    QPixmap puzzlePixmap(this->size());
    puzzlePixmap.fill(Qt::transparent);
    QPainter puzzlePainter(&puzzlePixmap);
    puzzlePainter.setRenderHints(QPainter::Antialiasing);
    puzzlePainter.setClipPath(cutoutpath);
    puzzlePainter.setPen(QPen(QColor(80, 80, 80), 2));
    puzzlePainter.setBrush(QColor(200, 200, 200, 100));
    puzzlePainter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
    puzzlePainter.drawPath(cutoutpath);

    painter.drawPixmap(-m_offsetPoint.x() + m_value, 0, this->width(), this->height(), puzzlePixmap);
}

bool PuzzleWidget::isOverlap()
{
    return qAbs(-m_offsetPoint.x() + m_value) < 5;
}
