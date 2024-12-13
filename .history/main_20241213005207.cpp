#include "start.h"
#include "Global.h"
#include <QApplication>

// 全局变量定义
Rankstruct g_rank;
Rankstruct* ranks[10] = {nullptr};
int g_spc = 5;
int g_props_boom = 1;
int g_props_row = 1;
int g_props_col = 1;
int g_props_color = 1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 初始化全局变量
    g_rank.nGrade = 0;
    g_rank.strName[0] = '\0';
    
    // 创建并显示开始界面
    Start w;
    w.show();
    
    return a.exec();
}
