#include "factory_set.h"
#include "ui_factory_set.h"



factory_set::factory_set(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::factory_set)
{
    ui->setupUi(this);
    //display();
}

factory_set::~factory_set()
{
    delete ui;
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
QString factory_set::openfile_display(QString filename, QString show)
{
    QString RunFrameNcFile = filename;
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
            if(strtemp.mid(0, temp.length()) == temp)
            {
                 temp = (strtemp.split("//").at(0)).split('=').at(1).simplified();
                 if(temp.length() == 0)
                 {
                     //temp = "此项为空";
                 }
                 qDebug() << temp;
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
** NAME     openfile_set_show
**
** PARAMETERS:  (QString filename, QString line_id, QLineEdit* wirte_show)
**
** RETURNS:
**
** DESCRIPTION  设置第一页中的相关参数.
**
** NOTES:       None.
**************************************************************************/
void factory_set::openfile_set_show(QString filename, QString line_id, QLineEdit* wirte_show)
{
    QString RunFrameNcFile = filename;
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
            if(strtemp.mid(0, line_id.length()) == line_id)
            {
                qDebug() << strtemp;
                temp += line_id + '=' + wirte_show->text() + "                          //" + strtemp.split("//").at(1);
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

/**************************************************************************
**
** NAME     display
**
** PARAMETERS:  void
**
** RETURNS:
**
** DESCRIPTION  查找关键字，并显示所有信息在界面上的lineEdit中.
**
** NOTES:       None.
**************************************************************************/
#if 1
void factory_set::display()
{
    if(!this->Usr_Type)
    {
        //第一页
        ui->pushButton_set->setEnabled(0);
        ui->lineEdit_IP->setReadOnly(1);
        ui->lineEdit_Port->setReadOnly(1);
        ui->lineEdit_WksNo->setReadOnly(1);
        ui->lineEdit_passwd->setReadOnly(1);
        ui->lineEdit_NgCount->setReadOnly(1);
        ui->lineEdit_causeNo->setReadOnly(1);
        ui->lineEdit_TestItem->setReadOnly(1);
        ui->lineEdit_WorkerNo->setReadOnly(1);
        ui->lineEdit_User_name->setReadOnly(1);
        ui->lineEdit_OS_address->setReadOnly(1);
        ui->lineEdit_workCenter->setReadOnly(1);
        ui->lineEdit_StationCode->setReadOnly(1);
        ui->lineEdit_TestVersion->setReadOnly(1);
        ui->lineEdit_make_address->setReadOnly(1);

        //第二页
        ui->pushButton_input->setEnabled(0);
        ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setReadOnly(1);
        ui->lineEdit_WT_IS_NEED_LINKMES->setReadOnly(1);
        ui->lineEdit_WT_TEST_LOG_PATH->setReadOnly(1);
        ui->lineEdit_WT_DUT_START_NUM->setReadOnly(1);
        ui->lineEdit_WT_IP_ADDRESS->setReadOnly(1);
        ui->lineEdit_PopUpFunction->setReadOnly(1);
        ui->lineEdit_PopUpEnable->setReadOnly(1);
        ui->checkBox_Debug_log->setEnabled(0);
    }
    QString RunFrameNcFile = "CVTE_MES.ini";
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        //Ncfile.readAll();
        qDebug() <<Ncfile.pos();
        QString strtemp;
        QTextStream NctextStream(&Ncfile);

        //修改项
        QString IP = "IP";
        QString Port = "Port";
        QString ProdUrl = "ProdUrl";
        QString SysUrl = "SysUrl";
        QString TokenName = "TokenName";
        QString UserName = "UserName";
        QString PassWord = "PassWord";
        QString CauseNo = "CauseNo";
        QString WorkCenter = "WorkCenter";
        QString WksNo = "WksNo";
        QString TestFrameidNo = "TestFrameidNo";
        QString WorkerNo = "WorkerNo";
        QString KeyInfo = "KeyInfo";
        QString AutoTestVersion = "AutoTestVersion";
        QString TestItem = "TestItem";
        QString StationCode = "StationCode";
        QString NgCount = "NgCount";

        //QString name = " ";
        QString Alltemp;
        while(!NctextStream.atEnd())
        {
            qDebug() <<NctextStream.pos();
            strtemp = NctextStream.readLine();
            /*if(strtemp.mid(0, IP.length()) == IP)
            {
                 ui->lineEdit_IP->setText(strtemp.split('=').at(1));
            }
            else */if(strtemp.mid(0,Port.length()) == Port)
            {
                ui->lineEdit_Port->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,ProdUrl.length()) == ProdUrl)
            {
                ui->lineEdit_make_address->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,SysUrl.length()) == SysUrl)
            {
                ui->lineEdit_OS_address->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,UserName.length()) == UserName)
            {
                ui->lineEdit_User_name->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,PassWord.length()) == PassWord)
            {
                ui->lineEdit_passwd->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,CauseNo.length()) == CauseNo)
            {
                ui->lineEdit_causeNo->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,WorkCenter.length()) == WorkCenter)
            {
                ui->lineEdit_workCenter->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,WksNo.length()) == WksNo)
            {
                ui->lineEdit_WksNo->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,TestFrameidNo.length()) == TestFrameidNo)
            {
                ui->lineEdit_TestItem->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,WorkerNo.length()) == WorkerNo)
            {
                ui->lineEdit_WorkerNo->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,AutoTestVersion.length()) == AutoTestVersion)
            {
                ui->lineEdit_TestVersion->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,StationCode.length()) == StationCode)
            {
                ui->lineEdit_StationCode->setText(strtemp.split('=').at(1));
            }
            else if(strtemp.mid(0,NgCount.length()) == NgCount)
            {
                ui->lineEdit_NgCount->setText(strtemp.split('=').at(1));
            }        
        }
        Ncfile.close();
    }
    //展示 CVTE_MES.ini
    /*ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));
    ui->lineEdit_IP->setText(openfile_display("CVTE_MES.ini", "IP"));*/
    //展示 WT_DUT_MIMO
    ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setText(openfile_display("WT_DUT_MIMO.txt", "WT_AUTO_TEST_WHEN_DUT_READY"));
    ui->lineEdit_WT_IS_NEED_LINKMES->setText(openfile_display("WT_DUT_MIMO.txt", "WT_IS_NEED_LINKMES"));
    ui->lineEdit_WT_TEST_LOG_PATH->setText(openfile_display("WT_DUT_MIMO.txt", "WT_TEST_LOG_PATH"));
    //展示 WT_TESTER
    ui->lineEdit_WT_IP_ADDRESS->setText(openfile_display("WT_TESTER.txt", "WT_IP_ADDRESS"));
    ui->lineEdit_WT_DUT_START_NUM->setText(openfile_display("WT_TESTER.txt", "WT_DUT_START_NUM"));
    //展示 advance.ini
    ui->lineEdit_PopUpEnable->setText(openfile_display("advance.ini", "PopUpEnable"));
    ui->lineEdit_PopUpFunction->setText(openfile_display("advance.ini", "PopUpFunction"));
    //展示 debug.ini
    if('1' == openfile_display("debug.ini", "print_send")
            && '1' == openfile_display("debug.ini", "print_receive")
            &&'1' == openfile_display("debug.ini", "print_cableloss"))
    {
        ui->checkBox_Debug_log->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        ui->checkBox_Debug_log->setCheckState(Qt::CheckState::Unchecked);
    }
    //提示信息
    //ui->lineEdit_PopUpFunction->setPlaceholderText(openfile_display("advance.ini", "PopUpFunction"));
}
#endif


/**************************************************************************
**
** NAME     on_pushButton_set_clicked
**
** PARAMETERS:  void
**
** RETURNS:
**
** DESCRIPTION  设置基础参数.
**
** NOTES:       None.
**************************************************************************/
void factory_set::on_pushButton_set_clicked()
{
#if 1
    QString RunFrameNcFile = "CVTE_MES.ini";
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        //Ncfile.readAll();
        qDebug() <<Ncfile.pos();
        QString strtemp;
        QTextStream NctextStream(&Ncfile);

        //修改项
        QString IP = "IP";
        QString Port = "Port";
        QString ProdUrl = "ProdUrl";
        QString SysUrl = "SysUrl";
        QString TokenName = "TokenName";
        QString UserName = "UserName";
        QString PassWord = "PassWord";
        QString CauseNo = "CauseNo";
        QString WorkCenter = "WorkCenter";
        QString WksNo = "WksNo";
        QString TestFrameidNo = "TestFrameidNo";
        QString WorkerNo = "WorkerNo";
        QString KeyInfo = "KeyInfo";
        QString AutoTestVersion = "AutoTestVersion";
        QString TestItem = "TestItem";
        QString StationCode = "StationCode";
        QString NgCount = "NgCount";

        QString Alltemp;
        while(!NctextStream.atEnd())
        {
            //qDebug() <<NctextStream.pos();
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, IP.length()) == IP)
            {
                Alltemp += IP + "=" + ui->lineEdit_IP->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,Port.length()) == Port)
            {
                Alltemp += Port + "=" + ui->lineEdit_Port->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,ProdUrl.length()) == ProdUrl)
            {
                Alltemp += ProdUrl + "=" + ui->lineEdit_make_address->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,SysUrl.length()) == SysUrl)
            {
                Alltemp += SysUrl + "=" + ui->lineEdit_OS_address->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,UserName.length()) == UserName)
            {
                Alltemp += UserName + "=" + ui->lineEdit_User_name->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,PassWord.length()) == PassWord)
            {
                Alltemp += PassWord + "=" + ui->lineEdit_passwd->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,CauseNo.length()) == CauseNo)
            {
                Alltemp += CauseNo + "=" + ui->lineEdit_causeNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WorkCenter.length()) == WorkCenter)
            {
                Alltemp += WorkCenter + "=" + ui->lineEdit_workCenter->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WksNo.length()) == WksNo)
            {
                Alltemp += WksNo + "=" + ui->lineEdit_WksNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,TestFrameidNo.length()) == TestFrameidNo)
            {
                Alltemp += TestFrameidNo + "=" + ui->lineEdit_TestItem->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WorkerNo.length()) == WorkerNo)
            {
                Alltemp += WorkerNo + "=" + ui->lineEdit_WorkerNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,AutoTestVersion.length()) == AutoTestVersion)
            {
                Alltemp += AutoTestVersion + "=" + ui->lineEdit_TestVersion->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,StationCode.length()) == StationCode)
            {
                Alltemp += StationCode + "=" + ui->lineEdit_StationCode->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,NgCount.length()) == NgCount)
            {
                Alltemp += NgCount + "=" + ui->lineEdit_NgCount->text();
                Alltemp += QString('\n');
            }
            else
            {
                Alltemp += strtemp;
                Alltemp += QString('\n');

            }

        }
        Ncfile.close();
        Ncfile.open(QIODevice::WriteOnly);
        QTextStream in(&Ncfile);
        in <<Alltemp;
        Ncfile.close();

        /*if(ui->lineEdit_IP->isModified())
        {
            qDebug() << "hello world !!!!!!!!!!!!!!!!!!!!!!";
        }
        else
        {
            qDebug() << "hello world  #####################";
        }*/


    }
#endif
}

/**************************************************************************
**
** NAME     openfile_set_debug
**
** PARAMETERS:  QString filename, bool check_box_sta
**
** RETURNS:
**
** DESCRIPTION  设置debug.int文件信息.
**
** NOTES:       None.
**************************************************************************/
void factory_set::openfile_set_debug(QString filename, bool check_box_sta)
{
    QString sta = "0";
    if(check_box_sta)
    {
        sta = "1";
    }
    QString RunFrameNcFile = filename;
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);
        //展示项
        QString temp;
        QString print_send = "print_send";
        QString print_receive = "print_receive";
        QString print_cableloss = "print_cableloss";
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, print_send.length()) == print_send)
            {
                temp += temp+ print_send + '=' + sta;
                temp += QString('\n');
            }
            else if(strtemp.mid(0, print_receive.length()) == print_receive)
            {
                temp += temp+ print_receive + '=' + sta;
                temp += QString('\n');
            }
            else if(strtemp.mid(0, print_cableloss.length()) == print_cableloss)
            {
                temp += temp+ print_cableloss + '=' + sta;
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
        qDebug() << temp;
        Ncfile.close();
    }
}

/**************************************************************************
**
** NAME     on_pushButton_input_clicked
**
** PARAMETERS:  void
**
** RETURNS:
**
** DESCRIPTION  按钮设置第二页的相关参数.
**
** NOTES:       None.
**************************************************************************/
void factory_set::on_pushButton_input_clicked()
{
    //WT_DUT_MIMO
    openfile_set_show("WT_DUT_MIMO.txt", "WT_AUTO_TEST_WHEN_DUT_READY", ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY);
    openfile_set_show("WT_DUT_MIMO.txt", "WT_IS_NEED_LINKMES", ui->lineEdit_WT_IS_NEED_LINKMES);
    openfile_set_show("WT_DUT_MIMO.txt", "WT_TEST_LOG_PATH", ui->lineEdit_WT_TEST_LOG_PATH);

    //WT_TESTER
    openfile_set_show("WT_TESTER.txt", "WT_IP_ADDRESS", ui->lineEdit_WT_IP_ADDRESS);
    openfile_set_show("WT_TESTER.txt", "WT_DUT_START_NUM", ui->lineEdit_WT_DUT_START_NUM);

    //advance.ini
    openfile_set_show("advance.ini", "PopUpEnable", ui->lineEdit_PopUpEnable);
    openfile_set_show("advance.ini", "PopUpFunction", ui->lineEdit_PopUpFunction);

    //debug.ini
    openfile_set_debug("debug.ini", ui->checkBox_Debug_log->checkState());

}
