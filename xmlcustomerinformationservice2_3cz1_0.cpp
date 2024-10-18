#include "xmlcustomerinformationservice2_3cz1_0.h"

XmlCustomerInformationService2_3CZ1_0::XmlCustomerInformationService2_3CZ1_0() {}





QString XmlCustomerInformationService2_3CZ1_0::AllData2_3CZ1_0gen(QDomDocument xmlDocument, Vdv301AllData2_3CZ1_0 allData)//, VehicleState vehicleState )
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


    QString vehicleref=allData.vehicleRef;
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(allData.vehicleInformationGroup.routeDeviation);
    QString vehicleStopRequested=QString::number(allData.vehicleInformationGroup.vehicleStopRequested);
    QString exitSide="right";
        //Vdv301Enumerations:: allData.vehicleInformationGroup.exitSide ;

    QDomProcessingInstruction dHlavicka=xmlCommon2_3CZ1_0.createProcessingInformation(xmlDocument,xmlCommon2_3CZ1_0.mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(xmlCommon2_3CZ1_0.TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef=xmlCommon2_3CZ1_0.ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=xmlCommon2_3CZ1_0.Value(xmlDocument,"DefaultLanguage",xmlCommon2_3CZ1_0.defaultLanguage2_3);
    dAllData.appendChild(dDefaultLanguage);


    if(!allData.tripInformationList.isEmpty())
    {
        // xxxx fix following connection
        int counter=0;
        foreach(Vdv301Trip2_3CZ1_0 vdv301trip, allData.tripInformationList)
        {

            QDomElement dTripInformation;
            bool isFollowing=(counter>0);
            dTripInformation=xmlCommon2_3CZ1_0.TripInformation2_3CZ1_0gen(xmlDocument,vdv301trip,isFollowing);
            dAllData.appendChild(dTripInformation);
            counter++;

        }



    }

    QDomElement dCurrentStopIndex=xmlCommon2_3CZ1_0.Value(xmlDocument,"CurrentStopIndex",QString::number(allData.currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(allData.vehicleInformationGroup.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=xmlCommon2_3CZ1_0.Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    dAllData.appendChild(xmlCommon2_3CZ1_0.MyOwnVehicleMode(xmlDocument,allData.vehicleInformationGroup.vehicleMode, allData.vehicleInformationGroup.vehicleSubMode));



    foreach(Vdv301DisplayContent displayContent, allData.globalDisplayContentList)
    {
        dAllData.appendChild(xmlCommon2_3CZ1_0.DisplayContentViaPointDestination2_3gen(xmlDocument,"GlobalDisplayContent", displayContent));
    }


    return xmlCommon2_3CZ1_0.qDomDocumentToQString(xmlDocument);

}


Vdv301AllData2_3CZ1_0 XmlCustomerInformationService2_3CZ1_0::AllData2_3CZ1_0new( QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, QVector<Vdv301DisplayContent> globalDisplayContentList )
{
    qDebug()<<Q_FUNC_INFO;


    Vdv301AllData2_3CZ1_0 allData;

    QVector<Vdv301Connection> vdv301ConnectionList;

    foreach(Connection connection, connectionList)
    {
        vdv301ConnectionList<<connection.toVdv301Connection();
    }


    QVector<Vdv301Trip2_3CZ1_0> vdv301TripList;

    /*
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        return "AllData2.3 stop list is empty";
    }
*/
    //   int currentStopIndex= vehicleState.currentStopIndex0+1; //úprava pro indexování zastávek od 1 vs od 0 pro pole


    allData.vehicleRef=QString::number(vehicleState.vehicleNumber);
    allData.defaultLanguage=xmlCommon2_3_new.defaultLanguage2_3;
    allData.currentStopIndex=vehicleState.currentStopIndex0+1; //úprava pro indexování zastávek od 1 vs od 0 pro pole
    allData.vehicleInformationGroup.vehicleStopRequested=vehicleState.isVehicleStopRequested;
    allData.vehicleInformationGroup.exitSide=Vdv301Enumerations::ExitSideRight;
    allData.vehicleInformationGroup.routeDeviation=vehicleState.routeDeviation;
    allData.vehicleInformationGroup.doorState=vehicleState.doorState;
    allData.vehicleInformationGroup.vehicleMode=vehicleState.vehicleMode;
    allData.vehicleInformationGroup.vehicleSubMode=vehicleState.vehicleSubMode;


    if(!tripList.isEmpty())
    {
        QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

        vdv301TripList<<xmlCommon2_3CZ1_0.TripInformation2_3CZ1_0new(tripList,vdv301ConnectionList,vehicleState,vehicleState.currentTripIndex,false);

        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            //qDebug()<<"abcd navaz Spoj existuje "<<;
            vdv301TripList<<xmlCommon2_3CZ1_0.TripInformation2_3CZ1_0new(tripList,vdv301ConnectionList,vehicleState,vehicleState.currentTripIndex+1,true);

        }
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);

    }

    allData.tripInformationList=vdv301TripList;
    allData.globalDisplayContentList=globalDisplayContentList;


    return allData;
}
