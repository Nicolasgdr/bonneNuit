#include <iostream>
#include <QApplication>
#include "Controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* controller = new Controller();
    controller->start();
    return a.exec();
}
