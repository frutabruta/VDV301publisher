#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <QUrl>

class Subscriber
{
public:
    explicit Subscriber();
    QUrl address=QUrl("127.0.0.1");
    QString structure="";
    QString path="";



    Subscriber(QUrl address, QString structure);
    Subscriber(QUrl addressWithoutPortNumber, QString structure, int portNumber);
    bool operator ==(const Subscriber &node) const;
signals:

};



#endif // SUBSCRIBER_H
