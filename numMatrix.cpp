#include "numMatrix.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<QDebug>
#include<windows.h>



// 初始化静态成员变量
int NumMatrix::MAPSIZE = 49;
int NumMatrix::MAPROWNUM = 7;
int NumMatrix::MAPCOLNUM = 7;

/**
 * @brief 默认构造函数
 * @details 初始化游戏地图为动态二维数组，设置默认地图大小为7x7，
 * 开始界面里的on_btn_startToGame_clicked()方法可以调用setMapSize()函数来设置地图大小
 */
NumMatrix::NumMatrix() {
    // 初始化动态数组
    m_aMap = new int*[MAX_MAP_SIZE];
    for(int i = 0; i < MAX_MAP_SIZE; i++) {
        m_aMap[i] = new int[MAX_MAP_SIZE]();  // 使用()初始化为0
    }
    
    // 设置默认地图大小，也可以调用setMapSize()函数来设置
    MAPROWNUM = 7;
    MAPCOLNUM = 7;
    MAPSIZE = MAPROWNUM * MAPCOLNUM;
    game_running = false;
}

/**
 * @brief 析构函数
 * @details 释放动态分配的地图内存
 */
NumMatrix::~NumMatrix() {
    // 释放动态数组内存
    for(int i = 0; i < MAX_MAP_SIZE; i++) {
        delete[] m_aMap[i];
    }
    delete[] m_aMap;
}

/**
 * @brief 设置地图大小
 * @param rows 地图行数
 * @param cols 地图列数
 * @return 是否设置成功
 * @details 检查地图大小是否合法，并重置地图数据
 */
bool NumMatrix::setMapSize(int rows, int cols) {
    // 检查地图大小是否在合理范围内
    if(rows < 3 || cols < 3 || rows > MAX_MAP_SIZE || cols > MAX_MAP_SIZE) {
        return false;
    }

    // 清空当前地图数据
    for(int i = 0; i < MAX_MAP_SIZE; i++) {
        for(int j = 0; j < MAX_MAP_SIZE; j++) {
            m_aMap[i][j] = 0;
        }
    }

    MAPROWNUM = rows;
    MAPCOLNUM = cols;
    MAPSIZE = rows * cols;
    return true;
}

/**
 * 生成游戏地图
 * 1. 随机生成初始布局
 * 2. 检查并修正三连情况
 * 3. 确保生成的地图没有可消除的组合
 */
void NumMatrix::BuildMap(int gemspecies){
    int gemnum;//宝石编号，从1到gemspecies
    srand((int)time(0));//使用当前时间作为种子来初始化随机数生成器，确保每次运行程序时都会得到不同的随机序列

    //初始生成一个数字矩阵
    for(int n=0;n<MAPROWNUM;n++){
        for(int m =0;m<MAPCOLNUM;m++){
            gemnum = rand()%gemspecies+1; //生成1-gemspecies的随机数
            m_aMap[n][m]=gemnum;
        }
    }

    while(checkmap()){
        //判断横向是否有相邻的三个宝石相同
        for(int j=0;j<MAPROWNUM;j++){
            for(int i=0;i<MAPROWNUM-3+1;i++){
                int check[3]; //用于检查宝石是否相同
                for(int n=0;n<3;n++){
                    check[n]=m_aMap[j][i+n];
                }
                if(check[0]==check[1]&&check[1]==check[2]){
                    while(check[1]==check[0]){//修正的具体实现：不断生成新的随机数，使直到check[1]不等于check[0]
                        check[1]=rand()%gemspecies+1;
                        m_aMap[j][i+1]=check[1];
                    }
                }
            }
        }

        //纵向
        for(int j=0;j<MAPCOLNUM;j++){
            for(int i=0;i<MAPROWNUM-3+1;i++){
                int check[3];
                for(int n=0;n<3;n++){
                    check[n]=m_aMap[i+n][j];
                }
                if(check[0]==check[1]&&check[1]==check[2]){
                    while(check[1]==check[0]){
                        check[1]=rand()%gemspecies+1;
                        m_aMap[i+1][j]=check[1];
                    }
                }
            }
        }
    }
}

// 显示地图
void NumMatrix::DisplayMap(std::ostream& os /*= std::cout*/) {
    for (int n = 0; n < MAPROWNUM; n++) {
        for (int m = 0; m < MAPCOLNUM; m++) {
            os << m_aMap[n][m] << " ";
        }
        os << std::endl;
    }
}

/**
 * 检查地图中是否存在可消除的组合
 * 横向和纵向分别检查是否有三个相同的宝石相邻
 */
bool NumMatrix::checkmap(){
    //判断横向是否有相邻的三个宝石相同
    for(int j=0;j<MAPROWNUM;j++){//遍历每一行
        for(int i=0;i<MAPROWNUM-3+1;i++){
            int check[3]; //对于每个i，创建一个大小为3的数组check，用于存储当前检查的三个宝石
            for(int n=0;n<3;n++){
                check[n]=m_aMap[j][i+n];//将当前行中从i开始的三个宝石依次存入check数组中
            }
            if(check[0]==check[1]&&check[1]==check[2]){//找到了三个相同的宝石
                return true;
            }
        }
    }

    //判断纵向是否有相邻的三个宝石相同
    for(int j=0;j<MAPCOLNUM;j++){
        for(int i=0;i<MAPROWNUM-3+1;i++){
            int check[3]; //用于检查宝石是否相同
            for(int n=0;n<3;n++){
                check[n]=m_aMap[i+n][j];
            }
            if(check[0]==check[1]&&check[1]==check[2]){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 交换两个宝石的位置
 * @param a,b 第一个宝石的位置坐标
 * @param m,n 第二个宝石的位置坐标
 * @return 交换是否有效（是否形成可消除的组合）
 * @details 
 * 1. 检查游戏是否运行中
 * 2. 验证两个位置是否相邻
 * 3. 执行交换并检查是否形成可消除组合
 * 4. 如果没有形成可消除组合则恢复位置
 */
bool NumMatrix::swap(int a, int b, int m, int n) {
    if (!game_running) return false;
    
    // 检查是否相邻
    bool isAdjacent = (a == m && std::abs(b - n) == 1) || 
                      (b == n && std::abs(a - m) == 1);
    if (!isAdjacent) return false;

    // 交换位置
    int temp = m_aMap[a][b];
    m_aMap[a][b] = m_aMap[m][n];
    m_aMap[m][n] = temp;

    // 检查是否可以消除
    bool canEliminate = false;
    
    // 检查横向是否有三连
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM-2; j++) {
            if(m_aMap[i][j] != 0 && 
               m_aMap[i][j] == m_aMap[i][j+1] && 
               m_aMap[i][j] == m_aMap[i][j+2]) {
                canEliminate = true;
                break;
            }
        }
        if(canEliminate) break;
    }
    
    // 检查纵向是否有三连
    if(!canEliminate) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            for(int i = 0; i < MAPROWNUM-2; i++) {
                if(m_aMap[i][j] != 0 && 
                   m_aMap[i][j] == m_aMap[i+1][j] && 
                   m_aMap[i][j] == m_aMap[i+2][j]) {
                    canEliminate = true;
                    break;
                }
            }
            if(canEliminate) break;
        }
    }
    
    // 如果不能消除，换回来
    if (!canEliminate) {
        m_aMap[a][b] = m_aMap[m][n];
        m_aMap[m][n] = temp;
    }
    
    return canEliminate;
}

/**
 * @brief 处理宝石消除逻辑
 * @param noChange 是否仅检查不执行实际消除
 * @return 是否存在可消除的组合
 * @details 
 * 1. 检查并处理特殊图形（L型、T型）
 * 2. 检查水平和垂直方向的连续相同宝石
 *    - 四连：获得行/列消除道具
 *    - 五连：获得同色消除道具
 *    - 交叉点：获得爆炸道具
 */
bool NumMatrix::eliminate(bool noChange) {
    if(!game_running) return false;
    bool isChange = false;

    // 创建临时数组
    int** temp_aMap = new int*[MAPROWNUM];
    for(int i = 0; i < MAPROWNUM; i++) {
        temp_aMap[i] = new int[MAPCOLNUM];
        for(int j = 0; j < MAPCOLNUM; j++) {
            temp_aMap[i][j] = m_aMap[i][j];
        }
    }

    // 创建标记数组
    bool** hasVertical = new bool*[MAPROWNUM];
    bool** hasHorizontal = new bool*[MAPROWNUM];
    for(int i = 0; i < MAPROWNUM; i++) {
        hasVertical[i] = new bool[MAPCOLNUM]();
        hasHorizontal[i] = new bool[MAPCOLNUM]();
    }

    // 先检查L型和T型消除
    for(int i = 0; i < MAPROWNUM-2; i++) {
        for(int j = 0; j < MAPCOLNUM-2; j++) {
            int current = m_aMap[i][j];
            if(current != 0) {
                // 检查L型(┗)
                if(m_aMap[i][j+1] == current && m_aMap[i][j+2] == current &&
                   m_aMap[i+1][j] == current && m_aMap[i+2][j] == current) {
                    // L型消除，奖励爆炸道具
                    if(noChange) g_props_boom++;
                    // 标记消除的宝石
                    temp_aMap[i][j] = temp_aMap[i][j+1] = temp_aMap[i][j+2] = 0;
                    temp_aMap[i+1][j] = temp_aMap[i+2][j] = 0;
                    isChange = true;
                }
                // 检查其他L型变体和T型...
            }
        }
    }

    // 检查横向三连
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM-2; j++) {
            int current = m_aMap[i][j];
            if(current != 0) {
                int count = 1;
                // 计算连续相同的宝石数量
                while(j + count < MAPCOLNUM && m_aMap[i][j+count] == current) {
                    count++;
                }
                
                if(count >= 3) { // 至少三连
                    for(int k = 0; k < count; k++) {
                        temp_aMap[i][j+k] = 0;
                        hasHorizontal[i][j+k] = true;
                    }
                    
                    if(noChange) {
                        if(count == 4) {
                            g_props_col++; // 四连奖励列消除道具
                        } else if(count >= 5) {
                            g_props_color++; // 五连奖励同色消除道具
                            g_props_col--;
                        }
                    }
                    isChange = true;
                }
            }
        }
    }

    // 检查纵向三连
    for(int j = 0; j < MAPCOLNUM; j++) {
        for(int i = 0; i < MAPROWNUM-2; i++) {
            int current = m_aMap[i][j];
            if(current != 0) {
                int count = 1;
                while(i + count < MAPROWNUM && m_aMap[i+count][j] == current) {
                    count++;
                }
                
                if(count >= 3) {
                    for(int k = 0; k < count; k++) {
                        temp_aMap[i+k][j] = 0;
                        hasVertical[i+k][j] = true;
                    }
                    
                    if(noChange) {
                        if(count == 4) {
                            g_props_row++; // 四连奖励行消除道具
                        } else if(count >= 5) {
                            g_props_color++; // 五连奖励同色消除道具
                            g_props_row--;
                        }
                    }
                    isChange = true;
                }
            }
        }
    }

// 检查交叉点奖励爆炸道具
if(noChange) {  // 只有在检查模式下才奖励道具
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            // 如果某个位置同时被水平和垂直消除标记，说明是交叉点
            if(hasHorizontal[i][j] && hasVertical[i][j]) {
                g_props_boom++;  // 奖励一个爆炸道具
            }
        }
    }
}

if(noChange && isChange) {  // 在检查模式且有变化时
    // 这里原本应该有处理四连和五连的代码
    emit propsChanged();  // 发送信号通知界面更新道具数量
}

if(!noChange && isChange) {  // 如果不是检查模式且有变化
    // 将临时地图的变化应用到实际地图
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            m_aMap[i][j] = temp_aMap[i][j];
        }
    }
}

    // 清理内存
    for(int i = 0; i < MAPROWNUM; i++) {
        delete[] temp_aMap[i];
        delete[] hasVertical[i];
        delete[] hasHorizontal[i];
    }
    delete[] temp_aMap;
    delete[] hasVertical;
    delete[] hasHorizontal;

    return isChange;
}

/**
 * @brief 处理宝石下落和填充
 * @return 是否发生了下落行为
 * @details 
 * 1. 检查每一列的空缺位置
 * 2. 将上方的宝石下移填补空缺
 * 3. 在顶部生成新的随机宝石
 */
bool NumMatrix::down()
{
    srand(GetTickCount());
    bool isChanged = false;

    // 遍历每一列
    for(int i = 0; i < MAPCOLNUM; i++) {
        // 从下往上遍历当前列
        for(int j = MAPROWNUM - 1; j >= 0; j--) {
            if(m_aMap[j][i] == 0) {
                // 移动宝石
                for(int k = j; k > 0; k--) {
                    m_aMap[k][i] = m_aMap[k - 1][i];
                }
                // 在顶部生成新宝石
                m_aMap[0][i] = rand() % g_spc + 1;
                isChanged = true;
                break;
            }
        }
    }
    return isChanged;
}


/*处理不同类型的道具在地图上的消除效果
 *
 * propsSpc：道具类型
 * 1 3x3范围内的爆炸
 * 2 一行的消除
 * 3 一列的消除
 * 4 同色宝石的消除
 * x 和 y：表示道具使用的坐标位置
 *
 */
void NumMatrix::propsEliminate(int propsSpc, int x, int y)
{
    switch (propsSpc) {
    case 1: //3*3boom
            for (int i = std::max(0, x - 1); i <= std::min(MAPROWNUM - 1, x + 1); ++i) {
                for (int j = std::max(0, y - 1); j <= std::min(MAPCOLNUM - 1, y + 1); ++j) {
                    m_aMap[i][j] = 0;
                }
            }
        g_props_boom--;
        emit propsChanged();  // 添加信号发射
        break;
        case 2: //line boom row
            for (int j = 0; j < MAPCOLNUM; ++j) {
                m_aMap[x][j] = 0;
            }
        g_props_row--;
        emit propsChanged();  // 添加信号发射
        break;

        case 3: //line boom column
            for (int i = 0; i < MAPROWNUM; ++i) {
                m_aMap[i][y] = 0;
            }
        g_props_col--;
        emit propsChanged();  // 添加信号发射
        break;

        case 4: //same gem delete
            int color = m_aMap[x][y];//数字矩阵中当前位置的宝石颜色（数字）
        for (int i = 0; i < MAPROWNUM; ++i) {
            for (int j = 0; j < MAPCOLNUM; ++j) {
                if (m_aMap[i][j] == color) {
                    m_aMap[i][j] = 0;
                }
            }
        }
        g_props_color--;
        emit propsChanged();  // 添加信号发射
        break;
    }
}

//设置游戏状态
void NumMatrix::setgamerunning(bool game_running){
    this->game_running=game_running;
}

/**
 * @brief 提示可能的有效移动
 * @return 1表示找到可移动位置，0表示未找到
 * @details 
 * 1. 检查所有可能的垂直交换
 * 2. 检查所有可能的水平交换
 * 3. 将找到的可移动位置存储在point数组中
 * 4. 优化内存使用，避免内存泄漏
 */
int NumMatrix::hint() {
    if(!game_running) return 0;

    // 使用动态分配的数组替代可变大小数组
    int** map = new int*[MAPROWNUM];
    for(int i = 0; i < MAPROWNUM; i++) {
        map[i] = new int[MAPCOLNUM];
    }

    // 复制地图数据
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            map[i][j] = m_aMap[i][j];
        }
    }

    // 将 lambda 改为普通成员函数
    auto checkHorizontal = [](int** map, int row, int col) {
        if(col <= NumMatrix::MAPCOLNUM-3) {
            for(int i = 0; i <= col; i++) {
                if(i + 2 < NumMatrix::MAPCOLNUM &&
                   map[row][i] == map[row][i+1] &&
                   map[row][i+1] == map[row][i+2]) {
                    return true;
                }
            }
        }
        return false;
    };

    auto checkVertical = [](int** map, int row, int col) {
        if(row <= NumMatrix::MAPROWNUM-3) {
            for(int i = 0; i <= row; i++) {
                if(i + 2 < NumMatrix::MAPROWNUM &&
                   map[i][col] == map[i+1][col] &&
                   map[i+1][col] == map[i+2][col]) {
                    return true;
                }
            }
        }
        return false;
    };

    bool found = false;
    // 检查垂直方向的交换
    for(int i = 0; i < MAPROWNUM-1 && !found; i++) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            std::swap(map[i][j], map[i+1][j]);

            if(checkHorizontal(map, i, j) || checkHorizontal(map, i+1, j) ||
               checkVertical(map, i, j) || checkVertical(map, i+1, j)) {
                point[0][0] = i;
                point[0][1] = j;
                point[1][0] = i+1;
                point[1][1] = j;

                found = true;
                break;
            }

            std::swap(map[i][j], map[i+1][j]);
        }
    }

    // 检查水平方向的交换
    if (!found) {
        for(int i = 0; i < MAPROWNUM; i++) {
            for(int j = 0; j < MAPCOLNUM-1; j++) {
                std::swap(map[i][j], map[i][j+1]);

                if(checkHorizontal(map, i, j) || checkHorizontal(map, i, j+1) ||
                   checkVertical(map, i, j) || checkVertical(map, i, j+1)) {
                    point[0][0] = i;
                    point[0][1] = j;
                    point[1][0] = i;
                    point[1][1] = j+1;
                    found = true;
                    break;
                }

                std::swap(map[i][j], map[i][j+1]);
            }
            if (found) break;
        }
    }

    // 清理动态分配的内存
    for(int i = 0; i < MAPROWNUM; i++) {
        delete[] map[i];
    }
    delete[] map;

    return found ? 1 : 0;
}
