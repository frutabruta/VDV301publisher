#ifndef HTTPSERVERPUBLISHER_H
#define HTTPSERVERPUBLISHER_H

#include <QObject>
#include <QtHttpServer>

class HttpServerPublisher: public QObject
{
    Q_OBJECT
public:
    //constructor
    HttpServerPublisher(quint16 newPortNumber, QString newServiceFolder);

    //variables
    QByteArray requestBody="xx";

    //functions
    int setBodyContent(QMap<QString, QString> input);

    //

    quint16 portNumber() const;
    void setPortNumber(quint16 newPortNumber);

private:

    //library instances
    QHttpServer httpServer;

    //variables
    quint16 mPortNumber=0;
    QString mServiceFolder="obsahGet";
    QString mContentRoot="";
    QString mContentSubscribe="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><Active><Value>true</Value></Active></SubscribeResponse>";
    QString mContentUnsubscribe="<UnsubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><Active><Value>true</Value></Active></UnsubscribeResponse>";

    QString mContentSet="<?xml version=\"1.0\" encoding=\"utf-8\"?><DataAcceptedResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><DataAcceptedResponseData><TimeStamp><Value>2022-09-12T12:28:22.6142112+02:00</Value></TimeStamp><DataAccepted><Value>true</Value></DataAccepted></DataAcceptedResponseData></DataAcceptedResponse>";
    QMap<QString,QString> mBodyContentArray;

    //functions
    int listen();

    int route(QString &serviceFolder, QMap<QString, QString> &contentBody);
    QString createHeaderOk();
    void setGetContent(QString input);
    void setSubscribeContent(QString input);

    QString createSubscribeResponse(QString result);
signals:
    void signalContentChanged(QByteArray result,QString structure) ;
    void signalDataReceived(QString result) ;
    void signalServerRuns(int portNumber);


public slots:
    void slotTest(int port);
    int slotStartServer();
};

#endif // HTTPSERVERPUBLISHER_H
