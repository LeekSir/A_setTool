#include "login.h"
#include "ui_login.h"
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_UserName->setPlaceholderText("请输入用户名");
    ui->lineEdit_PassWord->setPlaceholderText("请输入密码");
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


void login::on_pushButton_quit_clicked()
{
    this->close();
}



void login::on_pushButton_login_clicked()
{
    //this->close();
    this->accept();
}
