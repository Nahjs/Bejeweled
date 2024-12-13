#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct RankStruct
{
    char strName[50];
    int nGrade;
    int nRank;
} Rankstruct;

extern Rankstruct g_rank;

extern Rankstruct * ranks[10];

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
