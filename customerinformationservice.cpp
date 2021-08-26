#include "customerinformationservice.h"
#include "httpsluzba.h"


CustomerInformationService::CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
    connect(timer, &QTimer::timeout, this, &CustomerInformationService::tedOdesliNaPanelySlot);
    timer->start(60000);

}



void CustomerInformationService::tedOdesliNaPanelySlot()
{
    qDebug()<<"CustomerInformationService::tedOdesliNaPanely()";
    aktualizaceIntProm(prestupyDomDocumentInterni,stavInterni,seznamZastavekInterni);
}
void CustomerInformationService::aktualizaceIntProm(QDomDocument prestupyDomDocument, CestaUdaje &stav, QVector<ZastavkaCil>  seznamZastavek ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceIntProm"<<nazevSluzbyInterni<<" "<<globVerze;
    QByteArray zpracovanoMPV="";
    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";
    qDebug()<<"1";
    if (globVerze=="2.2CZ1.0")
    {
        qDebug()<<"2";
        //bodyAllData=TestXmlGenerator.AllData2_2CZ1_0( stav.indexAktZastavky,seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupyDomDocument);
        bodyAllData=TestXmlGenerator.AllData2_2CZ1_0(seznamZastavek,prestupyDomDocument,stav);
        bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek,stav);
    }
    else
    {
        qDebug()<<"3";
        bodyAllData=TestXmlGenerator.AllData1_0( seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupyDomDocument,stav);
        qDebug()<<"3,5";
        bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek, stav);
    }

    qDebug()<<"4";
    this->nastavObsahTela("AllData",bodyAllData);
    this->nastavObsahTela("CurrentDisplayContent",bodyCurrentDisplayContent);
    this->asocPoleDoServeru(obsahTelaPole);
    qDebug()<<"5";
    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }
    qDebug()<<"6";
}

void CustomerInformationService::aktualizaceObsahuSluzby(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector<ZastavkaCil>  seznamZastavek ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceInternichPromennychOdeslat";
    prestupyDomDocumentInterni=prestupyDomDocument;
    stavInterni=stav;
    seznamZastavekInterni=seznamZastavek;
    tedOdesliNaPanelySlot();
    timer->start(60000);


}
