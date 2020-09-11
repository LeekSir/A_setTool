#ifndef FACTORY_SET_H
#define FACTORY_SET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class factory_set; }
QT_END_NAMESPACE

class factory_set : public QMainWindow
{
    Q_OBJECT

public:
    factory_set(QWidget *parent = nullptr);
    ~factory_set();

private slots:
    void on_pushButton_set_clicked();

    void on_pushButton_clicked();

private:
    Ui::factory_set *ui;
};
#endif // FACTORY_SET_H
