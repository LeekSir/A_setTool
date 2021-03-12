#include "err_qdialog.h"
#include "ui_login.h"
#include <QDebug>

extern bool refresh_flag;

Err_QDialog::Err_QDialog(QWidget *parent) :
    QDialog(parent)
    //ui(new Ui::Err_QDialog)
{

    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->setGeometry(0, 0, 300, 100);
    this->setFixedSize(900,800);
    //this->setStyleSheet("#Err_QDialog{background-color: rgb(255, 0, 0);}");
    //this->setStyleSheet("background-image:url(:/image/404.jpg);");
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);


    QPixmap pixmap = QPixmap(":/image/404.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    //this->setStyleSheet("background-color:red;");



    QLabel *pLabel = new QLabel(this);
    pLabel->setText("警告！MIMO文件已损坏请及时修复!");
    pLabel->move(pLabel->width() ,  pLabel->height()*2);
    //设置字号
    QFont ft( "Microsoft YaHei", 20, 75);
    //ft.setPointSize(20);
    pLabel->setFont(ft);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    pLabel->setPalette(pa);

    pLabel->adjustSize();


    //pLabel->setStyleSheet("color: red");
    //QImage image(QString("D:/1.jpg"));
    /*QImage *image = new QImage;
    //pLabel->setPixmap(QPixmap::fromImage(image));
    image->load(":/image/404.jpg");
    pLabel->resize(image->width(),image->height());
    pLabel->setPixmap(QPixmap::fromImage(*image));
    pLabel->move((this->width())/2- pLabel->width()/2,(desktop->height()/2 - pLabel->height())/2);
*/
    QPushButton *btn = new QPushButton("一键修复文件",this);
    btn->setGeometry(600,700,300,100);
    //设置字号
    QFont ft1( "Microsoft YaHei", 20, 75);
    //ft.setPointSize(20);
    btn->setFont(ft1);

    //设置颜色
    QPalette pa1;
    pa1.setColor(QPalette::WindowText,Qt::red);
    btn->setPalette(pa1);
    btn->move((this->width())*1/3-btn->width()/2,this->height()*3/4 - btn->height()/2);

    connect(btn, SIGNAL(clicked()), this, SLOT(quit()));

}

Err_QDialog::~Err_QDialog()
{}


void Err_QDialog::quit()
{
    refresh_flag = true;
    this->accept();
    this->close();
}
