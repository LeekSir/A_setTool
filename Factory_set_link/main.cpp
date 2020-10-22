#include "factory_set.h"

#include <QApplication>
#include <QDebug>
#include <synchapi.h>//延时

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    factory_set w;
    w.show();
    return a.exec();
}
