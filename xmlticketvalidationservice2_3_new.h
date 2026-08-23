#ifndef XMLTICKETVALIDATIONSERVICE2_3_NEW_H
#define XMLTICKETVALIDATIONSERVICE2_3_NEW_H


#include "xmlcommon2_3_new.h"
#include "VDV301DataStructures/vdv301vehicleinformationgroup.h"
#include "VDV301DataStructures/vdv301vehicledata.h"

class XmlTicketValidationService2_3_new : public XmlCommon2_3_new
{
public:
    XmlTicketValidationService2_3_new();
    Vdv301StopPoint currentTariffStop(StopPointDestination stopPointDestination, int stopPointIterator);
    QString currentTariffStopGen(QDomDocument xmlDocument, Vdv301StopPoint stopPointDestination, QString tripRef);
    QString razziaGen(QDomDocument xmlDocument, Vdv301Enumerations::TicketRazziaInformationEnumeration razziaState);
    QString vehicleDataGen(QDomDocument xmlDocument, Vdv301VehicleData vehicleData);
    Vdv301VehicleData vehicleData(VehicleState vehicleState);
};

#endif // XMLTICKETVALIDATIONSERVICE2_3_NEW_H
