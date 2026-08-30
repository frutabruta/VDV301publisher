#ifndef TIMESERVICE_H
#define TIMESERVICE_H


#include <QObject>
#include <QTimeZone>

#include "QtZeroConf/qzeroconf.h"

class TimeService : public QObject
{
    Q_OBJECT
public:
    TimeService(QString serviceName, QString serviceType, int portNumber, QString version);

    ~TimeService();
    void bonjourStartAll();

    int portNumber() const;
    void setPortNumber(int newPortNumber);

    QHostAddress timeServerIp() const;
    void setTimeServerIp(QHostAddress addr);

    QTimeZone timeZone() const;
    QTimeZone resolveTimeZone() const;
    void setTimeZone(QTimeZone timeZone);

private:
    QString mServiceName="TimeService";
    QString mVersion="1.0";


    //instance knihoven
    QZeroConf zeroConf;
    //   HttpServerPublisher httpServerPublisher ;
    //   QNetworkAccessManager *qNetworkAccessManager = new QNetworkAccessManager();

    //promenne
    int mPortNumber=123;
    QString mServiceType="_ibisip_udp._udp";
    QHostAddress mTimeServerIP;
    QTimeZone mTimeZone;

    //funkce
    void bonjourStartPublish(QString serviceName, QString serviceType, int port, QString version, QZeroConf &qZeroConf);
    void stopBonjourService();

    static QString timeZoneToIbis(QTimeZone timeZone);
public slots:
    void slotServicePublished();
    void slotDumpZeroConfigError();
    void slotStartDnsSd(bool parameter);
    void slotStop(bool parameter);

signals:
    void signalStav(bool stav);
    void signalStart(); // unused
    void signalStop(); // unused
    void signalServicePublished(QString serviceName);
    void signalErrorMessage(QString message);

};

#endif // TIMESERVICE_H
