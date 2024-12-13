#include "sliderpuzzlewidget.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

SliderPuzzleWidget::SliderPuzzleWidget(QWidget *parent)
    : QWidget(parent), m_verified(false)
{
    initForm();
}

SliderPuzzleWidget::~SliderPuzzleWidget()
{
    delete horizontalSlider;
    delete puzzleWidget;
}

void SliderPuzzleWidget::initForm()
{
    auto *layout = new QVBoxLayout(this);
    
    puzzleWidget = new PuzzleWidget(this);
    horizontalSlider = new QSlider(Qt::Horizontal, this);
    
    layout->addWidget(puzzleWidget);
    layout->addWidget(horizontalSlider);
    
    QTimer::singleShot(10, this, SLOT(onUpdateWidget()));
    connect(horizontalSlider, &QSlider::valueChanged, this, &SliderPuzzleWidget::onSliderValueChanged);
    connect(horizontalSlider, &QSlider::sliderReleased, this, &SliderPuzzleWidget::onSliderReleased);
    
    puzzleWidget->setPixmap(":/res/images/c3.png");  // 修改为使用c3.png
    setFixedSize(300, 200);
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
    if (m_verified) {
        QMessageBox::information(this, "验证", "验证成功！");
        hide();
    } else {
        QMessageBox::warning(this, "验证", "验证失败，请重试！");
        horizontalSlider->setValue(0);
        puzzleWidget->setPixmap(":/res/images/c3.png");  // 修改为使用c3.png
    }
}
