#include "xmlremotecontrolservice2_3cz1_0.h"

XmlRemoteControlService2_3CZ1_0::XmlRemoteControlService2_3CZ1_0() {}


QString XmlRemoteControlService2_3CZ1_0::AllData2_3CZ1_0gen(QDomDocument xmlDocument, RemoteControlMessageType messageType, QString messageParameter)//, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;

    QDomProcessingInstruction dHlavicka=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dGetAllDataResponse=xmlDocument.createElement("RemoteControlService.GetAllDataResponse");
    xmlDocument.appendChild(dGetAllDataResponse);
    dGetAllDataResponse.appendChild(TimeStampTag1_0(xmlDocument));


    QDomElement dMessageContent=xmlDocument.createElement("MessageContent");




    QString messageTypeString="";

    switch (messageType)
    {

    case RemoteControlOk:
        messageTypeString="Ok";
        break;
    case RemoteControlError:
        messageTypeString="Error";
        break;
    case RemoteControlDestinationRequest:
        messageTypeString="DestinationRequest";
        break;
    case RemoteControlGetOnRequest:
        messageTypeString="GetOnRequest";
        break;
    case RemoteControlStartRazzia:
        messageTypeString="StartRazzia";
        break;
    case RemoteControlStopRazzia:
        messageTypeString="StopRazzia";
        break;
    }

    QDomElement dMessageType=xmlDocument.createElement("MessageType");

    dMessageContent.appendChild(namedElement(xmlDocument,"MessageType",messageTypeString));

    if(messageParameter!="")
    {
        dMessageContent.appendChild(Value(xmlDocument,"MessageParameter",messageParameter));
    }

    dGetAllDataResponse.appendChild(dMessageContent);

    return qDomDocumentToQString(xmlDocument);
}
