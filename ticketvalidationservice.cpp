#include "ticketvalidationservice.h"



TicketValidationService::TicketValidationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
   connect(timer, &QTimer::timeout, this, &TicketValidationService::slotTedOdesliNaPanely);
   timer->start(60000);

}




void TicketValidationService::aktualizaceIntProm(QVector<PrestupMPV> prestupy, CestaUdaje &stav, QVector<ZastavkaCil>  seznamZastavek ) //novy
{
    qDebug()<<"TicketValidationService::aktualizaceIntProm"<<nazevSluzbyInterni<<" "<<globVerze;
   // QByteArray zpracovanoMPV="";
    QString bodyCurrentTariffStopResponse="";
    QString bodyVehicleDataResponse="";
    QString bodyRazziaResponse="";




    if (globVerze=="2.2CZ1.0")
    {

        //bodyAllData=TestXmlGenerator.AllData2_2CZ1_0( stav.indexAktZastavky,seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupyDomDocument);
        bodyCurrentTariffStopResponse=xmlGenerator.TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(stav.indexAktZastavky,seznamZastavek,stav.doorState,stav.locationState,prestupy);
        bodyVehicleDataResponse=xmlGenerator.TicketValidationService_GetVehicleDataResponse2_2CZ1_0(stav);
        bodyRazziaResponse=xmlGenerator.TicketValidationService_GetRazziaResponse2_2CZ1_0(stav);

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


    this->nastavObsahTela("CurrentTariffStopResponse",bodyCurrentTariffStopResponse);
    this->nastavObsahTela("VehicleDataResponse",bodyVehicleDataResponse);
    this->nastavObsahTela("RazziaResponse",bodyRazziaResponse);
    this->asocPoleDoServeru(obsahTelaPole);

    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }

}



void TicketValidationService::slotTedOdesliNaPanely()
{
    qDebug()<<"CustomerInformationService::tedOdesliNaPanely()";
    aktualizaceIntProm( prestupyInterni,stavInterni,seznamZastavekInterni);
}

void TicketValidationService::aktualizaceObsahuSluzby(QVector<PrestupMPV> prestupy, CestaUdaje &stav ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceInternichPromennychOdeslat";
    prestupyInterni =prestupy;
    stavInterni=stav;
    seznamZastavekInterni=stav.aktObeh.seznamSpoju.at(stav.indexSpojeNaObehu).globalniSeznamZastavek;
    slotTedOdesliNaPanely();
    timer->start(60000);
}


