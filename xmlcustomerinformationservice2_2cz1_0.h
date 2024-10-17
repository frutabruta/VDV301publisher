#ifndef XMLCUSTOMERINFORMATIONSERVICE2_2CZ1_0_H
#define XMLCUSTOMERINFORMATIONSERVICE2_2CZ1_0_H

#include "xmlcustomerinformationservice.h"
#include "xmlcommon2_2cz1_0.h"
class XmlCustomerInformationService2_2CZ1_0 : public XmlCustomerInformationService
{
public:
    XmlCustomerInformationService2_2CZ1_0();
    XmlCommon2_2CZ1_0 xmlCommon2_2CZ1_0;
    QString CurrentDisplayContent2_2CZ1_0(QDomDocument xmlDocument, QVector<StopPointDestination> stopPointDestinationList, VehicleState vehicleState);
    QString AllData_empty2_2CZ1_0(QDomDocument xmlDocument);
    QString AllData2_2CZ1_0(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState);
};

#endif // XMLCUSTOMERINFORMATIONSERVICE2_2CZ1_0_H
