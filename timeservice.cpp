#include "timeservice.h"
#include <QDebug>


/*!
 * \brief TimeService::HttpSluzba
 * \param nazevSluzby
 * \param typSluzby
 * \param cisloPortu
 * \param verze
 */
TimeService::TimeService(QString serviceName,QString serviceType, int portNumber,QString version)//:httpServerPublisher (portNumber,serviceName)
{
    qDebug() <<  Q_FUNC_INFO <<" "<< serviceName <<" "<<QString::number(portNumber);
    mPortNumber=portNumber;
    mServiceName=serviceName;
    mServiceType=serviceType;
    mVersion=version;

    connect(&zeroConf,&QZeroConf::error,this,&TimeService::slotDumpZeroConfigError);
    connect(&zeroConf,&QZeroConf::servicePublished,this,&TimeService::slotServicePublished);
}

TimeService::~TimeService()
{
    stopBonjourService();
    qDebug()<<Q_FUNC_INFO;
}


void TimeService::bonjourStartAll()
{
    qDebug() <<  Q_FUNC_INFO;
    //zeroConf.clearServiceTxtRecords();
    this->bonjourStartPublish(this->mServiceName,this->mServiceType,this->mPortNumber,this->mVersion ,zeroConf);
}

int TimeService::portNumber() const
{
    return mPortNumber;
}

void TimeService::setPortNumber(int newPortNumber)
{
    mPortNumber = newPortNumber;
}

QHostAddress TimeService::timeServerIp() const 
{
    return mTimeServerIP;
}

void TimeService::setTimeServerIp(QHostAddress addr) 
{
    mTimeServerIP = addr;
}

QTimeZone TimeService::timeZone() const 
{
    return mTimeZone;
}

QTimeZone TimeService::resolveTimeZone() const 
{
    if (mTimeZone.isValid()) 
    {
        return mTimeZone;
    } 
    else 
    {
        return QTimeZone::systemTimeZone();
    }
}

void TimeService::setTimeZone(QTimeZone timeZone) 
{
    mTimeZone = timeZone;
}

/*!
 * \brief HttpSluzba::bonjourStartPublish
 * \param nazevSluzby
 * \param typSluzby
 * \param port
 * \param verze
 * \param instanceZeroConf
 */
void TimeService::bonjourStartPublish(QString serviceName, QString serviceType,int port,QString version, QZeroConf &qZeroConf)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<serviceName<<" "<<version<<" "<<serviceType<<" "<<port;

    qZeroConf.clearServiceTxtRecords();
    qZeroConf.addServiceTxtRecord("ver", version);
    if (!mTimeServerIP.isNull()) 
    {
        qZeroConf.addServiceTxtRecord("sntp-server", mTimeServerIP.toString());
    }
    qZeroConf.addServiceTxtRecord("timezone", timeZoneToIbis(resolveTimeZone()));
    qDebug()<<"Txt record added";

    qZeroConf.startServicePublish(serviceName.toUtf8(), serviceType.toUtf8(), "local", port,0);
    //  void QZeroConf::startServicePublish(const char *name, const char *type, const char *domain, quint16 port, quint32 interface)
}

QString TimeService::timeZoneToIbis(QTimeZone timeZone)
{
    QDateTime now = QDateTime::currentDateTimeUtc().toTimeZone(timeZone); //Qt5.15 fix
    int offset = timeZone.offsetFromUtc(now);

    QString desc = "UTC";
    if (offset != 0) 
    {
        desc += offset > 0 ? "+" : "-";
        QTime time = QTime::fromMSecsSinceStartOfDay(qAbs(offset) * 1000);
        if (time.minute() != 0) 
        {
            desc += time.toString("h:mm");
        }
        else 
        {
            desc += time.toString("h");
        }
    }
    return desc;
}

/*!
 * \brief HttpSluzba::slotVypisChybuZeroConfig
 */
void TimeService::slotDumpZeroConfigError()
{
    qDebug() <<  Q_FUNC_INFO;
}


/*!
 * \brief HttpSluzba::zastavBonjourSluzbu
 */
void TimeService::stopBonjourService()
{
    qDebug() <<  Q_FUNC_INFO<<mServiceName<<" "<<mVersion<<" "<<mPortNumber;
    zeroConf.stopServicePublish();
}


void TimeService::slotStartDnsSd(bool parameter)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<this->mServiceName<<" "<<this->mVersion;
    bonjourStartAll();
    emit this->signalStav(true);
    //emit this->startSignal();
}

void TimeService::slotStop(bool parameter)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<this->mServiceName<<" "<<this->mVersion;
    stopBonjourService();
    emit this->signalStav(false);
    //emit this->stopSignal();
}

void TimeService::slotServicePublished()
{
    qDebug() <<  Q_FUNC_INFO <<" "<<this->mServiceName<<" "<<this->mVersion ;
    emit signalServicePublished(this->mServiceName+" "+this->mVersion);
}
