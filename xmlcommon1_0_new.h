#ifndef XMLCOMMON1_0_NEW_H
#define XMLCOMMON1_0_NEW_H

#include "xmlcommon.h"
#include "VDV301DataStructures/vdv301trip.h"
#include "VDV301DataStructures/vehiclestate.h"

class XmlCommon1_0_new : public XmlCommon
{
public:

    XmlCommon1_0_new();

    DisplayContentClass lcdClass=DisplayContentInterior;

    bool addLineStyle=false; //setting to enable/disable line coloring using inline formatting

    bool addIconsInline=false;

    bool addIconsWuppertal=true;


    Vdv301Connection connectionToVdv301Connection(Connection connection, DisplayContentClass displayClass);
    QDomElement Connection1_0gen(QDomDocument &xmlDocument, Vdv301Connection connection);
    QDomElement DisplayContentViaPointDestination1_0gen(QDomDocument &xmlDocument, QString tagName, Vdv301DisplayContent displayContent);
    QVector<Vdv301DisplayContent> DisplayContentViaPointDestination1_0new(QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
    QStringList FareZoneInformationStructure1_0new(QVector<FareZone> fareZoneList);
    QString xxxProperty1_0(QString icon, QString text, bool value);
    QString lineToIcon(Line &line, QString subMode);
    Vdv301Line lineToVdv301Line1_0(Line &line, bool addStyle);
    Vdv301Line lineToVdv301Line1_0(Line &line, QString subMode, bool addStyle);
    QString stopPropertiesToString1_0(StopPoint stopPoint);
    Vdv301StopPoint StopPoint1_0new(QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language, int currentStopIndex);
    QDomElement StopPoint1_0gen(QDomDocument &xmlDocument, Vdv301StopPoint vdv301StopPoint);
    QVector<Vdv301StopPoint> StopSequence1_0new(QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList);
    QDomElement StopSequence1_0gen(QDomDocument &xmlDocument, QVector<Vdv301StopPoint> stopPointDestinationList);
    Vdv301ViaPoint stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language);
    QDomElement TripInformation1_0gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip);
    Vdv301Trip TripInformation1_0new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QDomElement ViaPoint1_0def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint);
    QString vehicleRunToRunNumber(VehicleRun vehicleRun); //unused
};

#endif // XMLCOMMON1_0_NEW_H
