#include "httpserverpublisher.h"

HttpServerPublisher::HttpServerPublisher(quint16 ppp,QString vstupSlozkaSluzby)
{
    qDebug() <<  Q_FUNC_INFO;
    cisloPortu=ppp;
    obsahRoot=vyrobHlavickuOk();
    slozkaSluzby=vstupSlozkaSluzby;
    proved();
}

int HttpServerPublisher::proved()
{
    qDebug() <<  Q_FUNC_INFO;

    this->route(slozkaSluzby,obsahTelaPole);
    this->listen();

    return 1;
}

int HttpServerPublisher::route(QString &slozkaSluzby,  QMap<QString,QString> &obsahyBody)
{

    qDebug() <<  Q_FUNC_INFO;
    httpServer.route("/CustomerInformationService/SubscribeAllData", [this ](const QHttpServerRequest &request)
    {
        qDebug()<<"request "<<"/CustomerInformationService/SubscribeAllData";
        //qDebug()<<request.headers()["Connection"].isNull();
        qDebug()<<request.body();
        qDebug()<<"tady se mel spustit emit";

        QString textVysledek="true";
        QString odpoved="";
        odpoved+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
        odpoved+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
        odpoved+="<Active><Value>";
        odpoved+=textVysledek;
        odpoved+="</Value></Active>";
        odpoved+="</SubscribeResponse>";
        this->bodyPozadavku=request.body();
        QString struktura="AllData";
        emit zmenaObsahu(request.body(),struktura);
        return this->obsahSubscribe;

    });
    httpServer.route("/CustomerInformationService/SubscribeCurrentDisplayContent", [this ](const QHttpServerRequest &request)
    {
        //qDebug()<<request.headers()["Connection"].isNull();
        qDebug()<<"request "<<"/CustomerInformationService/SubscribeCurrentDisplayContent";
        qDebug()<<request.body();

        qDebug()<<"tady se mel spustit emit";

        QString textVysledek="true";
        QString odpoved="";
        odpoved+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
        odpoved+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
        odpoved+="<Active><Value>";
        odpoved+=textVysledek;
        odpoved+="</Value></Active>";
        odpoved+="</SubscribeResponse>";
        this->bodyPozadavku=request.body();
        QString struktura="CurrentDisplayContent";
        emit zmenaObsahu(request.body(),struktura);
        return this->obsahSubscribe;

    });

    // qDebug()<<"vnejsi intObsahGet="<<intObsahGet;
    httpServer.route("/"+slozkaSluzby+"/Get<arg>", [&obsahyBody](const QUrl &url,const QHttpServerRequest &request)
    {


        QString struktura= QStringLiteral("%1").arg(url.path());
        qDebug()<<"request "<<struktura;
        //qDebug()<<"argument "<<struktura;

        //qDebug()<<"request "<<"/CustomerInformationService/Get<arg>";


        return obsahyBody.value(struktura);

    });



    httpServer.route("/", [this](const QHttpServerRequest &request)
    {
        //this->obsahRoot;
        qDebug()<<"request HEAD "<<request.headers();
        qDebug()<<"request BODY "<<request.body();
        emit prijemDat(request.body());
        return this->obsahRoot;
        //return intObsahGet;
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
    const auto port = httpServer.listen(QHostAddress::Any,cisloPortu);
    if (!port)
    {
        qDebug() << QCoreApplication::translate(
                        "QHttpServerExample", "Server failed to listen on a port.");
        return 0;
    }
    /* automaticky port
     const auto port = httpServer.listen(QHostAddress::Any);
    if (!port) {
        qDebug() << QCoreApplication::translate(
                "QHttpServerExample", "Server failed to listen on a port.");
        return 0;
    }
    */
    qDebug() << QCoreApplication::translate("QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);
    return 1;
}


void HttpServerPublisher::zapisDoPromenneGet(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    this->slozkaSluzby=vstup;

}

void HttpServerPublisher::zapisDoSubscribe(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    this->obsahSubscribe=vstup;
}

int HttpServerPublisher::nastavObsahTela(QMap<QString,QString> vstup )
{
    qDebug() <<  Q_FUNC_INFO;
    obsahTelaPole=vstup;
    return 1;
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
