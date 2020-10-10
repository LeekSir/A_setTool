#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtWidgets>
#include "mythread.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

     int logining();

private slots:

    void on_pushButton_quit_clicked();

    
    void on_pushButton_login_clicked();

private:
    Ui::login *ui;

    MyThread thread;
};

#endif // LOGIN_H
