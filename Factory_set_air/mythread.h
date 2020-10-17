#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void stop();
    QString strResult;


signals:
    void  mySignal();


protected:
    void run();

private:
    volatile bool stopped;
    bool Pass_log_clicked();
    void openfile_deal_lineloss_log(/*QString filename, QString show, int port_num*/);
    void openfile_set_LineLoss(QString Box_name, double loss_value, int port_num);
    bool folder_isEmpty(QString folder_Path);
    void about_info_auto(QString dlgTitle, QString strInfo, int timeout);
    void about_info(QString dlgTitle, QString strInfo);

};

#endif
