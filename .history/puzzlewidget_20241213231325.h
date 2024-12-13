#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QWidget>
#include <QRandomGenerator>

class PuzzleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PuzzleWidget(QWidget *parent = nullptr);
    ~PuzzleWidget();
    
    void setPixmap(const QString& pixmap);
    void setValue(int value);
    bool isOverlap();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onUpdatePixmap();
private:
    QString m_pixmap;
    int m_value;
    QPoint m_offsetPoint;
};

#endif // PUZZLEWIDGET_H
