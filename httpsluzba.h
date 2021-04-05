#ifndef HTTPSLUZBA_H
#define HTTPSLUZBA_H

#include <QObject>
#include <QtXml>
#include "qzeroconf.h"

#include <QtHttpServer>
#include "newhttpserver.h"
#include "xmlgenerator.h"
#include "cestaudaje.h"
#include "subscriber.h"

class HttpSluzba: public QObject
{
    Q_OBJECT
public:
    HttpSluzba(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);
    void bonjourStartKomplet();
    int aktualizuj();
    QByteArray vyrobSubscribeResponseBody(int vysledek);
    //QVector<QUrl> seznamSubscriberu;
    QVector<Subscriber> seznamSubscriberu;

    void PostDoDispleje(QUrl adresaDispleje, QString dataDoPostu);
   // void ObnoveniServeru(QString dataDoServeru);
    //void novySubscriber(QUrl adresaSubscribera, QString struktura);
    void OdeslatDataDoDispleju(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector<SeznamZastavek> interniSeznamZastavek);
    void novySubscriber(Subscriber subscriber);
    int jeSubscriberNaSeznamu(QVector<Subscriber> seznam, Subscriber prvek);
    int odstranitSubscribera(int index);
    int nastavObsahTela(QString klic, QString obsah);
    QString globVerze="1.0";
private:
    QZeroConf zeroConf;

    NewHttpServer InstanceNovehoServeru;
    int cisloPortuInterni=0;
    QString nazevSluzbyInterni="";
   //QString obsahInterni="";
    QString hlavickaInterni="";
    int delkaObsahu=0;
    void bonjourStartPublish(QString nazevSluzby, QString typSluzby, int port, QString verze, QZeroConf &instanceZeroConf);
    QString typSluzbyInterni="_ibisip_http._tcp";
    //int nastavHttpObsah(QString argumentXMLserveru);
    QByteArray vyrobHlavickuGet();
    /*
    int zkombinujHlavickaTeloGet(QString hlavicka, QString telo);

    int zkombinujHlavickaTeloSubscribe(QString hlavicka, QString telo);
    */
    //QString vyrobGetResponseBody();
    QString vyrobHlavickuSubscribe();
    xmlGenerator TestXmlGenerator;
    QMap<QString,QString> obsahTelaPole;

    int asocPoleDoServeru(QMap<QString, QString> pole);
public slots:
    //void vypisObsahRequestu();
    void vypisObsahRequestu(QByteArray vysledek, QString struktura);

signals:
    void pridejSubscribera(QUrl adresaSubscribera);
    void vypisSubscriberu(QVector<Subscriber> seznamSubscriberuInt);

};

#endif // HTTPSLUZBA_H