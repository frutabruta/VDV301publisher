#include "remotecontrolservice.h"


RemoteControlService::RemoteControlService(QString serviceName, QString serviceType, int portNumber, QString version, QString serviceNamePostfix):HttpService( serviceName,serviceType, portNumber,version,serviceNamePostfix)
{}

void RemoteControlService::postToSubscribers(QMap<QString,QString> structureContentMap)
{
    for(int i=0;i<subscriberList.count();i++ )
    {
        postToSubscriber(subscriberList[i].address,structureContentMap.value(subscriberList[i].structure));
    }
}