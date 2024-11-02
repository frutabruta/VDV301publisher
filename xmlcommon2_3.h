#ifndef XMLCOMMON2_3_H
#define XMLCOMMON2_3_H

#include "xmlcommon.h"

class XmlCommon2_3 : public XmlCommon
{
    //   Q_OBJECT
public:
    XmlCommon2_3();

    bool addLineStyle=true; //setting to enable/disable line coloring using inline formatting

    QVector<QDomElement> Connections2_3(QDomDocument &xmlDocument, QVector<Connection> connectionList);
    QDomElement FareZone2_3(QDomDocument &xmlDocument, QString shortName);
    QVector<QDomElement> FareZoneInformationStructure2_3(QDomDocument &xmlDocument, QVector<FareZone> fareZoneList, QString language);
    QDomElement DisplayContent2_3(QDomDocument &xmlDocument, QString tagName, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass); //unused
    QVector<QDomElement> DisplayContentViaPointDestination2_3(QDomDocument &xmlDocument, QString tagName, QVector<StopPointDestination> stopPointDestinationList, QString language, int stopPointIterator, int currentStopIndex, DisplayContentClass displayContentClass);
    Vdv301Line lineToVdv301Line2_3(Line &line, QString subMode, bool addStyle);
    QDomElement TripInformation2_3(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip);
    QDomElement StopSequence2_3(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language, int currentStopIndex, QVector<Connection> connectionList);
    QDomElement StopPoint2_3(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, int stopPointIterator, QVector<Connection> connectionList, QString language, int currentStopIndex);
    QDomElement ViaPoint2_3(QDomDocument &xmlDocument, StopPoint viaPoint, QString language);
    QDomElement ViaPoint2_3def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint); //unused
    QDomElement AdditionalTextMessage2_3(QDomDocument &xmlDocument, QString messageContent); //unused
    QString stopPropertiesToString2_3(StopPoint stopPoint);
    QString xxxProperty2_3(QString icon, QString text, bool value);

    Vdv301Line lineToVdv301Line2_3(Line &line, bool addStyle);
};

#endif // XMLCOMMON2_3_H
