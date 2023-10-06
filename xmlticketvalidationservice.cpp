#include "xmlticketvalidationservice.h"

XmlTicketValidationService::XmlTicketValidationService()
{

}




QString XmlTicketValidationService::TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(QDomDocument &xmlDocument, int currentStopIndex, QVector <StopPointDestination> stopPointDestinationList, QVector<Connection> connectionList)
{
    qDebug()<<Q_FUNC_INFO;

    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dGetCurrentTarrifStopResp=xmlDocument.createElement("TicketValidationService.GetCurrentTariffStopResponse");
    xmlDocument.appendChild(dGetCurrentTarrifStopResp);
    QDomElement dCurrentTarifStopData=xmlDocument.createElement("CurrentTariffStopData");
    dCurrentTarifStopData.appendChild(TimeStampTag1_0(xmlDocument));

    dCurrentTarifStopData.appendChild(StopPoint2_2CZ1_0(xmlDocument,stopPointDestinationList,currentStopIndex,connectionList, defaultLanguage2_2CZ1_0,currentStopIndex) );
    dGetCurrentTarrifStopResp.appendChild(dCurrentTarifStopData);

    return xmlDocument.toString();
}


QString XmlTicketValidationService::TicketValidationService_GetVehicleDataResponse2_2CZ1_0(QDomDocument &xmlDocument, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;

    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dGetVehicleDataResponse=xmlDocument.createElement("TicketValidationService.GetVehicleDataResponse");
    QDomElement dVehicleData=xmlDocument.createElement("VehicleData");
    dVehicleData.appendChild(this->TimeStampTag1_0(xmlDocument));
    dVehicleData.appendChild(this->ref(xmlDocument,"VehicleRef",QString::number(vehicleState.vehicleNumber)));
    dVehicleData.appendChild(this->RouteDeviation(xmlDocument,vehicleState.routeDeviation));
    dVehicleData.appendChild(this->DoorOpenState(xmlDocument,vehicleState.doorState));
    dVehicleData.appendChild(this->MyOwnVehicleMode(xmlDocument,vehicleState.vehicleSubMode,vehicleState.vehicleMode));

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
    return xmlDocument.toString();
}


QString XmlTicketValidationService::TicketValidationService_GetRazziaResponse2_2CZ1_0(QDomDocument &xmlDocument, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;
    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
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

    return xmlDocument.toString();
}
