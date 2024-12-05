#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H
#include <iostream>
#include <ostream>
#define MAPSIZE 36
#define MAPROWNUM 6
#define MAPCOLNUM 6

class CGameLogic
{
public:
    CGameLogic();
    int m_aMap[MAPROWNUM][MAPCOLNUM]{}; //0代表空，1~n代表第n种宝石（宝石号码取值为1-8）
    int point[2][2]{};//记录交换点
    bool game_running{}; //游戏运行状态，该布尔变量默认为true,当在cgamelog界面中点击“暂停游戏”按钮时该值为false。true时表示游戏处于运行状态

private:

    //*******在写 “交换函数（swap）” 时，务必判断该布尔变量game_running是否为true，只有为true是才能继续操作*********

    int species=8;//一共有8中宝石种类数

public:
    void BuildMap(int gemspecies);//生成不三连的图形，用于camglog中调用来初始化地图，以下消子、交换、下移、产生新子等函数需要地图时只需调用 "m_aMap[8][8]"
    void DisplayMap(std::ostream& os = std::cout);

    bool checkmap(); //只是为了再次判断地图中是否有相邻的三个宝石相同，只用于BuildMap()中引用,写其他代码时可忽略此函数。

    bool swap(int a, int b, int m, int n);//交换（不相邻或无法消子，返回false）需要调用eliminate；也可以不这样写
    bool eliminate(bool noChange= false);//消除
    bool down();//下移
    void propsEliminate(int propsSpc, int x, int y);//道具消除

    void setgame_running(bool game_running); //在cgamedlg中用于设置游戏是否暂停，写其他代码时可忽略本函数。
                                             //写消子、交换、下移、产生新子等函数时只用判断布尔变量 "game_running"是否为真

    void newGrade();//不太清楚怎么做
    bool isWin();//胜负判断？或者升级？
    int hint();//提示（需要扣分）
};

#endif // CGAMELOGIC_H
