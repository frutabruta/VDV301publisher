#ifndef XMLCOMMON2_2CZ1_0_H
#define XMLCOMMON2_2CZ1_0_H

#include  "xmlcommon.h"

class XmlCommon2_2CZ1_0 : public XmlCommon
{
public:
    XmlCommon2_2CZ1_0();
    QDomElement AdditionalTextMessage2_2CZ1_0(QDomDocument &xmlDocument, QString messageContent);
    QDomElement AdditionalTextMessage2_2CZ1_0(QDomDocument &xmlDocument, QString type, QString headline, QString text);
    QVector<QDomElement> Connections2_2CZ1_0(QDomDocument &xmlDocument, QVector<Connection> connectionList);
    QDomElement DisplayContent2_2CZ1_0(QDomDocument &xmlDocument, QString tagName, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex);
    QDomElement FareZone2_2CZ1_0(QDomDocument &xmlDocument, QString shortName, QString longName, QString type, QString language);
    QDomElement FareZoneChange2_2CZ1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneListFrom, QVector<FareZone> fareZoneListTo, QString language);
    QVector<QDomElement> FareZoneInformationStructure2_2CZ1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList, QString language);
    QDomElement MyOwnVehicleMode2_2CZ1_0(QDomDocument &xmlDocument, QString mainMode, QString subMode);
    QDomElement TripInformation2_2CZ1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionsList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QDomElement StopSequence2_2CZ1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList);
    QDomElement StopPoint2_2CZ1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex);
    QDomElement xxxProperty2_2CZ1_0(QDomDocument &xmlDocument, QString propertyName, bool valueBoolean, QString valueName);
    QDomElement ViaPoint2_2CZ1_0(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);
    QVector<QDomElement> lineToLineProperties(QDomDocument xmlDocument, Line line);
};

#endif // XMLCOMMON2_2CZ1_0_H
