#include "factory_set.h"

#include <QApplication>
#include "login.h"
#include <QDebug>
#include <synchapi.h>//延时

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customMessageHandler);
    /*qDebug() << "this is QtDebugMsg";
    qInfo() << "this is QtInfoMsg";
    qWarning() << "this is QtWarningMsg";
    qCritical() << "this is QtCriticalMsg";*/
    login log;
    log.setWindowTitle("用户登陆");
    log.show();
    if(log.exec() == QDialog::Accepted)
    {


        factory_set w;
        if(log.logining() == 0)//登陆
        {
            w.Usr_Type = true;
            w.setWindowTitle("产测软件配置工具V1.0(工程员)");
        }
        else
        {
            w.setWindowTitle("产测软件配置工具V1.0(操作员)");
        }

        qDebug() << w.Usr_Type;
        w.display();
        w.resize(1000,600);
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
