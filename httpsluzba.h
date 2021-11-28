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

    //funkce subscriber
    QString novySubscriber(Subscriber subscriber);
    int jeSubscriberNaSeznamu(QVector<Subscriber> seznam, Subscriber prvek);
    int odstranitSubscribera(int index);
    QByteArray vyrobSubscribeResponseBody(int vysledek);

    void bonjourStartKomplet();

    int aktualizuj();

    //casovac pro periodicke odesilani dat
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
    QNetworkAccessManager *manager2 = new QNetworkAccessManager();

protected:
    xmlGenerator TestXmlGenerator;
    QMap<QString,QString> obsahTelaPole;
    int asocPoleDoServeru(QMap<QString, QString> pole);

public slots:
    void slotVypisObsahRequestu(QByteArray vysledek, QString struktura);
    void slotVypisChybuZeroConfig();
    void slotStop(bool parametr);
    void slotStart(bool parametr);
    void slotVymazSubscribery();
    void slotZastavCasovac();


private slots:
    void slotVyprseniCasovace();
    void slotPrislaOdpovedNaPost(QNetworkReply *reply);


signals:
    void signalPridejSubscribera(QUrl adresaSubscribera);
    void signalVypisSubscriberu(QVector<Subscriber> seznamSubscriberuInt);
    void signalStav(bool stav);
    void signalStart();
    void signalStop();
    void signalOdpovedNaPost(QNetworkReply *reply);


};

#endif // HTTPSLUZBA_H
