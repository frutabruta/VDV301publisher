#include "subscriber.h"

Subscriber::Subscriber()
{
    this->address=QUrl("127.0.0.1:80");
    this->structure="";
}

Subscriber::Subscriber(QUrl address,QString structure)
{
    this->address=address;
    this->structure=structure;
}


Subscriber::Subscriber(QUrl addressWithoutPortNumber,QString structure, int portNumber)
{
    this->address=addressWithoutPortNumber;
    this->structure=structure;
}


bool Subscriber::operator==(const Subscriber &node) const
{
    return address==node.address && structure == node.structure;
}
