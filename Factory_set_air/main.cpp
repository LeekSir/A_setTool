#include "factory_set.h"

#include <QApplication>
#include "login.h"
#include <QDebug>
#include <synchapi.h>//延时

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login log;
    log.setWindowTitle("用户登陆");
    log.show();
    if(log.exec() == QDialog::Accepted)
    {


        factory_set w;
        if(log.logining() == 0)//登陆
        {
            w.Usr_Type = true;
            w.setWindowTitle("产测软件配置工具(工程员)");
        }
        else
        {
            w.setWindowTitle("产测软件配置工具(操作员)");
        }

        qDebug() << w.Usr_Type;
        w.display();
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
