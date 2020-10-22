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
extern bool PASS_flag;
extern QString correct_Port_Num;
extern QString filename_WT_ATTEN_DUT;
extern QMutex mutex;

bool get_pass_log = false;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Pass_log_clicked()));
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
    QProcess p(this);

    while(1)
    {
        if(correct)
        {
            if(!folder_isEmpty("../WT_SETUP_TEMP/"))
            {
                p.start("./reset_correct.bat");
                p.waitForFinished();
            }
            //1、拷入校准模式文件，拷出原始文件
            p.start("./copy_correct.bat");
            //备份金版数据
            if(p.waitForFinished())                     //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {
                //Sleep(1000);

                //p.start(correct_Port_Num);

                p.start("./open_factory.bat");
#if 0
                //等待

                timer->start(1000);
                //while(!Pass_log_clicked());
                while(!get_pass_log);
                get_pass_log = false;
                timer->stop();
                //about_info_auto("警告", "线损运行完毕！", 2000);
                p.start("./close_factory.bat");
                if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    if(p1.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    {
                        //Sleep(1000);
                    }
                    p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                    if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    {
                        //Sleep(1000);
                    }
                }

#else

                if(p.waitForFinished(120000))               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {

                    //Sleep(1000);
                    if(!Pass_log_clicked())
                    {

                        PASS_flag = false;
                        //about_info_auto("警告", "PASS_log 生成失败！", 2000);
                        break;
                    }
                    p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                    if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    {
                        //Sleep(1000);
                    }


                }
#endif
                openfile_deal_lineloss_log();
                if(correct_flag)
                    break;
                correct = false;
            }
        }
        else
        {
            //4、多次测试后，如测试数据和金板数据相差不大于正负0.5，则校准成功
            //p.start("./correct.bat");                 //运行校验线损脚本文件
            //p.start(correct_Port_Num);

            p.start("./open_factory.bat");
#if 0
            //等待
            timer->start(1000);
            //while(!Pass_log_clicked());
            while(!get_pass_log);
            get_pass_log = false;
            timer->stop();
            //about_info_auto("警告", "线损运行完毕！", 2000);
            p.start("./close_factory.bat");
            if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {
                if(p1.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    //Sleep(1000);
                }
                p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    //Sleep(1000);
                }
            }

#else
            if(p.waitForFinished(120000))               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {

                //Sleep(1000);
                if(!Pass_log_clicked())
                {

                    PASS_flag = false;
                    //about_info_auto("警告", "PASS_log 生成失败！", 2000);
                    break;
                }
                p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    //Sleep(1000);
                }


            }
#endif
            openfile_deal_lineloss_log();
            if(correct_flag)
                break;
            //set_LineLoss_correct();
        }
    }
    //mutex.unlock();
    emit mySignal();
#endif
}

void MyThread::stop()
{
    stopped = true;
    //this->stop();
    //this->quit();
    //this->wait();

}

//信息提示窗口
void MyThread::about_info(QString dlgTitle, QString strInfo)
{
    //QMessageBox::about(this, dlgTitle, strInfo);
    QMessageBox *m_box = new QMessageBox(QMessageBox::NoIcon,dlgTitle,strInfo);

    //QMessageBox::warning(this, dlgTitle, strInfo);

    //QMessageBox *m_box = new QMessageBox(about,dlgTitle,strInfo);
    m_box->setStandardButtons(0);
    //QTimer::singleShot(2000,m_box,SLOT(accept()));
    m_box->exec();
}

//信息提示窗口
void MyThread::about_info_auto(QString dlgTitle, QString strInfo, int timeout)
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::NoIcon,dlgTitle,strInfo);
    m_box->setStandardButtons(0);
    QTimer::singleShot(timeout,m_box,SLOT(accept()));
    m_box->exec();
}



//判断文件是否为空
bool MyThread::folder_isEmpty(QString folder_Path)
{
    QString filePath = folder_Path;
    QDir *dir=new QDir(filePath);
    return dir->isEmpty();
}



bool MyThread::Pass_log_clicked()
{
    get_pass_log = false;
    //qDebug() << "????????????";
    //about_info("提示", "1234567！");
    QString filePath = "../../LOG/PASS";
    //QString filePath = "../../LOG/FAIL";
    QDir *dir=new QDir(filePath);
    QStringList filter;
    QDateTime time;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(int i = 0;i<fileInfo->count(); i++)
    {


        if( fileInfo->at(i).suffix() == "log" && fileInfo->at(i).lastModified().secsTo(current_date_time) < 30)
        { 
            get_pass_log = true;
            return true;
        }
    }

    return false;
}


/**************************************************************************
**
** NAME     openfile_deal_lineloss_log
**
** PARAMETERS:  QString filename, QString show
**
** RETURNS: QString
**
** DESCRIPTION  显示文件中的关键信息对应到相应的lineEdit_d_id.
**
** NOTES:       None.
**************************************************************************/
void MyThread::openfile_deal_lineloss_log(/*QString filename, QString show, int port_num*/)
{
    //每次置true
    correct_flag = true;

    QString filePath = "../log/";
    QString RunFrameNcFile;
    QString curPath = QDir::currentPath();
    QDir *dir=new QDir(filePath);
    QStringList filter;


    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));

    RunFrameNcFile = filePath + fileInfo->at(2).fileName();
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);

        QString temp = "金板" + QString("\t\t\t\t\t\t\t") + "测试" + QString('\n');

        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            QStringList list;
            if(strtemp.mid(0, 15).count("ANT") >= 1)
            {
                list = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                temp += list.at(1) + "\t\t" + list.at(2) + "\t\t" + list.at(6).split('d').at(0);
                temp += QString('\n');
            }
        }
        Ncfile.close();
        Ncfile.remove();
        QFile Ncfile_select("../log/test_log.txt");
        Ncfile_select.open(QIODevice::WriteOnly);
        QTextStream in(&Ncfile_select);
        in <<temp;
        Ncfile_select.close();
    }
    else
    {
        about_info_auto("警告", "PASS_log 打开失败！", 2000);
        qDebug() << "log 文件打开失败";
    }


    QFile Ncfile_jinban("../log/standard.txt");
    QFile Ncfile_test("../log/test_log.txt");
    Ncfile_jinban.open(QIODevice::ReadOnly);
    Ncfile_test.open(QIODevice::ReadOnly);

    int port_num;
    if (Ncfile_jinban.isOpen() && Ncfile_test.isOpen())
    {
        QString strtemp_jinban,strtemp_test;
        QTextStream NctextStream_jinban(&Ncfile_jinban),NctextStream_test(&Ncfile_test);

        QString temp = "金板" + QString("\t\t\t\t\t\t") + "测试n" + QString("\t\t") + "微调值" + QString('\n');
        double loss_value, temp_value;
        int ch = 0;

        while(!NctextStream_jinban.atEnd() && !NctextStream_test.atEnd())
        {
            strtemp_jinban = NctextStream_jinban.readLine();
            strtemp_test = NctextStream_test.readLine();
            QStringList list_jinban,list_test;

            if(correct)
            {
                if(strtemp_test.mid(0, 3) == "ANT" && strtemp_jinban.mid(0, 3) == "ANT")
                {
                    list_test = strtemp_test.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    list_jinban = strtemp_jinban.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    temp += strtemp_jinban + "\t\t"  + list_test.at(2) + "\t\t" + QString::number((list_jinban.at(2).toDouble() - list_test.at(2).toDouble()),'f',2);
                    temp += QString('\n');
                    //if(list_jinban.at(2).toDouble() - list_test.at(2).toDouble())
                    if(qAbs(list_jinban.at(2).toDouble() - list_test.at(2).toDouble()) <= 0.5)
                    {
                        continue;
                    }
                    else
                    {
                        correct_flag = false;
                        loss_value = list_jinban.at(2).toDouble() - list_test.at(2).toDouble();
                    }
                    //loss_value = list_jinban.at(2).toDouble() - list_test.at(2).toDouble();
                    ch = list_jinban.at(1).toInt();
                    if(list_jinban.at(0) == "ANT0")
                    {
                        port_num = 1;
                        switch(ch)
                        {
                        case 1 : openfile_set_LineLoss("CH1", loss_value, port_num);
                            break;
                        case 3 : openfile_set_LineLoss("CH3", loss_value, port_num);
                            break;
                        case 7 : openfile_set_LineLoss("CH7", loss_value, port_num);
                            break;
                        case 11 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        case 13 : openfile_set_LineLoss("CH13", loss_value, port_num);
                            break;
                        case 36 : openfile_set_LineLoss("CH36", loss_value, port_num);
                            break;
                        case 48 : openfile_set_LineLoss("CH48", loss_value, port_num);
                            break;
                        case 52 : openfile_set_LineLoss("CH52", loss_value, port_num);
                            break;
                        case 64 : openfile_set_LineLoss("CH64", loss_value, port_num);
                            break;
                        case 100 : openfile_set_LineLoss("CH100", loss_value, port_num);
                            break;
                        case 116 : openfile_set_LineLoss("CH116", loss_value, port_num);
                            break;
                        case 120 : openfile_set_LineLoss("CH120", loss_value, port_num);
                            break;
                        case 136 : openfile_set_LineLoss("CH136", loss_value, port_num);
                            break;
                        case 140 : openfile_set_LineLoss("CH140", loss_value, port_num);
                            break;
                        case 157 : openfile_set_LineLoss("CH157", loss_value, port_num);
                            break;
                        case 161 : openfile_set_LineLoss("CH161", loss_value, port_num);
                            break;
                        case 165 : openfile_set_LineLoss("CH165", loss_value, port_num);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        port_num = 2;
                        switch(ch)
                        {
                            case 1 : openfile_set_LineLoss("CH1", loss_value, port_num);
                                break;
                            case 3 : openfile_set_LineLoss("CH3", loss_value, port_num);
                                break;
                            case 7 : openfile_set_LineLoss("CH7", loss_value, port_num);
                                break;
                            case 11 : openfile_set_LineLoss("CH11", loss_value, port_num);
                                break;
                            case 13 : openfile_set_LineLoss("CH13", loss_value, port_num);
                                break;
                            case 36 : openfile_set_LineLoss("CH36", loss_value, port_num);
                                break;
                            case 48 : openfile_set_LineLoss("CH48", loss_value, port_num);
                                break;
                            case 52 : openfile_set_LineLoss("CH52", loss_value, port_num);
                                break;
                            case 64 : openfile_set_LineLoss("CH64", loss_value, port_num);
                                break;
                            case 100 : openfile_set_LineLoss("CH100", loss_value, port_num);
                                break;
                            case 116 : openfile_set_LineLoss("CH116", loss_value, port_num);
                                break;
                            case 120 : openfile_set_LineLoss("CH120", loss_value, port_num);
                                break;
                            case 136 : openfile_set_LineLoss("CH136", loss_value, port_num);
                                break;
                            case 140 : openfile_set_LineLoss("CH140", loss_value, port_num);
                                break;
                            case 157 : openfile_set_LineLoss("CH157", loss_value, port_num);
                                break;
                            case 161 : openfile_set_LineLoss("CH161", loss_value, port_num);
                                break;
                            case 165 : openfile_set_LineLoss("CH165", loss_value, port_num);
                                break;
                            default:
                                break;
                        }
                    }
                }

            }
            else
            {
#if 1
                //微调操作
                //qDebug() << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW 微调";
                //qDebug() << "000000000"<<strtemp_test;
                if(strtemp_test.mid(0, 3) == "ANT" && strtemp_jinban.mid(0, 3) == "ANT")
                {


                    list_test = strtemp_test.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    list_jinban = strtemp_jinban.split(QRegExp("\\s+"), QString::SkipEmptyParts);

                    temp_value = list_jinban.at(2).toDouble() - list_test.at(2).toDouble();
                    /*if(qAbs(temp_value) > 0.5)
                    {
                        correct_flag = false;
                        loss_value = list_jinban.at(4).toDouble() + temp_value/2;
                    }
                    temp += list_jinban.at(0) + "\t\t" + list_jinban.at(1) + "\t\t" + list_jinban.at(2) + "\t\t";
                    temp += list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                    //temp += strtemp_jinban + "\t\t"  + list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                    temp += QString('\n');

                    if(qAbs(temp_value) <= 0.5)
                    {
                        continue;
                    }
                    else
                    {
                        correct_flag = false;
                        loss_value = list_jinban.at(4).toDouble() + temp_value/2;
                    }*/
                    temp += list_jinban.at(0) + "\t\t" + list_jinban.at(1) + "\t\t" + list_jinban.at(2) + "\t\t";
                    if(qAbs(temp_value) > 0.5)
                    {
                        correct_flag = false;
                        loss_value = list_jinban.at(4).toDouble() + temp_value/2;
                        temp += list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                        temp += QString('\n');
                    }
                    else
                    {
                        //loss_value = list_jinban.at(4).toDouble();
                        temp += list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                        temp += QString('\n');
                        continue;
                    }


                    ch = list_jinban.at(1).toInt();
                    if(list_jinban.at(0) == "ANT0")
                    {
                        port_num = 1;
                        switch(ch)
                        {
                        case 1 : openfile_set_LineLoss("CH1", loss_value, port_num);
                            break;
                        case 3 : openfile_set_LineLoss("CH3", loss_value, port_num);
                            break;
                        case 7 : openfile_set_LineLoss("CH7", loss_value, port_num);
                            break;
                        case 11 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        case 13 : openfile_set_LineLoss("CH13", loss_value, port_num);
                            break;
                        case 36 : openfile_set_LineLoss("CH36", loss_value, port_num);
                            break;
                        case 48 : openfile_set_LineLoss("CH48", loss_value, port_num);
                            break;
                        case 52 : openfile_set_LineLoss("CH52", loss_value, port_num);
                            break;
                        case 64 : openfile_set_LineLoss("CH64", loss_value, port_num);
                            break;
                        case 100 : openfile_set_LineLoss("CH100", loss_value, port_num);
                            break;
                        case 116 : openfile_set_LineLoss("CH116", loss_value, port_num);
                            break;
                        case 120 : openfile_set_LineLoss("CH120", loss_value, port_num);
                            break;
                        case 136 : openfile_set_LineLoss("CH136", loss_value, port_num);
                            break;
                        case 140 : openfile_set_LineLoss("CH140", loss_value, port_num);
                            break;
                        case 157 : openfile_set_LineLoss("CH157", loss_value, port_num);
                            break;
                        case 161 : openfile_set_LineLoss("CH161", loss_value, port_num);
                            break;
                        case 165 : openfile_set_LineLoss("CH165", loss_value, port_num);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        port_num = 2;
                        switch(ch)
                        {
                            case 1 : openfile_set_LineLoss("CH1", loss_value, port_num);
                                break;
                            case 3 : openfile_set_LineLoss("CH3", loss_value, port_num);
                                break;
                            case 7 : openfile_set_LineLoss("CH7", loss_value, port_num);
                                break;
                            case 11 : openfile_set_LineLoss("CH11", loss_value, port_num);
                                break;
                            case 13 : openfile_set_LineLoss("CH13", loss_value, port_num);
                                break;
                            case 36 : openfile_set_LineLoss("CH36", loss_value, port_num);
                                break;
                            case 48 : openfile_set_LineLoss("CH48", loss_value, port_num);
                                break;
                            case 52 : openfile_set_LineLoss("CH52", loss_value, port_num);
                                break;
                            case 64 : openfile_set_LineLoss("CH64", loss_value, port_num);
                                break;
                            case 100 : openfile_set_LineLoss("CH100", loss_value, port_num);
                                break;
                            case 116 : openfile_set_LineLoss("CH116", loss_value, port_num);
                                break;
                            case 120 : openfile_set_LineLoss("CH120", loss_value, port_num);
                                break;
                            case 136 : openfile_set_LineLoss("CH136", loss_value, port_num);
                                break;
                            case 140 : openfile_set_LineLoss("CH140", loss_value, port_num);
                                break;
                            case 157 : openfile_set_LineLoss("CH157", loss_value, port_num);
                                break;
                            case 161 : openfile_set_LineLoss("CH161", loss_value, port_num);
                                break;
                            case 165 : openfile_set_LineLoss("CH165", loss_value, port_num);
                                break;
                            default:
                                break;
                        }
                    }
                }
                #endif
            }

        }


        Ncfile_jinban.close();
        Ncfile_test.close();
        Ncfile_test.remove();
        QFile Ncfile_jinban("../log/standard.txt");
        Ncfile_jinban.open(QIODevice::WriteOnly);
        QTextStream in(&Ncfile_jinban);
        in <<temp;
        Ncfile_jinban.close();
    }
    else
    {
        about_info_auto("警告", "金版数据 | test_log 打开失败！", 2000);
        qDebug() << "text 和金板 文件打开失败";
    }

}



/**************************************************************************
**
** NAME     openfile_set_show
**
** PARAMETERS:  (QString filename, QString line_id, QLineEdit* wirte_show)
**
** RETURNS:
**
** DESCRIPTION  写入线损值.
**
** NOTES:       None.
**************************************************************************/
void MyThread::openfile_set_LineLoss(QString Box_name, double loss_value, int port_num)
{
    QString RunFrameNcFile = filename_WT_ATTEN_DUT;
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);

        QString temp;
        QString hello = "hello world!";

        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            QStringList list;
             //qDebug() << "!!!!!!!!!!!!!!!" << strtemp.mid(0, 2);

            if(strtemp.mid(0, 2) == "CH")
            {
                //qDebug() << "!!!!!!!!!!!!!!!";
                list = strtemp.split("//").at(0).split(QRegExp("\\s+"), QString::SkipEmptyParts);
            }
            else
            {
                list = hello.split(" ");
            }
            if(list.at(0) == Box_name)
            {
                QString sp = QString::number(loss_value,'f',1);
                int i=0;
                int len = list.size();
                for(i=0;i<len;i++)
                {
                    if(i == port_num)
                    {
                        temp += sp + "\t\t";

                    }
                    else{
                        temp += list.at(i) + "\t\t";
                    }
                }
                temp += "// " + strtemp.split("//").at(1);
                temp += QString('\n');
            }
            else
            {
                temp += strtemp;
                temp += QString('\n');
            }
        }
        Ncfile.close();
        Ncfile.open(QIODevice::WriteOnly);
        QTextStream in(&Ncfile);
        in <<temp;
        Ncfile.close();
    }
    else
    {
        //about_info_auto("错误", "DUT文件 打开失败！", 1000);
    }
}

