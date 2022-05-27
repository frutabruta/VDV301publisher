#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"
#include "../prestupmpv.h"
#include "./mainwindowpomocne.h"

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

    void aktualizaceIntProm(QVector<prestupMPV> prestupy, CestaUdaje &stav, QVector<Spoj> seznamSpoju );
    void aktualizaceObsahuSluzby(QVector<prestupMPV> prestup, CestaUdaje &stav);

    void aktualizaceIntPromEmpty(CestaUdaje &stav, QVector<Spoj> seznamSpoju);
public slots:
    void slotTedOdesliNaPanely();

signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
