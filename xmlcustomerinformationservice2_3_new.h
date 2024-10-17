#ifndef XMLCUSTOMERINFORMATIONSERVICE2_3_NEW_H
#define XMLCUSTOMERINFORMATIONSERVICE2_3_NEW_H

#include "xmlcustomerinformationservice2_3.h"
#include "xmlcommon2_3_new.h"
class XmlCustomerInformationService2_3_new : public XmlCustomerInformationService2_3
{
public:
    XmlCustomerInformationService2_3_new();
    XmlCommon2_3_new xmlCommon2_3_new;
    Vdv301AllData AllData2_3new(QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, QVector<Vdv301DisplayContent> globalDisplayContentList);
    QString AllData2_3gen(QDomDocument xmlDocument, Vdv301AllData allData);
};

#endif // XMLCUSTOMERINFORMATIONSERVICE2_3_NEW_H
