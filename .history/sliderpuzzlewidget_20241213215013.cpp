#include "sliderpuzzlewidget.h"
#include <QVBoxLayout>
#include <QTimer>

SliderPuzzleWidget::SliderPuzzleWidget(QWidget *parent)
    : QWidget(parent), m_verified(false)
{
    auto *layout = new QVBoxLayout(this);
    
    puzzleWidget = new PuzzleWidget(this);
    puzzleWidget->setMinimumHeight(150);
    
    horizontalSlider = new QSlider(Qt::Horizontal, this);
    horizontalSlider->setFixedHeight(30);
    
    layout->addWidget(puzzleWidget);
    layout->addWidget(horizontalSlider);
    
    setLayout(layout);
    initForm();
}

void SliderPuzzleWidget::initForm()
{
    QTimer::singleShot(10, this, &SliderPuzzleWidget::onUpdateWidget);
    connect(horizontalSlider, &QSlider::valueChanged, this, &SliderPuzzleWidget::onSliderValueChanged);
    connect(horizontalSlider, &QSlider::sliderReleased, this, &SliderPuzzleWidget::onSliderReleased);
    puzzleWidget->setPixmap(":/images/verify_back1.jpg");
}

void SliderPuzzleWidget::onUpdateWidget()
{
    horizontalSlider->setRange(0, width());
}

void SliderPuzzleWidget::onSliderValueChanged(int value)
{
    puzzleWidget->setValue(value);
}

void SliderPuzzleWidget::onSliderReleased()
{
    m_verified = puzzleWidget->isOverlap();
    if (!m_verified) {
        horizontalSlider->setValue(0);
    }
}
