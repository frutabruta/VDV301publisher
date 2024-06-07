QT += core gui
QT += xml
QT += httpserver

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


DEFINES+= QZEROCONF_STATIC
include(../../QtZeroConf/qtzeroconf.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../VDV301DataStructures/additionalannoucement.cpp \
    ../../VDV301DataStructures/connection.cpp \
    ../../VDV301DataStructures/vehiclerun.cpp \
    ../../VDV301DataStructures/vehiclestate.cpp \
    ../../VDV301DataStructures/connectionmpv.cpp \
    ../../VDV301DataStructures/line.cpp \
    ../../VDV301DataStructures/stoppoint.cpp \
    ../../VDV301DataStructures/trip.cpp \
    ../../colordisplayrules.cpp \
    ../../customerinformationservice.cpp \
    ../../httpserverpublisher.cpp \
    ../../httpservice.cpp \
    ../../subscriber.cpp \
    ../../xmlcommon.cpp \
    ../../xmlcustomerinformationservice.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../VDV301DataStructures/additionalannoucement.h \
    ../../VDV301DataStructures/connection.h \
    ../../VDV301DataStructures/vehiclerun.h \
    ../../VDV301DataStructures/vehiclestate.h \
    ../../VDV301DataStructures/connectionmpv.h \
    ../../VDV301DataStructures/line.h \
    ../../VDV301DataStructures/stoppoint.h \
    ../../VDV301DataStructures/trip.h \
    ../../colordisplayrules.h \
    ../../customerinformationservice.h \
    ../../httpserverpublisher.h \
    ../../httpservice.h \
    ../../subscriber.h \
    ../../xmlcommon.h \
    ../../xmlcustomerinformationservice.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
