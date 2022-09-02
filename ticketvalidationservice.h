#ifndef TICKETVALIDATIONSERVICE_H
#define TICKETVALIDATIONSERVICE_H

#include "httpsluzba.h"
#include "xmlticketvalidationservice.h"
#include "VDV301struktury/prestupmpv.h"

class TicketValidationService : public HttpSluzba
{
public:
    //konstruktor
    TicketValidationService();    
    explicit TicketValidationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);


    //instance knihoven


    //promenne


    //funkce

private:

    //instance knihoven
    XmlTicketValidationService xmlGenerator;

    //promenne
    CestaUdaje stavInterni;
    QVector<ZastavkaCil> seznamZastavekInterni ;

    //funkce
    void aktualizaceIntProm(QVector<PrestupMPV> prestupy, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);
    void aktualizaceObsahuSluzby(QVector<PrestupMPV> prestupy, CestaUdaje &stav);

    QVector<PrestupMPV> prestupyInterni;

private slots:
    void slotTedOdesliNaPanely();
};

#endif // TICKETVALIDATIONSERVICE_H
