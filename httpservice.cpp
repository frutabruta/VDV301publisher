#include "httpservice.h"




/*!
 * \brief HttpSluzba::HttpSluzba
 * \param nazevSluzby
 * \param typSluzby
 * \param cisloPortu
 * \param verze
 */
HttpService::HttpService(QString serviceName,QString serviceType, int portNumber,QString version):httpServerPublisher (portNumber,serviceName)
{
    qDebug() <<  Q_FUNC_INFO <<" "<< serviceName <<" "<<QString::number(portNumber);
    mPortNumber=portNumber;
    mServiceName=serviceName;
    mServiceType=serviceType;
    mVersion=version;

    //qDebug()<<"xxx"<<
    connect(&httpServerPublisher ,&HttpServerPublisher::signalServerRuns ,this,&HttpService::slotServerReady, Qt::QueuedConnection);

    connect(&httpServerPublisher ,&HttpServerPublisher::signalContentChanged,this,&HttpService::slotDumpRequestContent);

    connect(&zeroConf,&QZeroConf::error,this,&HttpService::slotDumpZeroConfigError);

    connect(&zeroConf,&QZeroConf::servicePublished,this,&HttpService::slotServicePublished);

    connect(qNetworkAccessManager,&QNetworkAccessManager::finished,this,&HttpService::slotReplyToPostReceived);





}

/*!
 * \brief HttpSluzba::~HttpSluzba
 */
HttpService::~HttpService()
{
    stopBonjourService();
    qDebug()<<Q_FUNC_INFO;
}


/*!
 * \brief HttpSluzba::slotVyprseniCasovace
 */
void HttpService::slotTimerTimeout()
{
    qDebug() <<  Q_FUNC_INFO;
}



/*!
 * \brief HttpSluzba::vyrobHlavickuGet
 * \return
 */
QByteArray HttpService::createGetHeader()
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray header;

    header+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    header+=("Content-Type: application/xml\r\n");
    header+=("Connection: close\r\n");
    header+=("Pragma: no-cache\r\n");
    header+=("\r\n");
    return header;
}


/*!
 * \brief HttpSluzba::vyrobHlavickuSubscribe
 * \return
 */


QString HttpService::createSubscribeHeader()
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray header;
    //this->hlavickaInterni="";
    header+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    header+=("Content-Type: text/xml\r\n");
    header+=("Connection: close\r\n");
    header+=("Pragma: no-cache\r\n");
    header+=("\r\n");
    return header;
}


/*!
 * \brief HttpSluzba::bonjourStartKomplet
 */


void HttpService::slotServerReady(int portNumber)
{
    qDebug() <<  Q_FUNC_INFO << " "<<QString::number(portNumber);
    mPortNumber=portNumber;
    slotStartDnsSd(true);
}

void HttpService::bonjourStartAll()
{
    qDebug() <<  Q_FUNC_INFO;
    //zeroConf.clearServiceTxtRecords();
    this->bonjourStartPublish(this->mServiceName,this->mServiceType,this->mPortNumber,this->mVersion ,zeroConf);
}


/*!
 * \brief HttpSluzba::bonjourStartPublish
 * \param nazevSluzby
 * \param typSluzby
 * \param port
 * \param verze
 * \param instanceZeroConf
 */
void HttpService::bonjourStartPublish(QString serviceName, QString serviceType,int port,QString version, QZeroConf &qZeroConf)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<serviceName<<" "<<version<<" "<<serviceType<<" "<<port;


    qZeroConf.clearServiceTxtRecords();
    qZeroConf.addServiceTxtRecord("ver", version);
    qDebug()<<"Txt record added";

    qZeroConf.startServicePublish(serviceName.toUtf8(), serviceType.toUtf8(), "local", port,0);
  //  void QZeroConf::startServicePublish(const char *name, const char *type, const char *domain, quint16 port, quint32 interface)



}

void HttpService::slotServicePublished()
{
    qDebug() <<  Q_FUNC_INFO <<" "<<this->mServiceName<<" "<<this->mVersion ;
    emit signalServicePublished(this->mServiceName+" "+this->mVersion);
}


/*!
 * \brief HttpSluzba::slotVypisChybuZeroConfig
 */
void HttpService::slotDumpZeroConfigError()
{
    qDebug() <<  Q_FUNC_INFO;
}


/*!
 * \brief HttpSluzba::vyrobSubscribeResponseBody
 * nikde nepouzito
 * \param vysledek
 * \return
 */
QByteArray HttpService::createSubscribeResponseBody(int desiredResult)
{

    qDebug() <<  Q_FUNC_INFO;
    QByteArray textResult="true";
    if (desiredResult!=1)
    {
        textResult="false";
    }
    QByteArray response ="";
    response+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
    response+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
    response+="<Active><Value>";
    response+=textResult;
    response+="</Value></Active>";
    response+="</SubscribeResponse>";
    return response;
}


/*!
 * \brief HttpSluzba::slotVypisObsahRequestu
 * \param vysledek
 * \param struktura
 */
void HttpService::slotDumpRequestContent(QByteArray request,QString structureName)
{
    qDebug() <<  Q_FUNC_INFO;
    QByteArray previousRequest=httpServerPublisher.requestBody;
    QDomDocument xmlRequest;
    qDebug()<<"length of last Request "<<QString::number(previousRequest.length())<<" length of result "<<QString::number(request.length());


    if(!xmlRequest.setContent(QString(request))) // UTF-16 fix
    {
        qDebug()<<"QByteArray could not be imported to QDomDocument";
        return;
    }

    QString firstTag=xmlRequest.firstChildElement().tagName();
    qDebug().noquote()<<"prvni tag "<<firstTag;
    qDebug().noquote()<<"body pozadavku"<<previousRequest;



    if(firstTag=="SubscribeRequest")
    {
        QDomElement subscribeRequest=xmlRequest.firstChildElement("SubscribeRequest");

        QString address=subscribeRequest.firstChildElement("Client-IP-Address").firstChildElement().text() ;
        QString port=subscribeRequest.elementsByTagName("ReplyPort").at(0).toElement().firstChildElement().text() ;
        QString path=subscribeRequest.firstChildElement("ReplyPath").toElement().firstChildElement("Value").firstChild().nodeValue();
        QString fullAddress="http://"+address+":"+port+"/"+path;

        if(address.contains("%")) //IP v fixM  ?
        {
            qDebug()<<" percent sign detected";
            fullAddress="http://["+address+"]:"+port;
        }

        QUrl fullAddressUrl=fullAddress;
        qDebug()<<"komplet adresa subscribera "<<fullAddress;

        Subscriber candidateToSubscribe;
        candidateToSubscribe.address=fullAddressUrl;
        candidateToSubscribe.structure=structureName;
        handleNewSubscriber(candidateToSubscribe);
    }
    if(firstTag=="UnsubscribeRequest")
    {
        QDomElement subscribeRequest=xmlRequest.firstChildElement("UnsubscribeRequest");

        QString address=subscribeRequest.firstChildElement("Client-IP-Address").firstChildElement().text() ;
        QString port=subscribeRequest.elementsByTagName("ReplyPort").at(0).toElement().firstChildElement().text() ;
        QString path=subscribeRequest.firstChildElement("ReplyPath").toElement().firstChildElement("Value").firstChild().nodeValue();
        QString fullAddress="http://"+address+":"+port+"/"+path;

        if(address.contains("%")) //IP v fixM  ?
        {
            qDebug()<<" percent sign detected";
            fullAddress="http://["+address+"]:"+port;
        }

        QUrl fullAddressUrl=fullAddress;
        qDebug()<<"komplet adresa subscribera "<<fullAddress;

        Subscriber candidateToSubscribe;
        candidateToSubscribe.address=fullAddressUrl;
        candidateToSubscribe.structure=structureName;

        removeSubscriber(candidateToSubscribe);

    }
    else if(firstTag=="DeviceManagementService.SetDeviceConfigurationRequest")
    {
        QDomElement subscribeRequest=xmlRequest.firstChildElement("DeviceManagementService.SetDeviceConfigurationRequest");
        QDomNodeList parameters=subscribeRequest.childNodes();
        QMap<QString,QString> values;

        for(int i=0;i<parameters.count();i++)
        {
            QDomNode parameter=parameters.at(i);
            QString key=parameter.nodeName();
            QString value=parameter.firstChildElement("Value").firstChild().nodeValue();
            values[key]=value;

            qDebug()<<"parameter: "<<key<<" "<<value;
        }
        emit signalParameterChange(values);

    }
    else
    {
        qDebug()<<"unknown request";
    }



}



/*!
 * \brief HttpSluzba::PostDoDispleje
 * odesílá jeden payload na jednu adresu
 * \param adresaDispleje
 * \param dataDoPostu
 */

void HttpService::postToSubscriber(QUrl subscriberAddress, QString contentToPost)
{
    qDebug() <<  Q_FUNC_INFO;
    //QByteArray postDataSize = QByteArray::number(dataDoPostu.size());
    QNetworkRequest requestToPost(subscriberAddress);

    //pozadavekPOST.setRawHeader("Content-Length", postDataSize );
    requestToPost.setRawHeader("Content-Type", "text/xml");
    requestToPost.setRawHeader("Expect", "100-continue");
    requestToPost.setRawHeader("Connection", "keep-Alive");
    //pozadavekPOST.setRawHeader("Accept-Encoding", "gzip, deflate");

    QByteArray contentToPostQByteArray=contentToPost.toUtf8() ;
    qNetworkAccessManager->post(requestToPost,contentToPostQByteArray);

}



/*!
 * \brief HttpSluzba::slotPrislaOdpovedNaPost
 * \param reply
 */

void HttpService::slotReplyToPostReceived(QNetworkReply* reply)
{
    qDebug() <<  Q_FUNC_INFO;
    emit this->signalReplyToPostReceived(reply);
}


/*!
 * \brief HttpSluzba::novySubscriber
 * \param subscriber
 * \return
 */
QString HttpService::handleNewSubscriber(Subscriber subscriber)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<subscriber.address;
    QString output;
    if(subscriber.address.toString()=="")
    {
        output="wrong address";
        return output;
    }

    if(isSubscriberOnTheList(subscriberList,subscriber))
    {
        output="subscriber is already on the list "+subscriber.address.toString()+""+subscriber.structure;
    }
    else
    {
        subscriberList.push_back(subscriber);
        output="new subscriber is "+subscriber.address.toString()+""+subscriber.structure;
        postToSubscriber(subscriber.address,structureContentMap.value(subscriber.structure)); //odeslání dat do zařízení hned po odběru
    }

    emit signalDumpSubscriberList(subscriberList);
    return output;

}



/*!
 * \brief HttpSluzba::jeSubscriberNaSeznamu
 * \param seznam
 * \param prvek
 * \return
 */
int HttpService::isSubscriberOnTheList(QVector<Subscriber> subscriberList ,Subscriber testedSubscriber)
{
    qDebug() <<  Q_FUNC_INFO;
    for(int i =0;i<subscriberList.length();i++)
    {
        if((subscriberList[i].address==testedSubscriber.address)&&(subscriberList[i].structure==testedSubscriber.structure ))
        {  return 1;}
    }
    return 0;
}


/*!
 * \brief HttpSluzba::odstranitSubscribera
 * \param index
 * \return
 */
int HttpService::removeSubscriber(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    if ((index<subscriberList.size())&&(index>=0))
    {
        qDebug()<<"removing "<<subscriberList.at(index).address<<subscriberList.at(index).structure;

        subscriberList.removeAt(index);
        emit signalDumpSubscriberList(subscriberList);
        return 1;
    }
    else
    {
        qDebug()<<"out of range";
    }
    return 0;
}

int HttpService::removeSubscriber(Subscriber selectedSubscriber)
{
    qDebug() <<  Q_FUNC_INFO;

    int index=subscriberList.indexOf(selectedSubscriber);
    if(index>=0)
    {
       return removeSubscriber(index);

    }

    return 0;
}



/*!
 * \brief HttpSluzba::nastavObsahTela
 * \param klic
 * \param obsah
 * \return
 */
int HttpService::setBodyContent(QString key, QString content)
{

    qDebug() <<  Q_FUNC_INFO<<" "<<key;
    structureContentMap.insert(key,content);

    return 1;
}




/*!
 * \brief HttpSluzba::asocPoleDoServeru
 * \param pole
 * \return
 */
int HttpService::updateServerContent(QMap<QString,QString> structureMap)
{
    httpServerPublisher.setBodyContent(structureMap);
    return 1;
}

QString HttpService::version() const
{
    return mVersion;
}

void HttpService::setVersion(const QString &newVersion)
{
    mVersion = newVersion;
}



/*!
 * \brief HttpSluzba::zastavBonjourSluzbu
 */
void HttpService::stopBonjourService()
{
    qDebug() <<  Q_FUNC_INFO<<mServiceName<<" "<<mVersion<<" "<<mPortNumber;
    zeroConf.stopServicePublish();

}



/*!
 * \brief HttpSluzba::slotStart
 * \param parametr
 */

void HttpService::slotStartServer()
{
    httpServerPublisher.slotStartServer();
}


void HttpService::slotStartDnsSd(bool parameter)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<this->mServiceName<<" "<<this->mVersion;
    bonjourStartAll();
    emit this->signalStav(true);
    //emit this->startSignal();

}


/*!
 * \brief HttpSluzba::slotStop
 * \param parametr
 */
void HttpService::slotStop(bool parameter)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<this->mServiceName<<" "<<this->mVersion;
    timer.stop();
    stopBonjourService();
    emit this->signalStav(false);
    //emit this->stopSignal();
}


/*!
 *
 * \brief HttpSluzba::slotVymazSubscribery
 *  vyprázdní všechny subscribery
 *
 */
void HttpService::slotRemoveAllSubscribers()
{
    qDebug() <<  Q_FUNC_INFO;
    subscriberList.clear();


}


/*!
 * \brief HttpSluzba::slotZastavCasovac
 */
void HttpService::slotStopTimer()
{
    qDebug() <<  Q_FUNC_INFO;
    timer.stop();

}


QString HttpService::StringToNmToken(QString input)
{
    input=input.replace(" ","-");
    return input;
}

int HttpService::portNumber() const
{
    return mPortNumber;
}

void HttpService::setPortNumber(int newPortNumber)
{
    qDebug() <<  Q_FUNC_INFO;
    mPortNumber = newPortNumber;
    httpServerPublisher.setPortNumber(mPortNumber);
}


QString HttpService::retrieveStructureContentMapValue(QString key)
{
    return  structureContentMap.value(key);
}

void HttpService::updateStructureMap()
{
    updateServerContent(structureContentMap);
    postToAllSubscribers();
}


void HttpService::postToAllSubscribers()
{
    for(int i=0;i<subscriberList.count();i++ )
    {
        postToSubscriber(subscriberList[i].address,structureContentMap.value(subscriberList[i].structure));
    }
}
