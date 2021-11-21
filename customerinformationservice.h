#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"
#include "../prestupmpv.h"

class CustomerInformationService : public HttpSluzba
{
public:
    explicit CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    void tedOdesliNaPanelySlot();

    void aktualizaceIntProm(QVector<prestupMPV> prestupy, CestaUdaje &stav, QVector<Spoj> seznamSpoju );
    //QDomDocument prestupyDomDocumentInterni;
    QVector<prestupMPV> prestupyInterni;
    CestaUdaje stavInterni;

    //QVector<ZastavkaCil> seznamZastavekInterni ;
    QVector<Spoj> seznamSpojuInterni;
    void aktualizaceObsahuSluzby(QVector<prestupMPV> prestup, CestaUdaje &stav);
signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
