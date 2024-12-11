#include "numMatrix.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<QDebug>
#include<windows.h>

#include "Global.h"
//构造函数
NumMatrix::NumMatrix(){}

//生成地图
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

//判断地图中是否有相邻的三个宝石相同
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

//交换地图上两个相邻宝石的位置，并检查交换后是否形成了可以消除的组合
bool NumMatrix::swap(int a,int b,int m,int n){//传入坐标(a,b)和(m,n)
    if(game_running){
        if(a==m){//同行？
            if(((b-n)==1)or((b-n)==-1)){//相邻？
                int mid_map=m_aMap[a][b];//用于交换操作的临时变量
                m_aMap[a][b]=m_aMap[m][n];
                m_aMap[m][n]=mid_map;

                //检查交换后的地图是否有可消除的组合
                if(checkmap()){
                    return true;
                }else{//没有可消除的组合，撤销交换操作
                    mid_map=m_aMap[a][b];
                    m_aMap[a][b]=m_aMap[m][n];
                    m_aMap[m][n]=mid_map;
                    return false;
                }
            }else{
                return false;//如果不相邻，直接返回 false
            }
        }else{
            if(b==n){//同列？
                if(((a-m)==1)or((a-m)==-1)){//相邻？
                    int mid=m_aMap[a][b];
                    m_aMap[a][b]=m_aMap[m][n];
                    m_aMap[m][n]=mid;
                    if(checkmap()){
                        return true;
                    }else{//不符合交换条件，撤销交换操作
                        mid=m_aMap[a][b];
                        m_aMap[a][b]=m_aMap[m][n];
                        m_aMap[m][n]=mid;
                        return false;
                    }
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
    }else{
        return false;//不允许交换
    }
}

bool NumMatrix::eliminate(bool noChange)
{
    if(!game_running) return false;
    bool isChange = false;

    int temp_aMap[MAPROWNUM][MAPCOLNUM];
    memcpy(temp_aMap, m_aMap, sizeof(m_aMap));

    bool hasVertical[MAPROWNUM][MAPCOLNUM] = {false}; // 记录竖直方向消除
    bool hasHorizontal[MAPROWNUM][MAPCOLNUM] = {false}; // 记录水平方向消除
    int current = 0;

    // 纵向消除判断
    for(int j = 0; j < MAPROWNUM; j++) {
        for(int i = 0; i < MAPCOLNUM-2; i++) {
            current = m_aMap[i][j];
            if(current == m_aMap[i + 1][j] && current == m_aMap[i + 2][j]) {
                // 标记竖直消除
                for(int k = 0; k < 3; k++) {
                    temp_aMap[i+k][j] = 0;
                    hasVertical[i+k][j] = true;
                }

                // 四连判断
                if(noChange && i + 3 < 8 && m_aMap[i + 3][j] == current) {
                    temp_aMap[i + 3][j] = 0;
                    hasVertical[i + 3][j] = true;
                    g_props_row++; // 纵向四连获得行消除道具

                    // 五连判断
                    if(i + 4 < 8 && m_aMap[i + 4][j] == current) {
                        temp_aMap[i + 4][j] = 0;
                        hasVertical[i + 4][j] = true;
                        g_props_row--; // 取消四连道具
                        g_props_color++; // 获得color道具
                    }
                }
                isChange = true;
            }
        }
    }

    // 横向消除判断
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM-2; j++) {
            current = m_aMap[i][j];
            if(current == m_aMap[i][j + 1] && current == m_aMap[i][j + 2]) {
                // 标记水平消除
                for(int k = 0; k < 3; k++) {
                    temp_aMap[i][j+k] = 0;
                    hasHorizontal[i][j+k] = true;
                }

                // 四连判断
                if(noChange && j + 3 < 8 && m_aMap[i][j + 3] == current) {
                    temp_aMap[i][j + 3] = 0;
                    hasHorizontal[i][j + 3] = true;
                    g_props_col++; // 横向四连获得列消除道具

                    // 五连判断
                    if(j + 4 < 8 && m_aMap[i][j + 4] == current) {
                        temp_aMap[i][j + 4] = 0;
                        hasHorizontal[i][j + 4] = true;
                        g_props_col--; // 取消四连道具
                        g_props_color++; // 获得color道具
                    }
                }
                isChange = true;
            }
        }
    }

    // 检查横竖相交点，生成boom道具
    if(noChange) {
        for(int i = 0; i < MAPROWNUM; i++) {
            for(int j = 0; j < MAPCOLNUM; j++) {
                if(hasHorizontal[i][j] && hasVertical[i][j]) {
                    g_props_boom++;
                }
            }
        }
    }

    if(noChange) return isChange;

    memcpy(m_aMap, temp_aMap, sizeof(m_aMap));
    return isChange;
}

//将地图上的空格（值为0的元素）向下移动，并在顶部补充新的宝石
bool NumMatrix::down()
{
    srand(GetTickCount());//返回自系统启动以来经过的毫秒数
    //srand((int)time(0));
    int isChanged = false;
    for(int i = 0; i < 8; i++)//遍历每一列
    {
        for(int j = 7; j >= 0; j--)//从下往上遍历每一列
        {
            if(m_aMap[j][i] == 0)//如果当前位置为空
            {
                //移动宝石
                for(int k = j; k > 0; k--)//内层循环变量 k 从 j 到1递减
                {
                    m_aMap[k][i] = m_aMap[k - 1][i];//将上方的宝石依次向下移动一位，填补空缺
                }
                //在顶部生成新宝石
                m_aMap[0][i] = rand()%g_spc + 1;
                isChanged = true;
                break;//处理了一个空格，就跳出内层循环，继续处理下一列。
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
        break;
        case 2: //line boom row
            for (int j = 0; j < MAPCOLNUM; ++j) {
                m_aMap[x][j] = 0;
            }
        g_props_row--;
        break;

        case 3: //line boom column
            for (int i = 0; i < MAPROWNUM; ++i) {
                m_aMap[i][y] = 0;
            }
        g_props_col--;
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
        break;
    }
}

//设置游戏状态
void NumMatrix::setgamerunning(bool game_running){
    this->game_running=game_running;
}

//提示
int NumMatrix::hint() {
    if(!game_running) return 0;

    int map[MAPROWNUM][MAPCOLNUM];

    // 复制地图数据
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            map[i][j] = m_aMap[i][j];
        }
    }

    // 检查指定位置是否可以消除
    auto checkPosition = [&map](int row, int col) {
        // 检查水平方向
        if(col <= MAPCOLNUM-3) {
            for(int i = 0; i <= col; i++) {
                if(i + 2 < MAPCOLNUM &&
                   map[row][i] == map[row][i+1] &&
                   map[row][i+1] == map[row][i+2]) {
                    return true;
                   }
            }
        }

        // 检查垂直方向
        if(row <= MAPROWNUM-3) {
            for(int i = 0; i <= row; i++) {
                if(i + 2 < MAPROWNUM &&
                   map[i][col] == map[i+1][col] &&
                   map[i+1][col] == map[i+2][col]) {
                    return true;
                   }
            }
        }
        return false;
    };

    // 检查垂直方向的交换
    for(int i = 0; i < MAPROWNUM-1; i++) {
        for(int j = 0; j < MAPCOLNUM; j++) {
            std::swap(map[i][j], map[i+1][j]);

            if(checkPosition(i, j) || checkPosition(i+1, j)) {
                point[0][0] = i;
                point[0][1] = j;
                point[1][0] = i+1;
                point[1][1] = j;
                return 1;
            }

            std::swap(map[i][j], map[i+1][j]);
        }
    }

    // 检查水平方向的交换
    for(int i = 0; i < MAPROWNUM; i++) {
        for(int j = 0; j < MAPCOLNUM-1; j++) {
            std::swap(map[i][j], map[i][j+1]);

            if(checkPosition(i, j) || checkPosition(i, j+1)) {
                point[0][0] = i;
                point[0][1] = j;
                point[1][0] = i;
                point[1][1] = j+1;
                return 1;
            }

            std::swap(map[i][j], map[i][j+1]);
        }
    }

    return 0;
}
