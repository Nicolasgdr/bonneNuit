#include <QApplication>
#include "Server.h"

/**
 * launch the game
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    server.start_server();
    return a.exec();
}
