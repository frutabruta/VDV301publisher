#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"
#include "../prestupmpv.h"

class CustomerInformationService : public HttpSluzba
{
public:
    //konstruktor
    explicit CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    //struktury
    QVector<prestupMPV> prestupyInterni;
    QVector<Spoj> seznamSpojuInterni;
    CestaUdaje stavInterni;

    //funkce
    void tedOdesliNaPanelySlot();
    void aktualizaceIntProm(QVector<prestupMPV> prestupy, CestaUdaje &stav, QVector<Spoj> seznamSpoju );
    void aktualizaceObsahuSluzby(QVector<prestupMPV> prestup, CestaUdaje &stav);

signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
