#ifndef XMLREMOTECONTROLSERVICE2_3CZ1___H
#define XMLREMOTECONTROLSERVICE2_3CZ1___H

#include "xmlcommon.h"

enum RemoteControlMessageType
{
    RemoteControlOk,
    RemoteControlError,
    RemoteControlDestinationRequest,
    RemoteControlGetOnRequest,
    RemoteControlStartRazzia,
    RemoteControlStopRazzia
};
class XmlRemoteControlService2_3CZ1_0 : public XmlCommon
{
public:
    XmlRemoteControlService2_3CZ1_0();
    QString AllData2_3CZ1_0gen(QDomDocument xmlDocument, RemoteControlMessageType messageType, QString messageParameter);
};

#endif // XMLREMOTECONTROLSERVICE2_3CZ1___H
