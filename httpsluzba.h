#ifndef HTTPSLUZBA_H
#define HTTPSLUZBA_H

#include <QObject>
#include <QtXml>
#include <QtHttpServer>

#include "qzeroconf.h"


#include "newhttpserver.h"
#include "xmlgenerator.h"
#include "subscriber.h"

#include "../VDV301struktury/cestaudaje.h"
#include "../VDV301struktury/zastavkacil.h"



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

    QString novySubscriber(Subscriber subscriber);
    int jeSubscriberNaSeznamu(QVector<Subscriber> seznam, Subscriber prvek);
    int odstranitSubscribera(int index);
    int nastavObsahTela(QString klic, QString obsah);
    QString globVerze="1.0";
    void aktualizaceIntProm(QDomDocument prestupyDomDocument, CestaUdaje &stav, QVector<ZastavkaCil> interniSeznamZastavek);
    void aktualizaceInternichPromennychOdeslat(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);
    QTimer *timer = new QTimer(this);
    QString nazevSluzbyInterni="";


    ~HttpSluzba();

private:
    QZeroConf zeroConf;

    NewHttpServer InstanceNovehoServeru;
    int cisloPortuInterni=0;

    //QString obsahInterni="";
    QString hlavickaInterni="";
    int delkaObsahu=0;
    void bonjourStartPublish(QString nazevSluzby, QString typSluzby, int port, QString verze, QZeroConf &instanceZeroConf);
    QString typSluzbyInterni="_ibisip_http._tcp";
    //int nastavHttpObsah(QString argumentXMLserveru);
    QByteArray vyrobHlavickuGet();
    QString vyrobHlavickuSubscribe();





    void zastavBonjourSluzbu();
protected:
    xmlGenerator TestXmlGenerator;
    QMap<QString,QString> obsahTelaPole;
    int asocPoleDoServeru(QMap<QString, QString> pole);





public slots:
    //void vypisObsahRequestu();
    void vypisObsahRequestu(QByteArray vysledek, QString struktura);
    //  void tedOdesliNaPanely();
    void vypisChybuZeroConfig();

    //void start();
    void stop(bool parametr);
    void start(bool parametr);
signals:
    void pridejSubscribera(QUrl adresaSubscribera);
    void vypisSubscriberu(QVector<Subscriber> seznamSubscriberuInt);
    void stavSignal(bool stav);
    void startSignal();
    void stopSignal();

private slots:
    void vyprseniCasovace();


};

#endif // HTTPSLUZBA_H
