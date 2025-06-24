#include "xmlticketvalidationservice2_3_new.h"

XmlTicketValidationService2_3_new::XmlTicketValidationService2_3_new() {}






// GetCurrentStopPoint provide information of current stop

Vdv301StopPoint XmlTicketValidationService2_3_new::currentTariffStop(StopPointDestination stopPointDestination)
{
    Vdv301StopPoint result;



    return result;
}


QString XmlTicketValidationService2_3_new::currentTariffStopGen(QDomDocument xmlDocument, Vdv301StopPoint stopPointDestination, QString tripRef)
{
    Vdv301StopPoint result;

    QDomElement dCurrentStopPointResponse=xmlDocument.createElement("TicketValidationService.GetCurrentStopPointResponse");

    QDomElement dCurrentTariffStopData=xmlDocument.createElement("CurrentTariffStopData");

    dCurrentTariffStopData.appendChild(xmlCommon2_3_new.TimeStampTag1_0(xmlDocument));

    dCurrentTariffStopData.appendChild(xmlCommon2_3_new.StopPoint2_3gen(xmlDocument,stopPointDestination,"CurrentTariffStop"));

    dCurrentTariffStopData.appendChild(xmlCommon2_3_new.ref(xmlDocument,"CurrentTripRef",tripRef));

    return xmlCommon2_3_new.qDomDocumentToQString(xmlDocument);
}



// GetRazzia provide, if Razzia was activated
// SubscribeCurrentStopPoint subscribe information of current stop
// UnsubscribeCurrentStopPoint related unsubscribe operation
// SubscribeRazzia subscribe, if Razzia was set
// UnsubscribeRazzia related unsubscribe operation
// GetCurrentLine provide information of current line
// SubscribeCurrentLine subscribe information of current line
// UnsubscribeCurrentLine related unsubscribe operation
// GetVehicleData provide information of the vehicle
// SubscribeVehicleData subscribe information of the vehicle
// UnsubscribeVehicleData related unsubscribe operation
// RetrieveTripData deliver for a stop the defined trip information
