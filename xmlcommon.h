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


class XmlCommon : public QMainWindow
{
    //  Q_OBJECT
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
    QDomElement internationalTextType(QDomDocument &xmlDocument, QString name, QString value, QString language);
    QVector<QDomElement> lineToLineProperties(QDomDocument xmlDocument, Line line);
    QDomElement rawInsert(QString input);
    QDomElement ref(QDomDocument &xmlDocument, QString name, QString value);
    QDomElement xxxProperty2_2CZ1_0(QDomDocument &xmlDocument, QString propertyName, bool valueBoolean, QString valueName);
    QDomProcessingInstruction createProcessingInformation(QDomDocument &xmlDocument, QString encoding);


    //VDV301 struktury
    QDomElement AdditionalTextMessage1_0(QString messageContent, bool isScrolling);
    QDomElement AdditionalTextMessage2_2CZ1_0(QDomDocument &xmlDocument, QString messageContent);
    QDomElement AdditionalTextMessage2_2CZ1_0(QDomDocument &xmlDocument, QString type, QString headline, QString text);

    QVector<QDomElement> Connections1_0(QDomDocument &xmlDocument, QVector<Connection> connectionList);
    QVector<QDomElement> Connections2_2CZ1_0(QDomDocument &xmlDocument, QVector<Connection> connectionList);
    QVector<QDomElement> Connections2_3(QDomDocument &xmlDocument, QVector<Connection> connectionList);
    //  QString CurrentDisplayContent1_0(int poradi, QVector<StopPointDestination> docasnySeznamZastavek, VehicleState stav);

    QDomElement DisplayContent1_0(QString tagName, QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex);
    QDomElement DisplayContent2_2CZ1_0(QDomDocument &xmlDocument, QString tagName, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex);
    QDomElement DoorOpenState(QDomDocument &xmlDocument, QString content);

    QDomElement FareZone1_0(QDomDocument &xmlDocument, QString shortName);
    QDomElement FareZone2_2CZ1_0(QDomDocument &xmlDocument, QString shortName, QString longName, QString type, QString language);
    QVector<QDomElement> FareZoneInformationStructure2_2CZ1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList, QString language);
    QVector<QDomElement> FareZoneInformationStructure1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList);
    QDomElement FareZoneChange2_2CZ1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneListFrom, QVector<FareZone> fareZoneListTo, QString language);

    QDomElement MyOwnVehicleMode(QDomDocument &xmlDocument, QString mode, QString subMode);
    QDomElement MyOwnVehicleMode2_2CZ1_0(QDomDocument &xmlDocument, QString mainMode, QString subMode);

    QDomElement StopPoint1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex, VehicleState vehicleState);
    QDomElement StopPoint2_2CZ1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex);
    QDomElement StopSequence2_2CZ1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList);
    QDomElement StopSequence1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList, VehicleState vehicleState);

    QDomElement RouteDeviation(QDomDocument &xmlDocument, QString content);

    QDomElement TimeStampTag1_0(QDomDocument &xmlDocument);
    QDomElement TripInformation1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int indexSpoje);
    QDomElement TripInformation2_2CZ1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionsList, VehicleState vehicleState, int indexSpoje, bool followingTrip);

    QDomElement ViaPoint2_2CZ1_0(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);
    QDomElement ViaPoint1_0(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);
    QDomElement Value(QDomDocument &xmlDocument, QString elementName, QString content);

    //WORK IN PROGRESS
    QDomElement StopPoint2_3(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex);
    QDomElement ViaPoint2_3(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);


    QDomElement TripInformation2_3(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QDomElement StopSequence2_3(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList);
    QString xxxProperty2_3(QString icon, QString text, bool value);
    QString stopPropertiesToString2_3(StopPoint stopPoint);

    QDomElement DisplayContent2_3(QDomDocument &xmlDocument, QString tagName, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
    QString escapeHtml(QString input);
    QVector<QDomElement> FareZoneInformationStructure2_3(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList, QString language);
    QDomElement FareZone2_3(QDomDocument &xmlDocument, QString shortName);
    QDomElement AdditionalTextMessage2_3(QDomDocument &xmlDocument, QString messageContent);
    QVector<QDomElement> DisplayContentViaPointDestination2_3(QDomDocument &xmlDocument, QString tagName, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
    QDateTime qTimeToQDateTimeToday(QTime input);
    QString qDomDocumentToQString(QDomDocument &input);
    QString qStringXmlEscape(QString input);
    Vdv301Line lineToVdv301Line2_3(Line &line);

    Vdv301ViaPoint stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language);
    QVector<Vdv301DisplayContent> DisplayContentViaPointDestination2_3new(QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
    Vdv301StopPoint StopPoint2_3new(QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language, int currentStopIndex);
    Vdv301Trip TripInformation2_3new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QVector<Vdv301StopPoint> StopSequence2_3new(QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList);
    QDomElement StopPoint2_3gen(QDomDocument &xmlDocument, Vdv301StopPoint stopPointDestination);
    QDomElement DisplayContentViaPointDestination2_3gen(QDomDocument &xmlDocument, QString tagName, Vdv301DisplayContent displayContent);

    QDomElement ViaPoint2_3def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint);
    QDomElement namedElement(QDomDocument &xmlDocument, QString name, QString value);
    QDomElement Connection2_3gen(QDomDocument &xmlDocument, Vdv301Connection connection);
    QDomElement StopSequence2_3gen(QDomDocument &xmlDocument, QVector<Vdv301StopPoint> stopPointDestinationList);
    QDomElement TripInformation2_3gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip);
    QStringList FareZoneInformationStructure2_3new(QVector<FareZone> fareZoneList);
private:

    QDomCDATASection createEscapedValueCdata(QDomDocument &document, QString input);
    QString vehicleRunToRunNumber(VehicleRun vehicleRun);
signals:

public slots:
};

#endif // XMLCOMMON_H
