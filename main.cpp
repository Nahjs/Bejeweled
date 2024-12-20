#include <QApplication>
#include "start.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
     //w.show(); // 移除此行，先显示登录窗口
    return a.exec();
}
