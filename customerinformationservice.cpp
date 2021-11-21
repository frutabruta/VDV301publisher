#include "customerinformationservice.h"
#include "httpsluzba.h"
#include "./prestupmpv.h"


CustomerInformationService::CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
    connect(timer, &QTimer::timeout, this, &CustomerInformationService::tedOdesliNaPanelySlot);
    timer->start(60000);

}



void CustomerInformationService::tedOdesliNaPanelySlot()
{
    qDebug()<<"CustomerInformationService::tedOdesliNaPanelySlot()";
    aktualizaceIntProm(prestupyInterni,stavInterni,seznamSpojuInterni);
}
void CustomerInformationService::aktualizaceIntProm(QVector<prestupMPV> prestupy, CestaUdaje &stav, QVector<Spoj>  seznamSpoju ) //novy
{
  qDebug()<<"CustomerInformationService::aktualizaceIntProm"<<nazevSluzbyInterni<<" "<<globVerze;
  qDebug()<<"velikost seznamTripu"<<seznamSpoju.size()<<" index"<<stav.indexTripu;
  if (seznamSpoju.isEmpty())
  {
      qDebug()<<"seznam spoju je prazdny, ukoncuji CustomerInformationService::aktualizaceIntProm";
      return;
  }
    QVector<ZastavkaCil>  seznamZastavek=seznamSpoju.at(stav.indexTripu).globalniSeznamZastavek;

  //  QByteArray zpracovanoMPV="";
    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";
    qDebug()<<"1";
    if (globVerze=="2.2CZ1.0")
    {
        qDebug()<<"2";
        //bodyAllData=TestXmlGenerator.AllData2_2CZ1_0( stav.indexAktZastavky,seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupyDomDocument);
        bodyAllData=TestXmlGenerator.AllData2_2CZ1_0(seznamSpoju,prestupy,stav);
        bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek,stav);
    }
    else
    {
        qDebug()<<"3";
        bodyAllData=TestXmlGenerator.AllData1_0( seznamZastavek, stav.aktlinka, stav.doorState, stav.locationState,prestupy,stav);
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

void CustomerInformationService::aktualizaceObsahuSluzby(QVector<prestupMPV> prestup, CestaUdaje &stav ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceInternichPromennychOdeslat";
   //prestupyDomDocumentInterni=prestupyDomDocument;
    //QVector<ZastavkaCil>  seznamZastavek;


   prestupyInterni=prestup;
    stavInterni=stav;
    //seznamZastavekInterni=seznamZastavek;
    seznamSpojuInterni=stav.aktObeh.seznamSpoju;
    tedOdesliNaPanelySlot();
    timer->start(60000);


}
