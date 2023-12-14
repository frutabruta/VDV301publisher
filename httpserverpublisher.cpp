#include "httpserverpublisher.h"

HttpServerPublisher::HttpServerPublisher(quint16 newPortNumber,QString newServiceFolder)
{
    qDebug() <<  Q_FUNC_INFO;
    mPortNumber=newPortNumber;
    mContentRoot=createHeaderOk();
    mServiceFolder=newServiceFolder;
    connect(this,&HttpServerPublisher::signalServerRuns,this,&HttpServerPublisher::slotTest);

    //   slotStartServer();



}

int HttpServerPublisher::slotStartServer()
{
    qDebug() <<  Q_FUNC_INFO;

    this->route(mServiceFolder,mBodyContentArray);
    mPortNumber=this->listen();

    emit signalServerRuns(mPortNumber);

    return 1;
}

int HttpServerPublisher::route(QString &serviceFolder,  QMap<QString,QString> &contentBody)
{

    qDebug() <<  Q_FUNC_INFO;
    qDebug() << serviceFolder;

    httpServer.route("/"+serviceFolder+"/Subscribe<arg>", [this](const QUrl &url,const QHttpServerRequest &request)
                     {
                         QString structure= QStringLiteral("%1").arg(url.path());
                         qDebug()<<"subscribe request "<<structure;
                         qDebug().noquote()<<request.body();
                         /*
        QString textVysledek="true";
        QString odpoved=vyrobSubscribeResponse(textVysledek);
    */
                         this->requestBody=request.body();
                         emit signalContentChanged(request.body(),structure);
                         return this->mContentSubscribe;

                     });

    httpServer.route("/"+serviceFolder+"/Unsubscribe<arg>", [this](const QUrl &url,const QHttpServerRequest &request)
                     {
                         QString structure= QStringLiteral("%1").arg(url.path());
                         qDebug()<<"unsubscribe request "<<structure;
                         qDebug().noquote()<<request.body();
                         /*
        QString textVysledek="true";
        QString odpoved=vyrobSubscribeResponse(textVysledek);
    */
                         this->requestBody=request.body();
                         emit signalContentChanged(request.body(),structure);
                         return this->mContentUnsubscribe;

                     });

    httpServer.route("/"+serviceFolder+"/Set<arg>", [this](const QUrl &url,const QHttpServerRequest &request)
                     {
                         QString struktura= QStringLiteral("%1").arg(url.path());
                         qDebug().noquote()<<"request Set"<<struktura;
                         this->requestBody=request.body();
                         emit signalContentChanged(request.body(),struktura);
                         return this->mContentSet;
                     });

    httpServer.route("/"+serviceFolder+"/Get<arg>", [&contentBody](const QUrl &url,const QHttpServerRequest &request)
                     {
                         QString structure= QStringLiteral("%1").arg(url.path());
                         qDebug().noquote()<<"request Get"<<structure;
                         return contentBody.value(structure);
                     });


    httpServer.route("/", [this](const QHttpServerRequest &request)
                     {
                         qDebug()<<"request HEAD "<<request.headers();
                         qDebug()<<"request BODY "<<request.body();

                         emit signalDataReceived(request.body());
                         return this->mContentRoot;
                     });

    httpServer.afterRequest([](QHttpServerResponse &&resp)
                            {
                                resp.setHeader("Server", "Super server!");
                                resp.setHeader("Content-Type", "text/xml");
                                return std::move(resp);
                            });
    return 1;
}


int HttpServerPublisher::listen()
{
    qDebug() <<  Q_FUNC_INFO;

    if (mPortNumber!=0)
    {
        /* manual port choice */
        const auto port = httpServer.listen(QHostAddress::Any,mPortNumber);
        if (!port)
        {
            qDebug() << QCoreApplication::translate(
                "QHttpServerExample", "Server failed to listen on a port.");

        }

        qDebug()<<"Starting server at port:"<<QString::number(port);
        return port;

        qDebug() << QCoreApplication::translate("QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);

    }
    else
    {
        /* automatic port selection */
        const auto port = httpServer.listen(QHostAddress::Any);
        if (!port) {
            qDebug() << QCoreApplication::translate(
                "QHttpServerExample", "Server failed to listen on a port.");

        }

        return port;

        qDebug() << QCoreApplication::translate("QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);

    }


    return 1;
}


void HttpServerPublisher::setGetContent(QString input)
{
    qDebug() <<  Q_FUNC_INFO;
    this->mServiceFolder=input;

}

void HttpServerPublisher::setSubscribeContent(QString input)
{
    qDebug() <<  Q_FUNC_INFO;
    this->mContentSubscribe=input;
}

int HttpServerPublisher::setBodyContent(QMap<QString,QString> input )
{
    qDebug() <<  Q_FUNC_INFO;
    mBodyContentArray=input;
    return 1;
}

quint16 HttpServerPublisher::portNumber() const
{
    return mPortNumber;
}

void HttpServerPublisher::setPortNumber(quint16 newPortNumber)
{
    qDebug() <<  Q_FUNC_INFO <<QString::number(newPortNumber);
    mPortNumber = newPortNumber;
}


QString HttpServerPublisher::createHeaderOk()
{
    qDebug() <<  Q_FUNC_INFO;
    QString hlavicka;

    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}

QString HttpServerPublisher::createSubscribeResponse(QString result)
{
    QString response;
    response+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
    response+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
    response+="<Active><Value>";
    response+=result;
    response+="</Value></Active>";
    response+="</SubscribeResponse>";
    return response;
}

void HttpServerPublisher::slotTest(int port)
{
    qDebug()<<Q_FUNC_INFO<<" "<<QString::number(port);
}
