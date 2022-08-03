#ifndef TICKETVALIDATIONSERVICE_H
#define TICKETVALIDATIONSERVICE_H

#include "httpsluzba.h"
#include "xmlticketvalidationservice.h"
#include "VDV301struktury/prestupmpv.h"

class TicketValidationService : public HttpSluzba
{
public:
    TicketValidationService();
    explicit TicketValidationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    XmlTicketValidationService xmlGenerator;

    void aktualizaceObsahuSluzby(QVector<PrestupMPV> prestupy, CestaUdaje &stav);
    void tedOdesliNaPanelySlot();


    CestaUdaje stavInterni;
    QVector<ZastavkaCil> seznamZastavekInterni ;


private:
    void aktualizaceIntProm(QVector<PrestupMPV> prestupy, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);
    QVector<PrestupMPV> prestupyInterni;
};

#endif // TICKETVALIDATIONSERVICE_H
