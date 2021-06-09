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
    QString appName("Factory_set.exe");
    QProcess process;
    process.start("tasklist", QStringList()<<"-fi"<<"imagename eq " +appName);
    process.waitForFinished();
    QString tasksList = QString::fromLocal8Bit(process.readAllStandardOutput());
    if(tasksList.contains(appName)){
        if(tasksList.count(appName) > 1)
        {

            QMessageBox::about(&log, "警告", "程序已经在运行了！");
            return 0;
        }

    }

    if(log.exec() == QDialog::Accepted)
    {


        factory_set w;
        if(log.logining() == 0)//登陆
        {
            w.Usr_Type = true;
            w.setWindowTitle("产测软件配置工具V5.7(工程员)");
        }
        else
        {
            w.setWindowTitle("产测软件配置工具V5.7(操作员)");
        }

        qDebug() << w.Usr_Type;
        w.display();
        w.resize(1000,600);
        w.setWindowFlags(Qt::CustomizeWindowHint
                           | Qt::WindowTitleHint
                           | Qt::WindowMinimizeButtonHint
                           | Qt::WindowMaximizeButtonHint
                           | Qt::WindowCloseButtonHint
                           );
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}

