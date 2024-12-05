#include "cgamedlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGameDlg w;
    w.show();
    return a.exec();
}
