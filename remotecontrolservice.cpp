#include "remotecontrolservice.h"


RemoteControlService::RemoteControlService(QString serviceName, QString serviceType, int portNumber, QString version, QString serviceNamePostfix):HttpService( serviceName,serviceType, portNumber,version,serviceNamePostfix)
{}
