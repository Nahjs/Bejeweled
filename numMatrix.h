#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H
#include <iostream>
#include <ostream>
#include "prop.h"
#include <QObject>  // 添加QObject头文件

/**
 * @brief 游戏核心逻辑类
 * 负责处理游戏的核心玩法逻辑
 */
class NumMatrix : public QObject {  // 需要继承QObject以支持信号
    Q_OBJECT

public:
    static int MAPSIZE;      // 地图总大小
    static int MAPROWNUM;    // 地图行数
    static int MAPCOLNUM;    // 地图列数
    static const int MAX_MAP_SIZE = 12;  // 最大地图尺寸限制

    int** m_aMap;            // 使用动态数组替代固定大小数组
    int point[2][2]{};       
    bool game_running{};     

private:
    int species = 8;

public:
    NumMatrix();
    ~NumMatrix();  // 需要析构函数来释放动态内存

    /**
     * @brief 设置地图大小
     * @param rows 行数
     * @param cols 列数
     * @return 是否设置成功
     */
    bool setMapSize(int rows, int cols);

    /**
     * @brief 初始化并生成游戏地图
     * @param gemspecies 本关卡使用的宝石种类数量
     * @details 生成的地图确保初始状态下没有可消除的组合
     */
    void BuildMap(int gemspecies);

    /**
     * @brief 显示当前地图状态（用于调试）
     * @param os 输出流对象
     */
    void DisplayMap(std::ostream& os = std::cout);

    /**
     * @brief 检查地图中是否存在可消除的宝石组合
     * @return true 表示存在可消除组合，false 表示不存在
     * @details 检查横向和纵向的三连情况
     */
    bool checkmap();

    /**
     * @brief 交换两个位置的宝石
     * @param a,b 第一个宝石的行列坐标
     * @param m,n 第二个宝石的行列坐标
     * @return true 表示交换后形成有效的消除组合，false 表示无效交换
     */
    bool swap(int a, int b, int m, int n);

    /**
     * @brief 消除符合条件的宝石组合
     * @param noChange 是否真实执行消除（false时仅检查不执行消除）
     * @return true 表示有宝石被消除，false 表示没有可消除的组合
     */
    bool eliminate(bool noChange = false);

    /**
     * @brief 处理宝石下落和空位填充
     * @return true 表示发生了下落行为，false 表示没有需要下落的宝石
     */
    bool down();

    /**
     * @brief 处理特殊道具的消除效果
     * @param propsSpc 道具类型(1:爆炸 2:行消除 3:列消除 4:同色消除)
     * @param x,y 道具使用的目标位置坐标
     */
    void propsEliminate(int propsSpc, int x, int y);

    /**
     * @brief 设置游戏运行状态
     * @param game_running true表示游戏运行，false表示游戏暂停
     */
    void setgamerunning(bool game_running);

    /**
     * @brief 分数更新处理
     */
    void newGrade();

    /**
     * @brief 检查是否达成胜利条件
     * @return true表示胜利，false表示未胜利
     */
    bool isWin();

    /**
     * @brief 查找并提示可以交换的宝石位置
     * @return 返回1表示找到可交换位置，0表示未找到
     * @details 会将可交换的位置坐标存储在point数组中
     */
    int hint();

signals:
    void propsChanged();  // 添加信号用于通知道具数量变化
};

#endif // CGAMELOGIC_H
