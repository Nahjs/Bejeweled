#ifndef SLIDERPUZZLEWIDGET_H
#define SLIDERPUZZLEWIDGET_H

#include <QWidget>
#include <QSlider>
#include "puzzlewidget.h"

class SliderPuzzleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SliderPuzzleWidget(QWidget *parent = nullptr);
    virtual ~SliderPuzzleWidget();
    bool isVerified() const { return m_verified; }
    void reset();  // 添加重置方法

private slots:
    void onUpdateWidget();
    void onSliderValueChanged(int value);
    void onSliderReleased();

private:
    void initForm();
    QSlider *horizontalSlider;
    PuzzleWidget *puzzleWidget;
    bool m_verified;
};

#endif // SLIDERPUZZLEWIDGET_H
