#ifndef XMLCOMMON2_3CZ1_0_H
#define XMLCOMMON2_3CZ1_0_H


#include "xmlcommon2_3_new.h"
#include "VDV301DataStructures/vdv301trip2_3cz1_0.h"
#include "VDV301DataStructures/vdv301additionalannouncement2_3cz1_0.h"
class XmlCommon2_3CZ1_0 : public XmlCommon2_3_new
{
public:
    bool useDelay=true;
    XmlCommon2_3CZ1_0();
    QDomElement TripInformation2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301Trip2_3CZ1_0 trip, bool followingTrip); //unused?
    QDomElement FareZoneChange2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301FareZoneChange2_3CZ1_0 vdv301FareZoneChange);
    QDomElement StopSequence2_3CZ1_0gen(QDomDocument &xmlDocument, QVector<Vdv301StopPoint2_3CZ1_0> stopPointDestinationList);
    Vdv301StopPoint2_3CZ1_0 StopPoint2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language, int currentStopIndex, int delaySeconds=0);
    Vdv301Trip2_3CZ1_0 TripInformation2_3CZ1_0new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip); //unused?
    QVector<Vdv301StopPoint2_3CZ1_0> StopSequence2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList,int delaySeconds=0);
    QDomElement StopPoint2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301StopPoint2_3CZ1_0 stopPointDestination);
    QStringList FareZoneInformationStructure2_3CZ1_0new(QVector<FareZone> fareZoneList);
    QVector<Vdv301InternationalText> fareZoneListToVdv301FareZoneList(QVector<FareZone> fareZoneList, QString language);
    QString vehicleRunToRunNumber(VehicleRun vehicleRun);
    QDomElement AddtitionalAnnouncement2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301AdditionalAnnouncement2_3CZ1_0 vdv301AdditionalAnnouncement);

    int minutesBetweenStops(StopPoint firstStop, StopPoint secondStop);
    QVector<Vdv301DisplayContent2_3CZ1_0> DisplayContentViaPointDestination2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
};

#endif // XMLCOMMON2_3CZ1_0_H
