QT       += core gui
CONFIG += resources_big
QT += axcontainer
#RC_ICONS = process_icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 resources_big


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppIcon.cpp \
    err_qdialog.cpp \
    login.cpp \
    factory_set.cpp \
    mythread.cpp

HEADERS += \
    err_qdialog.h \
    factory_set.h \
    login.h \
    mythread.h

FORMS += \
    factory_set.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    AppIcon.rc \
    uac.manifest

RC_FILE += AppIcon.rc

#RC_FILE += main.rc
#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'"
#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"
