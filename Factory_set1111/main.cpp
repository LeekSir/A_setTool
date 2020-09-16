#include "factory_set.h"

#include <QApplication>
#include "login.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    factory_set w;
    w.setWindowTitle("产测软件配置工具");
    login log;
    log.setWindowTitle("用户登陆");
    if(log.exec() == QDialog::Accepted)
    {
        //w.
        if(log.logining())//登陆
        {
            w.Usr_Type = true;
            //qDebug() << w.Usr_Type;
        }
        qDebug() << w.Usr_Type;
        w.display();
        w.show();
        return a.exec();

    }
    //w.show();
    else
    {

        return 0;
    }

}
