#include "factory_set.h"
#include "ui_factory_set.h"
#include <QChar>
#include <QLabel>
#include <QAxObject>
#include <QProcess>
#include <QDateTime>
#include <QTimer>
#include <Windows.h>
#include <tlhelp32.h>
#include <string.h>
#include "err_qdialog.h"


bool refresh_flag = false;
bool correct = true;
bool correct_flag = false;//是否校准成功
bool mythread_flag;
QString correct_Port_Num;
bool PASS_flag = true;
bool air_link_flag = true;
QString cmd;

QMutex mutex;

QString filename_WT_ATTEN_DUT;

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
    //filename_WT_ATTEN_DUT = "WT_ATTEN_DUT_1.txt";//"../WT_SETUP/WT_ATTEN_DUT_1.txt";
    filename_WT_WRITE_EFUSE = "WT_FLOW.txt";//"../WT_SETUP/WT_FLOW.txt";
    filename_WT_MAC =  "WT_MAC.txt";
    //filename_WT_ATTEN_DUT;//"../WT_SETUP/WT_ATTEN_DUT_1.txt";
#else
    //发布
    filename_CVTE_MES = "../../CVTE_MES.ini";
    filename_WT_DUT_MIMO = "../../WT_SETUP/WT_DUT_MIMO.txt";
    filename_WT_TESTER = "../../WT_SETUP/WT_TESTER.txt";
    filename_advance = "../../advance.ini";
    filename_debug = "../../debug.ini";
    filename_SoftVer = "../../CVTE_SoftVer_Readme.txt";
    //filename_WT_ATTEN_DUT = "../../WT_SETUP/WT_ATTEN_DUT_";
    filename_WT_WRITE_EFUSE = "../../WT_SETUP/WT_FLOW.txt";
    filename_WT_MAC = "../../WT_SETUP/WT_MAC.txt";
#endif
    //display();
    connect(&thread,SIGNAL(mySignal()), this, SLOT(mySlot()));

    //thread.start();
    mythread_flag = false;


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(display_refresh()));


/*
    //托盘初始化
    //托盘
    tray= new QSystemTrayIcon(this);//初始化托盘对象tray
    tray->setIcon(QIcon(QPixmap(":/image/set.jpg")));//设定托盘图标，引号内是自定义的png图片路径
    tray->setToolTip("My helper"); //提示文字
    QString title="APP Message";
    QString text="My helper start up";
    tray->show();//让托盘图标显示在系统托盘上
    tray->showMessage(title,text,QSystemTrayIcon::Information,3000); //最后一个参数为提示时长，默认10000，即10s


    //创建菜单项动作
    QAction *minimizeAction = new QAction("MinWin", this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    QAction *maximizeAction = new QAction("MaxWin", this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
    QAction *restoreAction = new QAction("restore", this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    QAction *quitAction = new QAction("exit", this);

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit())); //关闭应用

    //创建托盘菜单
    trayMenu = new QMenu(this);
    trayMenu->addAction(minimizeAction);
    trayMenu->addAction(maximizeAction);
    trayMenu->addAction(restoreAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);
    tray->setContextMenu(trayMenu);

    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

*/

}

factory_set::~factory_set()
{
    delete ui;
}
//重写关闭事件
void factory_set::closeEvent(QCloseEvent *event)
{
    this->setWindowState(Qt::WindowMinimized);
    //iconActivated(QSystemTrayIcon::MiddleClick);
    event->ignore(); //忽略事件
    /*if(tray->isVisible())
    {
        this->hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }*/

}

/*void factory_set::hideEvent(QHideEvent *event)
{
    if(tray->isVisible())
    {
        this->hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}*/

void factory_set::iconActivated(QSystemTrayIcon::ActivationReason ireason)
{
    switch (ireason)
    {
    case QSystemTrayIcon::Trigger:
        this->showNormal();
        break;
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        break;
    }
}

//kill progress

using namespace std;
/*根据进程名称杀死进程
 *1、根据进程名称找到PID
 *2、根据PID杀死进程
 */
 bool killTaskl(const QString& exe)
{
    //1、根据进程名称找到PID
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return false;
    }

    BOOL    bRet = FALSE;
    DWORD dwPid = -1;
    while (Process32Next(hProcessSnap, &pe32))
    {
        //将WCHAR转成const char*
        int iLn = WideCharToMultiByte (CP_UTF8, 0, const_cast<LPWSTR> (pe32.szExeFile), static_cast<int>(sizeof(pe32.szExeFile)), NULL, 0, NULL, NULL);
        std::string result (iLn, 0);
        WideCharToMultiByte (CP_UTF8, 0, pe32.szExeFile, static_cast<int>(sizeof(pe32.szExeFile)), const_cast<LPSTR> (result.c_str()), iLn, NULL, NULL);
        if (0 == strcmp(exe.toStdString().c_str(), result.c_str ()))
        {
            dwPid = pe32.th32ProcessID;
            bRet = TRUE;
            qDebug()<<"zhaodao";
            break;
        }
    }

    CloseHandle(hProcessSnap);
    qDebug()<<dwPid;
    //2、根据PID杀死进程
    HANDLE hProcess=NULL;
    //打开目标进程
    hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,dwPid);
    if (hProcess==NULL) {
        qDebug()<<"Open Process fAiled ,error:"<<GetLastError();
        return -1;
    }
    //结束目标进程
    DWORD ret=TerminateProcess(hProcess,0);
    if(ret==0) {
        qDebug()<<"kill task faild,error:"<<GetLastError();
        return false;
    }

    return true;
}

//void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file("../log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}



void factory_set::mySlot()
{
    mythread_flag = true;
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
        //qDebug() << "ERRERRERRERREERRR";
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
            if(strtemp.mid(0, box_id.length()) == box_id)
            {
                //qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!";
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
        bool key_flag = false;
        QString ignore_box_id = "//";// + box_id;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.indexOf(box_id) != -1 && strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0) == box_id)
            //if(strtemp.mid(0, box_id.length()) == box_id)
            //if(strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0) == box_id)
            {
                key_flag = true;
                if(ui->checkBox_WT_WRITE_EFUSE->checkState())
                {
                    temp += strtemp;
                    temp += QString('\n');
                }
                else
                {
                    temp += "//" + strtemp;
                    temp += QString('\n');
                }
            }
            //else if(strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0).mid(2, box_id.length()) == box_id)
            //else if(strtemp.mid(2, box_id.length()) == box_id)
            else if(strtemp.indexOf(box_id) != -1 && strtemp.indexOf(box_id) != -1 && strtemp.split(QRegExp("\\s+"), QString::SkipEmptyParts).at(0).mid(0,2) == ignore_box_id)
            {
                key_flag = true;
                if(!ui->checkBox_WT_WRITE_EFUSE->checkState())
                {
                    temp += strtemp;
                    temp += QString('\n');
                }
                else
                {
                    //qDebug() << strtemp.mid(2, strtemp.length()-2);
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
        if(!key_flag)
        {
            if(ui->checkBox_WT_WRITE_EFUSE->checkState())
            {
                temp += box_id + "\t\t //写efuse";
                temp += QString('\n');
            }
            else
            {
                temp += ignore_box_id + box_id + "\t\t //写efuse";
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
    //qDebug() << "helloworld##############";
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
        MES->load(":/image/MES_CONNECT.png");
        ui->label_MES_Status->setPixmap(QPixmap::fromImage(*MES));
    }
    else
    {
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

void factory_set::SetReadOnly(QCheckBox* checkBox, bool readOnly)
{
   checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, readOnly);
   checkBox->setFocusPolicy(readOnly ? Qt::NoFocus : Qt::StrongFocus);
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
    if(this->Usr_Type)
    {
        this->setStyleSheet("#factory_set{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));}");
        //ui->tabWidget->setStyleSheet("#tabWidget{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));}");
    }
    else
    {
        this->setStyleSheet("#factory_set{background-color: rgb(63, 150, 150);}");
    }
    if(!this->Usr_Type)
    {

        //主界面一键恢复按钮，用来恢复setup和rename.bin
        ui->pushButton_refresh->setEnabled(0);

        //第一页
        //ui->pushButton_set->setEnabled(0);
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

        //MAC
        ui->lineEdit_WT_MAC_RANGE_BEGIN->setReadOnly(1);
        ui->lineEdit_WT_MAC_RANGE_END->setReadOnly(1);
        ui->lineEdit_WT_MAC_CURRENT->setReadOnly(1);

        //new
        ui->lineEdit_MoLotNo->setReadOnly(1);
        ui->lineEdit_PartNo->setReadOnly(1);


        //第二页
        ui->pushButton_input->setEnabled(0);
        ui->pushButton_openfile_log->setEnabled(0);
        //ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setReadOnly(1);
        //ui->checkBox_WT_AUTO_TEST_WHEN_DUT_READY->setEnabled(0);
        SetReadOnly(ui->checkBox_WT_AUTO_TEST_WHEN_DUT_READY, 1);
        ui->lineEdit_WT_TEST_LOG_PATH->setReadOnly(1);
        ui->lineEdit_WT_DUT_START_NUM->setReadOnly(1);
        ui->lineEdit_WT_IP_ADDRESS->setReadOnly(1);
        //ui->lineEdit_PopUpFunction->setReadOnly(1);
        //ui->lineEdit_PopUpEnable->setReadOnly(1);
        //ui->checkBox_Debug_log->setEnabled(0);
        SetReadOnly(ui->checkBox_Debug_log, 1);



        //第三页
        ui->lineEdit_GoldBar_MAC->setReadOnly(1);
        ui->pushButton_correct->setEnabled(0);

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


    //设置MAC为只读
    ui->lineEdit_WT_MAC_RANGE_BEGIN->setReadOnly(1);
    ui->lineEdit_WT_MAC_RANGE_END->setReadOnly(1);
    ui->lineEdit_WT_MAC_CURRENT->setReadOnly(1);


    //设置只读wefuse
    //ui->checkBox_WT_WRITE_EFUSE->setEnabled(0);
    SetReadOnly(ui->checkBox_WT_WRITE_EFUSE, 1);

    //校准线损进度条

    //BT
    ui->doubleSpinBox_WT_FIXED_ATTEN_BT->setReadOnly(1);

    //2.4G
    ui->doubleSpinBox_CH1_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH3_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH4_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH7_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH10_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH11_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH13_Port1->setReadOnly(1);

    ui->doubleSpinBox_CH1_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH3_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH4_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH7_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH10_Port2->setReadOnly(1);
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
    //新增5G信道
    ui->doubleSpinBox_CH38_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH46_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH54_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH62_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH102_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH118_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH142_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH151_Port1->setReadOnly(1);
    ui->doubleSpinBox_CH175_Port1->setReadOnly(1);

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
    //新增5G信道
    ui->doubleSpinBox_CH38_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH46_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH54_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH62_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH102_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH118_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH142_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH151_Port2->setReadOnly(1);
    ui->doubleSpinBox_CH175_Port2->setReadOnly(1);

    //
    ui->lineEdit_ModuleType->setReadOnly(1);
    ui->lineEdit_AutoTestVersion->setReadOnly(1);
    SetReadOnly(ui->checkBox_WT_AUTO_TEST_WHEN_DUT_READY, 1);
    //ui->checkBox_WT_IS_NEED_LINKMES->setEnabled(0);
    SetReadOnly(ui->checkBox_WT_IS_NEED_LINKMES, 1);
    //ui->lineEdit_WT_IS_NEED_LINKMES->setReadOnly(1);
    //线损不可修改项
    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN0->setReadOnly(1);
    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN1->setReadOnly(1);
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN0->setReadOnly(1);
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN1->setReadOnly(1);

    //设置MAC不可写
    ui->lineEdit_WT_MAC_RANGE_BEGIN->setReadOnly(0);
    ui->lineEdit_WT_MAC_RANGE_END->setReadOnly(0);
    ui->lineEdit_WT_MAC_CURRENT->setReadOnly(0);
    //展示MAC号段及当前MAC,当MAC地址来源为配置文件时显示
    if(openfile_display(filename_WT_MAC, "WT_MAC_SOURCE") == "0")
    {
        ui->lineEdit_WT_MAC_RANGE_BEGIN->setText(openfile_display(filename_WT_MAC, "WT_MAC_VENDOR_ID")
         +openfile_display(filename_WT_MAC, "WT_MAC_RANGE_BEGIN_" + openfile_display(filename_WT_TESTER, "WT_DUT_START_NUM")));
        ui->lineEdit_WT_MAC_RANGE_END->setText(openfile_display(filename_WT_MAC, "WT_MAC_VENDOR_ID")
         +openfile_display(filename_WT_MAC, "WT_MAC_RANGE_END_" + openfile_display(filename_WT_TESTER, "WT_DUT_START_NUM")));
        ui->lineEdit_WT_MAC_CURRENT->setText(openfile_display(filename_WT_MAC, "WT_MAC_VENDOR_ID")
         +openfile_display(filename_WT_MAC, "WT_MAC_CURRENT_" + openfile_display(filename_WT_TESTER, "WT_DUT_START_NUM")));
    }
    else
    {
        ui->lineEdit_WT_MAC_RANGE_BEGIN->setText("外部输入");
        ui->lineEdit_WT_MAC_RANGE_END->setText("外部输入");
        ui->lineEdit_WT_MAC_CURRENT->setText("外部输入");
    }




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
    ui->lineEdit_ModuleType->setText(openfile_display(filename_SoftVer, "AutoTestVersion").split('-').at(0));
    cmd = ui->lineEdit_ModuleType->text() + ".exe";


    //增加显示MES连接与否，主要是配置产测软件
    //QFile::remove("../../userlogo.jpg");

    QString MoudleType = ui->lineEdit_ModuleType->text();
    //QString WT_IS_NEED_LINKMES =openfile_display(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES");
    QString filePath = "../image";
    QString curPath = QDir::currentPath();
    QDir *dir=new QDir(filePath);
    QStringList filter;


    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    //qDebug()<< "###########################" << fileInfo->count();
    for(int i = 0;i<fileInfo->count(); i++)
    {
        QString temp = fileInfo->at(i).fileName();
        //if(MoudleType + '.' + WT_IS_NEED_LINKMES + ".jpg" == temp)
        if(MoudleType + ".jpg" == temp)
        {
            QFile::copy("../image/" + temp,"../../userlogo.jpg");

        }

    }

    //展示 CVTE_SoftVer_Readme
    ui->lineEdit_AutoTestVersion->setText(openfile_display(filename_SoftVer, "AutoTestVersion"));


    //展示 WT_DUT_MIMO
    //ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setText(openfile_display(filename_WT_DUT_MIMO, "WT_AUTO_TEST_WHEN_DUT_READY"));
    if("0" == openfile_display(filename_WT_DUT_MIMO, "WT_AUTO_TEST_WHEN_DUT_READY"))
    {
        ui->checkBox_WT_AUTO_TEST_WHEN_DUT_READY->setCheckState(Qt::CheckState::Unchecked);
    }else
    {
        ui->checkBox_WT_AUTO_TEST_WHEN_DUT_READY->setCheckState(Qt::CheckState::Checked);
    }
    //ui->lineEdit_WT_IS_NEED_LINKMES->setText(openfile_display(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES"));
    if("0" == openfile_display(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES"))
    {
        ui->checkBox_WT_IS_NEED_LINKMES->setCheckState(Qt::CheckState::Unchecked);
    }else
    {
        ui->checkBox_WT_IS_NEED_LINKMES->setCheckState(Qt::CheckState::Checked);
    }
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
    if(openfile_wefuse_display("WT_WRITE_EFUSE"))//\t\t"))
    {
        ui->checkBox_WT_WRITE_EFUSE->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        //qDebug() << "111111111111111111";
        ui->checkBox_WT_WRITE_EFUSE->setCheckState(Qt::CheckState::Unchecked);
    }

    //展示 WT_ATTEN_DUT 线损参数
    display_LineLoss_clicked();
    //提示信息
    //ui->lineEdit_PopUpFunction->setPlaceholderText(openfile_display("advance.ini", "PopUpFunction"));
    //
    display_connect_mes();
    display_user_login();

    //write 端口号 到 MES.ini 中
    openfile_set_show(filename_CVTE_MES, "WT_DUT_START_NUM", ui->lineEdit_WT_DUT_START_NUM);


/*
    //展示直通率
    QString WT_PASS_NUMBER = "WT_PASS_NUMBER_" + ui->lineEdit_WT_DUT_START_NUM->text();
    QString WT_FAIL_NUMBER = "WT_FAIL_NUMBER_" + ui->lineEdit_WT_DUT_START_NUM->text();
    double first_PASS = openfile_display("../../TestStatistics.txt", WT_PASS_NUMBER).toDouble()/
            (openfile_display("../../TestStatistics.txt", WT_FAIL_NUMBER).toDouble()+
             openfile_display("../../TestStatistics.txt", WT_PASS_NUMBER).toDouble());
    //ui->lineEdit_WT_MAC_CURRENT->setText(QString::number(first_PASS*100,'f',2) + '%');
    if(!this->Usr_Type)
    {
        ui->label_user->setText("直通率：" + QString::number(first_PASS*100,'f',1) + '%');
    }
    else
    {
        ui->label_MES_Status->setText("直通率：" + QString::number(first_PASS*100,'f',1) + '%');

    }
*/
    timer->start(openfile_display(filename_CVTE_MES, "CheckDamageTime").toUInt());
    //timer->start(10000);


}
#endif

void factory_set::display_refresh()
{
#if 1
    //展示MAC号段及当前MAC,当MAC地址来源为配置文件时显示
    if(openfile_display(filename_WT_MAC, "WT_MAC_SOURCE") == "0")
    {
        ui->lineEdit_WT_MAC_CURRENT->setText(openfile_display(filename_WT_MAC, "WT_MAC_VENDOR_ID")
         +openfile_display(filename_WT_MAC, "WT_MAC_CURRENT_" + openfile_display(filename_WT_TESTER, "WT_DUT_START_NUM")));
    }

    //展示直通率
    QString WT_PASS_NUMBER = "WT_PASS_NUMBER_" + ui->lineEdit_WT_DUT_START_NUM->text();
    QString WT_FAIL_NUMBER = "WT_FAIL_NUMBER_" + ui->lineEdit_WT_DUT_START_NUM->text();
    double first_PASS = openfile_display("../../TestStatistics.txt", WT_PASS_NUMBER).toDouble()/
            (openfile_display("../../TestStatistics.txt", WT_FAIL_NUMBER).toDouble()+
             openfile_display("../../TestStatistics.txt", WT_PASS_NUMBER).toDouble());
    //ui->lineEdit_WT_MAC_CURRENT->setText(QString::number(first_PASS*100,'f',2) + '%');
    if(!this->Usr_Type)
    {
        /*if(first_PASS*100 <= openfile_display(filename_CVTE_MES, "first_PASS_yield").toDouble())
        {
            ui->label_user->setStyleSheet("color:red;");
            QMessageBox::warning(NULL, "警告", "直通率低于90%，严重影响生产！请立即点检产线配置！");
        }
        else
        {
            ui->label_user->setStyleSheet("color:green;");
        }*/
        ui->label_user->setText("直通率：" + QString::number(first_PASS*100,'f',1) + '%');

    }
    else
    {
        /*if(first_PASS*100 <= openfile_display(filename_CVTE_MES, "first_PASS_yield").toDouble())
        {
            ui->label_MES_Status->setStyleSheet("color:red;");
            QMessageBox::warning(NULL, "警告", "直通率低于90%，严重影响生产！请立即点检产线配置！");
        }
        else
        {
            ui->label_MES_Status->setStyleSheet("color:green;");
        }*/
        ui->label_MES_Status->setText("直通率：" + QString::number(first_PASS*100,'f',1) + '%');

    }

    //检查文件是否损坏

    QFile Ncfile_MIMO(filename_WT_DUT_MIMO);
    Ncfile_MIMO.open(QIODevice::ReadOnly);

    if (Ncfile_MIMO.isOpen())
    {
        while(!Ncfile_MIMO.atEnd())
        {
            //文件检查措施，确认筛选条件
            if(Ncfile_MIMO.readLine().mid(0, 20).count("WT_TEST_LOG_PATH") >= 1)
            {
               //提示框警告，文件已损坏
               return;
            }
        }
        Ncfile_MIMO.close();
        //杀死产测软件进程
        if(!killTaskl(cmd))
        {

            //about_info("错误", "产测软件程序退出失败！");
        }
        //文件损坏，弹框报错
        Err_QDialog QDial;



        QDial.show();
        if(QDial.exec() == QDialog::Accepted && refresh_flag)
        {
            on_pushButton_refresh_clicked();
            timer->stop();
            timer->start(openfile_display(filename_CVTE_MES, "CheckDamageTime").toUInt());
            refresh_flag = false;
            return;
        }
        //修改timer定时器循环时间
        timer->stop();
        timer->start(1000);
        //timer->start(openfile_display(filename_CVTE_MES, "CheckDamageTime").toUInt());

    }



#endif
}


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
        //qDebug() <<Ncfile.pos();
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
    Sleep(2000);
    about_info("提示", "参数配置成功！");

    //**************************************************
    //校准完线损后保存一份setup文件到指定文件夹，并在关键时刻恢复
    QProcess p(nullptr);
    p.start("./copy_setup.bat");  //运行脚本文件
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        Sleep(1000);
        //about_info("提示", "setup文件夹拷贝成功！");
    }

    display();
#endif
}


/**************************************************************************
**
** NAME     openfile_set_Check_box
**
** PARAMETERS:  QString filename, bool check_box_sta
**
** RETURNS:
**
** DESCRIPTION  设置DUT_MIMO文件信息.
**
** NOTES:       None.
**************************************************************************/
void factory_set::openfile_set_Check_box(QString filename, QString Check_box_id, bool check_box_sta)
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
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, Check_box_id.length()) == Check_box_id)
            {
                temp += Check_box_id + '=' + sta;
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
            /*else if(strtemp.mid(0, print_cableloss.length()) == print_cableloss)
            {
                temp += print_cableloss + '=' + sta;
                temp += QString('\n');
            }*/
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

    //QMessageBox::warning(this, dlgTitle, strInfo);

    /*QMessageBox *m_box = new QMessageBox(about,dlgTitle,strInfo);
    m_box->setStandardButtons(0);
    QTimer::singleShot(2000,m_box,SLOT(accept()));
    m_box->exec();*/
    //topWindow->setWindowFlags(topWindow->windowFlags() | Qt::WindowStaysOnTopHint);
}

//信息提示窗口
void factory_set::about_info_auto(QString dlgTitle, QString strInfo)
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::NoIcon,dlgTitle,strInfo);
    m_box->setStandardButtons(0);
    QTimer::singleShot(2000,m_box,SLOT(accept()));
    m_box->exec();
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
                //qDebug() << strtemp;
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
    //openfile_set_show(filename_WT_DUT_MIMO, "WT_AUTO_TEST_WHEN_DUT_READY", ui->lineEdit_WT_AUTO_TEST_WHEN_DUT_READY);
    //openfile_set_show(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES", ui->lineEdit_WT_IS_NEED_LINKMES);
    openfile_set_Check_box(filename_WT_DUT_MIMO, "WT_AUTO_TEST_WHEN_DUT_READY", ui->checkBox_WT_AUTO_TEST_WHEN_DUT_READY->checkState());
    openfile_set_Check_box(filename_WT_DUT_MIMO, "WT_IS_NEED_LINKMES", ui->checkBox_WT_IS_NEED_LINKMES->checkState());

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
    openfile_set_wefuse("WT_WRITE_EFUSE");

    //write 端口号 到 MES.ini 中
    openfile_set_show(filename_CVTE_MES, "WT_DUT_START_NUM", ui->lineEdit_WT_DUT_START_NUM);

    Sleep(2000);
    about_info("提示", "参数配置成功！");

    //**************************************************
    //校准完线损后保存一份setup文件到指定文件夹，并在关键时刻恢复
    QProcess p(nullptr);
    p.start("./copy_setup.bat");  //运行脚本文件
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        Sleep(1000);
        //about_info("提示", "setup文件夹拷贝成功！");
    }
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
                //qDebug() << strtemp;
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

void factory_set::LineLoss_clicked()
{

    //*************** 启动 copy.bat *****************
    QString strInfo;
    QProcess p(nullptr);

    //第一次运行成功修改correct = false

    openfile_deal_lineloss_log();
    if(correct)
    {
        correct = false;
    }
    if(correct_flag)
    {

        //correct = true;
        Sleep(1000);
        about_info("提示", "线损校准成功！");

        display_LineLoss_clicked();
        //correct_flag = false;

        p.start("./reset.bat");  //运行脚本文件
        if(p.waitForFinished()){      //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            strInfo = "完成！";
            Sleep(1000);
            about_info("提示", "原始文件reset成功！");
        }else{
            strInfo = "bat运行错误！";
        }
        return;
    }
    else
    {
        //Sleep(1000);
        //about_info("提示", "已微调，待写入！");
        set_LineLoss_correct();
        //*************** 启动 correct.bat *****************

        thread.start();       //运行校验线损脚本文件
        if(p.waitForFinished(120000)){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            strInfo = "完成！";
            Sleep(1000);
            about_info("提示", "线损运行成功！");

            //*************** 启动 copy_new_log.bat *****************
            p.start("./copy_new_log.bat");       //运行校验线损脚本文件
            if(p.waitForFinished()){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                strInfo = "完成！";
                Sleep(1000);
                about_info("提示", "log拷贝成功！");
            }else{
                strInfo = "bat运行错误！";
            }


        }else{
            strInfo = "bat运行错误！";
        }
        //循环测试，自动化测试
        LineLoss_clicked();

        //***********************************************
    }





}

//线损校准
void factory_set::set_LineLoss_correct()
{
    //filename_WT_ATTEN_DUT = "../../WT_SETUP/WT_ATTEN_DUT_" + ui->lineEdit_WT_DUT_START_NUM->text() + ".txt";

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
    Sleep(2000);
    //about_info("提示", "校准参数写入成功！");
    //display_LineLoss_clicked();
    //mythread_flag = false;
}





void factory_set::display_LineLoss_clicked()
{
    //展示 WT_ATTEN_DUT 线损参数


    filename_WT_ATTEN_DUT = "../../WT_SETUP/WT_ATTEN_DUT_" + ui->lineEdit_WT_DUT_START_NUM->text() + ".txt";
    //filename_WT_ATTEN_DUT =  "WT_ATTEN_DUT_" + ui->lineEdit_WT_DUT_START_NUM->text() + ".txt";
    if(ui->lineEdit_WT_DUT_START_NUM->text() != NULL)
    {
        ui->label_DUT_filename->setText("WT_ATTEN_DUT_" +ui->lineEdit_WT_DUT_START_NUM->text() + ".txt");
    }
    else
    {
        ui->label_DUT_filename->setText("文件未知");
    }

    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN0->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_2_4_CHAIN0"));
    ui->lineEdit_WT_FIXED_ATTEN_2_4_CHAIN1->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_2_4_CHAIN1"));
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN0->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_5_CHAIN0"));
    ui->lineEdit_WT_FIXED_ATTEN_5_CHAIN1->setText(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_5_CHAIN1"));
    //qDebug() <<  openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_2_4_CHAIN0") <<"???????????? display_LineLoss_clicked ???????????????";
    //BT
    ui->doubleSpinBox_WT_FIXED_ATTEN_BT->setValue(openfile_display(filename_WT_ATTEN_DUT, "WT_FIXED_ATTEN_BT").toDouble());


    //openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH1");
    int port_num = 1;
    //端口号为1，2.4G的值
    ui->doubleSpinBox_CH1_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH1", port_num).toDouble());
    ui->doubleSpinBox_CH3_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH3", port_num).toDouble());
    ui->doubleSpinBox_CH4_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH4", port_num).toDouble());
    ui->doubleSpinBox_CH7_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH7", port_num).toDouble());
    ui->doubleSpinBox_CH10_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH10", port_num).toDouble());
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
    //新增
    ui->doubleSpinBox_CH38_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH38", port_num).toDouble());
    ui->doubleSpinBox_CH46_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH46", port_num).toDouble());
    ui->doubleSpinBox_CH54_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH54", port_num).toDouble());
    ui->doubleSpinBox_CH62_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH62", port_num).toDouble());
    ui->doubleSpinBox_CH102_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH102", port_num).toDouble());
    ui->doubleSpinBox_CH118_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH118", port_num).toDouble());
    ui->doubleSpinBox_CH142_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH142", port_num).toDouble());
    ui->doubleSpinBox_CH151_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH151", port_num).toDouble());
    ui->doubleSpinBox_CH175_Port1->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH175", port_num).toDouble());

    port_num = 2;
    //端口号为2，2.4G的值
    ui->doubleSpinBox_CH1_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH1", port_num).toDouble());
    ui->doubleSpinBox_CH3_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH3", port_num).toDouble());
    ui->doubleSpinBox_CH4_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH4", port_num).toDouble());
    ui->doubleSpinBox_CH7_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH7", port_num).toDouble());
    ui->doubleSpinBox_CH10_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH10", port_num).toDouble());
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
    //新增
    ui->doubleSpinBox_CH38_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH38", port_num).toDouble());
    ui->doubleSpinBox_CH46_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH46", port_num).toDouble());
    ui->doubleSpinBox_CH54_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH54", port_num).toDouble());
    ui->doubleSpinBox_CH62_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH62", port_num).toDouble());
    ui->doubleSpinBox_CH102_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH102", port_num).toDouble());
    ui->doubleSpinBox_CH118_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH118", port_num).toDouble());
    ui->doubleSpinBox_CH142_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH142", port_num).toDouble());
    ui->doubleSpinBox_CH151_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH151", port_num).toDouble());
    ui->doubleSpinBox_CH175_Port2->setValue(openfile_display_lineloss(filename_WT_ATTEN_DUT, "CH175", port_num).toDouble());


}

/*
bool factory_set::Pass_log_clicked()
{
    QString filePath = "../log";
    //QString filePath = "./log/PASS";
    QDir *dir=new QDir(filePath);
    QStringList filter;
    QDateTime time;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(int i = 0;i<fileInfo->count(); i++)
    {


        if( fileInfo->at(i).suffix() == "log" && fileInfo->at(i).lastModified().secsTo(current_date_time) < 30)
        {
            return true;
        }
    }
    return false;
}*/



/**************************************************************************
**
** NAME     file_one_set
**
** PARAMETERS:  void
**
** RETURNS:
**
** DESCRIPTION  文件单独设置.
**
** NOTES:       None.
**************************************************************************/
void factory_set::file_one_set(QString filename)
{

    QString RunFrameNcFile = filename;
    QFile Ncfile(RunFrameNcFile);
    Ncfile.open(QIODevice::ReadOnly);
    if (Ncfile.isOpen())
    {
        //Ncfile.readAll();
        //qDebug() <<Ncfile.pos();
        QString strtemp;
        QTextStream NctextStream(&Ncfile);

        //修改项
        QString WT_MAC_CURRENT = "WT_MAC_CURRENT_" + ui->lineEdit_WT_DUT_START_NUM->text();
        QString Alltemp;
        while(!NctextStream.atEnd())
        {
            //qDebug() <<NctextStream.pos();
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, WT_MAC_CURRENT.length()) == WT_MAC_CURRENT)
            {
                Alltemp += WT_MAC_CURRENT + "\t=" + openfile_display(filename_CVTE_MES, "CurrentMac").mid(6,6);
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
    }
    //about_info("提示", "写入MAC成功");
}


void factory_set::on_pushButton_refresh_clicked()
{
    QString strInfo;
    QProcess p(nullptr);
    p.start("./reset_setup.bat");  //运行脚本文件
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        strInfo = "完成！";
        Sleep(1000);
        about_info("提示", "原始SETUP文件恢复成功！");
    }
    else
    {
        strInfo = "bat运行错误！";
    }

    file_one_set(filename_WT_MAC);

    display();

}

void factory_set::on_pushButton_openfile_log_clicked()
{
    /*const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("SDI"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
            return;
        }
        ui->lineEdit_WT_TEST_LOG_PATH->setText(file.fileName());
    }*/

    QString srcDirPath = QFileDialog::getExistingDirectory(
                   this, "choose src Directory",
                    "/");

        if (!srcDirPath.isEmpty())
        {
            //qDebug() << "srcDirPath=" << srcDirPath;
            srcDirPath += "/";
            ui->lineEdit_WT_TEST_LOG_PATH->setText(srcDirPath);
        }

        //openFile(fileName);
}


#if 0
void factory_set::on_pushButton_xls_clicked()
{
    openfile_deal_lineloss_log();

    QString strFilePathName = QFileDialog::getOpenFileName(this,QStringLiteral("选择Excel文件"),"",tr("Exel file(*.xls *.xlsx)"));
    if(strFilePathName.isNull())
    {
        return ;
    }
    QAxObject *excel = new QAxObject(this);    //连接Excel控件
    if (excel->setControl("Excel.Application"))
    {

    }
    else
    {
        excel->setControl("ket.Application");  //连接Excel控件
    }
    excel->setProperty("Visible", false);  //不显示窗体
    QAxObject* workbooks = excel->querySubObject("WorkBooks");  //获取工作簿集合
    workbooks->dynamicCall("Open(const QString&)", strFilePathName); //打开打开已存在的工作簿
    QAxObject* workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    //QAxObject* sheets = workbook->querySubObject("Sheets");  //获取工作表集合，Sheets也可换用WorkSheets
    QAxObject* sheet = workbook->querySubObject("WorkSheets(int)", 1);//获取工作表集合的工作表1，即sheet1
    QAxObject* range = sheet->querySubObject("UsedRange"); //获取该sheet的使用范围对象
    QVariant var = range->dynamicCall("Value");
    delete range;
    QVariantList varRows = var.toList();  //得到表格中的所有数据
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QStringList m_userid,m_card_id,m_action;
    for(int i = 1; i < rowCount; ++i)   //
    {
        QVariantList rowData = varRows[i].toList();
        m_userid<<rowData[0].toString();
        //m_card_id<<rowData[1].toString();
        //m_action<<rowData[2].toString();
        qDebug() << m_userid;
        //rowData[0].setValue();
    }

}
#endif


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
void factory_set::openfile_deal_lineloss_log(/*QString filename, QString show, int port_num*/)
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


    QFile Ncfile_jinban("../log/standard.txt");
    QFile Ncfile_test("../log/test_log.txt");
    Ncfile_jinban.open(QIODevice::ReadOnly);
    Ncfile_test.open(QIODevice::ReadOnly);
    if (Ncfile_jinban.isOpen() && Ncfile_test.isOpen())
    {
        QString strtemp_jinban,strtemp_test;
        QTextStream NctextStream_jinban(&Ncfile_jinban),NctextStream_test(&Ncfile_test);

        QString temp = "金板" + QString("\t\t\t\t\t\t") + "测试n" + QString("\t\t") + "微调值" + QString('\n');
        double loss_value, temp_value;
        int ch = 0;
        //about_info("提示", "我是openfile_deal_lineloss_log！");
        while(!NctextStream_jinban.atEnd() && !NctextStream_test.atEnd())
        {
            strtemp_jinban = NctextStream_jinban.readLine();
            strtemp_test = NctextStream_test.readLine();
            QStringList list_jinban,list_test;

            if(correct)
            {
                correct_flag = false;
                if(strtemp_test.mid(0, 3) == "ANT" && strtemp_jinban.mid(0, 3) == "ANT")
                {
                    list_test = strtemp_test.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    list_jinban = strtemp_jinban.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    temp += strtemp_jinban + "\t\t"  + list_test.at(2) + "\t\t" + QString::number((list_jinban.at(2).toDouble() - list_test.at(2).toDouble()),'f',2);
                    temp += QString('\n');
                    loss_value = list_jinban.at(2).toDouble() - list_test.at(2).toDouble();
                    ch = list_jinban.at(1).toInt();
                    if(list_jinban.at(0) == "ANT0")
                    {
                        switch(ch)
                        {
                            case 1 : ui->doubleSpinBox_CH1_Port1->setValue(loss_value);

                                break;
                            case 3 : ui->doubleSpinBox_CH3_Port1->setValue(loss_value);
                                break;
                            case 7 : ui->doubleSpinBox_CH7_Port1->setValue(loss_value);
                                break;
                            case 11 : ui->doubleSpinBox_CH11_Port1->setValue(loss_value);
                                break;
                            case 13 : ui->doubleSpinBox_CH13_Port1->setValue(loss_value);
                                break;
                            case 36 : ui->doubleSpinBox_CH36_Port1->setValue(loss_value);
                                break;
                            case 48 : ui->doubleSpinBox_CH48_Port1->setValue(loss_value);
                                break;
                            case 52 : ui->doubleSpinBox_CH52_Port1->setValue(loss_value);
                                break;
                            case 64 : ui->doubleSpinBox_CH64_Port1->setValue(loss_value);
                                break;
                            case 100 : ui->doubleSpinBox_CH100_Port1->setValue(loss_value);
                                break;
                            case 116 : ui->doubleSpinBox_CH116_Port1->setValue(loss_value);
                                break;
                            case 120 : ui->doubleSpinBox_CH120_Port1->setValue(loss_value);
                                break;
                            case 136 : ui->doubleSpinBox_CH136_Port1->setValue(loss_value);
                                break;
                            case 140 : ui->doubleSpinBox_CH140_Port1->setValue(loss_value);
                                break;
                            case 157 : ui->doubleSpinBox_CH157_Port1->setValue(loss_value);
                                break;
                            case 161 : ui->doubleSpinBox_CH161_Port1->setValue(loss_value);
                                break;
                            case 165 : ui->doubleSpinBox_CH165_Port1->setValue(loss_value);
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch(ch)
                        {
                            case 1 : ui->doubleSpinBox_CH1_Port2->setValue(loss_value);
                                break;
                            case 3 : ui->doubleSpinBox_CH3_Port2->setValue(loss_value);
                                break;
                            case 7 : ui->doubleSpinBox_CH7_Port2->setValue(loss_value);
                                break;
                            case 11 : ui->doubleSpinBox_CH11_Port2->setValue(loss_value);
                                break;
                            case 13 : ui->doubleSpinBox_CH13_Port2->setValue(loss_value);
                                break;
                            case 36 : ui->doubleSpinBox_CH36_Port2->setValue(loss_value);
                                break;
                            case 48 : ui->doubleSpinBox_CH48_Port2->setValue(loss_value);
                                break;
                            case 52 : ui->doubleSpinBox_CH52_Port2->setValue(loss_value);
                                break;
                            case 64 : ui->doubleSpinBox_CH64_Port2->setValue(loss_value);
                                break;
                            case 100 : ui->doubleSpinBox_CH100_Port2->setValue(loss_value);
                                break;
                            case 116 : ui->doubleSpinBox_CH116_Port2->setValue(loss_value);
                                break;
                            case 120 : ui->doubleSpinBox_CH120_Port2->setValue(loss_value);
                                break;
                            case 136 : ui->doubleSpinBox_CH136_Port2->setValue(loss_value);
                                break;
                            case 140 : ui->doubleSpinBox_CH140_Port2->setValue(loss_value);
                                break;
                            case 157 : ui->doubleSpinBox_CH157_Port2->setValue(loss_value);
                                break;
                            case 161 : ui->doubleSpinBox_CH161_Port2->setValue(loss_value);
                                break;
                            case 165 : ui->doubleSpinBox_CH165_Port2->setValue(loss_value);
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


                    if(qAbs(temp_value) > 0.5)
                    {
                        correct_flag = false;
                        loss_value = list_jinban.at(4).toDouble() + temp_value/2;
                    }
                    temp += list_jinban.at(0) + "\t\t" + list_jinban.at(1) + "\t\t" + list_jinban.at(2) + "\t\t";
                    temp += list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                    //temp += strtemp_jinban + "\t\t"  + list_test.at(2) + "\t\t" + QString::number(loss_value,'f',2);
                    temp += QString('\n');

                    ch = list_jinban.at(1).toInt();
                    if(list_jinban.at(0) == "ANT0")
                    {
                        //qDebug() << "ch = "<<ch <<", loss_value = " <<loss_value << "我是爸爸" ;
                        switch(ch)
                        {
                            case 1 : ui->doubleSpinBox_CH1_Port1->setValue(loss_value);

                                break;
                            case 3 : ui->doubleSpinBox_CH3_Port1->setValue(loss_value);
                                break;
                            case 7 : ui->doubleSpinBox_CH7_Port1->setValue(loss_value);
                                break;
                            case 11 : ui->doubleSpinBox_CH11_Port1->setValue(loss_value);
                                break;
                            case 13 : ui->doubleSpinBox_CH13_Port1->setValue(loss_value);
                                break;
                            case 36 : ui->doubleSpinBox_CH36_Port1->setValue(loss_value);
                                break;
                            case 48 : ui->doubleSpinBox_CH48_Port1->setValue(loss_value);
                                break;
                            case 52 : ui->doubleSpinBox_CH52_Port1->setValue(loss_value);
                                break;
                            case 64 : ui->doubleSpinBox_CH64_Port1->setValue(loss_value);
                                break;
                            case 100 : ui->doubleSpinBox_CH100_Port1->setValue(loss_value);
                                break;
                            case 116 : ui->doubleSpinBox_CH116_Port1->setValue(loss_value);
                                break;
                            case 120 : ui->doubleSpinBox_CH120_Port1->setValue(loss_value);
                                break;
                            case 136 : ui->doubleSpinBox_CH136_Port1->setValue(loss_value);
                                break;
                            case 140 : ui->doubleSpinBox_CH140_Port1->setValue(loss_value);
                                break;
                            case 157 : ui->doubleSpinBox_CH157_Port1->setValue(loss_value);
                                break;
                            case 161 : ui->doubleSpinBox_CH161_Port1->setValue(loss_value);
                                break;
                            case 165 : ui->doubleSpinBox_CH165_Port1->setValue(loss_value);
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch(ch)
                        {
                            case 1 : ui->doubleSpinBox_CH1_Port2->setValue(loss_value);
                                break;
                            case 3 : ui->doubleSpinBox_CH3_Port2->setValue(loss_value);
                                break;
                            case 7 : ui->doubleSpinBox_CH7_Port2->setValue(loss_value);
                                break;
                            case 11 : ui->doubleSpinBox_CH11_Port2->setValue(loss_value);
                                break;
                            case 13 : ui->doubleSpinBox_CH13_Port2->setValue(loss_value);
                                break;
                            case 36 : ui->doubleSpinBox_CH36_Port2->setValue(loss_value);
                                break;
                            case 48 : ui->doubleSpinBox_CH48_Port2->setValue(loss_value);
                                break;
                            case 52 : ui->doubleSpinBox_CH52_Port2->setValue(loss_value);
                                break;
                            case 64 : ui->doubleSpinBox_CH64_Port2->setValue(loss_value);
                                break;
                            case 100 : ui->doubleSpinBox_CH100_Port2->setValue(loss_value);
                                break;
                            case 116 : ui->doubleSpinBox_CH116_Port2->setValue(loss_value);
                                break;
                            case 120 : ui->doubleSpinBox_CH120_Port2->setValue(loss_value);
                                break;
                            case 136 : ui->doubleSpinBox_CH136_Port2->setValue(loss_value);
                                break;
                            case 140 : ui->doubleSpinBox_CH140_Port2->setValue(loss_value);
                                break;
                            case 157 : ui->doubleSpinBox_CH157_Port2->setValue(loss_value);
                                break;
                            case 161 : ui->doubleSpinBox_CH161_Port2->setValue(loss_value);
                                break;
                            case 165 : ui->doubleSpinBox_CH165_Port2->setValue(loss_value);
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

}

void factory_set::dialog_process_bar()
{
    int time = 1200000000;//12000000;//36000000;
    QProgressDialog dialog(tr("线损校准进度"), tr("取消"), 0, time, this);
    dialog.setWindowTitle(tr("线损校准"));

    dialog.setStyleSheet("QProgressBar{border:1px solid #FFFFFF;"
                              "height:30;"
                              "background:red;"
                              "text-align:center;"
                              "color:rgb(255,255,0);"
                              "border-radius:10px;}"
                              "QProgressBar::chunk{"
                              "border-radius:3px;"    // 斑马线圆角
                              "border:0.5px "
                              "solid green;" // 黑边，默认无边
                              "background-color:green;}");
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setModal(true);

    //滚动进度条
    dialog.setMinimum(0);
    dialog.setMaximum(0);

    dialog.show();

    int i = 0;
    for( ; i < time; i++)//已知最大值不超过50000
    {
        //mutex.lock();
        if(i % 500 == 0 && mythread_flag)
        {
            if(!PASS_flag || correct_flag)
            {
               dialog.setValue(time);
               break;
            }
        }

        //mutex.unlock();
        dialog.setValue(i);
        QCoreApplication::processEvents();
        if(dialog.wasCanceled())
        {
            PASS_flag = false;
            break;
        }

    }
    if(i == time)
    {
        PASS_flag = false;
    }
    //dialog.setValue(time);
    dialog.setValue(0);


}


/**************************************************************************
**
** NAME     display_GoldBar_MAC
**
** PARAMETERS:  (QString MAC)
**
** RETURNS:
**
** DESCRIPTION  显示多块金板MAC，用来选择校准使用的对应金板数据
**
** NOTES:       None.
**************************************************************************/
bool factory_set::display_GoldBar_MAC(QString MAC)
{
    QString filePath = "../GoldenBin/";
    QDir *dir=new QDir(filePath);
    QStringList filter;


    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    qDebug()<< "###########################" << fileInfo->count();
    for(int i = 0;i<fileInfo->count(); i++)
    {
        QString temp = fileInfo->at(i).fileName();
        //if(MoudleType + '.' + WT_IS_NEED_LINKMES + ".jpg" == temp)
        //if(MoudleType + ".jpg" == temp)
        if(fileInfo->at(i).suffix() == "txt" && fileInfo->at(i).fileName().split('.').at(0) == MAC)
        {
            QFile::copy(filePath + temp,"../standard.txt");
            return true;
        }

    }
    return false;
}


void factory_set::on_pushButton_correct_clicked()
{
#if 1
    if(!display_GoldBar_MAC(ui->lineEdit_GoldBar_MAC->text()))
    {
        about_info("提示", "此MAC查无对应金板！");
        return;
    }

    //自动校线损，加进度条
    //*************** 启动 copy.bat *****************
    QStringList arguments;
    correct_Port_Num = "./correct.bat " + ui->lineEdit_WT_DUT_START_NUM->text();
    QProcess p(nullptr);
    ui->label_about_correct->setText("校准中，请勿点击界面！");
    //关闭MAC弹窗
    bool PopUpEnable_flag = false;
    if(openfile_display("../../advance.ini", "PopUpEnable") == '1')
    {
        PopUpEnable_flag = true;
        openfile_set_Check_box("../../advance.ini", "PopUpEnable", 0);
    }

    //about_info_auto("提示", "进入校准模式成功！");
    timer->stop();
    //QApplication::setOverrideCursor(QCursor(Qt::WaitCursor)); //设置鼠标为等待状态
    ui->pushButton_correct->setText("校准进行中");
    ui->pushButton_correct->setEnabled(0);

    thread.start();
    dialog_process_bar();
    //thread.quit();
    thread.stop();



    //QApplication::restoreOverrideCursor();//恢复鼠标为箭头状态
    if(PASS_flag && correct_flag)// && air_link_flag)
    {
        ui->label_about_correct->setText("校准 PASS！");
        ui->label_about_correct->setStyleSheet("color:green;");
        about_info("提示", "线损校准 PASS！");
        ui->label_about_correct->setText("已校准！");
    }
    else
    {
        ui->label_about_correct->setText("校准 FAIL！");
        
        /*if(!air_link_flag)
        {
            about_info("提示", "线损值超过阈值，请及时检查配置环境并重新开始校准！");
        }
        else*/
        {
            about_info("提示", "PASS_log 获取失败！请检查配置并重新开始校准！");
        }
        PASS_flag = true;
        //air_link_flag = true;

    }

    //删除standard.txt
    QFile::remove("../standard.txt");

    //恢复MAC扫描框
    if(PopUpEnable_flag)
    {
        openfile_set_Check_box("../../advance.ini", "PopUpEnable", 1);
    }

    //5、拷入原始文件，替换校准文件
    p.start("./reset_correct.bat");  //运行脚本文件
    //恢复金版数据
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        //Sleep(1000);
        //about_info("提示", "原始文件reset成功！");
    }

    //Sleep(1000);
    //display_LineLoss_clicked();
    display();
    timer->start(3000);
    correct = true;
    //correct_flag = true;
    mythread_flag=false;
    ui->pushButton_correct->setEnabled(1);
    ui->pushButton_correct->setText("校准开始");


    //**************************************************
    //校准完线损后保存一份setup文件到指定文件夹，并在关键时刻恢复
    p.start("./copy_setup.bat");  //运行脚本文件
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        //Sleep(1000);
        //about_info("提示", "setup文件夹拷贝成功！");
    }
#else
    //自动校线损，未加进度条
    //*************** 启动 copy.bat *****************
    QStringList arguments;
    QString strInfo, Port_Num;
    Port_Num = "./correct.bat " + ui->lineEdit_WT_DUT_START_NUM->text();
    QProcess p(nullptr);
    ui->label_about_correct->setText("校准中，请勿点击界面！");

    bool PASS_flag_old = true;
    QString copy_new_log = "./copy_new_log.bat";// + ui->lineEdit_WT_TEST_LOG_PATH->text();
    while(1/*!correct_flag*/)
    {

        if(correct)
        {
            //1、拷入校准模式文件，拷出原始文件
            p.start("./copy_correct.bat");
            //备份金版数据

            if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            {

                strInfo = "完成！";
                Sleep(1000);
                about_info("提示", "进入校准模式成功！");
                QApplication::setOverrideCursor(QCursor(Qt::WaitCursor)); //设置鼠标为等待状态
                ui->pushButton_correct->setText("校准进行中");
                ui->pushButton_correct->setEnabled(0);
            //2、跑校准模式和金板对比，并重复N次
                //第一遍不用循环
                p.start(Port_Num);       //运行校验线损脚本文件
                if(p.waitForFinished(120000))//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                {
                    strInfo = "完成！";
                    Sleep(1000);
                    //about_info("提示", "线损运行成功！");

                    //*************** 启动 copy_new_log.bat *****************
                    p.start(copy_new_log);       //运行校验线损脚本文件
                    if(p.waitForFinished() ){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1

                        strInfo = "完成！";
                        Sleep(1000);
                        //about_info("提示", "log拷贝成功！");
                        if(!Pass_log_clicked())
                        {
                            PASS_flag_old = false;
                            break;
                        }

                    }

                 }

                openfile_deal_lineloss_log();
                if(correct_flag)
                    break;
                set_LineLoss_correct();
                correct = false;
                //about_info("提示", "第一次跑完了哦！");
            }
        }
        else
        {
            //4、多次测试后，如测试数据和金板数据相差不大于正负0.5，则校准成功
            //p.start("./correct.bat");       //运行校验线损脚本文件
            p.start(Port_Num);
            if(p.waitForFinished(120000)){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                strInfo = "完成！";
                Sleep(1000);
                //about_info("提示", "线损运行成功！");

                //*************** 启动 copy_new_log.bat *****************
                //p.start("./copy_new_log.bat");       //运行校验线损脚本文件
                p.start(copy_new_log);       //运行校验线损脚本文件
                if(p.waitForFinished()){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
                    strInfo = "完成！";
                    Sleep(1000);
                    if(!Pass_log_clicked())
                    {
                        PASS_flag_old = false;
                        break;
                    }
                    //about_info("提示", "log拷贝成功！");
                }else{
                    strInfo = "bat运行错误！";
                }
            }else{
                strInfo = "bat运行错误！";
            }
            openfile_deal_lineloss_log();
            if(correct_flag)
                break;
            set_LineLoss_correct();
            //about_info("提示", "第N次跑完了哦！");
            //correct_flag = true;
        }
    }

    QApplication::restoreOverrideCursor();//恢复鼠标为箭头状态
    if(!PASS_flag)
    {
        ui->label_about_correct->setText("校准 FAIL！");
        about_info("提示", "PASS_log 获取失败！请检查配置并重新开始校准！");
        PASS_flag_old = true;
    }
    else
    {
        ui->label_about_correct->setText("校准 PASS！");
        ui->label_about_correct->setStyleSheet("color:green;");
        about_info("提示", "线损校准 PASS！");
        ui->label_about_correct->setText("");
    }

    //5、拷入原始文件，替换校准文件
    p.start("./reset_correct.bat");  //运行脚本文件
    //恢复金版数据
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        strInfo = "完成！";
        Sleep(1000);
        //about_info("提示", "原始文件reset成功！");
    }

    Sleep(1000);
    //display_LineLoss_clicked();
    display();
    correct = true;
    ui->pushButton_correct->setEnabled(1);
    ui->pushButton_correct->setText("校准开始");


    //**************************************************
    //校准完线损后保存一份setup文件到指定文件夹，并在关键时刻恢复
    p.start("./copy_setup.bat");  //运行脚本文件
    if(p.waitForFinished())//等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        strInfo = "完成！";
        Sleep(1000);
        //about_info("提示", "setup文件夹拷贝成功！");
    }
    else
    {
        strInfo = "bat运行错误！";
    }
#endif
}

void factory_set::on_pushButton_open_factory_tool_clicked()
{
    QProcess p(this);
    QStringList arguments;
    //arguments << "/c" << "ping www.baidu.com";
    //arguments << "cd ../../ " << " && " << "E:/qt_code/8.SKO.W618U.1_638BU/WLAN_Console.exe -p 1";

    //QString cmd = "SKO.W618U.1_638BU.exe";
    arguments << "/c" << "cd ../../ && " + cmd;


    QProcess process(this);
    //process.start("./correct.bat");
    process.startDetached("cmd.exe", arguments);
    process.waitForStarted();
    process.waitForFinished();
    /*if(process.waitForFinished())   //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
    {
        process.start("./copy_new_log.bat");       //运行校验线损脚本文件
        if(process.waitForFinished()){        //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            emit mySignal();
        }
    }*/
}
