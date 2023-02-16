#include "httpserverpublisher.h"

HttpServerPublisher::HttpServerPublisher(quint16 portVstup,QString vstupSlozkaSluzby)
{
    qDebug() <<  Q_FUNC_INFO;
    mCisloPortu=portVstup;
    mObsahRoot=vyrobHlavickuOk();
    mSlozkaSluzby=vstupSlozkaSluzby;
    connect(this,&HttpServerPublisher::signalServerBezi,this,&HttpServerPublisher::slotTest);

 //   slotStartServer();



}

int HttpServerPublisher::slotStartServer()
{
    qDebug() <<  Q_FUNC_INFO;

    this->route(mSlozkaSluzby,mObsahTelaPole);
    mCisloPortu=this->listen();

    emit signalServerBezi(mCisloPortu);

    return 1;
}

int HttpServerPublisher::route(QString &slozkaSluzby,  QMap<QString,QString> &obsahyBody)
{

    qDebug() <<  Q_FUNC_INFO;
    qDebug() << slozkaSluzby;

    httpServer.route("/"+slozkaSluzby+"/Subscribe<arg>", [this](const QUrl &url,const QHttpServerRequest &request)
    {
        QString struktura= QStringLiteral("%1").arg(url.path());
        qDebug()<<"subscribe pozadavek "<<struktura;
        qDebug().noquote()<<request.body();
    /*
        QString textVysledek="true";
        QString odpoved=vyrobSubscribeResponse(textVysledek);
    */
        this->bodyPozadavku=request.body();
        emit zmenaObsahu(request.body(),struktura);
        return this->mObsahSubscribe;

    });

    httpServer.route("/"+slozkaSluzby+"/Set<arg>", [this](const QUrl &url,const QHttpServerRequest &request)
    {
        QString struktura= QStringLiteral("%1").arg(url.path());
        qDebug().noquote()<<"request Set"<<struktura;
        this->bodyPozadavku=request.body();
        emit zmenaObsahu(request.body(),struktura);
        return this->mObsahSet;
    });

    httpServer.route("/"+slozkaSluzby+"/Get<arg>", [&obsahyBody](const QUrl &url,const QHttpServerRequest &request)
    {
        QString struktura= QStringLiteral("%1").arg(url.path());
        qDebug().noquote()<<"request Get"<<struktura;
        return obsahyBody.value(struktura);
    });


    httpServer.route("/", [this](const QHttpServerRequest &request)
    {
        qDebug()<<"request HEAD "<<request.headers();
        qDebug()<<"request BODY "<<request.body();

        emit prijemDat(request.body());
        return this->mObsahRoot;
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

    if (mCisloPortu!=0)
    {
        /* manuální volba portu*/
        const auto port = httpServer.listen(QHostAddress::Any,mCisloPortu);
        if (!port)
        {
            qDebug() << QCoreApplication::translate(
                            "QHttpServerExample", "Server failed to listen on a port.");

        }

        qDebug()<<"Startuju na portu:"<<QString::number(port);
        return port;

        qDebug() << QCoreApplication::translate("QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);

    }
    else
    {
        /* automaticky port */
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


void HttpServerPublisher::zapisDoPromenneGet(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    this->mSlozkaSluzby=vstup;

}

void HttpServerPublisher::zapisDoSubscribe(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    this->mObsahSubscribe=vstup;
}

int HttpServerPublisher::nastavObsahTela(QMap<QString,QString> vstup )
{
    qDebug() <<  Q_FUNC_INFO;
    mObsahTelaPole=vstup;
    return 1;
}

quint16 HttpServerPublisher::cisloPortu() const
{
    return mCisloPortu;
}

void HttpServerPublisher::setCisloPortu(quint16 newCisloPortu)
{
    qDebug() <<  Q_FUNC_INFO <<QString::number(newCisloPortu);
    mCisloPortu = newCisloPortu;
}


QString HttpServerPublisher::vyrobHlavickuOk()
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

QString HttpServerPublisher::vyrobSubscribeResponse(QString result)
{
    QString odpoved;
    odpoved+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
    odpoved+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
    odpoved+="<Active><Value>";
    odpoved+=result;
    odpoved+="</Value></Active>";
    odpoved+="</SubscribeResponse>";
    return odpoved;
}

void HttpServerPublisher::slotTest(int port)
{
    qDebug()<<Q_FUNC_INFO<<" "<<QString::number(port);
}
