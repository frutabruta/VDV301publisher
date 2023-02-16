#ifndef HTTPSERVERPUBLISHER_H
#define HTTPSERVERPUBLISHER_H

#include <QObject>
#include <QtHttpServer>

class HttpServerPublisher: public QObject
{
    Q_OBJECT
public:
    //konstruktor
    HttpServerPublisher(quint16 portVstup, QString vstupSlozkaSluzby);

    //promenne
    QByteArray bodyPozadavku="xx";

    //funkce
    int nastavObsahTela(QMap<QString, QString> vstup);

    //

    quint16 cisloPortu() const;
    void setCisloPortu(quint16 newCisloPortu);

private:

    //instance knihoven
    QHttpServer httpServer;

    //promenne
    quint16 mCisloPortu=0;
    QString mSlozkaSluzby="obsahGet";
    QString mObsahRoot="";
    QString mObsahSubscribe="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><Active><Value>true</Value></Active></SubscribeResponse>";
    QString mObsahSet="<?xml version=\"1.0\" encoding=\"utf-8\"?><DataAcceptedResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><DataAcceptedResponseData><TimeStamp><Value>2022-09-12T12:28:22.6142112+02:00</Value></TimeStamp><DataAccepted><Value>true</Value></DataAccepted></DataAcceptedResponseData></DataAcceptedResponse>";
    QMap<QString,QString> mObsahTelaPole;

    //funkce
    int listen();

    int route(QString &slozkaSluzby, QMap<QString, QString> &obsahyBody);
    QString vyrobHlavickuOk();
    void zapisDoPromenneGet(QString vstup);
    void zapisDoSubscribe(QString vstup);

    QString vyrobSubscribeResponse(QString result);
signals:
    void zmenaObsahu(QByteArray vysledek,QString struktura) ;
    void prijemDat(QString vysledek) ;
    void signalServerBezi(int cisloPortu);
    //void zmenaObsahu() ;

public slots:
    void slotTest(int port);
    int slotStartServer();
};

#endif // HTTPSERVERPUBLISHER_H
