#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"
#include "VDV301struktury/prestupmpv.h"

#include "xmlcustomerinformationservice.h"

class CustomerInformationService : public HttpSluzba
{
public:
    //konstruktor
    explicit CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    //instance trid

    //struktury

    //funkce
    void aktualizaceObsahuSluzby(QVector<PrestupMPV> prestup, CestaUdaje &stav);
    void mimoVydej();

private:

    //instance trid
    XmlCustomerInformationService xmlGenerator;
    //promenne
    QVector<PrestupMPV> prestupyInterni;
    QVector<Spoj> seznamSpojuInterni;
    CestaUdaje stavInterni;


    //funkce
    void aktualizaceIntProm(QVector<PrestupMPV> prestupy, CestaUdaje &stav, QVector<Spoj> seznamSpoju );
    void aktualizaceIntPromEmpty(CestaUdaje &stav, QVector<Spoj> seznamSpoju);







public slots:
    void slotTedOdesliNaPanely();

signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
