#ifndef PROP_H
#define PROP_H

typedef struct Picelem
{
    int nRow;
    int nCol;
    int nPicNum;
} Picelem;

// 道具价格常量
const int PRICE_BOOM = 10;    // 爆炸道具价格
const int PRICE_ROW = 8;      // 行消除道具价格
const int PRICE_COL = 8;      // 列消除道具价格
const int PRICE_COLOR = 15;   // 同色消除道具价格

extern int g_spc;
extern int g_props_boom;
extern int g_props_row;
extern int g_props_col;
extern int g_props_color;

// 添加金币相关
extern int g_coins;           // 用户当前金币数

#endif // PROP_H
