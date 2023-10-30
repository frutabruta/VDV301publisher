#ifndef XMLTICKETVALIDATIONSERVICE_H
#define XMLTICKETVALIDATIONSERVICE_H
#include "xmlcommon.h"

class XmlTicketValidationService : XmlCommon
{
public:
    XmlTicketValidationService();
    QString TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(QDomDocument xmlDocument, int currentStopIndex, QVector<StopPointDestination> stopPointDestinationList, QVector<Connection> connectionList);
    QString TicketValidationService_GetVehicleDataResponse2_2CZ1_0(QDomDocument xmlDocument, VehicleState vehicleState);
    QString TicketValidationService_GetRazziaResponse2_2CZ1_0(QDomDocument xmlDocument, VehicleState vehicleState);
};

#endif // XMLTICKETVALIDATIONSERVICE_H
