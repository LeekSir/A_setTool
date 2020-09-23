#include "factory_set.h"
#include "ui_factory_set.h"
#include <QChar>
#include <QLabel>


factory_set::factory_set(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::factory_set)
{
    ui->setupUi(this);
#if 0
    //测试
    filename_CVTE_MES = "CVTE_MES.ini";//"../CVTE_MES.ini";
    filename_WT_DUT_MIMO = "WT_DUT_MIMO.txt";//"../WT_SETUP/WT_DUT_MIMO.txt";
    filename_WT_TESTER = "WT_TESTER.txt";//"../WT_SETUP/WT_TESTER.txt";
    filename_advance = "advance.ini";//"../advance.ini";
    filename_debug = "debug.ini";//"../debug.ini";
    filename_SoftVer = "CVTE_SoftVer_Readme.txt";//"../CVTE_SoftVer_Readme.txt";
    filename_WT_ATTEN_DUT = "WT_ATTEN_DUT_1.txt";//"../WT_SETUP/WT_ATTEN_DUT_1.txt";
    filename_WT_WRITE_EFUSE = "WT_FLOW.txt";//"../WT_SETUP/WT_FLOW.txt";
#else
    //发布
    filename_CVTE_MES = "../../CVTE_MES.ini";
    filename_WT_DUT_MIMO = "../../WT_SETUP/WT_DUT_MIMO.txt";
    filename_WT_TESTER = "../../WT_SETUP/WT_TESTER.txt";
    filename_advance = "../../advance.ini";
    filename_debug = "../../debug.ini";
    filename_SoftVer = "../../CVTE_SoftVer_Readme.txt";
    filename_WT_ATTEN_DUT = "../../WT_SETUP/WT_ATTEN_DUT_1.txt";
    filename_WT_WRITE_EFUSE = "../../WT_SETUP/WT_FLOW.txt";
#endif
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
** NAME     openfile_wefuse_display
**
** PARAMETERS:  QString box_id
**
** RETURNS: bool
**
** DESCRIPTION  查看是否需要 写efuse.
**
** NOTES:       None.
**************************************************************************/
bool factory_set::openfile_wefuse_display(QString box_id)
{
    QString RunFrameNcFile = filename_WT_WRITE_EFUSE;
    QFile Ncfile(RunFrameNcFile);
    if(!Ncfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "ERRERRERRERREERRR";
        return NULL;
    }

    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);
        //展示项
        QString temp;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            //if(strtemp.split("//").at(0).simplified() == box_id)
            if(strtemp.mid(0, box_id.length()) == box_id)
            {
                //if()
                qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!";
                Ncfile.close();
                return true;
            }
        }
        Ncfile.close();
    }

    return false;

}

/**************************************************************************
**
** NAME     openfile_set_show
**
** PARAMETERS:  (QString filename, QString line_id, QLineEdit* wirte_show)
**
** RETURNS:
**
** DESCRIPTION  设置第二页中的相关参数.
**
** NOTES:       None.
**************************************************************************/
void factory_set::openfile_set_wefuse(QString box_id)
{
    QString RunFrameNcFile = filename_WT_WRITE_EFUSE;
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
            if(strtemp.mid(0, box_id.length()) == box_id)
            {
                if(ui->checkBox_WT_WRITE_EFUSE->checkState())
                {
                    qDebug() << "222222222222222222222";
                    temp += strtemp;
                    temp += QString('\n');
                }
                else
                {
                    temp += "//" + strtemp;
                    temp += QString('\n');
                }
            }
            else if(strtemp.mid(2, box_id.length()) == box_id)
            {
                if(!ui->checkBox_WT_WRITE_EFUSE->checkState())
                {
                    qDebug() << "3333333333333333333333";
                    temp += strtemp;
                    temp += QString('\n');
                }
                else
                {
                    qDebug() << strtemp.mid(2, strtemp.length()-2);
                    temp += strtemp.mid(2, strtemp.length()-2);
                    temp += QString('\n');
                }
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
** NAME     display_user_login
**
** PARAMETERS:  void
**
** RETURNS:
**
** DESCRIPTION  显示MES连接信息，并显示在界面上
**
** NOTES:       None.
**************************************************************************/
void factory_set::display_user_login()
{
    QImage *USER = new QImage;
    qDebug() << "helloworld##############";
    if(this->Usr_Type)
    {
        USER->load(":/image/USER.png");
        ui->label_user->setPixmap(QPixmap::fromImage(*USER));
    }
}

/**************************************************************************
**
** NAME     display_connect_mes
**
** PARAMETERS:  void
**
** RETURNS:
**
** DESCRIPTION  显示MES连接信息，并显示在界面上
**
** NOTES:       None.
**************************************************************************/
void factory_set::display_connect_mes()
{
    QImage *MES = new QImage;
    QString MES_STA = openfile_display(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES");
    if(this->Usr_Type)
    {
        //USER->load(":/image/USER.png");
        //ui->label_user->setPixmap(QPixmap::fromImage(*USER));
        return;
    }
    if("1" == MES_STA)
    {
        qDebug() << "################################";
        MES->load(":/image/MES_CONNECT.png");
        ui->label_MES_Status->setPixmap(QPixmap::fromImage(*MES));
    }
    else// if("0" == MES_STA)
    {
        qDebug() << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        MES->load(":/image/MES_DISCONNECT.png");
        ui->label_MES_Status->setPixmap(QPixmap::fromImage(*MES));
    }
#if 0
    else //if(NULL == MES_STA)
    {
        MES->load(":/image/file_no_find.png");
        ui->label_MES_Status->setPixmap(QPixmap::fromImage(*MES));
    }
#endif


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

        //ui->lineEdit_PassWord->setReadOnly(1);
        //ui->lineEdit_NgCount->setReadOnly(1);
        //ui->lineEdit_CauseNo->setReadOnly(1);
        //ui->lineEdit_TestItem->setReadOnly(1);
        //ui->lineEdit_WorkerNo->setReadOnly(1);
        //ui->lineEdit_UserName->setReadOnly(1);
        //ui->lineEdit_SysUrl->setReadOnly(1);
        ui->lineEdit_WorkCenter->setReadOnly(1);
        //ui->lineEdit_StationCode->setReadOnly(1);
        ui->lineEdit_AutoTestVersion->setReadOnly(1);
        //ui->lineEdit_ProdUrl->setReadOnly(1);

        //new
        ui->lineEdit_MoLotNo->setReadOnly(1);
        ui->lineEdit_PartNo->setReadOnly(1);
        ui->lineEdit_ModuleType->setReadOnly(1);

        //第二页
        ui->pushButton_input->setEnabled(0);
        ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setReadOnly(1);
        ui->lineEdit_WT_TEST_LOG_PATH->setReadOnly(1);
        ui->lineEdit_WT_DUT_START_NUM->setReadOnly(1);
        ui->lineEdit_WT_IP_ADDRESS->setReadOnly(1);
        //ui->lineEdit_PopUpFunction->setReadOnly(1);
        //ui->lineEdit_PopUpEnable->setReadOnly(1);
        ui->checkBox_Debug_log->setEnabled(0);
        ui->checkBox_WT_WRITE_EFUSE->setEnabled(0);

        //第三页
        ui->pushButton_set_LineLoss->setEnabled(0);
        //ui->comboBox_WT_ATTEN_DUT_Select->setEnabled(0);

        //BT
        ui->doubleSpinBox_WT_FIXED_ATTEN_BT->setReadOnly(1);

        //2.4G
        ui->doubleSpinBox_CH1_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH3_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH7_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH11_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH13_Port1->setReadOnly(1);

        ui->doubleSpinBox_CH1_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH3_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH7_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH11_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH13_Port2->setReadOnly(1);
        //5G
        ui->doubleSpinBox_CH36_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH48_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH52_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH64_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH100_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH116_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH120_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH136_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH140_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH157_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH161_Port1->setReadOnly(1);
        ui->doubleSpinBox_CH165_Port1->setReadOnly(1);

        ui->doubleSpinBox_CH36_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH48_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH52_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH64_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH100_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH116_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH120_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH136_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH140_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH157_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH161_Port2->setReadOnly(1);
        ui->doubleSpinBox_CH165_Port2->setReadOnly(1);

    }
    else
    {
        //this->setWindowOpacity(0.9);
        //this->setObjectName("dialog");
        //this->setStyleSheet("QDialog#dialog{border-image:url(me.png)}");
    }

    /*if(!(ui->lineEdit_AutoTestVersion->text() == openfile_display(filename_CVTE_MES, "AutoTestVersion")))
    {
       QMessageBox::critical(0 , "警告信息" , "软件版本号不一致，请核对！",
                             QMessageBox::Ok | QMessageBox::Default , QMessageBox::Cancel
                             | QMessageBox::Escape , 	0 );
    }*/

    ui->lineEdit_AutoTestVersion->setReadOnly(1);
    ui->lineEdit_WT_IS_NEED_LINKMES->setReadOnly(1);
    //线损不可以修改项
    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN0->setReadOnly(1);
    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN1->setReadOnly(1);
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN0->setReadOnly(1);
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN1->setReadOnly(1);
    QString filename = "CVTE_MES.ini";
    //展示 CVTE_MES.ini
    ui->lineEdit_IP->setText(openfile_display(filename_CVTE_MES, "IP"));
    ui->lineEdit_Port->setText(openfile_display(filename_CVTE_MES, "Port"));
    //ui->lineEdit_ProdUrl->setText(openfile_display(filename_CVTE_MES, "ProdUrl"));
    //ui->lineEdit_SysUrl->setText(openfile_display(filename_CVTE_MES, "SysUrl"));
    //ui->lineEdit_UserName->setText(openfile_display(filename_CVTE_MES, "UserName"));
    //ui->lineEdit_PassWord->setText(openfile_display(filename_CVTE_MES, "PassWord"));
    //ui->lineEdit_CauseNo->setText(openfile_display(filename_CVTE_MES, "CauseNo"));
    ui->lineEdit_WorkCenter->setText(openfile_display(filename_CVTE_MES, "WorkCenter"));
    ui->lineEdit_WksNo->setText(openfile_display(filename_CVTE_MES, "WksNo"));
    ui->lineEdit_TestFrameidNo->setText(openfile_display(filename_CVTE_MES, "TestFrameidNo"));
    ui->lineEdit_WorkerNo->setText(openfile_display(filename_CVTE_MES, "WorkerNo"));
    ui->lineEdit_AutoTestVersion->setText(openfile_display(filename_CVTE_MES, "AutoTestVersion"));
    //ui->lineEdit_TestItem->setText(openfile_display(filename_CVTE_MES, "TestItem"));
    //ui->lineEdit_StationCode->setText(openfile_display(filename_CVTE_MES, "StationCode"));
    //ui->lineEdit_NgCount->setText(openfile_display(filename_CVTE_MES, "NgCount"));
    ui->lineEdit_MoLotNo->setText(openfile_display(filename_CVTE_MES, "MoLotNo"));
    ui->lineEdit_PartNo->setText(openfile_display(filename_CVTE_MES, "PartNo"));
    ui->lineEdit_ModuleType->setText(openfile_display(filename_CVTE_MES, "ModuleType"));


    //增加显示MES连接与否，主要是配置产测软件
    QFile::remove("../../userlogo.jpg");

    QString MoudleType = openfile_display(filename_CVTE_MES, "ModuleType");
    QString WT_IS_NEED_LINKMES =openfile_display(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES");
    QString filePath = "../image";
    QString curPath = QDir::currentPath();
    QDir *dir=new QDir(filePath);
    QStringList filter;

    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(int i = 0;i<fileInfo->count(); i++)
    {
        QString temp = fileInfo->at(i).fileName();
        //qDebug()<<fileInfo->at(i).filePath() << curPath << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
        if(MoudleType + '.' + WT_IS_NEED_LINKMES + ".jpg" == temp)
        {
            qDebug() << "????????????????????????????" << QFile::copy("../image/" + temp,"../../userlogo.jpg");//<< QFile::copy(curPath + "/image/" + temp,curPath + "/userlogo.jpg");
        }

    }


    //展示 CVTE_SoftVer_Readme
    ui->lineEdit_AutoTestVersion->setText(openfile_display(filename_SoftVer, "AutoTestVersion"));


    //展示 WT_DUT_MIMO
    ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setText(openfile_display(filename_WT_DUT_MIMO, "WT_AUTO_TEST_WHEN_DUT_READY"));
    ui->lineEdit_WT_IS_NEED_LINKMES->setText(openfile_display(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES"));
    ui->lineEdit_WT_TEST_LOG_PATH->setText(openfile_display(filename_WT_DUT_MIMO, "WT_TEST_LOG_PATH"));
    //展示 WT_TESTER
    ui->lineEdit_WT_IP_ADDRESS->setText(openfile_display(filename_WT_TESTER, "WT_IP_ADDRESS"));
    ui->lineEdit_WT_DUT_START_NUM->setText(openfile_display(filename_WT_TESTER, "WT_DUT_START_NUM"));
    //展示 advance.ini
    //ui->lineEdit_PopUpEnable->setText(openfile_display(filename_advance, "PopUpEnable"));
    //ui->lineEdit_PopUpFunction->setText(openfile_display(filename_advance, "PopUpFunction"));
    //展示 debug.ini
    if('1' == openfile_display(filename_debug, "print_send")
            && '1' == openfile_display(filename_debug, "print_receive")
            &&'1' == openfile_display(filename_debug, "print_cableloss"))
    {
        ui->checkBox_Debug_log->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        ui->checkBox_Debug_log->setCheckState(Qt::CheckState::Unchecked);
    }

    //展示 WT_FLOW
    if(openfile_wefuse_display("WT_WRITE_EFUSE\t\t"))
    {
        ui->checkBox_WT_WRITE_EFUSE->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        qDebug() << "111111111111111111";
        ui->checkBox_WT_WRITE_EFUSE->setCheckState(Qt::CheckState::Unchecked);
    }

    //展示 WT_ATTEN_DUT 线损参数
    on_pushButton_display_LineLoss_clicked();
    //提示信息
    //ui->lineEdit_PopUpFunction->setPlaceholderText(openfile_display("advance.ini", "PopUpFunction"));
    //
    display_connect_mes();
    display_user_login();





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

    QString RunFrameNcFile = filename_CVTE_MES;
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

        //new
        QString MoLotNo = "MoLotNo";
        QString PartNo = "StationCode";
        QString ModuleType = "NgCount";

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
            #if 0
            else if(strtemp.mid(0,ProdUrl.length()) == ProdUrl)
            {
                Alltemp += ProdUrl + "=" + ui->lineEdit_ProdUrl->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,SysUrl.length()) == SysUrl)
            {
                Alltemp += SysUrl + "=" + ui->lineEdit_SysUrl->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,UserName.length()) == UserName)
            {
                Alltemp += UserName + "=" + ui->lineEdit_UserName->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,PassWord.length()) == PassWord)
            {
                Alltemp += PassWord + "=" + ui->lineEdit_PassWord->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,CauseNo.length()) == CauseNo)
            {
                Alltemp += CauseNo + "=" + ui->lineEdit_CauseNo->text();
                Alltemp += QString('\n');
            }
            #endif
            else if(strtemp.mid(0,WorkCenter.length()) == WorkCenter)
            {
                Alltemp += WorkCenter + "=" + ui->lineEdit_WorkCenter->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WksNo.length()) == WksNo)
            {
                Alltemp += WksNo + "=" + ui->lineEdit_WksNo->text();
                Alltemp += QString('\n');
            }
            /*
            else if(strtemp.mid(0,TestFrameidNo.length()) == TestFrameidNo)
            {
                Alltemp += TestFrameidNo + "=" + ui->lineEdit_TestItem->text();
                Alltemp += QString('\n');
            }*/
            else if(strtemp.mid(0,WorkerNo.length()) == WorkerNo)
            {
                Alltemp += WorkerNo + "=" + ui->lineEdit_WorkerNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,AutoTestVersion.length()) == AutoTestVersion)
            {
                Alltemp += AutoTestVersion + "=" + ui->lineEdit_AutoTestVersion->text();
                Alltemp += QString('\n');
            }
            /*
            else if(strtemp.mid(0,StationCode.length()) == StationCode)
            {
                Alltemp += StationCode + "=" + ui->lineEdit_StationCode->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,NgCount.length()) == NgCount)
            {
                Alltemp += NgCount + "=" + ui->lineEdit_NgCount->text();
                Alltemp += QString('\n');
            }*/
            //new
            else if(strtemp.mid(0,UserName.length()) == MoLotNo)
            {
                Alltemp += UserName + "=" + ui->lineEdit_MoLotNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,PassWord.length()) == PartNo)
            {
                Alltemp += PassWord + "=" + ui->lineEdit_PartNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,CauseNo.length()) == ModuleType)
            {
                Alltemp += CauseNo + "=" + ui->lineEdit_ModuleType->text();
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
    Sleep(3000);
    about_info("提示", "参数配置成功！");

    display();
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
                temp += print_send + '=' + sta;
                temp += QString('\n');
            }
            else if(strtemp.mid(0, print_receive.length()) == print_receive)
            {
                temp += print_receive + '=' + sta;
                temp += QString('\n');
            }
            else if(strtemp.mid(0, print_cableloss.length()) == print_cableloss)
            {
                temp += print_cableloss + '=' + sta;
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

//信息提示窗口
void factory_set::about_info(QString dlgTitle, QString strInfo)
{
    QMessageBox::about(this, dlgTitle, strInfo);
}

/**************************************************************************
**
** NAME     openfile_set_show
**
** PARAMETERS:  (QString filename, QString line_id, QLineEdit* wirte_show)
**
** RETURNS:
**
** DESCRIPTION  设置第二页中的相关参数.
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
                if(strtemp.indexOf("//", 0) != -1)
                {
                    temp += line_id + '=' + wirte_show->text() + "                          //" + strtemp.split("//").at(1);
                    temp += QString('\n');
                }
                else
                {
                    temp += line_id + '=' + wirte_show->text();// + "                          //" + strtemp.split("//").at(1);
                    temp += QString('\n');
                }

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
    openfile_set_show(filename_WT_DUT_MIMO, "WT_AUTO_TEST_WHEN_DUT_READY", ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY);
    openfile_set_show(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES", ui->lineEdit_WT_IS_NEED_LINKMES);
    openfile_set_show(filename_WT_DUT_MIMO, "WT_TEST_LOG_PATH", ui->lineEdit_WT_TEST_LOG_PATH);


    //WT_TESTER
    openfile_set_show(filename_WT_TESTER, "WT_IP_ADDRESS", ui->lineEdit_WT_IP_ADDRESS);
    openfile_set_show(filename_WT_TESTER, "WT_DUT_START_NUM", ui->lineEdit_WT_DUT_START_NUM);

    //advance.ini
    //openfile_set_show(file_advance, "PopUpEnable", ui->lineEdit_PopUpEnable);
    //openfile_set_show(file_advance, "PopUpFunction", ui->lineEdit_PopUpFunction);

    //debug.ini
    openfile_set_debug(filename_debug, ui->checkBox_Debug_log->checkState());

    //WT_FLOW 写EFUSE
    openfile_set_wefuse("WT_WRITE_EFUSE\t\t");

    Sleep(3000);
    about_info("提示", "参数配置成功！");

    display();

}

//void

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
QString factory_set::openfile_display_lineloss(QString filename, QString show, int port_num)
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
            //temp = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0);
            if(strtemp.mid(0, temp.length()) == temp)
            {
                 qDebug() << strtemp;
                 temp = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(port_num);// + "#" + strtemp.split(' ').at(2).simplified();
                 //QStringList list = strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts);
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
** DESCRIPTION  设置第二页中的相关参数.
**
** NOTES:       None.
**************************************************************************/
void factory_set::openfile_set_LineLoss(QString Box_name, QDoubleSpinBox* SpinBox, int port_num)
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
             qDebug() << "!!!!!!!!!!!!!!!" << strtemp.mid(0, 2);

            if(strtemp.mid(0, 2) == "CH")
            {
                qDebug() << "!!!!!!!!!!!!!!!";
                list = strtemp.split("//").at(0).split(QRegExp("\\s+"), QString::SkipEmptyParts);
            }
            else
            {
                list = hello.split(" ");
            }
            if(list.at(0) == Box_name)
            {
                QString sp = QString::number(SpinBox->value(),'f',1);
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
}

/**************************************************************************
**
** NAME     openfile_set_show
**
** PARAMETERS:  (QString filename, QString line_id, QLineEdit* wirte_show)
**
** RETURNS:
**
** DESCRIPTION  设置第二页中的相关参数.
**
** NOTES:       None.
**************************************************************************/
void factory_set::openfile_set_BT_show(QString filename, QString Box_id, QDoubleSpinBox* SpinBox)
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
            if(strtemp.mid(0, Box_id.length()) == Box_id)
            {
                qDebug() << strtemp;
                temp += Box_id + "\t=\t" + QString::number(SpinBox->value(),'f',1);
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

void factory_set::on_pushButton_set_LineLoss_clicked()
{
    ui->pushButton_set_LineLoss->setChecked(true);
    filename_WT_ATTEN_DUT = "../../WT_SETUP/WT_ATTEN_" + ui->comboBox_WT_ATTEN_DUT_Select->currentText() + ".txt";

    int port_num = 1;

    openfile_set_BT_show(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_BT", ui->doubleSpinBox_WT_FIXED_ATTEN_BT);

    //端口号为1，2.4G的值
    openfile_set_LineLoss("CH1", ui->doubleSpinBox_CH1_Port1, port_num);
    openfile_set_LineLoss("CH3", ui->doubleSpinBox_CH3_Port1, port_num);
    openfile_set_LineLoss("CH7", ui->doubleSpinBox_CH7_Port1, port_num);
    openfile_set_LineLoss("CH11", ui->doubleSpinBox_CH11_Port1, port_num);
    openfile_set_LineLoss("CH13", ui->doubleSpinBox_CH13_Port1, port_num);
    //端口号为1，5G的值
    openfile_set_LineLoss("CH36", ui->doubleSpinBox_CH36_Port1, port_num);
    openfile_set_LineLoss("CH48", ui->doubleSpinBox_CH48_Port1, port_num);
    openfile_set_LineLoss("CH52", ui->doubleSpinBox_CH52_Port1, port_num);
    openfile_set_LineLoss("CH64", ui->doubleSpinBox_CH64_Port1, port_num);
    openfile_set_LineLoss("CH100", ui->doubleSpinBox_CH100_Port1, port_num);
    openfile_set_LineLoss("CH116", ui->doubleSpinBox_CH116_Port1, port_num);
    openfile_set_LineLoss("CH120", ui->doubleSpinBox_CH120_Port1, port_num);
    openfile_set_LineLoss("CH136", ui->doubleSpinBox_CH136_Port1, port_num);
    openfile_set_LineLoss("CH140", ui->doubleSpinBox_CH140_Port1, port_num);
    openfile_set_LineLoss("CH157", ui->doubleSpinBox_CH157_Port1, port_num);
    openfile_set_LineLoss("CH161", ui->doubleSpinBox_CH161_Port1, port_num);
    openfile_set_LineLoss("CH165", ui->doubleSpinBox_CH165_Port1, port_num);


    port_num = 2;
    //端口号为2，2.4G的值
    openfile_set_LineLoss("CH1", ui->doubleSpinBox_CH1_Port2, port_num);
    openfile_set_LineLoss("CH3", ui->doubleSpinBox_CH3_Port2, port_num);
    openfile_set_LineLoss("CH7", ui->doubleSpinBox_CH7_Port2, port_num);
    openfile_set_LineLoss("CH11", ui->doubleSpinBox_CH11_Port2, port_num);
    openfile_set_LineLoss("CH13", ui->doubleSpinBox_CH13_Port2, port_num);
    //端口号为2，5G的值
    openfile_set_LineLoss("CH36", ui->doubleSpinBox_CH36_Port2, port_num);
    openfile_set_LineLoss("CH48", ui->doubleSpinBox_CH48_Port2, port_num);
    openfile_set_LineLoss("CH52", ui->doubleSpinBox_CH52_Port2, port_num);
    openfile_set_LineLoss("CH64", ui->doubleSpinBox_CH64_Port2, port_num);
    openfile_set_LineLoss("CH100", ui->doubleSpinBox_CH100_Port2, port_num);
    openfile_set_LineLoss("CH116", ui->doubleSpinBox_CH116_Port2, port_num);
    openfile_set_LineLoss("CH120", ui->doubleSpinBox_CH120_Port2, port_num);
    openfile_set_LineLoss("CH136", ui->doubleSpinBox_CH136_Port2, port_num);
    openfile_set_LineLoss("CH140", ui->doubleSpinBox_CH140_Port2, port_num);
    openfile_set_LineLoss("CH157", ui->doubleSpinBox_CH157_Port2, port_num);
    openfile_set_LineLoss("CH161", ui->doubleSpinBox_CH161_Port2, port_num);
    openfile_set_LineLoss("CH165", ui->doubleSpinBox_CH165_Port2, port_num);
    ui->pushButton_set_LineLoss->setChecked(true);
    Sleep(3000);
    about_info("提示", "参数配置成功！");

    on_pushButton_display_LineLoss_clicked();
    ui->pushButton_set_LineLoss->setChecked(false);
}





void factory_set::on_pushButton_display_LineLoss_clicked()
{
    //展示 WT_ATTEN_DUT 线损参数
    filename_WT_ATTEN_DUT = "../../WT_SETUP/WT_ATTEN_" + ui->comboBox_WT_ATTEN_DUT_Select->currentText() + ".txt";


    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN0->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_2_4_CHAIN0"));
    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN1->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_2_4_CHAIN1"));
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN0->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_5_CHAIN0"));
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN1->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_5_CHAIN1"));

    //BT
    ui->doubleSpinBox_WT_FIXED_ATTEN_BT->setValue(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_BT").toDouble());


    //openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH1");
    int port_num = 1;
    //端口号为1，2.4G的值
    ui->doubleSpinBox_CH1_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH1", port_num).toDouble());
    ui->doubleSpinBox_CH3_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH3", port_num).toDouble());
    ui->doubleSpinBox_CH7_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH7", port_num).toDouble());
    ui->doubleSpinBox_CH11_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH11", port_num).toDouble());
    ui->doubleSpinBox_CH13_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH13", port_num).toDouble());
    //端口号为1，5G的值
    ui->doubleSpinBox_CH36_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH36", port_num).toDouble());
    ui->doubleSpinBox_CH48_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH48", port_num).toDouble());
    ui->doubleSpinBox_CH52_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH52", port_num).toDouble());
    ui->doubleSpinBox_CH64_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH64", port_num).toDouble());
    ui->doubleSpinBox_CH100_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH100", port_num).toDouble());
    ui->doubleSpinBox_CH116_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH116", port_num).toDouble());
    ui->doubleSpinBox_CH120_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH120", port_num).toDouble());
    ui->doubleSpinBox_CH136_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH136", port_num).toDouble());
    ui->doubleSpinBox_CH140_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH140", port_num).toDouble());
    ui->doubleSpinBox_CH157_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH157", port_num).toDouble());
    ui->doubleSpinBox_CH161_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH161", port_num).toDouble());
    ui->doubleSpinBox_CH165_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH165", port_num).toDouble());

    port_num = 2;
    //端口号为2，2.4G的值
    ui->doubleSpinBox_CH1_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH1", port_num).toDouble());
    ui->doubleSpinBox_CH3_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH3", port_num).toDouble());
    ui->doubleSpinBox_CH7_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH7", port_num).toDouble());
    ui->doubleSpinBox_CH11_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH11", port_num).toDouble());
    ui->doubleSpinBox_CH13_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH13", port_num).toDouble());
    //端口号为2，5G的值
    ui->doubleSpinBox_CH36_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH36", port_num).toDouble());
    ui->doubleSpinBox_CH48_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH48", port_num).toDouble());
    ui->doubleSpinBox_CH52_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH52", port_num).toDouble());
    ui->doubleSpinBox_CH64_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH64", port_num).toDouble());
    ui->doubleSpinBox_CH100_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH100", port_num).toDouble());
    ui->doubleSpinBox_CH116_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH116", port_num).toDouble());
    ui->doubleSpinBox_CH120_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH120", port_num).toDouble());
    ui->doubleSpinBox_CH136_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH136", port_num).toDouble());
    ui->doubleSpinBox_CH140_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH140", port_num).toDouble());
    ui->doubleSpinBox_CH157_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH157", port_num).toDouble());
    ui->doubleSpinBox_CH161_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH161", port_num).toDouble());
    ui->doubleSpinBox_CH165_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH165", port_num).toDouble());


}

void factory_set::on_pushButton_refresh_clicked()
{
   display();
   Sleep(1000);
   about_info("提示", "刷新成功！");
}
