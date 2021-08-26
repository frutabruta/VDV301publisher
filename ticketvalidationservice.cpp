#include "ticketvalidationservice.h"



TicketValidationService::TicketValidationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
   connect(timer, &QTimer::timeout, this, &TicketValidationService::tedOdesliNaPanelySlot);
   timer->start(60000);

}




void TicketValidationService::aktualizaceIntProm(QDomDocument prestupyDomDocument, CestaUdaje &stav, QVector<ZastavkaCil>  seznamZastavek ) //novy
{
    qDebug()<<"TicketValidationService::aktualizaceIntProm"<<nazevSluzbyInterni<<" "<<globVerze;
    QByteArray zpracovanoMPV="";
    QString bodyCurrentTariffStopResponse="";
    QString bodyVehicleDataResponse="";
    QString bodyRazziaResponse="";




    qDebug()<<"1";
    if (globVerze=="2.2CZ1.0")
    {
        qDebug()<<"2";
        //bodyAllData=TestXmlGenerator.AllData2_2CZ1_0( stav.indexAktZastavky,seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupyDomDocument);
        bodyCurrentTariffStopResponse=TestXmlGenerator.TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(stav.indexAktZastavky,seznamZastavek,stav.aktlinka,stav.doorState,stav.locationState,prestupyDomDocument);
        bodyVehicleDataResponse=TestXmlGenerator.TicketValidationService_GetVehicleDataResponse2_2CZ1_0(stav);
        bodyRazziaResponse=TestXmlGenerator.TicketValidationService_GetRazziaResponse2_2CZ1_0(stav);

                //bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek,stav);
        //bodyVehicleDataResponse=TestXmlGenerator.tick

    }
    else
    {
        /*
        qDebug()<<"3";
        bodyAllData=TestXmlGenerator.AllData1_0( seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupyDomDocument,stav);
        qDebug()<<"3,5";
        bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek, stav);
        */
    }

    qDebug()<<"4";
    this->nastavObsahTela("CurrentTariffStopResponse",bodyCurrentTariffStopResponse);
    this->nastavObsahTela("VehicleDataResponse",bodyVehicleDataResponse);
    this->nastavObsahTela("RazziaResponse",bodyRazziaResponse);
    this->asocPoleDoServeru(obsahTelaPole);
    qDebug()<<"5";
    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }
    qDebug()<<"6";
}



void TicketValidationService::tedOdesliNaPanelySlot()
{
    qDebug()<<"CustomerInformationService::tedOdesliNaPanely()";
    aktualizaceIntProm(prestupyDomDocumentInterni,stavInterni,seznamZastavekInterni);
}

void TicketValidationService::aktualizaceObsahuSluzby(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector<ZastavkaCil>  seznamZastavek ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceInternichPromennychOdeslat";
    prestupyDomDocumentInterni=prestupyDomDocument;
    stavInterni=stav;
    seznamZastavekInterni=seznamZastavek;
    tedOdesliNaPanelySlot();
    timer->start(60000);


}
