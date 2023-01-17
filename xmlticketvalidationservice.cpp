#include "xmlticketvalidationservice.h"

XmlTicketValidationService::XmlTicketValidationService()
{

}




QString XmlTicketValidationService::TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(int poradi, QVector <ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<Prestup> prestupy)
{
    qDebug()<<"XmlCommon::TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0";
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dGetCurrentTarrifStopResp=xmlko.createElement("TicketValidationService.GetCurrentTariffStopResponse");
    xmlko.appendChild(dGetCurrentTarrifStopResp);
    QDomElement dCurrentTarifStopData=xmlko.createElement("CurrentTariffStopData");
    dCurrentTarifStopData.appendChild(TimeStampTag1_0(xmlko));

    dCurrentTarifStopData.appendChild(StopPoint2_2CZ1_0(docasnySeznamZastavek,poradi,prestupy, defaultniJazyk2_2CZ1_0,poradi) );
    dGetCurrentTarrifStopResp.appendChild(dCurrentTarifStopData);

    return xmlko.toString();
}


QString XmlTicketValidationService::TicketValidationService_GetVehicleDataResponse2_2CZ1_0( CestaUdaje stav)
{
    qDebug()<<"XmlCommon::TicketValidationService_GetVehicleDataResponse2_2CZ1_0";
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dGetVehicleDataResponse=xmlko.createElement("TicketValidationService.GetVehicleDataResponse");
    QDomElement dVehicleData=xmlko.createElement("VehicleData");
    dVehicleData.appendChild(this->TimeStampTag1_0(xmlko));
    dVehicleData.appendChild(this->ref("VehicleRef",QString::number(stav.cisloVozu)));
    dVehicleData.appendChild(this->RouteDeviation(xmlko,stav.routeDeviation));
    dVehicleData.appendChild(this->DoorOpenState(xmlko,stav.doorState));
    dVehicleData.appendChild(this->MyOwnVehicleMode(xmlko,stav.vehicleSubMode,stav.vehicleMode));

    dGetVehicleDataResponse.appendChild(dVehicleData);
    xmlko.appendChild(dGetVehicleDataResponse);
    /*
    QDomElement dGetCurrentTarrifStopResp=xmlko.createElement("TicketValidationService.GetCurrentTariffStopResponse");
    xmlko.appendChild(dGetCurrentTarrifStopResp);
    QDomElement dCurrentTarifStopData=xmlko.createElement("CurrentTariffStopData");
    dCurrentTarifStopData.appendChild(TimeStampTag1_0(xmlko));

    dCurrentTarifStopData.appendChild(stopPoint2_2CZ1_0(docasnySeznamZastavek,poradi,Connections, "cz",poradi) );
    dGetCurrentTarrifStopResp.appendChild(dCurrentTarifStopData);
*/
    return xmlko.toString();
}


QString XmlTicketValidationService::TicketValidationService_GetRazziaResponse2_2CZ1_0( CestaUdaje stav)
{
    qDebug()<<"XmlCommon::TicketValidationService_GetRazziaResponse2_2CZ1_0";
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dGetRazziaResponse=xmlko.createElement("TicketValidationService.GetRazziaResponse");
    QDomElement dRazziaData=xmlko.createElement("RazziaData");
    dRazziaData.appendChild(xmlko.createTextNode(stav.razziaState));
    /*
    dVehicleData.appendChild(this->TimeStampTag1_0(xmlko));
    dVehicleData.appendChild(this->ref("VehicleRef",QString::number(stav.cisloVozu)));
    dVehicleData.appendChild(this->RouteDeviation(xmlko,stav.routeDeviation));
    dVehicleData.appendChild(this->DoorOpenState(xmlko,stav.doorState));
    dVehicleData.appendChild(this->VehicleMode(xmlko,stav.vehicleSubMode,stav.vehicleMode));
*/
    dGetRazziaResponse.appendChild(dRazziaData);
    xmlko.appendChild(dGetRazziaResponse);

    return xmlko.toString();
}
