#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "numMatrix.h"
#include <string.h>
#include <QDebug>
#include <QTimer>
#include <thread>
#include <chrono>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

#include "rank.h"
#include "prop.h"


namespace Ui {
class Mainwindow;
}

/**
 * @brief 主游戏窗口类
 * 处理游戏界面显示、用户交互及游戏逻辑控制
 */
class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

    void Music();                        // 音乐控制
    void Game_over(bool saveRank = true);// 游戏结束处理
    NumMatrix* getNumMatrix() { return numMatrix; } // 获取NumMatrix对象
    void Game_start();                    // 游戏开始
    void setLevelMode(bool isLevel);
    void setLevelConfig(int levelId, int targetScore, int time, int mapSize, int gemTypes, int steps);

signals:
    void gameToStart();
    void gameToMenu();
    void gameToLevel();  // 添加新的信号

public slots:
  //  void closeFromRank();  // 从排行榜返回处理
    void updateGemTheme(QString path);

private slots:
    void on_btn_gameToStart_clicked();    // 返回开始界面按钮点击
    void doStartToGame();                 // 开始游戏处理
    void doMenuToGame();                  // 返回游戏处理
    void on_btn_gameToMenu_clicked();     // 返回菜单按钮点击
    void do_theme_background_change(QString); // 主题背景更改
    void on_pushButton_stop_clicked();    // 暂停按钮点击
    void update();                // 时间条更新
    void on_pushButton_continue_clicked();// 继续游戏
    void on_pushButton_restart_clicked(); // 重新开始
    void do_btn_hint();                   // 提示按钮处理
    void paintEvent(QPaintEvent *event);  // 绘制事件
    void closeEvent(QCloseEvent *event);  // 关闭事件

    // 音乐控制按钮
    void on_pushButton_clicked();         // 音乐开
    void on_pushButton_2_clicked();       // 音乐关

    // 道具按钮点击处理
    void on_pushButton_row_clicked();     // 行消除道具
    void on_pushButton_col_clicked();     // 列消除道具
    void on_pushButton_color_clicked();   // 同色消除道具
    void on_pushButton_boom_clicked();    // 爆炸道具

    void updateBackgroundMusic(float volume);
    void updateMuteState(bool muted);
    void on_bgmSlider_valueChanged(int value);
    void on_effectSlider_valueChanged(int value);

private:
    Ui::Mainwindow *ui;           // UI界面
    QTimer *timer;                // 游戏计时器
    QImage *image_stop;           // 暂停图片
    QImage *image_gameover;       // 游戏结束图片
    QLabel *label_image=new QLabel(this); // 图片显示标签
    NumMatrix *numMatrix = new NumMatrix(); // 游戏核心逻辑对象
    QPoint point;                 // 鼠标位置
    QPoint point1;                // 第一次点击位置
    QPoint point2;                // 第二次点击位置
    QPixmap pixmap_gem[8];       // 宝石图片数组
    QPixmap pixmap_di;           // 选中框图片
    QPixmap number[10];          // 数字图片数组
    QPixmap disappear1;          // 消除动画1
    QPixmap disappear2;          // 消除动画2
    QPixmap disappear3;          // 消除动画3

    // 游戏状态变量
    int mouseflag;               // 鼠标点击标志
    int focus;                   // 焦点状态
    int focus_x;                // 焦点x坐标
    int focus_y;                // 焦点y坐标
    int eliminateNumber = 0;    // 消除数量
    int **isSelected;           // 是否选中（0/1）
    int **midSituation;         // 消除中间过程（1，2，3，对应三张图片）
    std::string string_grade;   // 分数转成string类型
    int addScoreSituation=-1;   // 加分情况的状态（0-9）
    int totaltime=60;           // 时间
    QString gemtype;            // 宝石类型，默认值为"a"
    int music = 1;
    int eli_music=0;
    Rank* rankInstance;

    bool props=false,boom=false,color=false,row=false,col=false; // 判断是否选择道具

    int cellSize ;              // 每个单元格的大小
    int offsetX ;
    int offsetY ;               // 绘制时的偏移量
    int scoreOffsetX ;
    int scoreOffsetY ;          // 分数显示的偏移量。
    int scoreStep ;             // 分数动画的步长
    int t;                      // 动画持续时间
    bool coinsAdded = false;

    bool hintUsedThisRound = false; // 追踪提示按钮的使用状态

    void updatePropsUI();  // 添加一个统一的更新道具UI的函数

    void setupAudioConnections();

    // 添加音效播放器
    QMediaPlayer* greatSound;
    QMediaPlayer* excellentSound;
    QMediaPlayer* amazingSound;
    QMediaPlayer* unbelievableSound;
    QAudioOutput* effectAudioOutput;  // 音效专用的音频输出
    
    void initSoundEffects();  // 初始化音效
    void playSoundEffect(QMediaPlayer* effect);  // 播放音效的辅助函数
    void initAudioSettings(); // 初始化音频设置

    bool isLevelMode;
    int currentLevelId;
    int levelTargetScore;

    int currentSteps;     // 当前已用步数
    int maxSteps;         // 最大步数限制
    int currentStars;     // 当前获得的星星数

    void checkLevelComplete(); // 检查关卡完成情况

    QPropertyAnimation* stepsAnimation;  // 步数动画
    QParallelAnimationGroup* starAnimations;  // 星星动画组
    QSequentialAnimationGroup* scoreAnimations;  // 分数动画序列
    
    void setupAnimations();  // 设置动画
    void updateStarProgress(int score);  // 更新星级进度
    void playStarAnimation(int starCount);  // 播放获星动画

    // 添加关卡时间变量
    int levelTime;

protected:
    void mousePressEvent(QMouseEvent *event);
    QPoint mousePos;            // 鼠标位置

    void initArrays();     // 添加初始化数组的辅助方法
    void cleanupArrays();  // 添加清理数组的辅助方法
};

#endif // MAINWINDOW_H