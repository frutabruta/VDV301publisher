QT       += core gui
QT       += xml
QT       += httpserver
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DEFINES+= QZEROCONF_STATIC
include(../../QtZeroConf/qtzeroconf.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../VDV301DataStructures/vdv301enumerations.cpp \
    ../../VDV301DataStructures/vdv301internationaltext.cpp \
    ../../colordisplayrules.cpp \
    ../../httpserverpublisher.cpp \
    ../../httpservice.cpp \
    ../../remotecontrolservice.cpp \
    ../../subscriber.cpp \
    ../../xmlcommon.cpp \
    ../../xmlremotecontrolservice2_3cz1_0.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../VDV301DataStructures/vdv301enumerations.h \
    ../../VDV301DataStructures/vdv301internationaltext.h \
    ../../colordisplayrules.h \
    ../../httpserverpublisher.h \
    ../../httpservice.h \
    ../../remotecontrolservice.h \
    ../../subscriber.h \
    ../../xmlcommon.h \
    ../../xmlremotecontrolservice2_3cz1_0.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
