#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"

class CustomerInformationService : public HttpSluzba
{
public:
    explicit CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    void tedOdesliNaPanelySlot();

    void aktualizaceIntProm(QDomDocument prestupyDomDocument, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);
    QDomDocument prestupyDomDocumentInterni;
    CestaUdaje stavInterni;

    QVector<ZastavkaCil> seznamZastavekInterni ;
    void aktualizaceObsahuSluzby(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector <ZastavkaCil> seznamZastavek);
signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
