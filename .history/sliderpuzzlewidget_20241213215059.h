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
    ~SliderPuzzleWidget();
    bool isVerified() const { return m_verified; }

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
