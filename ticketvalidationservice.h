#ifndef TICKETVALIDATIONSERVICE_H
#define TICKETVALIDATIONSERVICE_H

#include "httpsluzba.h"
#include "../prestupmpv.h"

class TicketValidationService : public HttpSluzba
{
public:
    TicketValidationService();
    explicit TicketValidationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);
   // void aktualizaceInternichPromennychOdeslat(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector seznamZastavek);
    //void aktualizaceInternichPromennychOdeslat();
    void aktualizaceObsahuSluzby(QVector<prestupMPV> prestupy, int verzeVDV301, CestaUdaje &stav, QVector<ZastavkaCil>  seznamZastavek);
    void tedOdesliNaPanelySlot();
    CestaUdaje stavInterni;
    QVector<ZastavkaCil> seznamZastavekInterni ;


private:
    void aktualizaceIntProm(QVector<prestupMPV> prestupy, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);
    //QDomDocument prestupyDomDocumentInterni;
    QVector<prestupMPV> prestupyInterni;
};

#endif // TICKETVALIDATIONSERVICE_H
