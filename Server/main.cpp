#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    if (!server.startServer(5371)) {
        qCritical() << "服务器启动失败";
        return -1;
    }
    return a.exec();
}
