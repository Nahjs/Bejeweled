#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct Rank
{
    char strName[50];
    int nGrade;
    int nRank;
} Rank;

extern Rank g_rank;

extern Rank * ranks[10];

typedef struct Picelem
{
    int nRow;
    int nCol;
    int nPicNum;
} Picelem;

extern int g_spc;

extern int g_props_boom;

extern int g_props_row ;

extern int g_props_col ;

extern int g_props_color;


#endif // GLOBAL_H
