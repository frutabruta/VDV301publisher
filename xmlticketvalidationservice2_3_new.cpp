#include "xmlticketvalidationservice2_3_new.h"

XmlTicketValidationService2_3_new::XmlTicketValidationService2_3_new() {}

// GetCurrentStopPoint provide information of current stop

Vdv301StopPoint XmlTicketValidationService2_3_new::currentTariffStop(StopPointDestination stopPointDestination,int stopPointIterator)
{
    qDebug()<<Q_FUNC_INFO;
    Vdv301StopPoint output;

    return output;
}


QString XmlTicketValidationService2_3_new::currentTariffStopGen(QDomDocument xmlDocument, Vdv301StopPoint stopPointDestination, QString tripRef)
{
    QDomProcessingInstruction dHlavicka=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dCurrentStopPointResponse=xmlDocument.createElement("TicketValidationService.GetCurrentTariffStopResponse");

    QDomElement dCurrentTariffStopData=xmlDocument.createElement("CurrentTariffStopData");
    dCurrentTariffStopData.appendChild(TimeStampTag1_0(xmlDocument));
    dCurrentTariffStopData.appendChild(StopPoint2_3gen(xmlDocument,stopPointDestination,"CurrentTariffStop"));
    dCurrentTariffStopData.appendChild(ref(xmlDocument,"CurrentTripRef",tripRef));
    dCurrentStopPointResponse.appendChild(dCurrentTariffStopData);
    xmlDocument.appendChild(dCurrentStopPointResponse);

    QString result=qDomDocumentToQString(xmlDocument);
    return result;
}

Vdv301VehicleData XmlTicketValidationService2_3_new::vehicleData(VehicleState vehicleState)
{
    Vdv301VehicleData result;
    result.vehicleRef=QString::number(vehicleState.vehicleNumber);
    result.doorOpenState=vehicleState.doorState;
    result.driverNumber=vehicleState.driverNumber;
    result.movingDirectionForward=vehicleState.movingDirectionForward;
    result.routeDeviation=vehicleState.routeDeviation;
    //result.vehicleMode1_0=vehicleInformationGroup.vehicleMode1_0;
    result.vehicleMode=vehicleState.vehicleMode;
    result.vehicleSubMode=vehicleState.vehicleSubMode;

    return result;
}

QString XmlTicketValidationService2_3_new::vehicleDataGen(QDomDocument xmlDocument, Vdv301VehicleData vehicleData)
{
    QDomProcessingInstruction dHlavicka=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dVehicleDataResponse=xmlDocument.createElement("TicketValidationService.GetVehicleDataResponse");

    QDomElement dVehicleData=xmlDocument.createElement("VehicleData");

    //"TimeStamp" type="IBIS-IP.dateTime"
    dVehicleData.appendChild(TimeStampTag1_0(xmlDocument));

    // "VehicleRef" type="IBIS-IP.NMTOKEN"
    dVehicleData.appendChild(ref(xmlDocument,"VehicleRef",vehicleData.vehicleRef));

    // "RouteDeviation" type="RouteDeviationEnumeration" minOccurs="0"
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleData.routeDeviation);
    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dVehicleData.appendChild(dRouteDeviation);

    //"DoorOpenState" type="DoorOpenStateEnumeration" minOccurs="0"/>
    QDomElement dDoorState = xmlDocument.createElement("DoorOpenState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleData.doorOpenState)));
    dVehicleData.appendChild(dDoorState);

    // "MovingDirectionForward" type="IBIS-IP.boolean" minOccurs="0"
    QDomElement dMovingDirectionForward = Value(xmlDocument, "MovingDirectionForward",QString::number(vehicleData.movingDirectionForward));
    dVehicleData.appendChild(dMovingDirectionForward);

    // "VehicleMode" type="VehicleModeEnumeration" minOccurs="0"
    QDomElement dVehicleMode = namedElement(xmlDocument,"VehicleMode","bus");

    dVehicleData.appendChild(dVehicleMode);

    // "DriverNumber" type="IBIS-IP.string" minOccurs="0"
    QDomElement dDriverNumber = Value(xmlDocument, "DriverNumber",vehicleData.driverNumber);
    if(!vehicleData.driverNumber.isEmpty())
    {
        dVehicleData.appendChild(dDriverNumber);
    }
    dVehicleDataResponse.appendChild(dVehicleData);
    xmlDocument.appendChild(dVehicleDataResponse);

    QString result=qDomDocumentToQString(xmlDocument);
    return result;
}

QString XmlTicketValidationService2_3_new::razziaGen(QDomDocument xmlDocument, Vdv301Enumerations::TicketRazziaInformationEnumeration razziaState)
{
    QDomProcessingInstruction dHlavicka=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);

    QDomElement dRazziaResponse=xmlDocument.createElement("TicketValidationService.GetRazziaResponse");

    QDomElement dRazziaData=xmlDocument.createElement("RazziaData");
    dRazziaData.appendChild(TimeStampTag1_0(xmlDocument));
    dRazziaData.appendChild(namedElement(xmlDocument,"RazziaState",Vdv301Enumerations::TicketRazziaInformationEnumerationToQString(razziaState)));
    dRazziaResponse.appendChild(dRazziaData);
    xmlDocument.appendChild(dRazziaResponse);

    QString result=qDomDocumentToQString(xmlDocument);
    return result;
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
