#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H

#include <QObject>
#include <QtXml>
#include <QtHttpServer>
#include <QMap>
#include <QLoggingCategory>

#include "QtZeroConf/qzeroconf.h"

#include "httpserverpublisher.h"
#include "subscriber.h"

//#include "VDV301DataStructures/vehiclestate.h"
//#include "VDV301DataStructures/stoppointdestination.h"


class HttpService: public QObject
{
    Q_OBJECT
public:
    HttpService(QString serviceName, QString serviceType, int portNumber, QString version, QString serviceNamePostfix="");
    ~HttpService();

    //periodic data send timer
    QTimer timer;

    //structures
    QVector<Subscriber> subscriberList;
    QString mServiceName="";
    QString mServiceNamePostFix="";

    //settings
    bool blockBonjour=false;

    //functions
    void bonjourStartAll();
    int isInRange(int index, int valueCount, QString nameOfFunction);
    void postToSubscriber(QUrl subscriberAddress, QString contentToPost);
    QString retrieveStructureContentMapValue(QString key); //unused
    int setBodyContent(QString key, QString content);
    void updateStructureMap();


    //funkce subscriber
    QString handleNewSubscriber(Subscriber subscriber);
    int isSubscriberOnTheList(QVector<Subscriber> subscriberList, Subscriber testedSubscriber);
    int removeSubscriber(int index);
    int removeSubscriber(Subscriber selectedSubscriber);

    QByteArray createSubscribeResponseBody(int desiredResult);  // unused

    QString StringToNmToken(QString input);

    //setters and getters
    int portNumber() const;
    void setPortNumber(int newPortNumber);

    QString version() const;
    void setVersion(const QString &newVersion);    
private:
    //instance knihoven
    QZeroConf zeroConf;
    HttpServerPublisher httpServerPublisher ;
    QNetworkAccessManager qNetworkAccessManager;

    //promenne
    int mPortNumber=0;
    QString mServiceType="_ibisip_http._tcp";

    //funkce
    void bonjourStartPublish(QString serviceName, QString serviceType, int port, QString version, QZeroConf &qZeroConf);
    void stopBonjourService();

    QByteArray createGetHeader(); // unused
    QString createSubscribeHeader(); //unused

protected:

    QMap<QString,QString> structureContentMap; //contains payload and a key(AllData etc.)
    int updateServerContent(QMap<QString, QString> structureMap);
    QString mVersion="1.0";
    void postToAllSubscribers();
public slots:
    void slotDumpRequestContent(QByteArray request, QString structureName);
    void slotDumpZeroConfigError(QZeroConf::error_t error);
    void slotStop(bool parameter);
    void slotStartDnsSd(bool parameter);
    void slotRemoveAllSubscribers();
    void slotReplyToPostReceived();
    void slotStopTimer();
    void slotServerReady(int portNumber);
    void slotStartServer();

private slots:
    void slotTimerTimeout(); // unused
    void slotServicePublished();

signals:
    void signalSubscriberAdded(QUrl subscriberSddress); // unused
    void signalDumpSubscriberList(QVector<Subscriber> subscriberList);
    void signalStav(bool stav);
    void signalStart(); // unused
    void signalStop(); // unused
    //void signalReplyToPostReceived(QNetworkReply *reply);
    void signalPostResult(const QUrl &url, int httpStatus, QNetworkReply::NetworkError error, const QString &errorString, const QByteArray &body);
    void signalParameterChange(QMap<QString,QString> values);
    void signalServicePublished(QString serviceName);
    void signalPortUpdate(int port);
    void signalErrorMessage(QString message);
};

#endif // HTTPSERVICE_H
