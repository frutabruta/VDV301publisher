#ifndef XMLCUSTOMERINFORMATIONSERVICE2_3_H
#define XMLCUSTOMERINFORMATIONSERVICE2_3_H

#include  "xmlcustomerinformationservice.h"
#include "xmlcommon2_3.h"
class XmlCustomerInformationService2_3 : public XmlCustomerInformationService
{
public:
    XmlCustomerInformationService2_3();
    XmlCommon2_3 xmlCommon2_3;
    QString AllData2_3(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState);
    QString CurrentDisplayContent2_3(QDomDocument xmlDocument, QVector<StopPointDestination> stopPointDestinationList, VehicleState vehicleState);
};

#endif // XMLCUSTOMERINFORMATIONSERVICE2_3_H
