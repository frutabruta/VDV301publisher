#include "xmlticketvalidationservice2_2cz1_0.h"

XmlTicketValidationService2_2CZ1_0::XmlTicketValidationService2_2CZ1_0() {}


QString XmlTicketValidationService2_2CZ1_0::TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(QDomDocument xmlDocument, int currentStopIndex, QVector <StopPointDestination> stopPointDestinationList, QVector<Connection> connectionList)
{
    qDebug()<<Q_FUNC_INFO;

    QDomProcessingInstruction dProcessingInformation= xmlCommon2_2CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_2CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dGetCurrentTarrifStopResp=xmlDocument.createElement("TicketValidationService.GetCurrentTariffStopResponse");
    xmlDocument.appendChild(dGetCurrentTarrifStopResp);
    QDomElement dCurrentTarifStopData=xmlDocument.createElement("CurrentTariffStopData");
    dCurrentTarifStopData.appendChild(xmlCommon2_2CZ1_0.TimeStampTag1_0(xmlDocument));

    dCurrentTarifStopData.appendChild(xmlCommon2_2CZ1_0.StopPoint2_2CZ1_0(xmlDocument,stopPointDestinationList,currentStopIndex,connectionList, xmlCommon2_2CZ1_0.defaultLanguage2_2CZ1_0,currentStopIndex) );
    dGetCurrentTarrifStopResp.appendChild(dCurrentTarifStopData);

    return xmlCommon2_2CZ1_0.qDomDocumentToQString(xmlDocument);
}



QString XmlTicketValidationService2_2CZ1_0::TicketValidationService_GetVehicleDataResponse2_2CZ1_0(QDomDocument xmlDocument, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;

    QDomProcessingInstruction dProcessingInformation=xmlCommon2_2CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_2CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dGetVehicleDataResponse=xmlDocument.createElement("TicketValidationService.GetVehicleDataResponse");
    QDomElement dVehicleData=xmlDocument.createElement("VehicleData");
    dVehicleData.appendChild(xmlCommon2_2CZ1_0.TimeStampTag1_0(xmlDocument));
    dVehicleData.appendChild(xmlCommon2_2CZ1_0.ref(xmlDocument,"VehicleRef",QString::number(vehicleState.vehicleNumber)));
    dVehicleData.appendChild(xmlCommon2_2CZ1_0.RouteDeviation(xmlDocument,Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleState.routeDeviation)));
    dVehicleData.appendChild(xmlCommon2_2CZ1_0.DoorOpenState(xmlDocument,Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleState.doorState)));
    dVehicleData.appendChild(xmlCommon2_2CZ1_0.MyOwnVehicleMode(xmlDocument,vehicleState.vehicleSubMode,vehicleState.vehicleMode));

    dGetVehicleDataResponse.appendChild(dVehicleData);
    xmlDocument.appendChild(dGetVehicleDataResponse);
    /*
    QDomElement dGetCurrentTarrifStopResp=xmlko.createElement("TicketValidationService.GetCurrentTariffStopResponse");
    xmlko.appendChild(dGetCurrentTarrifStopResp);
    QDomElement dCurrentTarifStopData=xmlko.createElement("CurrentTariffStopData");
    dCurrentTarifStopData.appendChild(TimeStampTag1_0(xmlko));

    dCurrentTarifStopData.appendChild(stopPoint2_2CZ1_0(docasnySeznamZastavek,poradi,Connections, "cz",poradi) );
    dGetCurrentTarrifStopResp.appendChild(dCurrentTarifStopData);
*/
    return xmlCommon2_2CZ1_0.qDomDocumentToQString(xmlDocument);
}


QString XmlTicketValidationService2_2CZ1_0::TicketValidationService_GetRazziaResponse2_2CZ1_0(QDomDocument xmlDocument, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;
    QDomProcessingInstruction dProcessingInformation=xmlCommon2_2CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_2CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dGetRazziaResponse=xmlDocument.createElement("TicketValidationService.GetRazziaResponse");
    QDomElement dRazziaData=xmlDocument.createElement("RazziaData");
    dRazziaData.appendChild(xmlDocument.createTextNode(vehicleState.razziaState));
    /*
    dVehicleData.appendChild(this->TimeStampTag1_0(xmlko));
    dVehicleData.appendChild(this->ref("VehicleRef",QString::number(stav.cisloVozu)));
    dVehicleData.appendChild(this->RouteDeviation(xmlko,stav.routeDeviation));
    dVehicleData.appendChild(this->DoorOpenState(xmlko,stav.doorState));
    dVehicleData.appendChild(this->VehicleMode(xmlko,stav.vehicleSubMode,stav.vehicleMode));
*/
    dGetRazziaResponse.appendChild(dRazziaData);
    xmlDocument.appendChild(dGetRazziaResponse);

    return xmlCommon2_2CZ1_0.qDomDocumentToQString(xmlDocument);
}
