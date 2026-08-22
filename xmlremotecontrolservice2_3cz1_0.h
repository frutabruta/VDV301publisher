#ifndef XMLREMOTECONTROLSERVICE2_3CZ1___H
#define XMLREMOTECONTROLSERVICE2_3CZ1___H

#include "xmlcommon.h"
#include "VDV301DataStructures/vdv301enumerations.h"

class XmlRemoteControlService2_3CZ1_0 : public XmlCommon
{
public:
    XmlRemoteControlService2_3CZ1_0();
    QString AllData2_3CZ1_0gen(QDomDocument xmlDocument, Vdv301Enumerations::RemoteControlMessageTypeEnumeration messageType, QString messageParameter);
};

#endif // XMLREMOTECONTROLSERVICE2_3CZ1___H
