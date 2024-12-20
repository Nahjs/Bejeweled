#include "sliderpuzzlewidget.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QRandomGenerator>

SliderPuzzleWidget::SliderPuzzleWidget(QWidget *parent)
    : QWidget(parent), 
    m_verified(false),
    currentPos(0),
    targetPos(0)  // 初始化成员变量
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
    
    // 设置滑块的初始范围
    horizontalSlider->setMinimum(0);
    horizontalSlider->setMaximum(200);  // 设置一个合理的初始最大值
    
    layout->addWidget(puzzleWidget);
    layout->addWidget(horizontalSlider);
    
    QTimer::singleShot(100, this, SLOT(onUpdateWidget()));  // 增加延时确保控件已完成初始化
    connect(horizontalSlider, &QSlider::valueChanged, this, &SliderPuzzleWidget::onSliderValueChanged);
    connect(horizontalSlider, &QSlider::sliderReleased, this, &SliderPuzzleWidget::onSliderReleased);
    
    puzzleWidget->setPixmap(":/res/images/c3.png");
    setFixedSize(201, 191);  // 使用与verificationFrame相同的尺寸
}

void SliderPuzzleWidget::onUpdateWidget()
{
    if (width() > 0) {  // 确保宽度大于0
        horizontalSlider->setRange(0, width());
    } else {
        horizontalSlider->setRange(0, 200);  // 设置默认范围
    }
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

void SliderPuzzleWidget::reset()
{
    m_verified = false;
    horizontalSlider->setValue(0);  // 重置滑块位置
    currentPos = 0;
    targetPos = generateRandomPosition();  // 使用随机生成的位置
    update();  // 刷新界面
}

int SliderPuzzleWidget::generateRandomPosition() const
{
    // 设置合理的范围,避免太靠边
    const int minPos = width() * 0.2;  // 左边界为20%宽度
    const int maxPos = width() * 0.7;  // 右边界为70%宽度
    
    // 生成随机位置
    return QRandomGenerator::global()->bounded(minPos, maxPos);
}

// 在验证逻辑中调整判定范围
bool SliderPuzzleWidget::checkPosition() const
{
    // 允许有5像素的误差范围
    const int errorMargin = 5;
    return qAbs(currentPos - targetPos) <= errorMargin;
}
