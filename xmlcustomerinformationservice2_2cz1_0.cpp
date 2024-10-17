#include "xmlcustomerinformationservice2_2cz1_0.h"

XmlCustomerInformationService2_2CZ1_0::XmlCustomerInformationService2_2CZ1_0() {}




QString XmlCustomerInformationService2_2CZ1_0::AllData2_2CZ1_0( QDomDocument xmlDocument,QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;
    QString vehicleref=QString::number(vehicleState.vehicleNumber);
    int currentStopIndex= vehicleState.currentStopIndex0+1; //modification for stop indexing from 0 (c++ arrays) to 1 (VDV301)
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleState.routeDeviation);
    QString vehicleStopRequested=QString::number(vehicleState.isVehicleStopRequested);
    QString exitSide="right";
    xmlDocument.clear();


    QVector<StopPointDestination> stopPointDestinationList;







    QDomProcessingInstruction dProcessingInformation= xmlCommon2_2CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_2CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild( xmlCommon2_2CZ1_0.TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef= xmlCommon2_2CZ1_0.ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage= xmlCommon2_2CZ1_0.Value(xmlDocument,"DefaultLanguage",xmlCommon2_2CZ1_0.defaultLanguage2_2CZ1_0);
    dAllData.appendChild(dDefaultLanguage);


    if(xmlCommon2_2CZ1_0.isInRange(vehicleState.currentTripIndex,tripList.count(),Q_FUNC_INFO))
    {
        stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;
        QDomElement dTripInformation= xmlCommon2_2CZ1_0.TripInformation2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex,false);
        dAllData.appendChild(dTripInformation);


        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            dTripInformation= xmlCommon2_2CZ1_0.TripInformation2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex+1,true);
            dAllData.appendChild(dTripInformation);
        }
    }

    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        // return "stop list is empty";
    }







    QDomElement dCurrentStopIndex= xmlCommon2_2CZ1_0.Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleState.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested= xmlCommon2_2CZ1_0.Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    if(xmlCommon2_2CZ1_0.isInRange(vehicleState.currentStopIndex0,stopPointDestinationList.count(),Q_FUNC_INFO))
    {
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);
        dAllData.appendChild( xmlCommon2_2CZ1_0.MyOwnVehicleMode(xmlDocument,vehicleState.vehicleMode,vehicleState.vehicleSubMode));
    }

    return  xmlCommon2_2CZ1_0.qDomDocumentToQString(xmlDocument);
}



QString XmlCustomerInformationService2_2CZ1_0::AllData_empty2_2CZ1_0(QDomDocument xmlDocument)
{
    qDebug()<<Q_FUNC_INFO;


    QString vehicleref="33";
    int currentStopIndex= 1;

    QString routeDeviation="onroute";

    QDomProcessingInstruction dProcessingInformation=xmlCommon2_2CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_2CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);
    dAllData.appendChild( xmlCommon2_2CZ1_0.TimeStampTag1_0(xmlDocument));
    QDomElement dVehicleRef= xmlCommon2_2CZ1_0.Value(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage= xmlCommon2_2CZ1_0.Value(xmlDocument,"DefaultLanguage",xmlCommon2_2CZ1_0.defaultLanguage2_2CZ1_0);
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dCurrentStopIndex= xmlCommon2_2CZ1_0.Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex+1));
    dAllData.appendChild(dCurrentStopIndex);
    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);
    /*QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(doorState));
    dAllData.appendChild(dDoorState);*/
    /* QDomElement dVehicleStopRequested=xmlko.createElement("VehicleStopRequested");
    dVehicleStopRequested.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(vehicleStopRequested));
    dAllData.appendChild(dVehicleStopRequested);
    */
    /*
    QDomElement dExitSide = xmlko.createElement("ExitSide");
    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);*/
    /*telo="";
    telo+=xmlko;*/

    return  xmlCommon2_2CZ1_0.qDomDocumentToQString(xmlDocument);
}


//rozpracovano
QString XmlCustomerInformationService2_2CZ1_0::CurrentDisplayContent2_2CZ1_0(QDomDocument xmlDocument, QVector <StopPointDestination> stopPointDestinationList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;
    if (stopPointDestinationList.size()==0)
    {
        qDebug()<<"currentDisplayContent stop list is empty";
        return "stop list is empty";
    }


    QDomProcessingInstruction dProcessingInformation= xmlCommon2_2CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_2CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild( xmlCommon2_2CZ1_0.TimeStampTag1_0(xmlDocument));

    dCurrentDisplayContentData.appendChild( xmlCommon2_2CZ1_0.DisplayContent2_2CZ1_0(xmlDocument,"CurrentDisplayContent",stopPointDestinationList,xmlCommon2_2CZ1_0.defaultLanguage2_2CZ1_0,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);

    return  xmlCommon2_2CZ1_0.qDomDocumentToQString(xmlDocument);

}
