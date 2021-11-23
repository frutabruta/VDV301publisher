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

    //struktury
    QVector<Subscriber> seznamSubscriberu;
    QString globVerze="1.0";
    QString nazevSluzbyInterni="";

    //funkce
    void PostDoDispleje(QUrl adresaDispleje, QString dataDoPostu);
    int nastavObsahTela(QString klic, QString obsah);
    void aktualizaceIntProm(QDomDocument prestupyDomDocument, CestaUdaje &stav, QVector<ZastavkaCil> interniSeznamZastavek);
    void aktualizaceInternichPromennychOdeslat(QDomDocument prestupyDomDocument, int verzeVDV301, CestaUdaje &stav, QVector<ZastavkaCil> seznamZastavek);


    QString novySubscriber(Subscriber subscriber);
    int jeSubscriberNaSeznamu(QVector<Subscriber> seznam, Subscriber prvek);
    int odstranitSubscribera(int index);
    QByteArray vyrobSubscribeResponseBody(int vysledek);

    void bonjourStartKomplet();
    int aktualizuj();


    QTimer *timer = new QTimer(this);


    ~HttpSluzba();


private:
    //instance knihoven
    QZeroConf zeroConf;
    NewHttpServer InstanceNovehoServeru;

    //promenne
    int cisloPortuInterni=0;
    QString hlavickaInterni="";
    int delkaObsahu=0;
    QString typSluzbyInterni="_ibisip_http._tcp";

    //funkce
    void bonjourStartPublish(QString nazevSluzby, QString typSluzby, int port, QString verze, QZeroConf &instanceZeroConf);
    QByteArray vyrobHlavickuGet();
    QString vyrobHlavickuSubscribe();
    void zastavBonjourSluzbu();

protected:
    xmlGenerator TestXmlGenerator;
    QMap<QString,QString> obsahTelaPole;
    int asocPoleDoServeru(QMap<QString, QString> pole);

public slots:
    void vypisObsahRequestu(QByteArray vysledek, QString struktura);
    void vypisChybuZeroConfig();
    void stop(bool parametr);
    void start(bool parametr);
    void vymazSubscribery();

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
