#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"
#include "../prestupmpv.h"

class CustomerInformationService : public HttpSluzba
{
public:
    explicit CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    void tedOdesliNaPanelySlot();

    void aktualizaceIntProm(QVector<prestupMPV> prestupy, CestaUdaje &stav, QVector<Trip>  seznamTripu );
    //QDomDocument prestupyDomDocumentInterni;
    QVector<prestupMPV> prestupyInterni;
    CestaUdaje stavInterni;

    //QVector<ZastavkaCil> seznamZastavekInterni ;
    QVector<Trip> seznamTripuInterni;
    void aktualizaceObsahuSluzby(QVector<prestupMPV> prestup, int verzeVDV301, CestaUdaje &stav, QVector<Trip> seznamTripu);
signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
