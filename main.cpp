#include "cbejeweleddlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBejeweledDlg w;
    w.show();
 /*   // 加载宝石图片
    QImage image_gem1(":/res/gem1.png");
    if (image_gem1.isNull()) {
        qDebug() << "Failed to load gem1 image using resource path.";
    } else {
        qDebug() << "Gem1 image loaded successfully using resource path.";

        // 创建一个 QLabel 来显示图片
        QLabel label;
        label.setPixmap(QPixmap::fromImage(image_gem1));
        label.show();
    }*/
    return a.exec();
}

