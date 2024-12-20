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
    bool isVerified() const { return m_verified; }  // 获取验证状态
    void reset();                                   // 重置滑块状态

private slots:
    void onUpdateWidget();                         // 更新控件尺寸
    void onSliderValueChanged(int value);          // 处理滑块值变化
    void onSliderReleased();                       // 处理滑块释放事件

private:
    void initForm();                               // 初始化界面
    bool checkPosition() const;                    // 检查滑块位置是否正确
    int generateRandomPosition() const;            // 生成随机目标位置
    
    QSlider *horizontalSlider;                     // 滑动条控件
    PuzzleWidget *puzzleWidget;                    // 拼图控件
    bool m_verified;                               // 验证状态
    int currentPos;                                // 当前位置
    int targetPos;                                 // 目标位置
};

#endif // SLIDERPUZZLEWIDGET_H
