#include "httpsluzba.h"




/*!
 * \brief HttpSluzba::HttpSluzba
 * \param nazevSluzby
 * \param typSluzby
 * \param cisloPortu
 * \param verze
 */
HttpSluzba::HttpSluzba(QString nazevSluzby,QString typSluzby, int cisloPortu,QString verze):InstanceNovehoServeru(cisloPortu,nazevSluzby)
{
    qDebug() <<  Q_FUNC_INFO;
    cisloPortuInterni=cisloPortu;
    nazevSluzbyInterni=nazevSluzby;
    typSluzbyInterni=typSluzby;
    globVerze=verze;

    connect(&InstanceNovehoServeru,&HttpServerPublisher::zmenaObsahu,this,&HttpSluzba::slotVypisObsahRequestu);
    connect(&zeroConf,&QZeroConf::error,this,&HttpSluzba::slotVypisChybuZeroConfig);

    connect(manager2,&QNetworkAccessManager::finished,this,&HttpSluzba::slotPrislaOdpovedNaPost);
}

/*!
 * \brief HttpSluzba::~HttpSluzba
 */
HttpSluzba::~HttpSluzba()
{
    zastavBonjourSluzbu();
    qDebug()<<"konec";
}


/*!
 * \brief HttpSluzba::slotVyprseniCasovace
 */
void HttpSluzba::slotVyprseniCasovace()
{
    qDebug() <<  Q_FUNC_INFO;
}



/*!
 * \brief HttpSluzba::vyrobHlavickuGet
 * \return
 */
QByteArray HttpSluzba::vyrobHlavickuGet()
{
   qDebug() <<  Q_FUNC_INFO;
    QByteArray hlavicka;

    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}


/*!
 * \brief HttpSluzba::vyrobHlavickuSubscribe
 * \return
 */


QString HttpSluzba::vyrobHlavickuSubscribe()
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray hlavicka;
    //this->hlavickaInterni="";
    QByteArray argumentXMLserveru = "";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: text/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}


/*!
 * \brief HttpSluzba::bonjourStartKomplet
 */


void HttpSluzba::bonjourStartKomplet()
{
    qDebug() <<  Q_FUNC_INFO;
    //zeroConf.clearServiceTxtRecords();
    this->bonjourStartPublish(this->nazevSluzbyInterni,this->typSluzbyInterni,this->cisloPortuInterni,this->globVerze ,zeroConf);
}


/*!
 * \brief HttpSluzba::bonjourStartPublish
 * \param nazevSluzby
 * \param typSluzby
 * \param port
 * \param verze
 * \param instanceZeroConf
 */
void HttpSluzba::bonjourStartPublish(QString nazevSluzby, QString typSluzby,int port,QString verze, QZeroConf &instanceZeroConf)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<nazevSluzby<<" "<<verze<<" "<<typSluzby<<" "<<port;


    instanceZeroConf.clearServiceTxtRecords();
    instanceZeroConf.addServiceTxtRecord("ver", verze);
    qDebug()<<"Txt zaznam pridan";

    instanceZeroConf.startServicePublish(nazevSluzby.toUtf8(), typSluzby.toUtf8(), "local", port);

}


/*!
 * \brief HttpSluzba::slotVypisChybuZeroConfig
 */
void HttpSluzba::slotVypisChybuZeroConfig()
{
    qDebug() <<  Q_FUNC_INFO;
}


/*!
 * \brief HttpSluzba::vyrobSubscribeResponseBody
 * nikde nepouzito
 * \param vysledek
 * \return
 */
QByteArray HttpSluzba::vyrobSubscribeResponseBody(int vysledek)
{

    qDebug() <<  Q_FUNC_INFO;
    QByteArray textVysledek="true";
    if (vysledek!=1)
    {
        textVysledek="false";
    }
    QByteArray odpoved ="";
    odpoved+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
    odpoved+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
    odpoved+="<Active><Value>";
    odpoved+=textVysledek;
    odpoved+="</Value></Active>";
    odpoved+="</SubscribeResponse>";
    return odpoved;
}


/*!
 * \brief HttpSluzba::slotVypisObsahRequestu
 * \param vysledek
 * \param struktura
 */
void HttpSluzba::slotVypisObsahRequestu(QByteArray vysledek,QString struktura)
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray posledniRequest=InstanceNovehoServeru.bodyPozadavku;
    QDomDocument xmlrequest;
    xmlrequest.setContent(vysledek);



    QDomElement subscribeRequest=xmlrequest.firstChildElement("SubscribeRequest");

    QString adresa= subscribeRequest.firstChildElement("Client-IP-Address").firstChildElement().text() ;
    QString port= subscribeRequest.elementsByTagName("ReplyPort").at(0).toElement().firstChildElement().text() ;
    QString cesta=subscribeRequest.firstChildElement("ReplyPath").toElement().firstChildElement("Value").firstChild().nodeValue();

   // cesta="CustomerInformationService";
    qDebug()<<"body pozadavku"<<posledniRequest;
    //qDebug()<<"vysledek"<<vysledek;
    QString kompletadresa="http://"+adresa+":"+port+"/"+cesta;
    if(adresa.contains("%"))
    {
        qDebug()<<"detekovano procento";
        kompletadresa="http://["+adresa+"]:"+port;
    }

    QUrl adresaurl=kompletadresa;
    qDebug()<<"komplet adresa subscribera "<<kompletadresa;

    //pridejSubscribera(adresaurl);
    Subscriber kandidat;
    kandidat.adresa=adresaurl;
    kandidat.struktura=struktura;
    //kandidat.cesta=cesta;
    novySubscriber(kandidat);
    //qDebug()<<obsahBody;
}



/*!
 * \brief HttpSluzba::PostDoDispleje
 * odesílá jeden payload na jednu adresu
 * \param adresaDispleje
 * \param dataDoPostu
 */

void HttpSluzba::PostDoDispleje(QUrl adresaDispleje, QString dataDoPostu)
{
    qDebug() <<  Q_FUNC_INFO;
    //QByteArray postDataSize = QByteArray::number(dataDoPostu.size());
    QNetworkRequest pozadavekPOST(adresaDispleje);

    //pozadavekPOST.setRawHeader("Content-Length", postDataSize );
    pozadavekPOST.setRawHeader("Content-Type", "text/xml");
    pozadavekPOST.setRawHeader("Expect", "100-continue");
    pozadavekPOST.setRawHeader("Connection", "keep-Alive");
    //pozadavekPOST.setRawHeader("Accept-Encoding", "gzip, deflate");

    QByteArray dataDoPostuQByte=dataDoPostu.toUtf8() ;
    manager2->post(pozadavekPOST,dataDoPostuQByte);


}



/*!
 * \brief HttpSluzba::slotPrislaOdpovedNaPost
 * \param reply
 */

void HttpSluzba::slotPrislaOdpovedNaPost(QNetworkReply* reply)
{
    qDebug() <<  Q_FUNC_INFO;
    emit this->signalOdpovedNaPost(reply);
}


/*!
 * \brief HttpSluzba::novySubscriber
 * \param subscriber
 * \return
 */
QString HttpSluzba::novySubscriber(Subscriber subscriber)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<subscriber.adresa;
    QString vysledek;
    if(subscriber.adresa.toString()=="")
    {
        vysledek="spatna adresa";
        return vysledek;
    }

    if(jeSubscriberNaSeznamu(seznamSubscriberu,subscriber))
    {
        vysledek="subscriber uz je na seznamu "+subscriber.adresa.toString()+""+subscriber.struktura;
    }
    else
    {
        seznamSubscriberu.push_back(subscriber);
        vysledek="novy subscriber je "+subscriber.adresa.toString()+""+subscriber.struktura;
        PostDoDispleje(subscriber.adresa,obsahTelaPole.value(subscriber.struktura)); //odeslání dat do zařízení hned po odběru
    }

    emit signalVypisSubscriberu(seznamSubscriberu);
    return vysledek;

}



/*!
 * \brief HttpSluzba::jeSubscriberNaSeznamu
 * \param seznam
 * \param prvek
 * \return
 */
int HttpSluzba::jeSubscriberNaSeznamu(QVector<Subscriber> seznam ,Subscriber prvek)
{
    qDebug() <<  Q_FUNC_INFO;
    for(int i =0;i<seznam.length();i++)
    {
        if((seznam[i].adresa==prvek.adresa)&&(seznam[i].struktura==prvek.struktura ))
        {  return 1;}
    }
    return 0;
}


/*!
 * \brief HttpSluzba::odstranitSubscribera
 * \param index
 * \return
 */
int HttpSluzba::odstranitSubscribera(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    if ((index<seznamSubscriberu.size())&&(index>=0))
    {
        qDebug()<<"mazu "<<seznamSubscriberu.at(index).adresa<<seznamSubscriberu.at(index).struktura;

        seznamSubscriberu.removeAt(index);
        return 1;
    }
    else
    {
        qDebug()<<"mimo rozsah";
    }
    return 0;
}



/*!
 * \brief HttpSluzba::nastavObsahTela
 * \param klic
 * \param obsah
 * \return
 */
int HttpSluzba::nastavObsahTela(QString klic, QString obsah)
{

    qDebug() <<  Q_FUNC_INFO<<" "<<klic;
    obsahTelaPole.insert(klic,obsah);


    return 1;
}




/*!
 * \brief HttpSluzba::asocPoleDoServeru
 * \param pole
 * \return
 */
int HttpSluzba::asocPoleDoServeru(QMap<QString,QString> pole)
{
    InstanceNovehoServeru.nastavObsahTela(pole);
    return 1;
}



/*!
 * \brief HttpSluzba::zastavBonjourSluzbu
 */
void HttpSluzba::zastavBonjourSluzbu()
{
    qDebug() <<  Q_FUNC_INFO<<nazevSluzbyInterni<<" "<<globVerze<<" "<<cisloPortuInterni;
    zeroConf.stopServicePublish();

}



/*!
 * \brief HttpSluzba::slotStart
 * \param parametr
 */
void HttpSluzba::slotStart(bool parametr)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<this->nazevSluzbyInterni<<" "<<this->globVerze;
    bonjourStartKomplet();
    emit this->signalStav(true);
    //emit this->startSignal();

}


/*!
 * \brief HttpSluzba::slotStop
 * \param parametr
 */
void HttpSluzba::slotStop(bool parametr)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<this->nazevSluzbyInterni<<" "<<this->globVerze;
    timer->stop();
    zastavBonjourSluzbu();
    emit this->signalStav(false);
    //emit this->stopSignal();
}


/*!
 *
 * \brief HttpSluzba::slotVymazSubscribery
 *  vyprázdní všechny subscribery
 *
 */
void HttpSluzba::slotVymazSubscribery()
{
    qDebug() <<  Q_FUNC_INFO;
    seznamSubscriberu.clear();


}


/*!
 * \brief HttpSluzba::slotZastavCasovac
 */
void HttpSluzba::slotZastavCasovac()
{
    qDebug() <<  Q_FUNC_INFO;
    timer->stop();

}

