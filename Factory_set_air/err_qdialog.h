#ifndef ERR_QDIALOG_H
#define ERR_QDIALOG_H


#include<QDialog>
#include <QtWidgets>

namespace Ui {
class Err_QDialog;
}


class Err_QDialog : public QDialog
{
    Q_OBJECT

private slots:
    void quit();
public:
    explicit Err_QDialog(QWidget *parent = nullptr);
    ~Err_QDialog();
//    void paintEvent(QPaintEvent *);
//signals:

//public slots:
    //void slotOpenNewWindow();

};

#endif // ERR_QDIALOG_H
