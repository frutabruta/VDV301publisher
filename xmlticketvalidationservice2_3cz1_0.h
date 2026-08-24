#ifndef XMLTICKETVALIDATIONSERVICE2_3CZ1_0_H
#define XMLTICKETVALIDATIONSERVICE2_3CZ1_0_H


#include "xmlcommon2_3cz1_0.h"
//#include "VDV301DataStructures/vdv301vehicleinformationgroup.h"
#include "VDV301DataStructures/vdv301vehicledata.h"

class XmlTicketValidationService2_3CZ1_0 : public XmlCommon2_3CZ1_0
{
public:
    XmlTicketValidationService2_3CZ1_0();
    Vdv301StopPoint currentTariffStop(StopPointDestination stopPointDestination, int stopPointIterator);
    QString currentTariffStopGen(QDomDocument xmlDocument, Vdv301StopPoint2_3CZ1_0 stopPointDestination, QString tripRef);
    QString razziaGen(QDomDocument xmlDocument, Vdv301Enumerations::TicketRazziaInformationEnumeration razziaState);
    QString vehicleDataGen(QDomDocument xmlDocument, Vdv301VehicleData vehicleData);
    Vdv301VehicleData vehicleData(VehicleState vehicleState);
};

#endif // XMLTICKETVALIDATIONSERVICE2_3CZ1_0_H
