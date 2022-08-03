#ifndef XMLTICKETVALIDATIONSERVICE_H
#define XMLTICKETVALIDATIONSERVICE_H
#include "xmlcommon.h"

class XmlTicketValidationService : XmlCommon
{
public:
    XmlTicketValidationService();
    QString TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(int poradi, QVector<ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<PrestupMPV> prestupy);
    QString TicketValidationService_GetVehicleDataResponse2_2CZ1_0(CestaUdaje stav);
    QString TicketValidationService_GetRazziaResponse2_2CZ1_0(CestaUdaje stav);
};

#endif // XMLTICKETVALIDATIONSERVICE_H
