#ifndef XMLCOMMON2_3CZ1_0_H
#define XMLCOMMON2_3CZ1_0_H


#include "xmlcommon2_3_new.h"
#include "VDV301DataStructures/vdv301trip2_3cz1_0.h"
#include "VDV301DataStructures/vdv301stoppoint.h"
class XmlCommon2_3CZ1_0 : public XmlCommon2_3_new
{
public:
    XmlCommon2_3CZ1_0();
    QDomElement TripInformation2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301Trip2_3CZ1_0 trip, bool followingTrip);
    QDomElement FareZoneChange2_3CZ1_0gen(QDomDocument &xmlDocument, QVector<Vdv301InternationalText> fareZoneFrom, QVector<Vdv301InternationalText> fareZoneTo);
    QDomElement StopSequence2_3CZ1_0gen(QDomDocument &xmlDocument, QVector<Vdv301StopPoint2_3CZ1_0> stopPointDestinationList);
    Vdv301StopPoint2_3CZ1_0 StopPoint2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language, int currentStopIndex);
    Vdv301Trip2_3CZ1_0 TripInformation2_3CZ1_0new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QVector<Vdv301StopPoint2_3CZ1_0> StopSequence2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList);
    QDomElement StopPoint2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301StopPoint2_3CZ1_0 stopPointDestination);
    QStringList FareZoneInformationStructure2_3CZ1_0new(QVector<FareZone> fareZoneList);
};

#endif // XMLCOMMON2_3CZ1_0_H
