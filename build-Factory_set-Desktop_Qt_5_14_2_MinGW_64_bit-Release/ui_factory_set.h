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
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_factory_set
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QTabWidget *tabWidget;
    QWidget *base_set;
    QPushButton *pushButton_set;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *lineEdit_User_name;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLineEdit *lineEdit_passwd;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_IP;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_Port;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLineEdit *lineEdit_TestVersion;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_make_address;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_OS_address;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QLineEdit *lineEdit_TestItem;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_16;
    QLineEdit *lineEdit_NgCount;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_15;
    QLineEdit *lineEdit_StationCode;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_8;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QLineEdit *lineEdit_WorkerNo;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *lineEdit_WksNo;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QLineEdit *lineEdit_workCenter;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_causeNo;
    QWidget *special_set;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_21;
    QLineEdit *lineEdit_WT_AUTO_TEST_WHEN_DUT_READY;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_22;
    QLineEdit *lineEdit_WT_IS_NEED_LINKMES;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_23;
    QLineEdit *lineEdit_WT_TEST_LOG_PATH;
    QLabel *label_20;
    QCheckBox *checkBox_Debug_log;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_26;
    QLineEdit *lineEdit_PopUpEnable;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_27;
    QLineEdit *lineEdit_PopUpFunction;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_24;
    QLineEdit *lineEdit_WT_IP_ADDRESS;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_25;
    QLineEdit *lineEdit_WT_DUT_START_NUM;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_45;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_input;
    QSpacerItem *horizontalSpacer_16;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *factory_set)
    {
        if (factory_set->objectName().isEmpty())
            factory_set->setObjectName(QString::fromUtf8("factory_set"));
        factory_set->resize(884, 565);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(factory_set->sizePolicy().hasHeightForWidth());
        factory_set->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(factory_set);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMouseTracking(false);
        base_set = new QWidget();
        base_set->setObjectName(QString::fromUtf8("base_set"));
        pushButton_set = new QPushButton(base_set);
        pushButton_set->setObjectName(QString::fromUtf8("pushButton_set"));
        pushButton_set->setGeometry(QRect(626, 444, 75, 23));
        layoutWidget = new QWidget(base_set);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(67, 9, 330, 266));
        verticalLayout_7 = new QVBoxLayout(layoutWidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(70, 0));

        horizontalLayout_7->addWidget(label_6);

        lineEdit_User_name = new QLineEdit(layoutWidget);
        lineEdit_User_name->setObjectName(QString::fromUtf8("lineEdit_User_name"));

        horizontalLayout_7->addWidget(lineEdit_User_name);


        verticalLayout_7->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(70, 0));

        horizontalLayout_8->addWidget(label_7);

        lineEdit_passwd = new QLineEdit(layoutWidget);
        lineEdit_passwd->setObjectName(QString::fromUtf8("lineEdit_passwd"));
        lineEdit_passwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_8->addWidget(lineEdit_passwd);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(70, 0));

        horizontalLayout->addWidget(label);

        lineEdit_IP = new QLineEdit(layoutWidget);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));
        lineEdit_IP->setMinimumSize(QSize(250, 0));

        horizontalLayout->addWidget(lineEdit_IP);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(70, 0));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_Port = new QLineEdit(layoutWidget);
        lineEdit_Port->setObjectName(QString::fromUtf8("lineEdit_Port"));

        horizontalLayout_3->addWidget(lineEdit_Port);


        verticalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(70, 0));

        horizontalLayout_14->addWidget(label_13);

        lineEdit_TestVersion = new QLineEdit(layoutWidget);
        lineEdit_TestVersion->setObjectName(QString::fromUtf8("lineEdit_TestVersion"));

        horizontalLayout_14->addWidget(lineEdit_TestVersion);


        verticalLayout_7->addLayout(horizontalLayout_14);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(70, 0));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_make_address = new QLineEdit(layoutWidget);
        lineEdit_make_address->setObjectName(QString::fromUtf8("lineEdit_make_address"));

        horizontalLayout_5->addWidget(lineEdit_make_address);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(70, 0));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_OS_address = new QLineEdit(layoutWidget);
        lineEdit_OS_address->setObjectName(QString::fromUtf8("lineEdit_OS_address"));

        horizontalLayout_6->addWidget(lineEdit_OS_address);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(70, 0));

        horizontalLayout_15->addWidget(label_14);

        lineEdit_TestItem = new QLineEdit(layoutWidget);
        lineEdit_TestItem->setObjectName(QString::fromUtf8("lineEdit_TestItem"));

        horizontalLayout_15->addWidget(lineEdit_TestItem);


        verticalLayout_7->addLayout(horizontalLayout_15);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(70, 0));

        horizontalLayout_17->addWidget(label_16);

        lineEdit_NgCount = new QLineEdit(layoutWidget);
        lineEdit_NgCount->setObjectName(QString::fromUtf8("lineEdit_NgCount"));

        horizontalLayout_17->addWidget(lineEdit_NgCount);


        verticalLayout_7->addLayout(horizontalLayout_17);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(70, 0));

        horizontalLayout_16->addWidget(label_15);

        lineEdit_StationCode = new QLineEdit(layoutWidget);
        lineEdit_StationCode->setObjectName(QString::fromUtf8("lineEdit_StationCode"));

        horizontalLayout_16->addWidget(lineEdit_StationCode);


        verticalLayout_7->addLayout(horizontalLayout_16);

        layoutWidget1 = new QWidget(base_set);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(459, 9, 330, 104));
        verticalLayout_8 = new QVBoxLayout(layoutWidget1);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(70, 0));

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        lineEdit_WorkerNo = new QLineEdit(layoutWidget1);
        lineEdit_WorkerNo->setObjectName(QString::fromUtf8("lineEdit_WorkerNo"));
        lineEdit_WorkerNo->setMinimumSize(QSize(250, 0));

        gridLayout->addWidget(lineEdit_WorkerNo, 0, 1, 1, 1);


        verticalLayout_8->addLayout(gridLayout);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(70, 0));

        horizontalLayout_11->addWidget(label_10);

        lineEdit_WksNo = new QLineEdit(layoutWidget1);
        lineEdit_WksNo->setObjectName(QString::fromUtf8("lineEdit_WksNo"));
        lineEdit_WksNo->setMinimumSize(QSize(250, 0));

        horizontalLayout_11->addWidget(lineEdit_WksNo);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(70, 0));

        horizontalLayout_10->addWidget(label_9);

        lineEdit_workCenter = new QLineEdit(layoutWidget1);
        lineEdit_workCenter->setObjectName(QString::fromUtf8("lineEdit_workCenter"));

        horizontalLayout_10->addWidget(lineEdit_workCenter);


        verticalLayout_8->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(70, 0));

        horizontalLayout_9->addWidget(label_8);

        lineEdit_causeNo = new QLineEdit(layoutWidget1);
        lineEdit_causeNo->setObjectName(QString::fromUtf8("lineEdit_causeNo"));
        lineEdit_causeNo->setMinimumSize(QSize(250, 0));

        horizontalLayout_9->addWidget(lineEdit_causeNo);


        verticalLayout_8->addLayout(horizontalLayout_9);

        tabWidget->addTab(base_set, QString());
        special_set = new QWidget();
        special_set->setObjectName(QString::fromUtf8("special_set"));
        special_set->setEnabled(true);
        special_set->setMouseTracking(false);
        special_set->setAcceptDrops(false);
        gridLayout_7 = new QGridLayout(special_set);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalSpacer_8 = new QSpacerItem(26, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_17 = new QLabel(special_set);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_17);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_21 = new QLabel(special_set);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy2);
        label_21->setMinimumSize(QSize(100, 0));
        label_21->setMaximumSize(QSize(100, 16777215));
        label_21->setBaseSize(QSize(0, 0));

        horizontalLayout_2->addWidget(label_21);

        lineEdit_WT_AUTO_TEST_WHEN_DUT_READY = new QLineEdit(special_set);
        lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setObjectName(QString::fromUtf8("lineEdit_WT_AUTO_TEST_WHEN_DUT_READY"));
        lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setMinimumSize(QSize(250, 0));
        lineEdit_WT_AUTO_TEST_WHEN_DUT_READY->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_2->addWidget(lineEdit_WT_AUTO_TEST_WHEN_DUT_READY);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_22 = new QLabel(special_set);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy2.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy2);
        label_22->setMinimumSize(QSize(100, 0));
        label_22->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(label_22);

        lineEdit_WT_IS_NEED_LINKMES = new QLineEdit(special_set);
        lineEdit_WT_IS_NEED_LINKMES->setObjectName(QString::fromUtf8("lineEdit_WT_IS_NEED_LINKMES"));
        lineEdit_WT_IS_NEED_LINKMES->setMinimumSize(QSize(250, 0));
        lineEdit_WT_IS_NEED_LINKMES->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_12->addWidget(lineEdit_WT_IS_NEED_LINKMES);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_23 = new QLabel(special_set);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy2.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy2);
        label_23->setMinimumSize(QSize(100, 0));

        horizontalLayout_18->addWidget(label_23);

        lineEdit_WT_TEST_LOG_PATH = new QLineEdit(special_set);
        lineEdit_WT_TEST_LOG_PATH->setObjectName(QString::fromUtf8("lineEdit_WT_TEST_LOG_PATH"));
        lineEdit_WT_TEST_LOG_PATH->setMinimumSize(QSize(250, 0));
        lineEdit_WT_TEST_LOG_PATH->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_18->addWidget(lineEdit_WT_TEST_LOG_PATH);


        verticalLayout->addLayout(horizontalLayout_18);


        verticalLayout_5->addLayout(verticalLayout);

        label_20 = new QLabel(special_set);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(label_20);

        checkBox_Debug_log = new QCheckBox(special_set);
        checkBox_Debug_log->setObjectName(QString::fromUtf8("checkBox_Debug_log"));

        verticalLayout_5->addWidget(checkBox_Debug_log);


        gridLayout_2->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_19 = new QLabel(special_set);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_19);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_26 = new QLabel(special_set);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy2.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy2);
        label_26->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_19->addWidget(label_26);

        lineEdit_PopUpEnable = new QLineEdit(special_set);
        lineEdit_PopUpEnable->setObjectName(QString::fromUtf8("lineEdit_PopUpEnable"));
        lineEdit_PopUpEnable->setMinimumSize(QSize(250, 0));
        lineEdit_PopUpEnable->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_19->addWidget(lineEdit_PopUpEnable);


        verticalLayout_2->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_27 = new QLabel(special_set);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy2.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy2);
        label_27->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_20->addWidget(label_27);

        lineEdit_PopUpFunction = new QLineEdit(special_set);
        lineEdit_PopUpFunction->setObjectName(QString::fromUtf8("lineEdit_PopUpFunction"));
        lineEdit_PopUpFunction->setMinimumSize(QSize(250, 0));
        lineEdit_PopUpFunction->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_20->addWidget(lineEdit_PopUpFunction);


        verticalLayout_2->addLayout(horizontalLayout_20);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_18 = new QLabel(special_set);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label_18);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_24 = new QLabel(special_set);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy2.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy2);
        label_24->setMinimumSize(QSize(100, 0));
        label_24->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_21->addWidget(label_24);

        lineEdit_WT_IP_ADDRESS = new QLineEdit(special_set);
        lineEdit_WT_IP_ADDRESS->setObjectName(QString::fromUtf8("lineEdit_WT_IP_ADDRESS"));
        lineEdit_WT_IP_ADDRESS->setMinimumSize(QSize(250, 0));
        lineEdit_WT_IP_ADDRESS->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_21->addWidget(lineEdit_WT_IP_ADDRESS);


        verticalLayout_3->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_25 = new QLabel(special_set);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy2.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy2);
        label_25->setMinimumSize(QSize(100, 0));
        label_25->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_22->addWidget(label_25);

        lineEdit_WT_DUT_START_NUM = new QLineEdit(special_set);
        lineEdit_WT_DUT_START_NUM->setObjectName(QString::fromUtf8("lineEdit_WT_DUT_START_NUM"));
        lineEdit_WT_DUT_START_NUM->setMinimumSize(QSize(250, 0));
        lineEdit_WT_DUT_START_NUM->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_22->addWidget(lineEdit_WT_DUT_START_NUM);


        verticalLayout_3->addLayout(horizontalLayout_22);


        verticalLayout_4->addLayout(verticalLayout_3);


        gridLayout_2->addLayout(verticalLayout_4, 0, 2, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 0, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        horizontalSpacer_5 = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_5);

        pushButton_input = new QPushButton(special_set);
        pushButton_input->setObjectName(QString::fromUtf8("pushButton_input"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_input->sizePolicy().hasHeightForWidth());
        pushButton_input->setSizePolicy(sizePolicy3);
        pushButton_input->setMaximumSize(QSize(100, 50));

        horizontalLayout_45->addWidget(pushButton_input);


        verticalLayout_6->addLayout(horizontalLayout_45);


        gridLayout_7->addLayout(verticalLayout_6, 0, 1, 2, 1);

        horizontalSpacer_16 = new QSpacerItem(26, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_16, 1, 2, 1, 1);

        tabWidget->addTab(special_set, QString());

        gridLayout_6->addWidget(tabWidget, 0, 0, 1, 1);

        factory_set->setCentralWidget(centralwidget);
        menubar = new QMenuBar(factory_set);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 884, 23));
        factory_set->setMenuBar(menubar);
        statusbar = new QStatusBar(factory_set);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        factory_set->setStatusBar(statusbar);

        retranslateUi(factory_set);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(factory_set);
    } // setupUi

    void retranslateUi(QMainWindow *factory_set)
    {
        factory_set->setWindowTitle(QCoreApplication::translate("factory_set", "factory_set", nullptr));
        pushButton_set->setText(QCoreApplication::translate("factory_set", "\351\205\215 \347\275\256", nullptr));
        label_6->setText(QCoreApplication::translate("factory_set", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_7->setText(QCoreApplication::translate("factory_set", "\347\231\273\351\231\206\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("factory_set", "IP", nullptr));
        label_2->setText(QCoreApplication::translate("factory_set", "Port", nullptr));
        label_13->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\347\211\210\346\234\254\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("factory_set", "\347\224\237\344\272\247\345\234\260\345\235\200", nullptr));
        label_5->setText(QCoreApplication::translate("factory_set", "\347\263\273\347\273\237\345\234\260\345\235\200", nullptr));
        label_14->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\351\241\271", nullptr));
        label_16->setText(QCoreApplication::translate("factory_set", "\345\205\201\350\256\270NG\346\254\241\346\225\260", nullptr));
        label_15->setText(QCoreApplication::translate("factory_set", "\345\267\245\346\255\245\347\274\226\345\217\267", nullptr));
        label_11->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\345\221\230\347\274\226\345\217\267", nullptr));
        label_10->setText(QCoreApplication::translate("factory_set", "\346\265\213\350\257\225\345\267\245\344\275\215\347\274\226\345\217\267", nullptr));
        label_9->setText(QCoreApplication::translate("factory_set", "\344\272\247\345\223\201\347\272\277\347\274\226\345\217\267", nullptr));
        label_8->setText(QCoreApplication::translate("factory_set", "\345\223\201\350\264\250\347\216\260\350\261\241\347\274\226\345\217\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(base_set), QCoreApplication::translate("factory_set", "\345\237\272\347\241\200\350\256\276\347\275\256", nullptr));
#if QT_CONFIG(whatsthis)
        special_set->setWhatsThis(QCoreApplication::translate("factory_set", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_17->setText(QCoreApplication::translate("factory_set", "WT_DUT_MIMO:", nullptr));
        label_21->setText(QCoreApplication::translate("factory_set", "WT_AUTO_TEST_WHEN_DUT_READY", nullptr));
        label_22->setText(QCoreApplication::translate("factory_set", "WT_IS_NEED_LINKMES", nullptr));
        label_23->setText(QCoreApplication::translate("factory_set", "WT_TEST_LOG_PATH", nullptr));
        label_20->setText(QCoreApplication::translate("factory_set", "debug.ini:", nullptr));
        checkBox_Debug_log->setText(QCoreApplication::translate("factory_set", "Debug_log", nullptr));
        label_19->setText(QCoreApplication::translate("factory_set", "advance.int:", nullptr));
        label_26->setText(QCoreApplication::translate("factory_set", "PopUpEnable", nullptr));
        label_27->setText(QCoreApplication::translate("factory_set", "PopUpFunction", nullptr));
        label_18->setText(QCoreApplication::translate("factory_set", "WT_TESTER:", nullptr));
        label_24->setText(QCoreApplication::translate("factory_set", "WT_IP_ADDRESS", nullptr));
        label_25->setText(QCoreApplication::translate("factory_set", "WT_DUT_START_NUM", nullptr));
        pushButton_input->setText(QCoreApplication::translate("factory_set", "\351\205\215 \347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(special_set), QCoreApplication::translate("factory_set", "\344\273\252\345\231\250\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class factory_set: public Ui_factory_set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTORY_SET_H
