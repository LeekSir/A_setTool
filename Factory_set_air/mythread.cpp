#include "mythread.h"
#include "factory_set.h"
#include <QDebug>
#include <QProcess>
#include <QMessageBox>


#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QtWidgets>

extern bool correct;
extern bool correct_flag;//是否校准成功
extern bool mythread_flag;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
}

void MyThread::run()
{
#if 0
    qreal i = 0;
    while (!stopped)
    {
        qDebug() << QString("in MyThread: %1").arg(i);
        msleep(1000);
        i++;
    }
    stopped = false;
#else
    QProcess process(this);
/*
    if(correct)
    {
        qDebug() << "hello world";
    }
    //emit mySignal();
    QStringList arguments;
    //arguments << "/c" << "ping www.baidu.com";
    //arguments << "cd ../../ " << " && " << "E:/qt_code/8.SKO.W618U.1_638BU/WLAN_Console.exe -p 1";
    arguments << "/c" << "cd ../../ && 'WLAN Console.exe' -p 1";

    QProcess process(this);
    process.start("./correct.bat");
    //process.startDetached("cmd.exe", arguments);
    process.waitForStarted();
    //process.waitForFinished();
    if(process.waitForFinished())   //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        process.start("./copy_new_log.bat");       //运行校验线损脚本文件
        if(process.waitForFinished()){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            emit mySignal();
        }
    }
    QString strResult = QString::fromLocal8Bit(process.readAllStandardOutput());

    //QMessageBox msgBox(this);
    //msgBox.setText(strResult);
    //msgBox.exec();
*/

    while(!correct_flag)
    {
        if(correct)
        {
            //1、拷入校准模式文件，拷出原始文件
            process.start("./copy_correct.bat");
            if(process.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {
                Sleep(1000);

             }
        }
        //2、跑校准模式和金板对比，并重复N次
        //第一遍不用循环
        process.start("./correct.bat");                 //运行校验线损脚本文件
        if(process.waitForFinished(120000)){            //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            Sleep(1000);
            //about_info("提示", "线损运行成功！");

            //*************** 启动 copy_new_log.bat *****************
            process.start("./copy_new_log.bat");        //运行校验线损脚本文件
            if(process.waitForFinished())               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {
                Sleep(1000);
                //about_info("提示", "log拷贝成功！");
            }
        }

        if(correct)
        {
            correct = false;
        }
        else
        {
           correct_flag = true;
        }
        emit mySignal();
        //
/*


        //about_info("提示", "第一次跑完了哦！");
        }
        else
        {
            //4、多次测试后，如测试数据和金板数据相差不大于正负0.5，则校准成功
            process.start("./correct.bat");       //运行校验线损脚本文件
            if(process.waitForFinished(120000)){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                Sleep(1000);
                //about_info("提示", "线损运行成功！");

                //启动 copy_new_log.bat
                process.start("./copy_new_log.bat");       //运行校验线损脚本文件
                if(process.waitForFinished()){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    Sleep(1000);
                    //about_info("提示", "log拷贝成功！");
                }
            openfile_deal_lineloss_log();
            set_LineLoss_correct();
            //about_info("提示", "第N次跑完了哦！");
            correct_flag = true;
            }
         }*/
    }





#endif
}

void MyThread::stop()
{
    stopped = true;
}
