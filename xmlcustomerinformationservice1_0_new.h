#ifndef XMLCUSTOMERINFORMATIONSERVICE1_0_NEW_H
#define XMLCUSTOMERINFORMATIONSERVICE1_0_NEW_H

#include "xmlcommon1_0_new.h"
#include "VDV301DataStructures/vdv301alldata.h"

class XmlCustomerInformationService1_0_new
{
public:
    XmlCustomerInformationService1_0_new();


    XmlCommon1_0_new xmlCommon1_0_new;


    Vdv301AllData AllData1_0new(QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, QVector<Vdv301DisplayContent> globalDisplayContentList);
    QString AllData1_0gen(QDomDocument xmlDocument, Vdv301AllData allData);
    QVector<Vdv301DisplayContent> CurrentDisplayContentFromAllData1_0new(Vdv301AllData vdv301AllData);
    QString CurrentDisplayContent1_0gen(QDomDocument xmlDocument, QVector<Vdv301DisplayContent> vdv301displayContentList);

};

#endif // XMLCUSTOMERINFORMATIONSERVICE1_0_NEW_H
