#include "customerinformationservice.h"
#include "httpsluzba.h"
#include "./prestupmpv.h"


/*!
 * \brief CustomerInformationService::CustomerInformationService
 * \param nazevSluzby
 * \param typSluzby
 * \param cisloPortu
 * \param verze
 */
CustomerInformationService::CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
    qDebug()<<"CustomerInformationService::CustomerInformationService "<<nazevSluzby<<" "<<verze;
    connect(timer, &QTimer::timeout, this, &CustomerInformationService::slotTedOdesliNaPanely);

    //naplnění prázdných struktur
    aktualizaceIntPromEmpty(stavInterni,seznamSpojuInterni);
    //nastartování periodického zasílání
    timer->start(60000);

}

/*!
 * \brief CustomerInformationService::slotTedOdesliNaPanely
 */

void CustomerInformationService::slotTedOdesliNaPanely()
{
    qDebug()<<"CustomerInformationService::slotTedOdesliNaPanely";
    if (seznamSpojuInterni.isEmpty())
    {
        aktualizaceIntPromEmpty(stavInterni,seznamSpojuInterni);
    }
    else
    {
        aktualizaceIntProm(prestupyInterni,stavInterni,seznamSpojuInterni);
    }

}

/*!
 * \brief CustomerInformationService::aktualizaceIntProm
 * \param prestupy
 * \param stav
 * \param seznamSpoju
 */
void CustomerInformationService::aktualizaceIntProm(QVector<PrestupMPV> prestupy, CestaUdaje &stav, QVector<Spoj>  seznamSpoju ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceIntProm"<<nazevSluzbyInterni<<" "<<globVerze;
    qDebug()<<"velikost seznamTripu"<<seznamSpoju.size()<<" index"<<stav.indexSpojeNaObehu;

    if (seznamSpoju.isEmpty())
    {
        qDebug()<<"seznam spoju je prazdny, ukoncuji CustomerInformationService::aktualizaceIntProm";
        return;
    }

    if(!MainWindowPomocne::jeVRozsahu(stav.indexSpojeNaObehu,seznamSpoju.size(),"CustomerInformationService::aktualizaceIntProm"))
    {
        return;
    }


    QVector<ZastavkaCil>  seznamZastavek=seznamSpoju.at(stav.indexSpojeNaObehu).globalniSeznamZastavek;
    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";

    if (globVerze=="2.2CZ1.0")
    {   
        bodyAllData=TestXmlGenerator.AllData2_2CZ1_0(seznamSpoju,prestupy,stav);
        bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek,stav);
    }
    else
    {    
        bodyAllData=TestXmlGenerator.AllData1_0( seznamZastavek, stav.doorState, stav.locationState,prestupy,stav);
        bodyCurrentDisplayContent=TestXmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek, stav);
    }

    this->nastavObsahTela("AllData",bodyAllData);
    this->nastavObsahTela("CurrentDisplayContent",bodyCurrentDisplayContent);
    this->asocPoleDoServeru(obsahTelaPole);

    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }

}


/*!
 * \brief CustomerInformationService::aktualizaceIntPromEmpty
 * \param stav
 * \param seznamSpoju
 */
void CustomerInformationService::aktualizaceIntPromEmpty(CestaUdaje &stav, QVector<Spoj>  seznamSpoju ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceIntPromEmpty"<<nazevSluzbyInterni<<" "<<globVerze;
    qDebug()<<"velikost seznamTripu"<<seznamSpoju.size()<<" index"<<stav.indexSpojeNaObehu;
    /* if (seznamSpoju.isEmpty())
  {
      qDebug()<<"seznam spoju je prazdny, ukoncuji CustomerInformationService::aktualizaceIntProm";
      return;
  }
  */

    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";

    if (globVerze=="2.2CZ1.0")
    {

        bodyAllData=TestXmlGenerator.AllDataEmpty2_2CZ1_0();
    }
    else
    {

        bodyAllData=TestXmlGenerator.AllData_empty_1_0();

    }


    this->nastavObsahTela("AllData",bodyAllData);
    this->nastavObsahTela("CurrentDisplayContent",bodyCurrentDisplayContent);
    this->asocPoleDoServeru(obsahTelaPole);

    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }

}


/*!
 * \brief CustomerInformationService::aktualizaceObsahuSluzby
 * \param prestup
 * \param stav
 */

void CustomerInformationService::aktualizaceObsahuSluzby(QVector<PrestupMPV> prestup, CestaUdaje &stav ) //novy
{
    qDebug()<<"CustomerInformationService::aktualizaceInternichPromennychOdeslat";
    prestupyInterni=prestup;
    stavInterni=stav;
    seznamSpojuInterni=stav.aktObeh.seznamSpoju;
    slotTedOdesliNaPanely();
    timer->start(60000);
}
