#ifndef XMLCOMMON2_3_NEW_H
#define XMLCOMMON2_3_NEW_H
#include "xmlcommon2_3.h"
#include "VDV301DataStructures/vdv301trip.h"

class XmlCommon2_3_new : public XmlCommon// : public XmlCommon2_3
{
public:
    XmlCommon2_3_new();

    DisplayContentClass lcdClass=DisplayContentInterior;

    bool addLineStyle=true; //setting to enable/disable line coloring using inline formatting

    QDomElement ViaPoint2_3def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint);
    QDomElement Connection2_3gen(QDomDocument &xmlDocument, Vdv301Connection connection);
    QDomElement TripInformation2_3gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip);
    QDomElement DisplayContentViaPointDestination2_3gen(QDomDocument &xmlDocument, QString tagName, Vdv301DisplayContent displayContent);
    QVector<Vdv301DisplayContent> DisplayContentViaPointDestination2_3new(QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
    QStringList FareZoneInformationStructure2_3new(QVector<FareZone> fareZoneList);
    Vdv301Trip TripInformation2_3new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QVector<Vdv301StopPoint> StopSequence2_3new(QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList);
    QDomElement StopSequence2_3gen(QDomDocument &xmlDocument, QVector<Vdv301StopPoint> stopPointDestinationList);
    Vdv301StopPoint StopPoint2_3new(QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language, int currentStopIndex);
    QDomElement StopPoint2_3gen(QDomDocument &xmlDocument, Vdv301StopPoint vdv301StopPoint);
    Vdv301ViaPoint stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language);
    Vdv301Connection connectionToVdv301Connection(Connection connection, DisplayContentClass displayClass); //unused
    QString stopPropertiesToString2_3(StopPoint stopPoint);
    QString xxxProperty2_3(QString icon, QString text, bool value);
    Vdv301Line lineToVdv301Line2_3(Line &line, bool addStyle);
    Vdv301Line lineToVdv301Line2_3(Line &line, QString subMode, bool addStyle);
    QString lineToIcon(Line &line, QString subMode);
};

#endif // XMLCOMMON2_3_NEW_H
