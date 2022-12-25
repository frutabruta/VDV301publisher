#include "customerinformationservice.h"
#include "httpsluzba.h"
#include "VDV301struktury/prestupmpv.h"


/*!
 * \brief CustomerInformationService::CustomerInformationService
 * \param nazevSluzby
 * \param typSluzby
 * \param cisloPortu
 * \param verze
 */
CustomerInformationService::CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
   qDebug() <<  Q_FUNC_INFO<<" "<<nazevSluzby<<" "<<verze;
    connect(timer, &QTimer::timeout, this, &CustomerInformationService::slotTedOdesliNaPanely);

    //naplnění prázdných struktur

    mimoVydej();
    //nastartování periodického zasílání
    timer->start(60000);

}



/*!
 * \brief CustomerInformationService::aktualizaceIntProm
 * \param prestupy
 * \param stav
 * \param seznamSpoju
 */
void CustomerInformationService::aktualizaceIntProm(QVector<Prestup> prestupy, CestaUdaje &stav, QVector<Spoj>  seznamSpoju ) //novy
{
    qDebug() <<  Q_FUNC_INFO<<" "<<nazevSluzbyInterni<<" "<<globVerze;
    qDebug()<<"velikost seznamTripu"<<seznamSpoju.size()<<" index"<<stav.indexSpojeNaObehu;

    if (seznamSpoju.isEmpty())
    {
        qDebug()<<"seznam spoju je prazdny, ukoncuji CustomerInformationService::aktualizaceIntProm";
        return;
    }

    /*
    if(!MainWindowPomocne::jeVRozsahu(stav.indexSpojeNaObehu,seznamSpoju.size(),"CustomerInformationService::aktualizaceIntProm"))
    {
        return;
    }
    */


    QVector<ZastavkaCil>  seznamZastavek=seznamSpoju.at(stav.indexSpojeNaObehu).globalniSeznamZastavek;
    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";

    if (globVerze=="2.2CZ1.0")
    {   
        bodyAllData=xmlGenerator.AllData2_2CZ1_0(seznamSpoju,prestupy,stav);
        bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek,stav);
    }
    else
    {    
        bodyAllData=xmlGenerator.AllData1_0(seznamSpoju,prestupy,stav);
        bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent1_0( stav.indexAktZastavky,seznamZastavek, stav);
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
    qDebug() <<  Q_FUNC_INFO<<" "<<nazevSluzbyInterni<<" "<<globVerze;

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

        bodyAllData=xmlGenerator.AllData_empty2_2CZ1_0();
    }
    else
    {

        bodyAllData=xmlGenerator.AllData_empty_1_0();

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



void CustomerInformationService::aktualizaceObsahuSluzby(QVector<Prestup> prestup, CestaUdaje &stav ) //novy
{
    qDebug() <<  Q_FUNC_INFO;
    mPrestupy=prestup;
    mStav=stav;
    mSeznamSpoju=stav.aktObeh.seznamSpoju;
    slotTedOdesliNaPanely();
    timer->start(60000);
}


void CustomerInformationService::mimoVydej()
{
    qDebug() <<  Q_FUNC_INFO;
    aktualizaceIntPromEmpty(mStav,mSeznamSpoju);

}


/*!
 * \brief CustomerInformationService::slotTedOdesliNaPanely
 */

void CustomerInformationService::slotTedOdesliNaPanely()
{
    qDebug() <<  Q_FUNC_INFO;
    if (mSeznamSpoju.isEmpty())
    {
        aktualizaceIntPromEmpty(mStav,mSeznamSpoju);
    }
    else
    {
        aktualizaceIntProm(mPrestupy,mStav,mSeznamSpoju );
    }

}
