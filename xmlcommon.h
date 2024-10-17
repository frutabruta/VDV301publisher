#ifndef XMLCOMMON_H
#define XMLCOMMON_H
#include <QMainWindow>
#include <QObject>
#include <QTime>
#include <QCoreApplication>
#include <QtDebug>
#include <QtXml>
#include <QDomDocument>

#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vehiclestate.h"
#include "VDV301DataStructures/farezone.h"
#include "VDV301DataStructures/connectionmpv.h"
#include "VDV301DataStructures/vdv301displaycontent.h"
#include "VDV301DataStructures/vdv301destination.h"
#include "VDV301DataStructures/vdv301line.h"
#include "VDV301DataStructures/vdv301stoppoint.h"
#include "VDV301DataStructures/vdv301trip.h"
#include "VDV301DataStructures/vdv301vehicleinformationgroup.h"

#include "VDV301DataStructures/vdv301alldata.h"


#include "colordisplayrules.h"
//#include "xmlmpvparser.h"


class XmlCommon : public QObject
{
    Q_OBJECT
public:
    /*
    enum DisplayContentClass
    {
        DisplayContentFront,
        DisplayContentSide,
        DisplayContentRear,
        DisplayContentLcd
    };*/

    ColorDisplayRules colorDisplayRules;

    XmlCommon();

    //constants
    QString defaultLanguage1_0="de";
    QString defaultLanguage2_2CZ1_0="cs";
    QString defaultLanguage2_3="cs";
    QString defaultLanguage2_3CZ1_0="cs";
    QString mDefaultEncoding="utf-8";


    //pomocneFce
    //  QString devStatus();
    QString createTimestamp();
    QDomElement internationalTextTypeToDom(QDomDocument &xmlDocument, QString name, QString value, QString language);
    QVector<QDomElement> lineToLineProperties(QDomDocument xmlDocument, Line line);
    QDomElement rawInsert(QString input);
    QDomElement ref(QDomDocument &xmlDocument, QString name, QString value);
    QDomProcessingInstruction createProcessingInformation(QDomDocument &xmlDocument, QString encoding);


    //VDV301 struktury
    QDomElement AdditionalTextMessage1_0(QString messageContent, bool isScrolling);

    QVector<QDomElement> Connections1_0(QDomDocument &xmlDocument, QVector<Connection> connectionList);


    //  QString CurrentDisplayContent1_0(int poradi, QVector<StopPointDestination> docasnySeznamZastavek, VehicleState stav);

    QDomElement DisplayContent1_0(QString tagName, QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex);
     QDomElement DoorOpenState(QDomDocument &xmlDocument, QString content);

    QDomElement FareZone1_0(QDomDocument &xmlDocument, QString shortName);
    QVector<QDomElement> FareZoneInformationStructure1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList);

    QDomElement MyOwnVehicleMode(QDomDocument &xmlDocument, QString mode, QString subMode);

    QDomElement StopPoint1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex, VehicleState vehicleState);
     QDomElement StopSequence1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList, VehicleState vehicleState);

    QDomElement RouteDeviation(QDomDocument &xmlDocument, QString content);

    QDomElement TimeStampTag1_0(QDomDocument &xmlDocument);
    QDomElement TripInformation1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int indexSpoje);

     QDomElement ViaPoint1_0(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);
    QDomElement Value(QDomDocument &xmlDocument, QString elementName, QString content);

    //WORK IN PROGRESS



     QString escapeHtml(QString input);
    QDateTime qTimeToQDateTimeToday(QTime input);
    QString qDomDocumentToQString(QDomDocument &input);
    QString qStringXmlEscape(QString input);

    Vdv301ViaPoint stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language);

     QDomElement namedElement(QDomDocument &xmlDocument, QString name, QString value);
    //QDomElement Connection2_3gen(QDomDocument &xmlDocument, Vdv301Connection connection);

    int isInRange(int index, int valueCount, QString nameOfFunction);

    QDomElement internationalTextTypeToDom(QDomDocument &xmlDocument, QString name, Vdv301InternationalText internationalText);

    QString vehicleRunToRunNumber(VehicleRun vehicleRun);
private:

    QDomCDATASection createEscapedValueCdata(QDomDocument &document, QString input);


public slots:
signals:
    void signalErrorMessage(QString message);

};

#endif // XMLCOMMON_H
