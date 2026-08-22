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

    //qDebug()<<"xxx"<<

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
    qDebug()<<"Txt record added";

    qZeroConf.startServicePublish(serviceName.toUtf8(), serviceType.toUtf8(), "local", port,0);
    //  void QZeroConf::startServicePublish(const char *name, const char *type, const char *domain, quint16 port, quint32 interface)



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

