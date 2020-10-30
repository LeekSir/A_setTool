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
extern bool air_link_flag;

extern QString correct_Port_Num;
extern QString filename_WT_ATTEN_DUT;
extern QMutex mutex;
extern QString cmd;

bool get_pass_log = false;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;

    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(Pass_log_clicked()));
}

void MyThread::run()
{
//半自动，
#if 1
    QProcess p(this);

    while(1)
    {
        QStringList arguments;
        arguments << "/c" << "cd ../../ && " + cmd;
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
                p.start("cmd.exe", arguments);
                if(p.waitForFinished(120000))               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {

                    //Sleep(1000);
                    if(!Pass_log_clicked())
                    {

                        PASS_flag = false;
                        break;
                    }
                    p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                    if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    {
                        //Sleep(1000);
                    }


                }
                openfile_deal_lineloss_log();
                if(correct_flag)
                    break;
                correct = false;
            }
        }
        else
        {
            //4、多次测试后，如测试数据和金板数据相差不大于正负0.5，则校准成功
            p.start("cmd.exe", arguments);
            if(p.waitForFinished(120000))               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {

                //Sleep(1000);
                if(!Pass_log_clicked())
                {

                    PASS_flag = false;
                    break;
                }
                p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    //Sleep(1000);
                }


            }
            openfile_deal_lineloss_log();
            if(correct_flag)
                break;
            //set_LineLoss_correct();
        }
    }
    //mutex.unlock();
    emit mySignal();
//全自动
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
                p.start(correct_Port_Num);
                if(p.waitForFinished(120000))               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {

                    //Sleep(1000);
                    if(!Pass_log_clicked())
                    {

                        PASS_flag = false;
                        break;
                    }
                    p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                    if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    {
                        //Sleep(1000);
                    }
                }
                openfile_deal_lineloss_log();
                if(correct_flag)
                    break;
                correct = false;
            }
        }
        else
        {
            //4、多次测试后，如测试数据和金板数据相差不大于正负0.5，则校准成功
            p.start(correct_Port_Num);  //运行校验线损脚本文件
            if(p.waitForFinished(120000))               //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {
                if(!Pass_log_clicked())
                {

                    PASS_flag = false;
                    break;
                }
                p.start("./copy_new_log.bat");          //运行校验线损脚本文件
                if(p.waitForFinished())                 //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    //Sleep(1000);
                }


            }
            openfile_deal_lineloss_log();
            if(correct_flag)
                break;
        }
    }
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
    air_link_flag=false;

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
        bool old_new_flag = false;
        int i = 0;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            QStringList list;
            if(strtemp.mid(0, 30).count("ANT0") >= 1 || strtemp.mid(0, 30).count("ANT1") >= 1)
            {

                list = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts);

                //因为新旧产测软件的汇总数据差异，需要做筛选
                for(; i<list.size() && !old_new_flag; i++)
                {
                    if(list.at(i).count("ANT") == 1)
                    {
                        old_new_flag = true;
                        break;
                    }
                }
                if(list.at(i+3) != "1DH1")
                {
                    temp += list.at(i) + "\t\t" + list.at(i+1) + "\t\t" + list.at(i+5).split('d').at(0);
                    temp += QString('\n');
                }

            }
            if((strtemp.mid(0, 30).count("42") == 1 && strtemp.mid(0, 30).count("2444") == 1 && strtemp.mid(0, 30).count("1DH1") == 1)
                    || (strtemp.mid(0, 50).count("15") == 1 && strtemp.mid(0, 50).count("ANT0") == 1 && strtemp.mid(0, 50).count("42") == 1 && strtemp.mid(0, 50).count("2444") == 1 && strtemp.mid(0, 50).count("1DH1") == 1))
            {
                list = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts);

                //因为新旧产测软件的汇总数据差异，需要做筛选
                for(; i<list.size(); i++)
                {
                    if(list.at(i).count("dBm") == 1)
                    {
                        break;
                    }
                }
                temp += "BT\t\t42\t\t" + list.at(i).split('d').at(0);
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
        correct_flag = false;
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
                if((strtemp_test.mid(0, 3) == "ANT" && strtemp_jinban.mid(0, 3) == "ANT") || (strtemp_test.mid(0, 2) == "BT" && strtemp_jinban.mid(0, 2) == "BT"))
                {
                    list_test = strtemp_test.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    list_jinban = strtemp_jinban.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    temp += strtemp_jinban + "\t\t"  + list_test.at(2) + "\t\t" + QString::number((list_jinban.at(2).toDouble() - list_test.at(2).toDouble()),'f',2);
                    temp += QString('\n');
                    //if(list_jinban.at(2).toDouble() - list_test.at(2).toDouble())

                    ch = list_jinban.at(1).toInt();
                    if(qAbs(list_jinban.at(2).toDouble() - list_test.at(2).toDouble()) <= 0.5)
                    {
                        continue;
                    }
                    else
                    {
                        correct_flag = false;
                        //loss_value = list_jinban.at(2).toDouble() - list_test.at(2).toDouble();
                    }
                    loss_value = list_jinban.at(2).toDouble() - list_test.at(2).toDouble();
                    //写蓝牙线损数据
                    if(list_test.at(0) == "BT" && list_jinban.at(0) == "BT")
                    {
                        openfile_set_BT_value("WT_FIXED_ATTEN_BT", loss_value + openfile_display(filename_WT_ATTEN_DUT,"WT_FIXED_ATTEN_BT").toDouble());
                        break;
                    }

                    if(list_jinban.at(0) == "ANT0")
                    {
                        port_num = 1;
                        switch(ch)
                        {
                            case 1 : openfile_set_LineLoss("CH1", loss_value + openfile_display_lineloss("CH1", port_num).toDouble(), port_num);
                                break;
                            case 3 : openfile_set_LineLoss("CH3", loss_value + openfile_display_lineloss("CH3", port_num).toDouble(), port_num);
                                break;
                            case 7 : openfile_set_LineLoss("CH7", loss_value + openfile_display_lineloss("CH7", port_num).toDouble(), port_num);
                                break;
                            case 11 : openfile_set_LineLoss("CH11", loss_value + openfile_display_lineloss("CH11", port_num).toDouble(), port_num);
                                break;
                            case 13 : openfile_set_LineLoss("CH13", loss_value + openfile_display_lineloss("CH13", port_num).toDouble(), port_num);
                                break;
                            case 36 : openfile_set_LineLoss("CH36", loss_value + openfile_display_lineloss("CH36", port_num).toDouble(), port_num);
                                break;
                            case 48 : openfile_set_LineLoss("CH48", loss_value + openfile_display_lineloss("CH48", port_num).toDouble(), port_num);
                                break;
                            case 52 : openfile_set_LineLoss("CH52", loss_value + openfile_display_lineloss("CH52", port_num).toDouble(), port_num);
                                break;
                            case 64 : openfile_set_LineLoss("CH64", loss_value + openfile_display_lineloss("CH64", port_num).toDouble(), port_num);
                                break;
                            case 100 : openfile_set_LineLoss("CH100", loss_value + openfile_display_lineloss("CH100", port_num).toDouble(), port_num);
                                break;
                            case 116 : openfile_set_LineLoss("CH116", loss_value + openfile_display_lineloss("CH116", port_num).toDouble(), port_num);
                                break;
                            case 120 : openfile_set_LineLoss("CH120", loss_value + openfile_display_lineloss("CH120", port_num).toDouble(), port_num);
                                break;
                            case 136 : openfile_set_LineLoss("CH136", loss_value + openfile_display_lineloss("CH136", port_num).toDouble(), port_num);
                                break;
                            case 140 : openfile_set_LineLoss("CH140", loss_value + openfile_display_lineloss("CH140", port_num).toDouble(), port_num);
                                break;
                            case 157 : openfile_set_LineLoss("CH157", loss_value + openfile_display_lineloss("CH157", port_num).toDouble(), port_num);
                                break;
                            case 161 : openfile_set_LineLoss("CH161", loss_value + openfile_display_lineloss("CH161", port_num).toDouble(), port_num);
                                break;
                            case 165 : openfile_set_LineLoss("CH165", loss_value + openfile_display_lineloss("CH165", port_num).toDouble(), port_num);
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
                            case 1 : openfile_set_LineLoss("CH1", loss_value + openfile_display_lineloss("CH1", port_num).toDouble(), port_num);
                                break;
                            case 3 : openfile_set_LineLoss("CH3", loss_value + openfile_display_lineloss("CH3", port_num).toDouble(), port_num);
                                break;
                            case 7 : openfile_set_LineLoss("CH7", loss_value + openfile_display_lineloss("CH7", port_num).toDouble(), port_num);
                                break;
                            case 11 : openfile_set_LineLoss("CH11", loss_value + openfile_display_lineloss("CH11", port_num).toDouble(), port_num);
                                break;
                            case 13 : openfile_set_LineLoss("CH13", loss_value + openfile_display_lineloss("CH13", port_num).toDouble(), port_num);
                                break;
                            case 36 : openfile_set_LineLoss("CH36", loss_value + openfile_display_lineloss("CH36", port_num).toDouble(), port_num);
                                break;
                            case 48 : openfile_set_LineLoss("CH48", loss_value + openfile_display_lineloss("CH48", port_num).toDouble(), port_num);
                                break;
                            case 52 : openfile_set_LineLoss("CH52", loss_value + openfile_display_lineloss("CH52", port_num).toDouble(), port_num);
                                break;
                            case 64 : openfile_set_LineLoss("CH64", loss_value + openfile_display_lineloss("CH64", port_num).toDouble(), port_num);
                                break;
                            case 100 : openfile_set_LineLoss("CH100", loss_value + openfile_display_lineloss("CH100", port_num).toDouble(), port_num);
                                break;
                            case 116 : openfile_set_LineLoss("CH116", loss_value + openfile_display_lineloss("CH116", port_num).toDouble(), port_num);
                                break;
                            case 120 : openfile_set_LineLoss("CH120", loss_value + openfile_display_lineloss("CH120", port_num).toDouble(), port_num);
                                break;
                            case 136 : openfile_set_LineLoss("CH136", loss_value + openfile_display_lineloss("CH136", port_num).toDouble(), port_num);
                                break;
                            case 140 : openfile_set_LineLoss("CH140", loss_value + openfile_display_lineloss("CH140", port_num).toDouble(), port_num);
                                break;
                            case 157 : openfile_set_LineLoss("CH157", loss_value + openfile_display_lineloss("CH157", port_num).toDouble(), port_num);
                                break;
                            case 161 : openfile_set_LineLoss("CH161", loss_value + openfile_display_lineloss("CH161", port_num).toDouble(), port_num);
                                break;
                            case 165 : openfile_set_LineLoss("CH165", loss_value + openfile_display_lineloss("CH165", port_num).toDouble(), port_num);
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
                    ch = list_jinban.at(1).toInt();

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
                        //进行传导和耦合的判断，并设定线损阈值
                        /*QString air_link=openfile_display("../CFG_FILE/air_link.txt", "air_link");
                        double line_Loss_0 = openfile_display_lineloss("CH" + list_jinban.at(1), 1).toDouble();
                        double line_Loss_1 = openfile_display_lineloss("CH" + list_jinban.at(1), 2).toDouble();
                        qDebug() << "line_Loss_0 = " << line_Loss_0 << "; line_Loss_1 = " << line_Loss_1;
                        if(ch <= 13)
                        {
                            if((air_link == '0'))// && line_Loss_0 < 10 && line_Loss_1 < 10) || (air_link == '1' && line_Loss_0.toDouble() < 15 && line_Loss_1 < 15))
                            {
                                if(line_Loss_0 > 10 || line_Loss_1 > 10)
                                {
                                    air_link_flag=false;
                                }
                            }
                            else if(air_link == '1')
                            {
                                if(line_Loss_0 > 15 || line_Loss_1 > 15)
                                {
                                    air_link_flag=false;
                                }
                            }
                        }
                        else
                        {
                            if((air_link == '0'))// && line_Loss_0 < 10 && line_Loss_1 < 10) || (air_link == '1' && line_Loss_0.toDouble() < 15 && line_Loss_1 < 15))
                            {
                                if(line_Loss_0 > 15 || line_Loss_1 > 15)
                                {
                                    air_link_flag=false;
                                }
                            }
                            else if(air_link == '1')
                            {
                                if(line_Loss_0 > 20 || line_Loss_1 > 20)
                                {
                                    air_link_flag=false;
                                }
                            }

                        }*/
                        //loss_value = list_jinban.at(4).toDouble();
                        temp += list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                        temp += QString('\n');



                        continue;
                    }

                    //写蓝牙线损数据
                    if(list_test.at(0) == "BT" && list_jinban.at(0) == "BT")
                    {
                        openfile_set_BT_value("WT_FIXED_ATTEN_BT", loss_value);
                        break;
                    }


                    if(list_jinban.at(0) == "ANT0")
                    {
                        port_num = 1;
                        switch(ch)
                        {
                        //5G
                        case 1 : openfile_set_LineLoss("CH1", loss_value, port_num);
                            break;
                        case 2 : openfile_set_LineLoss("CH2", loss_value, port_num);
                            break;
                        case 3 : openfile_set_LineLoss("CH3", loss_value, port_num);
                            break;
                        case 4 : openfile_set_LineLoss("CH4", loss_value, port_num);
                            break;
                        case 5 : openfile_set_LineLoss("CH5", loss_value, port_num);
                            break;
                        case 6 : openfile_set_LineLoss("CH6", loss_value, port_num);
                            break;
                        case 7 : openfile_set_LineLoss("CH7", loss_value, port_num);
                            break;
                        case 8 : openfile_set_LineLoss("CH8", loss_value, port_num);
                            break;
                        case 9 : openfile_set_LineLoss("CH9", loss_value, port_num);
                            break;
                        case 10 : openfile_set_LineLoss("CH10", loss_value, port_num);
                            break;
                        case 11 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        case 12 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        case 13 : openfile_set_LineLoss("CH13", loss_value, port_num);
                            break;
                        case 14 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        //5G
                        case 36 : openfile_set_LineLoss("CH36", loss_value, port_num);
                            break;
                        case 38 : openfile_set_LineLoss("CH38", loss_value, port_num);
                            break;
                        case 40 : openfile_set_LineLoss("CH40", loss_value, port_num);
                            break;
                        case 42 : openfile_set_LineLoss("CH42", loss_value, port_num);
                            break;
                        case 44 : openfile_set_LineLoss("CH44", loss_value, port_num);
                            break;
                        case 46 : openfile_set_LineLoss("CH46", loss_value, port_num);
                            break;
                        case 48 : openfile_set_LineLoss("CH48", loss_value, port_num);
                            break;
                        case 50 : openfile_set_LineLoss("CH48", loss_value, port_num);
                            break;
                        case 52 : openfile_set_LineLoss("CH52", loss_value, port_num);
                            break;
                        case 54 : openfile_set_LineLoss("CH54", loss_value, port_num);
                            break;
                        case 56 : openfile_set_LineLoss("CH56", loss_value, port_num);
                            break;
                        case 58 : openfile_set_LineLoss("CH58", loss_value, port_num);
                            break;
                        case 60 : openfile_set_LineLoss("CH60", loss_value, port_num);
                            break;
                        case 62 : openfile_set_LineLoss("CH62", loss_value, port_num);
                            break;
                        case 64 : openfile_set_LineLoss("CH64", loss_value, port_num);
                            break;
                        case 100 : openfile_set_LineLoss("CH100", loss_value, port_num);
                            break;
                        case 102 : openfile_set_LineLoss("CH102", loss_value, port_num);
                            break;
                        case 104 : openfile_set_LineLoss("CH104", loss_value, port_num);
                            break;
                        case 106 : openfile_set_LineLoss("CH106", loss_value, port_num);
                            break;
                        case 108 : openfile_set_LineLoss("CH108", loss_value, port_num);
                            break;
                        case 110 : openfile_set_LineLoss("CH110", loss_value, port_num);
                            break;
                        case 112 : openfile_set_LineLoss("CH112", loss_value, port_num);
                            break;
                        case 116 : openfile_set_LineLoss("CH116", loss_value, port_num);
                            break;
                        case 118 : openfile_set_LineLoss("CH118", loss_value, port_num);
                            break;
                        case 120 : openfile_set_LineLoss("CH120", loss_value, port_num);
                            break;
                        case 122 : openfile_set_LineLoss("CH122", loss_value, port_num);
                            break;
                        case 124 : openfile_set_LineLoss("CH124", loss_value, port_num);
                            break;
                        case 126 : openfile_set_LineLoss("CH126", loss_value, port_num);
                            break;
                        case 128 : openfile_set_LineLoss("CH128", loss_value, port_num);
                            break;
                        case 130 : openfile_set_LineLoss("CH130", loss_value, port_num);
                            break;
                        case 132 : openfile_set_LineLoss("CH132", loss_value, port_num);
                            break;
                        case 134 : openfile_set_LineLoss("CH134", loss_value, port_num);
                            break;
                        case 136 : openfile_set_LineLoss("CH136", loss_value, port_num);
                            break;
                        case 140 : openfile_set_LineLoss("CH140", loss_value, port_num);
                            break;
                        case 142 : openfile_set_LineLoss("CH142", loss_value, port_num);
                            break;
                        case 144 : openfile_set_LineLoss("CH144", loss_value, port_num);
                            break;
                        case 146 : openfile_set_LineLoss("CH146", loss_value, port_num);
                            break;
                        case 149 : openfile_set_LineLoss("CH149", loss_value, port_num);
                            break;
                        case 151 : openfile_set_LineLoss("CH151", loss_value, port_num);
                            break;
                        case 153 : openfile_set_LineLoss("CH153", loss_value, port_num);
                            break;
                        case 155 : openfile_set_LineLoss("CH155", loss_value, port_num);
                            break;
                        case 157 : openfile_set_LineLoss("CH157", loss_value, port_num);
                            break;
                        case 159 : openfile_set_LineLoss("CH159", loss_value, port_num);
                            break;
                        case 161 : openfile_set_LineLoss("CH161", loss_value, port_num);
                            break;
                        case 163 : openfile_set_LineLoss("CH163", loss_value, port_num);
                            break;
                        case 165 : openfile_set_LineLoss("CH165", loss_value, port_num);
                            break;
                        case 167 : openfile_set_LineLoss("CH167", loss_value, port_num);
                            break;
                        case 169 : openfile_set_LineLoss("CH169", loss_value, port_num);
                            break;
                        case 171 : openfile_set_LineLoss("CH171", loss_value, port_num);
                            break;
                        case 173 : openfile_set_LineLoss("CH173", loss_value, port_num);
                            break;
                        case 175 : openfile_set_LineLoss("CH175", loss_value, port_num);
                            break;
                        case 177 : openfile_set_LineLoss("CH177", loss_value, port_num);
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
                        //5G
                        case 1 : openfile_set_LineLoss("CH1", loss_value, port_num);
                            break;
                        case 2 : openfile_set_LineLoss("CH2", loss_value, port_num);
                            break;
                        case 3 : openfile_set_LineLoss("CH3", loss_value, port_num);
                            break;
                        case 4 : openfile_set_LineLoss("CH4", loss_value, port_num);
                            break;
                        case 5 : openfile_set_LineLoss("CH5", loss_value, port_num);
                            break;
                        case 6 : openfile_set_LineLoss("CH6", loss_value, port_num);
                            break;
                        case 7 : openfile_set_LineLoss("CH7", loss_value, port_num);
                            break;
                        case 8 : openfile_set_LineLoss("CH8", loss_value, port_num);
                            break;
                        case 9 : openfile_set_LineLoss("CH9", loss_value, port_num);
                            break;
                        case 10 : openfile_set_LineLoss("CH10", loss_value, port_num);
                            break;
                        case 11 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        case 12 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        case 13 : openfile_set_LineLoss("CH13", loss_value, port_num);
                            break;
                        case 14 : openfile_set_LineLoss("CH11", loss_value, port_num);
                            break;
                        //5G
                        case 36 : openfile_set_LineLoss("CH36", loss_value, port_num);
                            break;
                        case 38 : openfile_set_LineLoss("CH38", loss_value, port_num);
                            break;
                        case 40 : openfile_set_LineLoss("CH40", loss_value, port_num);
                            break;
                        case 42 : openfile_set_LineLoss("CH42", loss_value, port_num);
                            break;
                        case 44 : openfile_set_LineLoss("CH44", loss_value, port_num);
                            break;
                        case 46 : openfile_set_LineLoss("CH46", loss_value, port_num);
                            break;
                        case 48 : openfile_set_LineLoss("CH48", loss_value, port_num);
                            break;
                        case 50 : openfile_set_LineLoss("CH48", loss_value, port_num);
                            break;
                        case 52 : openfile_set_LineLoss("CH52", loss_value, port_num);
                            break;
                        case 54 : openfile_set_LineLoss("CH54", loss_value, port_num);
                            break;
                        case 56 : openfile_set_LineLoss("CH56", loss_value, port_num);
                            break;
                        case 58 : openfile_set_LineLoss("CH58", loss_value, port_num);
                            break;
                        case 60 : openfile_set_LineLoss("CH60", loss_value, port_num);
                            break;
                        case 62 : openfile_set_LineLoss("CH62", loss_value, port_num);
                            break;
                        case 64 : openfile_set_LineLoss("CH64", loss_value, port_num);
                            break;
                        case 100 : openfile_set_LineLoss("CH100", loss_value, port_num);
                            break;
                        case 102 : openfile_set_LineLoss("CH102", loss_value, port_num);
                            break;
                        case 104 : openfile_set_LineLoss("CH104", loss_value, port_num);
                            break;
                        case 106 : openfile_set_LineLoss("CH106", loss_value, port_num);
                            break;
                        case 108 : openfile_set_LineLoss("CH108", loss_value, port_num);
                            break;
                        case 110 : openfile_set_LineLoss("CH110", loss_value, port_num);
                            break;
                        case 112 : openfile_set_LineLoss("CH112", loss_value, port_num);
                            break;
                        case 116 : openfile_set_LineLoss("CH116", loss_value, port_num);
                            break;
                        case 118 : openfile_set_LineLoss("CH118", loss_value, port_num);
                            break;
                        case 120 : openfile_set_LineLoss("CH120", loss_value, port_num);
                            break;
                        case 122 : openfile_set_LineLoss("CH122", loss_value, port_num);
                            break;
                        case 124 : openfile_set_LineLoss("CH124", loss_value, port_num);
                            break;
                        case 126 : openfile_set_LineLoss("CH126", loss_value, port_num);
                            break;
                        case 128 : openfile_set_LineLoss("CH128", loss_value, port_num);
                            break;
                        case 130 : openfile_set_LineLoss("CH130", loss_value, port_num);
                            break;
                        case 132 : openfile_set_LineLoss("CH132", loss_value, port_num);
                            break;
                        case 134 : openfile_set_LineLoss("CH134", loss_value, port_num);
                            break;
                        case 136 : openfile_set_LineLoss("CH136", loss_value, port_num);
                            break;
                        case 140 : openfile_set_LineLoss("CH140", loss_value, port_num);
                            break;
                        case 142 : openfile_set_LineLoss("CH142", loss_value, port_num);
                            break;
                        case 144 : openfile_set_LineLoss("CH144", loss_value, port_num);
                            break;
                        case 146 : openfile_set_LineLoss("CH146", loss_value, port_num);
                            break;
                        case 149 : openfile_set_LineLoss("CH149", loss_value, port_num);
                            break;
                        case 151 : openfile_set_LineLoss("CH151", loss_value, port_num);
                            break;
                        case 153 : openfile_set_LineLoss("CH153", loss_value, port_num);
                            break;
                        case 155 : openfile_set_LineLoss("CH155", loss_value, port_num);
                            break;
                        case 157 : openfile_set_LineLoss("CH157", loss_value, port_num);
                            break;
                        case 159 : openfile_set_LineLoss("CH159", loss_value, port_num);
                            break;
                        case 161 : openfile_set_LineLoss("CH161", loss_value, port_num);
                            break;
                        case 163 : openfile_set_LineLoss("CH163", loss_value, port_num);
                            break;
                        case 165 : openfile_set_LineLoss("CH165", loss_value, port_num);
                            break;
                        case 167 : openfile_set_LineLoss("CH167", loss_value, port_num);
                            break;
                        case 169 : openfile_set_LineLoss("CH169", loss_value, port_num);
                            break;
                        case 171 : openfile_set_LineLoss("CH171", loss_value, port_num);
                            break;
                        case 173 : openfile_set_LineLoss("CH173", loss_value, port_num);
                            break;
                        case 175 : openfile_set_LineLoss("CH175", loss_value, port_num);
                            break;
                        case 177 : openfile_set_LineLoss("CH177", loss_value, port_num);
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
        //Ncfile_test.remove();
        QFile Ncfile_jinban("../log/standard.txt");
        Ncfile_jinban.open(QIODevice::WriteOnly);
        QTextStream in(&Ncfile_jinban);
        in <<temp;
        Ncfile_jinban.close();
    }
    else
    {
        correct_flag = false;
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

/**************************************************************************
**
** NAME     openfile_display
**
** PARAMETERS:  QString filename, QString show
**
** RETURNS: QString
**
** DESCRIPTION  显示文件中的关键信息对应到相应的lineEdit_d_id.
**
** NOTES:       None.
**************************************************************************/
QString MyThread::openfile_display_lineloss(QString show, int port_num)
{
    QString RunFrameNcFile = filename_WT_ATTEN_DUT;
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);
        //展示项
        QString temp = show;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            //temp = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0);
            if(strtemp.mid(0, temp.length()) == temp)
            {
                 //qDebug() << strtemp;
                 temp = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(port_num);
                 //qDebug() << temp;
                 Ncfile.close();
                 return temp;
            }
        }
        Ncfile.close();
    }
    return NULL;

}



/**************************************************************************
**
** NAME     openfile_display
**
** PARAMETERS:  QString filename, QString show
**
** RETURNS: QString
**
** DESCRIPTION  显示文件中的关键信息对应到相应的lineEdit_d_id.
**
** NOTES:       None.
**************************************************************************/
QString MyThread::openfile_display(QString filename, QString show)
{
    QString RunFrameNcFile = filename;
    QFile Ncfile(RunFrameNcFile);
    if(!Ncfile.open(QIODevice::ReadOnly))
    {
        return NULL;
    }

    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);
        //展示项
        QString temp = show;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, temp.length()) == temp)
            {
                 temp = (strtemp.split("//").at(0)).split('=').at(1).simplified();
                 if(temp.length() == 0)
                 {
                     //temp = "此项为空";
                 }
                 //qDebug() << temp;
                 Ncfile.close();
                 return temp;
            }
        }
        Ncfile.close();
    }
    return NULL;

}

/**************************************************************************
**
** NAME     openfile_set_BT_value
**
** PARAMETERS:  (QString Box_id, double lineloss)
**
** RETURNS:
**
** DESCRIPTION  设置第二页中的相关参数.
**
** NOTES:       None.
**************************************************************************/
void MyThread::openfile_set_BT_value(QString Box_id, double loss_value)
{
    QString RunFrameNcFile = filename_WT_ATTEN_DUT;
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);

        QString temp;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, Box_id.length()) == Box_id)
            {
                qDebug() << strtemp;
                temp += Box_id + "\t=\t" + QString::number(loss_value,'f',1);
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
}


