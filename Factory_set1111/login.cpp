#include "login.h"
#include "ui_login.h"
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

bool login::logining()
{
    if("cvte" == ui->lineEdit_UserName->text() && "666666" == ui->lineEdit_PassWord->text())
    {
        qDebug() << "logining successfully!!!" << ui->lineEdit_UserName->text() << ui->lineEdit_PassWord->text();
        return true;
    }
    return false;
}
