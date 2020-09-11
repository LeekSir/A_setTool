/********************************************************************************
** Form generated from reading UI file 'factory_set.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTORY_SET_H
#define UI_FACTORY_SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_factory_set
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *base_set;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_IP;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QLineEdit *lineEdit_TestItem;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QLineEdit *lineEdit_keyInfo;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLineEdit *lineEdit_passwd;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_Port;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_16;
    QLineEdit *lineEdit_NgCount;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_15;
    QLineEdit *lineEdit_StationCode;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_User;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_set;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QLineEdit *lineEdit_WorkerNo;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_causeNo;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_OS_address;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *lineEdit_WksNo;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QLineEdit *lineEdit_workCenter;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *lineEdit_User_name;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_make_address;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLineEdit *lineEdit_TestVersion;
    QWidget *special_set;
    QPushButton *pushButton_input;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *factory_set)
    {
        if (factory_set->objectName().isEmpty())
            factory_set->setObjectName(QString::fromUtf8("factory_set"));
        factory_set->resize(859, 619);
        centralwidget = new QWidget(factory_set);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        base_set = new QWidget();
        base_set->setObjectName(QString::fromUtf8("base_set"));
        gridLayout_3 = new QGridLayout(base_set);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(base_set);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(70, 0));

        horizontalLayout->addWidget(label);

        lineEdit_IP = new QLineEdit(base_set);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));

        horizontalLayout->addWidget(lineEdit_IP);


        gridLayout_3->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(105, 348, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 12, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_14 = new QLabel(base_set);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(70, 0));

        horizontalLayout_15->addWidget(label_14);

        lineEdit_TestItem = new QLineEdit(base_set);
        lineEdit_TestItem->setObjectName(QString::fromUtf8("lineEdit_TestItem"));

        horizontalLayout_15->addWidget(lineEdit_TestItem);


        gridLayout_3->addLayout(horizontalLayout_15, 4, 1, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_12 = new QLabel(base_set);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(70, 0));

        horizontalLayout_13->addWidget(label_12);

        lineEdit_keyInfo = new QLineEdit(base_set);
        lineEdit_keyInfo->setObjectName(QString::fromUtf8("lineEdit_keyInfo"));

        horizontalLayout_13->addWidget(lineEdit_keyInfo);


        gridLayout_3->addLayout(horizontalLayout_13, 11, 1, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(base_set);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(70, 0));

        horizontalLayout_8->addWidget(label_7);

        lineEdit_passwd = new QLineEdit(base_set);
        lineEdit_passwd->setObjectName(QString::fromUtf8("lineEdit_passwd"));
        lineEdit_passwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_8->addWidget(lineEdit_passwd);


        gridLayout_3->addLayout(horizontalLayout_8, 10, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(base_set);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(70, 0));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_Port = new QLineEdit(base_set);
        lineEdit_Port->setObjectName(QString::fromUtf8("lineEdit_Port"));

        horizontalLayout_3->addWidget(lineEdit_Port);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 1, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_16 = new QLabel(base_set);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(70, 0));

        horizontalLayout_17->addWidget(label_16);

        lineEdit_NgCount = new QLineEdit(base_set);
        lineEdit_NgCount->setObjectName(QString::fromUtf8("lineEdit_NgCount"));

        horizontalLayout_17->addWidget(lineEdit_NgCount);


        gridLayout_3->addLayout(horizontalLayout_17, 8, 1, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_15 = new QLabel(base_set);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(70, 0));

        horizontalLayout_16->addWidget(label_15);

        lineEdit_StationCode = new QLineEdit(base_set);
        lineEdit_StationCode->setObjectName(QString::fromUtf8("lineEdit_StationCode"));

        horizontalLayout_16->addWidget(lineEdit_StationCode);


        gridLayout_3->addLayout(horizontalLayout_16, 6, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(569, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 12, 0, 1, 4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(base_set);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(70, 0));

        horizontalLayout_4->addWidget(label_3);

        lineEdit_User = new QLineEdit(base_set);
        lineEdit_User->setObjectName(QString::fromUtf8("lineEdit_User"));

        horizontalLayout_4->addWidget(lineEdit_User);


        gridLayout_3->addLayout(horizontalLayout_4, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(106, 348, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 2, 12, 1);

        pushButton_set = new QPushButton(base_set);
        pushButton_set->setObjectName(QString::fromUtf8("pushButton_set"));

        gridLayout_3->addWidget(pushButton_set, 12, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(105, 348, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 5, 12, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_11 = new QLabel(base_set);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(70, 0));

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        lineEdit_WorkerNo = new QLineEdit(base_set);
        lineEdit_WorkerNo->setObjectName(QString::fromUtf8("lineEdit_WorkerNo"));

        gridLayout->addWidget(lineEdit_WorkerNo, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 3, 1, 2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(base_set);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(70, 0));

        horizontalLayout_9->addWidget(label_8);

        lineEdit_causeNo = new QLineEdit(base_set);
        lineEdit_causeNo->setObjectName(QString::fromUtf8("lineEdit_causeNo"));

        horizontalLayout_9->addWidget(lineEdit_causeNo);


        gridLayout_3->addLayout(horizontalLayout_9, 3, 3, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(base_set);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(70, 0));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_OS_address = new QLineEdit(base_set);
        lineEdit_OS_address->setObjectName(QString::fromUtf8("lineEdit_OS_address"));

        horizontalLayout_6->addWidget(lineEdit_OS_address);


        gridLayout_3->addLayout(horizontalLayout_6, 7, 1, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_10 = new QLabel(base_set);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(70, 0));

        horizontalLayout_11->addWidget(label_10);

        lineEdit_WksNo = new QLineEdit(base_set);
        lineEdit_WksNo->setObjectName(QString::fromUtf8("lineEdit_WksNo"));

        horizontalLayout_11->addWidget(lineEdit_WksNo);


        gridLayout_3->addLayout(horizontalLayout_11, 1, 3, 1, 2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_9 = new QLabel(base_set);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(70, 0));

        horizontalLayout_10->addWidget(label_9);

        lineEdit_workCenter = new QLineEdit(base_set);
        lineEdit_workCenter->setObjectName(QString::fromUtf8("lineEdit_workCenter"));

        horizontalLayout_10->addWidget(lineEdit_workCenter);


        gridLayout_3->addLayout(horizontalLayout_10, 2, 3, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(base_set);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(70, 0));

        horizontalLayout_7->addWidget(label_6);

        lineEdit_User_name = new QLineEdit(base_set);
        lineEdit_User_name->setObjectName(QString::fromUtf8("lineEdit_User_name"));

        horizontalLayout_7->addWidget(lineEdit_User_name);


        gridLayout_3->addLayout(horizontalLayout_7, 9, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(base_set);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(70, 0));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_make_address = new QLineEdit(base_set);
        lineEdit_make_address->setObjectName(QString::fromUtf8("lineEdit_make_address"));

        horizontalLayout_5->addWidget(lineEdit_make_address);


        gridLayout_3->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(base_set);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(70, 0));

        horizontalLayout_14->addWidget(label_13);

        lineEdit_TestVersion = new QLineEdit(base_set);
        lineEdit_TestVersion->setObjectName(QString::fromUtf8("lineEdit_TestVersion"));

        horizontalLayout_14->addWidget(lineEdit_TestVersion);


        gridLayout_3->addLayout(horizontalLayout_14, 2, 1, 1, 1);

        tabWidget->addTab(base_set, QString());
        special_set = new QWidget();
        special_set->setObjectName(QString::fromUtf8("special_set"));
        special_set->setEnabled(true);
        special_set->setMouseTracking(false);
        special_set->setAcceptDrops(false);
        pushButton_input = new QPushButton(special_set);
        pushButton_input->setObjectName(QString::fromUtf8("pushButton_input"));
        pushButton_input->setGeometry(QRect(610, 470, 93, 28));
        tabWidget->addTab(special_set, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        factory_set->setCentralWidget(centralwidget);
        menubar = new QMenuBar(factory_set);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 859, 23));
        factory_set->setMenuBar(menubar);
        statusbar = new QStatusBar(factory_set);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        factory_set->setStatusBar(statusbar);

        retranslateUi(factory_set);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(factory_set);
    } // setupUi

    void retranslateUi(QMainWindow *factory_set)
    {
        factory_set->setWindowTitle(QCoreApplication::translate("factory_set", "factory_set", nullptr));
        label->setText(QCoreApplication::translate("factory_set", "IP", nullptr));
        label_14->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\351\241\271", nullptr));
        label_12->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225key\344\277\241\346\201\257", nullptr));
        label_7->setText(QCoreApplication::translate("factory_set", "\347\231\273\351\231\206\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("factory_set", "Port", nullptr));
        label_16->setText(QCoreApplication::translate("factory_set", "\345\205\201\350\256\270NG\346\254\241\346\225\260", nullptr));
        label_15->setText(QCoreApplication::translate("factory_set", "\345\267\245\346\255\245\347\274\226\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("factory_set", "User", nullptr));
        pushButton_set->setText(QCoreApplication::translate("factory_set", "\351\205\215 \347\275\256", nullptr));
        label_11->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\345\221\230\347\274\226\345\217\267", nullptr));
        label_8->setText(QCoreApplication::translate("factory_set", "\345\223\201\350\264\250\347\216\260\350\261\241\347\274\226\345\217\267", nullptr));
        label_5->setText(QCoreApplication::translate("factory_set", "\347\263\273\347\273\237\345\234\260\345\235\200", nullptr));
        label_10->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\345\267\245\344\275\215\347\274\226\345\217\267", nullptr));
        label_9->setText(QCoreApplication::translate("factory_set", "\344\272\247\345\223\201\347\272\277\347\274\226\345\217\267", nullptr));
        label_6->setText(QCoreApplication::translate("factory_set", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("factory_set", "\347\224\237\344\272\247\345\234\260\345\235\200", nullptr));
        label_13->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\347\211\210\346\234\254\344\277\241\346\201\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(base_set), QCoreApplication::translate("factory_set", "\345\237\272\347\241\200\350\256\276\347\275\256", nullptr));
#if QT_CONFIG(whatsthis)
        special_set->setWhatsThis(QCoreApplication::translate("factory_set", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_input->setText(QCoreApplication::translate("factory_set", "\345\257\274\345\205\245", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(special_set), QCoreApplication::translate("factory_set", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class factory_set: public Ui_factory_set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTORY_SET_H
