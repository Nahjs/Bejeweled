#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QWidget>

/**
 * @brief 验证码生成和显示控件类
 * 用于生成图形验证码并提供交互功能
 */
class Verification : public QWidget
{
    Q_OBJECT
public:
    // 验证码背景样式枚举
    enum class BackgroundStyle {
        E_DOT   // 点状背景
    };

    explicit Verification(QWidget *parent = nullptr);
    ~Verification();
    
    /**
     * @brief 获取当前验证码
     * @return 返回当前验证码字符串
     */
    QString getVerificationCode() const { return m_verificationCode; }
    
    /**
     * @brief 刷新验证码
     * 重新生成验证码并更新显示
     */
    void refreshCode() {
        m_verificationCode = getVerificationCodeByRand();
        m_colors = getColors();
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override;         // 绘制事件
    void mouseDoubleClickEvent(QMouseEvent *event) override;  // 鼠标双击事件

private slots:
    void sltTimerOut();  // 定时器超时处理

private:
    /**
     * @brief 随机生成验证码
     * @return 返回生成的验证码字符串
     */
    QString getVerificationCodeByRand();
    
    /**
     * @brief 获取随机颜色数组
     * @return 返回随机生成的颜色数组
     */
    Qt::GlobalColor* getColors();
    
    /**
     * @brief 绘制背景噪点
     * @param painter 绘图对象指针
     */
    void paintDot(QPainter* painter);

private:
    QString m_verificationCode;        // 验证码内容
    int m_codeNum;                    // 验证码字符数量
    Qt::GlobalColor* m_colors;        // 验证码字符颜色数组
    BackgroundStyle m_bstyle = BackgroundStyle::E_DOT;  // 背景样式
};

#endif // VERIFICATION_H
