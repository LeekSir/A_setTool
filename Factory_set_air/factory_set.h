#ifndef FACTORY_SET_H
#define FACTORY_SET_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QtWidgets>
#include "mythread.h"

//bool correct;//是否第一次校准

QT_BEGIN_NAMESPACE
namespace Ui { class factory_set; }
QT_END_NAMESPACE

class factory_set : public QMainWindow
{
    Q_OBJECT

public:
    factory_set(QWidget *parent = nullptr);
    ~factory_set();

    bool Usr_Type = false;
    void display();

    void set_LineLoss_correct();
    void openfile_deal_lineloss_log(/*QString filename, QString show, int port_num*/);

public slots:
       // 声明槽函数 mySlot()
       void mySlot();

private slots:
    void on_pushButton_set_clicked();

    void on_pushButton_input_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_openfile_log_clicked();


    void on_pushButton_correct_clicked();

private:
    QString openfile_display(QString filename, QString show);
    void openfile_set_show(QString filename, QString line_id, QLineEdit* wirte_show);
    void openfile_set_debug(QString filename, bool check_box_sta);
    void about_info(QString dlgTitle, QString strInfo);
    QString openfile_display_lineloss(QString filename, QString show, int port_num);
    void openfile_set_LineLoss(QString Box_name, QDoubleSpinBox* wirte_show, int port_num);

    void openfile_set_BT_show(QString filename, QString Box_id, QDoubleSpinBox* SpinBox);
    bool openfile_wefuse_display(QString show);
    void openfile_set_wefuse(QString box_id);
    void display_user_login();
    void display_LineLoss_clicked();
    void LineLoss_clicked();
    void dialog_process_bar();//进度条

    bool Pass_log_clicked();

    void openfile_set_Check_box(QString filename, QString Check_box_id, bool check_box_sta);



    void display_connect_mes();


    void file_one_set(QString filename);


    Ui::factory_set *ui;

    QString filename_CVTE_MES;
    QString filename_WT_DUT_MIMO;
    QString filename_WT_TESTER;
    QString filename_advance;
    QString filename_debug;
    QString filename_SoftVer;
    QString filename_WT_ATTEN_DUT;
    QString filename_WT_WRITE_EFUSE;
    QString filename_WT_MAC;

    //端口信道




    //添加线程私有对象
    MyThread thread;




};
#endif // FACTORY_SET_H
