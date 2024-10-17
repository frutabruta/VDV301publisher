#include "xmlcustomerinformationservice2_3.h"

XmlCustomerInformationService2_3::XmlCustomerInformationService2_3() {}




QString XmlCustomerInformationService2_3::AllData2_3(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;

    /*
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        return "AllData2.3 stop list is empty";
    }
*/


    QString vehicleref=QString::number(vehicleState.vehicleNumber);
    int currentStopIndex= vehicleState.currentStopIndex0+1; //úprava pro indexování zastávek od 1 vs od 0 pro pole
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleState.routeDeviation);
    QString vehicleStopRequested=QString::number(vehicleState.isVehicleStopRequested);
    QString exitSide="right";

    QDomProcessingInstruction dHlavicka=xmlCommon2_3.createProcessingInformation(xmlDocument,xmlCommon2_3.mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(xmlCommon2_3.TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef=xmlCommon2_3.ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=xmlCommon2_3.Value(xmlDocument,"DefaultLanguage",xmlCommon2_3.defaultLanguage2_3);
    dAllData.appendChild(dDefaultLanguage);


    if(!tripList.isEmpty())
    {
        QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

        QDomElement dTripInformation=xmlCommon2_3.TripInformation2_3(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex,false);
        dAllData.appendChild(dTripInformation);
        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            //qDebug()<<"abcd navaz Spoj existuje "<<;
            dTripInformation=xmlCommon2_3.TripInformation2_3(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex+1,true);
            dAllData.appendChild(dTripInformation);
        }
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);

    }

    QDomElement dCurrentStopIndex=xmlCommon2_3.Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleState.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=xmlCommon2_3.Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    dAllData.appendChild(xmlCommon2_3.MyOwnVehicleMode(xmlDocument,vehicleState.vehicleMode,vehicleState.vehicleSubMode));

    return xmlCommon2_3.qDomDocumentToQString(xmlDocument);

}
//xx


QString XmlCustomerInformationService2_3::CurrentDisplayContent2_3(QDomDocument xmlDocument, QVector <StopPointDestination> stopPointDestinationList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;

    if (stopPointDestinationList.size()==0)
    {
        qDebug()<<"currentDisplayContent empty stop list";
        return "empty stop list";
    }
    QString language=xmlCommon2_3.defaultLanguage2_3;

    QDomProcessingInstruction dProcessingInformation=xmlCommon2_3.createProcessingInformation(xmlDocument,xmlCommon2_3.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild(xmlCommon2_3.TimeStampTag1_0(xmlDocument));

    /*
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentFront));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentSide));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentRear));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentLcd));
*/

    QVector<QDomElement> displayContentDomVector;


    displayContentDomVector<<xmlCommon2_3.DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentFront);
    displayContentDomVector<<xmlCommon2_3.DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentSide);
    displayContentDomVector<<xmlCommon2_3.DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentRear);
    displayContentDomVector<<xmlCommon2_3.DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentLcd);


    foreach(QDomElement dDisplayContentSide, displayContentDomVector)
    {
        dCurrentDisplayContentData.appendChild(dDisplayContentSide);
    }


    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);

    return xmlCommon2_3.qDomDocumentToQString(xmlDocument);
}
