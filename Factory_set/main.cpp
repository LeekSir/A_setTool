#include "factory_set.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    factory_set w;
    w.setWindowTitle("产测软件配置工具");
    w.show();
    return a.exec();
}
