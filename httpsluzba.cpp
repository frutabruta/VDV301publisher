#include "httpsluzba.h"

#include "qtzeroconf/qzeroconf.h"
#include "VDV301struktury/zastavkacil.h"



HttpSluzba::HttpSluzba(QString nazevSluzby,QString typSluzby, int cisloPortu,QString verze):InstanceNovehoServeru(cisloPortu)
{
    qDebug()<<"HttpSluzba::HttpSluzba";
    cisloPortuInterni=cisloPortu;
    nazevSluzbyInterni=nazevSluzby;
    typSluzbyInterni=typSluzby;
    globVerze=verze;
    bonjourStartKomplet();
    //hlavickaInterni=vyrobHlavickuGet();

    //connect(&InstanceNovehoServeru,SIGNAL(zmenaObsahu()),this,SLOT(vypisObsahRequestu()));
    connect(&InstanceNovehoServeru,&NewHttpServer::zmenaObsahu,this,&HttpSluzba::vypisObsahRequestu);
    connect(&zeroConf,&QZeroConf::error,this,&HttpSluzba::vypisChybuZeroConfig);

}


void HttpSluzba::vyprseniCasovace()
{
    qDebug()<<"casovac vyrpsel";
}


/*
int HttpSluzba::aktualizuj()
{
    qDebug()<<"HttpSluzba::aktualizuj()";
    //InstanceNovehoServeru.zapisDoPromenneGet(vyrobGetResponseBody());
    InstanceNovehoServeru.zapisDoSubscribe(vyrobSubscribeResponseBody(1));
    return 1;
} */

QByteArray HttpSluzba::vyrobHlavickuGet()
{
    qDebug()<<"HttpSluzba::vyrobHlavicku()";
    QByteArray hlavicka;
    //this->hlavickaInterni="";
    QByteArray argumentXMLserveru = "";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}

QString HttpSluzba::vyrobHlavickuSubscribe()
{
    qDebug()<<"HttpSluzba::vyrobHlavicku()";
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




void HttpSluzba::bonjourStartKomplet()
{
    qDebug()<<"HttpSluzba::bonjourStartKomplet";
    //zeroConf.clearServiceTxtRecords();
    this->bonjourStartPublish(this->nazevSluzbyInterni,this->typSluzbyInterni,this->cisloPortuInterni,this->globVerze ,zeroConf);
}



void HttpSluzba::bonjourStartPublish(QString nazevSluzby, QString typSluzby,int port,QString verze, QZeroConf &instanceZeroConf)
{
    qDebug()<<"HttpSluzba::bonjourStartPublish"<<nazevSluzby;
    instanceZeroConf.addServiceTxtRecord("ver", verze);
    instanceZeroConf.startServicePublish(nazevSluzby.toUtf8(), typSluzby.toUtf8(), "local", port);

}



void HttpSluzba::vypisChybuZeroConfig()
{
    qDebug()<<"HttpSluzba::vypisChybuZeroConfig2";
}

QByteArray HttpSluzba::vyrobSubscribeResponseBody(int vysledek)
{
    qDebug()<<"HttpSluzba::vyrobSubscribeResponseBody";
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


void HttpSluzba::vypisObsahRequestu(QByteArray vysledek,QString struktura)
{
    qDebug()<<"HttpSluzba::HttpSluzba::vypisObsahRequestu";
    QByteArray posledniRequest=InstanceNovehoServeru.bodyPozadavku;
    QDomDocument xmlrequest;
    xmlrequest.setContent(vysledek);
    QString adresa= xmlrequest.elementsByTagName("Client-IP-Address").at(0).toElement().firstChildElement().text() ;
    QString port= xmlrequest.elementsByTagName("ReplyPort").at(0).toElement().firstChildElement().text() ;
    qDebug()<<"prvni element "<<adresa<<" "<<port;
    qDebug()<<"body pozadavku"<<posledniRequest;
    //qDebug()<<"vysledek"<<vysledek;
    QString kompletadresa="http://"+adresa+":"+port;
    if(adresa.contains("%"))
    {
        qDebug()<<"detekovano procento";
        kompletadresa="http://["+adresa+"]:"+port;
    }
    QUrl adresaurl=kompletadresa;

    //pridejSubscribera(adresaurl);
    Subscriber kandidat;
    kandidat.adresa=adresaurl;
    kandidat.struktura=struktura;
    novySubscriber(kandidat);
    //qDebug()<<obsahBody;
}





void HttpSluzba::PostDoDispleje(QUrl adresaDispleje, QString dataDoPostu)
{
    qDebug()<<"HttpSluzba::PostDoDispleje";
    //QByteArray postDataSize = QByteArray::number(dataDoPostu.size());
    QNetworkRequest pozadavekPOST(adresaDispleje);

    //pozadavekPOST.setRawHeader("Content-Length", postDataSize );
    pozadavekPOST.setRawHeader("Content-Type", "text/xml");
    pozadavekPOST.setRawHeader("Expect", "100-continue");
    pozadavekPOST.setRawHeader("Connection", "keep-Alive");
    //pozadavekPOST.setRawHeader("Accept-Encoding", "gzip, deflate");
    QNetworkAccessManager *manager2 = new QNetworkAccessManager();
    QByteArray dataDoPostuQByte=dataDoPostu.toUtf8() ;
    manager2->post(pozadavekPOST,dataDoPostuQByte);

}



QString HttpSluzba::novySubscriber(Subscriber subscriber)
{
    qDebug()<<"MainWindow::novySubsriber "<<subscriber.adresa;
    QString vysledek;
    if(subscriber.adresa.toString()=="")
    {
        //qDebug()<<"spatna adresa";
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
    }

    emit vypisSubscriberu(seznamSubscriberu);
    return vysledek;

}

int HttpSluzba::jeSubscriberNaSeznamu(QVector<Subscriber> seznam ,Subscriber prvek)
{
    qDebug()<<"HttpSluzba::jeSubscriberNaSeznamu";
    for(int i =0;i<seznam.length();i++)
    {
        if((seznam[i].adresa==prvek.adresa)&&(seznam[i].struktura==prvek.struktura ))
        {  return 1;}
    }
    return 0;
}


int HttpSluzba::odstranitSubscribera(int index)
{
    qDebug()<<"HttpSluzba::odstranitSubscribera";
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

int HttpSluzba::nastavObsahTela(QString klic, QString obsah)
{

    qDebug()<<"HttpSluzba::nastavObsahTela";
    obsahTelaPole.insert(klic,obsah);

//qDebug()<<"hh "<<obsahTelaPole.value("xx");


return 1;
}

int HttpSluzba::asocPoleDoServeru(QMap<QString,QString> pole)
{
    InstanceNovehoServeru.nastavObsahTela(pole);
    return 1;
}


