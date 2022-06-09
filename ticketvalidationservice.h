#ifndef TICKETVALIDATIONSERVICE_H
#define TICKETVALIDATIONSERVICE_H

#include "httpsluzba.h"
#include "../prestupmpv.h"

class TicketValidationService : public HttpSluzba
{
public:
    TicketValidationService();
    explicit TicketValidationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    void aktualizaceObsahuSluzby(QVector<PrestupMPV> prestupy, CestaUdaje &stav);
    void tedOdesliNaPanelySlot();


    CestaUdaje stavInterni;
    QVector<ZastavkaCil> seznamZastavekInterni ;


private:
    void aktualizaceIntProm(QVector<PrestupMPV> prestupy, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);
    QVector<PrestupMPV> prestupyInterni;
};

#endif // TICKETVALIDATIONSERVICE_H
