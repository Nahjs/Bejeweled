#include "Verification.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QRandomGenerator>  

/**
 * @brief 构造函数
 * @param parent 父窗口指针
 * 初始化验证码控件，生成首次验证码
 */
Verification::Verification(QWidget *parent)
    : QWidget(parent), m_verificationCode(QString()), m_codeNum(4)
{
    m_verificationCode = getVerificationCodeByRand();
    m_colors = getColors();
}

/**
 * @brief 析构函数
 */
Verification::~Verification()
{
}

/**
 * @brief 定时器超时处理
 * 更新验证码颜色并重绘
 */
void Verification::sltTimerOut()
{
    m_colors = getColors();
    update();
}

/**
 * @brief 随机生成验证码
 * @return 返回生成的验证码字符串
 * 生成包含数字和字母的随机验证码
 */
QString Verification::getVerificationCodeByRand()
{
    QString destCode = QString();
    for (int i = 0; i < m_codeNum; i++) {
        int flag = QRandomGenerator::global()->bounded(2);  // 随机选择数字或字母
        if (0 == flag) {
            // 生成随机数字
            int c = '0' + QRandomGenerator::global()->bounded(10);
            destCode += static_cast<QChar>(c);
        }
        else {
            // 生成随机字母（大小写随机）
            int c = (QRandomGenerator::global()->bounded(2)) ? 'a' : 'A';
            destCode += static_cast<QChar>(c + QRandomGenerator::global()->bounded(26));
        }
    }
    return destCode;
}

/**
 * @brief 获取随机颜色数组
 * @return 返回随机生成的颜色数组
 */
Qt::GlobalColor* Verification::getColors()
{
    static Qt::GlobalColor colors[4];
    for (int i = 0; i < 4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>(2 + QRandomGenerator::global()->bounded(16));  // 替换 qrand() % 16
    }
    return colors;
}

/**
 * @brief 绘制事件处理
 * @param event 绘制事件对象
 * 负责验证码的可视化展示
 */
void Verification::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    // 绘制背景
    painter.fillRect(0, 0, 100, 30, QColor(255, 250, 240));
    painter.setFont(QFont("Comic Sans MS", 12));

    // 绘制验证码字符
    for (int i = 0; i < m_codeNum; i++)
    {
        painter.setPen(m_colors[i]);
        painter.drawText(25 * i, 0, 25, 30, Qt::AlignCenter, QString(m_verificationCode[i]));
    }

    // 根据样式绘制背景
    if (m_bstyle == BackgroundStyle::E_DOT)
        paintDot(&painter);
}

/**
 * @brief 绘制背景噪点
 * @param painter 绘图对象指针
 * 添加随机噪点增加验证码识别难度
 */
void Verification::paintDot(QPainter* painter)
{
    if (Q_NULLPTR == painter)
        return;

    // 随机绘制150个噪点
    for (int i = 0; i < 150; i++)
    {
        painter->setPen(m_colors[i % 4]);
        painter->drawPoint(QRandomGenerator::global()->bounded(99),
                         QRandomGenerator::global()->bounded(29));
    }
}

/**
 * @brief 鼠标双击事件处理
 * @param event 鼠标事件对象
 * 双击时刷新验证码
 */
void Verification::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_verificationCode = getVerificationCodeByRand();
    m_colors = getColors();
    update();
    QWidget::mouseDoubleClickEvent(event);
}
