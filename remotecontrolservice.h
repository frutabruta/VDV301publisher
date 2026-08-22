#ifndef REMOTECONTROLSERVICE_H
#define REMOTECONTROLSERVICE_H

#include "httpservice.h"

class RemoteControlService : public HttpService
{
public:
    RemoteControlService();
    explicit RemoteControlService(QString serviceName, QString serviceType, int portNumber, QString version, QString serviceNamePostfix="");
};

#endif // REMOTECONTROLSERVICE_H
