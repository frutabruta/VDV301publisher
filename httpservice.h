#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H

#include <QObject>
#include <QtXml>
#include <QtHttpServer>
#include <QMap>

#include "QtZeroConf/qzeroconf.h"

#include "httpserverpublisher.h"
#include "subscriber.h"

//#include "VDV301DataStructures/vehiclestate.h"
//#include "VDV301DataStructures/stoppointdestination.h"



class HttpService: public QObject
{
    Q_OBJECT
public:
    HttpService(QString serviceName,QString serviceType, int portNumber,QString version);

    //structures
    QVector<Subscriber> subscriberList;

    QString mServiceName="";

    //functions
    void postToSubscriber(QUrl subscriberAddress, QString contentToPost);
    int setBodyContent(QString key, QString content);
    void bonjourStartAll();

    //funkce subscriber
    QString handleNewSubscriber(Subscriber subscriber);
    int isSubscriberOnTheList(QVector<Subscriber> subscriberList, Subscriber testedSubscriber);
    int removeSubscriber(int index);
    int removeSubscriber(Subscriber selectedSubscriber);

    QByteArray createSubscribeResponseBody(int desiredResult);  // unused

    //casovac pro periodicke odesilani dat
    QTimer timer;

    ~HttpService();

    QString StringToNmToken(QString input);

    int portNumber() const;
    void setPortNumber(int newPortNumber);


    QString version() const;
    void setVersion(const QString &newVersion);

private:
    //instance knihoven
    QZeroConf zeroConf;
    HttpServerPublisher httpServerPublisher ;
    QNetworkAccessManager *qNetworkAccessManager = new QNetworkAccessManager();

    //promenne
    int mPortNumber=0;
    QString mServiceType="_ibisip_http._tcp";

    //funkce
    void bonjourStartPublish(QString serviceName, QString serviceType, int port, QString version, QZeroConf &qZeroConf);
    void stopBonjourService();

    QByteArray createGetHeader(); // unused
    QString createSubscribeHeader();
protected:

    QMap<QString,QString> structureContentMap; //contains payload and a key(AllData etc.)
    int updateServerContent(QMap<QString, QString> structureMap);
    QString mVersion="1.0";
public slots:
    void slotDumpRequestContent(QByteArray request, QString structureName);
    void slotDumpZeroConfigError();
    void slotStop(bool parameter);
    void slotStartDnsSd(bool parameter);
    void slotRemoveAllSubscribers();
    void slotStopTimer();
    void slotServerReady(int portNumber);
    void slotStartServer();


private slots:
    void slotTimerTimeout(); // unused
    void slotReplyToPostReceived(QNetworkReply *reply);

    void slotServicePublished();
signals:
    void signalSubscriberAdded(QUrl subscriberSddress); // unused
    void signalDumpSubscriberList(QVector<Subscriber> subscriberList);
    void signalStav(bool stav);
    void signalStart(); // unused
    void signalStop(); // unused
    void signalReplyToPostReceived(QNetworkReply *reply);
    void signalParameterChange(QMap<QString,QString> values);
    void signalServicePublished(QString serviceName);

};

#endif // HTTPSERVICE_H
