#ifndef XMLTICKETVALIDATIONSERVICE2_3_NEW_H
#define XMLTICKETVALIDATIONSERVICE2_3_NEW_H


#include "xmlcommon2_3_new.h"

class XmlTicketValidationService2_3_new : public XmlCommon2_3_new
{
public:
    XmlTicketValidationService2_3_new();
    XmlCommon2_3_new xmlCommon2_3_new;
    Vdv301StopPoint currentTariffStop(StopPointDestination stopPointDestination, int stopPointIterator);
    QString currentTariffStopGen(QDomDocument xmlDocument, Vdv301StopPoint stopPointDestination, QString tripRef);
};

#endif // XMLTICKETVALIDATIONSERVICE2_3_NEW_H
