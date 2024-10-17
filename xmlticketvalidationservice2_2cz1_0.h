#ifndef XMLTICKETVALIDATIONSERVICE2_2CZ1_0_H
#define XMLTICKETVALIDATIONSERVICE2_2CZ1_0_H

#include "xmlticketvalidationservice.h"
#include "xmlcommon2_2cz1_0.h"
class XmlTicketValidationService2_2CZ1_0 : public XmlTicketValidationService
{
public:
    XmlTicketValidationService2_2CZ1_0();
    XmlCommon2_2CZ1_0 xmlCommon2_2CZ1_0;
    QString TicketValidationService_GetVehicleDataResponse2_2CZ1_0(QDomDocument xmlDocument, VehicleState vehicleState);
    QString TicketValidationService_GetRazziaResponse2_2CZ1_0(QDomDocument xmlDocument, VehicleState vehicleState);
    QString TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(QDomDocument xmlDocument, int currentStopIndex, QVector<StopPointDestination> stopPointDestinationList, QVector<Connection> connectionList);
};

#endif // XMLTICKETVALIDATIONSERVICE2_2CZ1_0_H
