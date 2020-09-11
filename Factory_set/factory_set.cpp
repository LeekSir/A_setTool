#include "factory_set.h"
#include "ui_factory_set.h"
#include <QDebug>
#include <QtWidgets>


factory_set::factory_set(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::factory_set)
{
    ui->setupUi(this);
}

factory_set::~factory_set()
{
    delete ui;
}

void factory_set::on_pushButton_set_clicked()
{
#if 0
    qDebug() << ui->lineEdit_IP->text();
    QString IP = ui->lineEdit_IP->text();
    QString Port = ui->lineEdit_Port->text();
    ui->textBrowser->setText(IP + Port);


    //打开文件配置文件
    QString fileName = "CVTE_MES.ini";
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
        QMessageBox::warning(this, tr("SDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    QByteArray line;
    QString display;

    while(!file.atEnd())
    {
        qDebug() << "file.atEnd() = " << file.atEnd();
        line = file.readLine();
        QString str(line);
        if(0 == str.indexOf("IP="))
        {
            display = display + str + "\r\n";
            qDebug() << str << "hello" << file.pos();
            int i = file.pos() - str.length() -1;
            file.seek(i);
            //file.write(0, 50);
            //file.seek(i);
            //IP = "IP=" + IP;
            if(IP.length() - str.length() >= 0)
            {
                IP = "IP=" + IP;
            }
            else {
                IP = "IP=" + IP + "   ";
            }
            file.write(IP.toLatin1());
            //continue;
        }
        //qDebug()<< str << file.pos();

    }

    //FILE* fp = fopen(fileName,"rb");
    //QTextStream in(&file);
    //QString line, display;

/*    while (in.readLineInto(&line))
    {

        if(0 == line.indexOf("IP="))
        {

            display = display + line + "\r\n";
            qDebug() << line << "hello" << file.pos();
            continue;
        }
        if(0 == line.indexOf("Port="))
        {
            display = display + line + "\r\n";
            qDebug() << line << "hello" << file.pos();
        }
        qDebug() <<  file.pos();
    }
*/
    //QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    //ui->textBrowser->setText(display);
    file.close();
    //设置配置文件

    /*
    ui->textBrowser->setText(ui->lineEdit_Port->text());
    ui->textBrowser->setText(ui->lineEdit_User->text());
    ui->textBrowser->setText(ui->lineEdit_WksNo->text());
    ui->textBrowser->setText(ui->lineEdit_passwd->text());
    ui->textBrowser->setText(ui->lineEdit_NgCount->text());
    ui->textBrowser->setText(ui->lineEdit_causeNo->text());
    ui->textBrowser->setText(ui->lineEdit_keyInfo->text());
    ui->textBrowser->setText(ui->lineEdit_TestItem->text());
    ui->textBrowser->setText(ui->lineEdit_User_name->text());
    ui->textBrowser->setText(ui->lineEdit_OS_address->text());
    */
#endif

#if 0
     QString strAll, fileName = "CVTE_MES.ini";
     QStringList strList;
     QFile readFile(fileName);
     if(readFile.open((QIODevice::ReadOnly|QIODevice::Text)))
     {
         qDebug()<<readFile.atEnd();
         QTextStream stream(&readFile);
         strAll=stream.readAll();
     }
     readFile.close();
     QFile writeFile(fileName);
     qDebug() << "helloworld1";
     QString IP = "IP=" + ui->lineEdit_IP->text();
     QString Port ="Port=" + ui->lineEdit_Port->text();
     ui->textBrowser->setText(IP + "\n" + Port);
     if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
     {
             QTextStream stream(&writeFile);
             strList=strAll.split("\n");
             for(int i=0;i<strList.count();i++)
             {
                 if(i==strList.count()-1)
                 {
                     //最后一行不需要换行
                     stream<<strList.at(i);
                 }
                 else
                 {
                     stream<<strList.at(i)<<'\n';
                 }
                 //strList.removeAt(1);
                 //if(strList.at(i).contains("[Server]"))
                 if(strList.at(i).contains("IP="))
                 {
                     strList.removeAt(5);
                     qDebug() << "helloworld3" << strList.at(i);
                     QString tempStr=strList.at(i);
                     //strList.at(i).replace(0,strList.at(i).length(),IP);
                     strList.removeAt(i);
                     //tempStr.insert(i, IP);
                     //tempStr.insert(i, IP);
                     //stream<<strList.<<'\n';
                     /*tempStr=strList.at(i+2);
                     tempStr.replace(0,tempStr.length(),Port);
                     stream<<tempStr<<'\n';
                     i+=1;*/
                     //i+=1;
                 }
             }
     }
     writeFile.close();
#endif
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
        QString IP = "IP=";
        QString Port = "Port=";
        QString ProdUrl = "ProdUrl=";
        QString SysUrl = "SysUrl=";
        QString TokenName = "TokenName=";
        QString UserName = "UserName=";
        QString PassWord = "PassWord=";
        QString CauseNo = "CauseNo=";
        QString WorkCenter = "WorkCenter=";
        QString WksNo = "WksNo=";
        QString TestFrameidNo = "TestFrameidNo=";
        QString WorkerNo = "WorkerNo=";
        QString KeyInfo = "KeyInfo=";
        QString AutoTestVersion = "AutoTestVersion=";
        QString TestItem = "TestItem=";
        QString StationCode = "StationCode=";
        QString NgCount = "NgCount=";

        //QString name = " ";
        QString Alltemp;
        while(!NctextStream.atEnd())
        {
            qDebug() <<NctextStream.pos();
            strtemp = NctextStream.readLine();
            if(strtemp.mid(0, IP.length()) == IP)
            {
                Alltemp = Alltemp+ IP + ui->lineEdit_IP->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,Port.length()) == Port)
            {
                Alltemp = Alltemp+ Port + ui->lineEdit_Port->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,ProdUrl.length()) == ProdUrl)
            {
                Alltemp = Alltemp+ ProdUrl + ui->lineEdit_make_address->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,SysUrl.length()) == SysUrl)
            {
                Alltemp = Alltemp+ SysUrl + ui->lineEdit_OS_address->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,UserName.length()) == UserName)
            {
                Alltemp = Alltemp+ UserName + ui->lineEdit_User_name->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,PassWord.length()) == PassWord)
            {
                Alltemp = Alltemp+ PassWord + ui->lineEdit_passwd->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,CauseNo.length()) == CauseNo)
            {
                Alltemp = Alltemp+ CauseNo + ui->lineEdit_causeNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WorkCenter.length()) == WorkCenter)
            {
                Alltemp = Alltemp+ WorkCenter + ui->lineEdit_workCenter->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WksNo.length()) == WksNo)
            {
                Alltemp = Alltemp+ WksNo + ui->lineEdit_WksNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,TestFrameidNo.length()) == TestFrameidNo)
            {
                Alltemp = Alltemp+ TestFrameidNo + ui->lineEdit_TestItem->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,WorkerNo.length()) == WorkerNo)
            {
                Alltemp = Alltemp+ WorkerNo + ui->lineEdit_WorkerNo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,KeyInfo.length()) == KeyInfo)
            {
                Alltemp = Alltemp+ KeyInfo + ui->lineEdit_keyInfo->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,AutoTestVersion.length()) == AutoTestVersion)
            {
                Alltemp = Alltemp+ AutoTestVersion + ui->lineEdit_TestVersion->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,StationCode.length()) == StationCode)
            {
                Alltemp = Alltemp+ StationCode + ui->lineEdit_StationCode->text();
                Alltemp += QString('\n');
            }
            else if(strtemp.mid(0,NgCount.length()) == NgCount)
            {
                Alltemp = Alltemp+ NgCount + ui->lineEdit_NgCount->text();
                Alltemp += QString('\n');
            }
            /*else if(strtemp.mid(0,11) == Fname)
            {
                Alltemp = Alltemp+ QString("#<FValue> = ").toLatin1() + QString::number(RunFrameSpeed).toLatin1();
                Alltemp += QString('\n').toLatin1();
            }*/
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
#endif
}
