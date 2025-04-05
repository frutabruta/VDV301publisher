#ifndef XMLCOMMONVEHICLESTATE_H
#define XMLCOMMONVEHICLESTATE_H
#include "xmlcommon.h"


#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vehiclestate.h"
#include "VDV301DataStructures/farezone.h"


class XmlCommonVehicleState : XmlCommon
{
public:
    XmlCommonVehicleState();
    QVector<QDomElement> Connections1_0(QDomDocument &xmlDocument, QVector<Connection> connectionList);
    QDomElement DisplayContent1_0(QString tagName, QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex);
    QVector<QDomElement> FareZoneInformationStructure1_0(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList);
    QDomElement StopPoint1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex, VehicleState vehicleState);
    QDomElement StopSequence1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList, VehicleState vehicleState);
    QDomElement TripInformation1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int indexSpoje);
    QString vehicleRunToRunNumber(VehicleRun vehicleRun);
    QDomElement ViaPoint1_0(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);
};

#endif // XMLCOMMONVEHICLESTATE_H
