#ifndef RANK_H
#define RANK_H

#include "Global.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QDir>

using namespace std;

class CRankDao
{
public:
    CRankDao();

    static int getRank();

    static void saveRank();

public:

};

#endif // RANK_H
