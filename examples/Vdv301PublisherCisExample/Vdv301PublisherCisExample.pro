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
    ../../VDV301DataStructures/stoppointdestination.cpp \
    ../../VDV301DataStructures/vdv301alldata.cpp \
    ../../VDV301DataStructures/vdv301alldata2_3cz1_0.cpp \
    ../../VDV301DataStructures/vdv301connection.cpp \
    ../../VDV301DataStructures/vdv301currentdisplaycontent.cpp \
    ../../VDV301DataStructures/vdv301currentdisplaycontent2_3cz1_0.cpp \
    ../../VDV301DataStructures/vdv301destination.cpp \
    ../../VDV301DataStructures/vdv301displaycontent.cpp \
    ../../VDV301DataStructures/vdv301displaycontent2_3cz1_0.cpp \
    ../../VDV301DataStructures/vdv301enumerations.cpp \
    ../../VDV301DataStructures/vdv301farezonechange2_3cz1_0.cpp \
    ../../VDV301DataStructures/vdv301internationaltext.cpp \
    ../../VDV301DataStructures/vdv301line.cpp \
    ../../VDV301DataStructures/vdv301stoppoint.cpp \
    ../../VDV301DataStructures/vdv301stoppoint2_3cz1_0.cpp \
    ../../VDV301DataStructures/vdv301trip.cpp \
    ../../VDV301DataStructures/vdv301trip2_3cz1_0.cpp \
    ../../VDV301DataStructures/vdv301vehicleinformationgroup.cpp \
    ../../VDV301DataStructures/vdv301viapoint.cpp \
    ../../VDV301DataStructures/vdv301viapoint2_3cz1_0.cpp \
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
    ../../xmlcommon1_0_new.cpp \
    ../../xmlcommon2_3_new.cpp \
    ../../xmlcommon2_3cz1_0.cpp \
    ../../xmlcommonvehiclestate.cpp \
    ../../xmlcustomerinformationservice.cpp \
    ../../xmlcustomerinformationservice1_0_new.cpp \
    ../../xmlcustomerinformationservice2_3_new.cpp \
    ../../xmlcustomerinformationservice2_3cz1_0.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../VDV301DataStructures/additionalannoucement.h \
    ../../VDV301DataStructures/connection.h \
    ../../VDV301DataStructures/stoppointdestination.h \
    ../../VDV301DataStructures/vdv301alldata.h \
    ../../VDV301DataStructures/vdv301alldata2_3cz1_0.h \
    ../../VDV301DataStructures/vdv301connection.h \
    ../../VDV301DataStructures/vdv301currentdisplaycontent.h \
    ../../VDV301DataStructures/vdv301currentdisplaycontent2_3cz1_0.h \
    ../../VDV301DataStructures/vdv301destination.h \
    ../../VDV301DataStructures/vdv301displaycontent.h \
    ../../VDV301DataStructures/vdv301displaycontent2_3cz1_0.h \
    ../../VDV301DataStructures/vdv301enumerations.h \
    ../../VDV301DataStructures/vdv301farezonechange2_3cz1_0.h \
    ../../VDV301DataStructures/vdv301internationaltext.h \
    ../../VDV301DataStructures/vdv301line.h \
    ../../VDV301DataStructures/vdv301stoppoint.h \
    ../../VDV301DataStructures/vdv301stoppoint2_3cz1_0.h \
    ../../VDV301DataStructures/vdv301trip.h \
    ../../VDV301DataStructures/vdv301trip2_3cz1_0.h \
    ../../VDV301DataStructures/vdv301vehicleinformationgroup.h \
    ../../VDV301DataStructures/vdv301viapoint.h \
    ../../VDV301DataStructures/vdv301viapoint2_3cz1_0.h \
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
    ../../xmlcommon1_0_new.h \
    ../../xmlcommon2_3_new.h \
    ../../xmlcommon2_3cz1_0.h \
    ../../xmlcommonvehiclestate.h \
    ../../xmlcustomerinformationservice.h \
    ../../xmlcustomerinformationservice1_0_new.h \
    ../../xmlcustomerinformationservice2_3_new.h \
    ../../xmlcustomerinformationservice2_3cz1_0.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
