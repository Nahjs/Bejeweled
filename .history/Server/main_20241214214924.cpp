#include <QCoreApplication>
#include "chatserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    ChatServer server;
    if(!server.startServer(8888)) {
        return -1;
    }
    
    return a.exec();
}
