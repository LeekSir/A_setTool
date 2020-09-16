#ifndef FACTORY_SET_H
#define FACTORY_SET_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QtWidgets>
/*
#define FILE_CVTE_MES "..\CVTE_MES.ini"
#define FILE_WT_DUT_MIMO "..\WT_SETUP\WT_DUT_MIMO.txt"
#define FILE_WT_TESTER "..\WT_SETUP\WT_TESTER.txt"
#define FILE_ADVANCE_INI "..\advance.ini"
#define FILE_DEBUG_INI "..\debug.ini"
*/
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

private slots:
    void on_pushButton_set_clicked();

    void on_pushButton_clicked();

    void on_pushButton_input_clicked();

private:
    QString openfile_display(QString filename, QString show);
    void openfile_set_show(QString filename, QString line_id, QLineEdit* wirte_show);
    void openfile_set_debug(QString filename, bool check_box_sta);
    Ui::factory_set *ui;




};
#endif // FACTORY_SET_H
