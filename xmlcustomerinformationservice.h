#ifndef XMLCUSTOMERINFORMATIONSERVICE_H
#define XMLCUSTOMERINFORMATIONSERVICE_H
#include "xmlcommon.h"
#include <QObject>

class XmlCustomerInformationService : XmlCommon
{
public:
    XmlCustomerInformationService();
    // QString AllData1_0(QVector<StopPointDestination> docasnySeznamZastavek, QString doorState, QString locationState, QVector<PrestupMPV> prestupy, CestaUdaje stav);

    QString AllData1_0(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState);
    QString AllData2_2CZ1_0(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState);
    QString AllData_empty_1_0(QDomDocument xmlDocument);
    QString AllData_empty2_2CZ1_0(QDomDocument xmlDocument);
    QString CurrentDisplayContent1_0(QDomDocument xmlDocument, QVector<StopPointDestination> stopPointDestinationList, VehicleState vehicleState);

    QString CurrentDisplayContent2_2CZ1_0(QDomDocument xmlDocument, QVector<StopPointDestination> stopPointDestinationList, VehicleState vehicleState);

    //rozdelano
    QString CurrentDisplayContent2_4(QDomDocument xmlDocument, QVector<StopPointDestination> stopPointDestinationList, VehicleState vehicleState);
    QString AllData2_4(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState);

private:

};

#endif // XMLCUSTOMERINFORMATIONSERVICE_H
