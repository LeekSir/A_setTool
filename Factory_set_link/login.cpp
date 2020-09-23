#include "login.h"
#include "ui_login.h"
#include <QDebug>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_UserName->setPlaceholderText("输入用户名(空为操作员)");
    ui->lineEdit_PassWord->setPlaceholderText("请输入密码(空为操作员)");

}

login::~login()
{
    delete ui;
}

int login::logining()
{
    if(ui->lineEdit_UserName->text().length() != 0 || ui->lineEdit_PassWord->text().length() != 0)
    {
        if("cvte" == ui->lineEdit_UserName->text() && "666666" == ui->lineEdit_PassWord->text())
        {
            ui->pushButton_login->setText("登陆成功");
            qDebug() << "logining successfully!!!" << ui->lineEdit_UserName->text() << ui->lineEdit_PassWord->text();
            return 0;
        }
        else
        {
            QMessageBox::critical(0 , "错误" , "用户名或密码输入错误！操作员身份登陆。",
                                  QMessageBox::Ok | QMessageBox::Default , QMessageBox::Cancel
                                  | QMessageBox::Escape , 	0 );
            return -1;
        }

    }
    else
    {
        return -2;
    }

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
