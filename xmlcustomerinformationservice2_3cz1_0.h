#ifndef XMLCUSTOMERINFORMATIONSERVICE2_3CZ1_0_H
#define XMLCUSTOMERINFORMATIONSERVICE2_3CZ1_0_H


#include "xmlcustomerinformationservice2_3_new.h"
#include "xmlcommon2_3cz1_0.h"
#include "VDV301DataStructures/vdv301alldata2_3cz1_0.h"
class XmlCustomerInformationService2_3CZ1_0 : public XmlCustomerInformationService2_3_new
{
public:
    XmlCustomerInformationService2_3CZ1_0();
    XmlCommon2_3CZ1_0 xmlCommon2_3CZ1_0;

    QString AllData2_3CZ1_0gen(QDomDocument xmlDocument, Vdv301AllData2_3CZ1_0 allData);
    Vdv301AllData2_3CZ1_0 AllData2_3CZ1_0new(QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, QVector<Vdv301DisplayContent> globalDisplayContentList);
};

#endif // XMLCUSTOMERINFORMATIONSERVICE2_3CZ1_0_H
