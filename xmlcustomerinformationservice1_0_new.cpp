#include "xmlcustomerinformationservice1_0_new.h"


#include "VDV301DataStructures/connectionmpv.h"
XmlCustomerInformationService1_0_new::XmlCustomerInformationService1_0_new() {}








Vdv301AllData XmlCustomerInformationService1_0_new::AllData1_0new( QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, QVector<Vdv301DisplayContent> globalDisplayContentList )
{
    qDebug()<<Q_FUNC_INFO;


    Vdv301AllData allData;

    QVector<Vdv301Connection> vdv301ConnectionList;

    foreach(Connection connection, connectionList)
    {

        vdv301ConnectionList<<xmlCommon1_0_new.connectionToVdv301Connection(connection,xmlCommon1_0_new.lcdClass);
    }


    QVector<Vdv301Trip> vdv301TripList;

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
    allData.defaultLanguage=xmlCommon1_0_new.defaultLanguage2_3;
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

        vdv301TripList<<xmlCommon1_0_new.TripInformation1_0new(tripList,vdv301ConnectionList,vehicleState,vehicleState.currentTripIndex,false);

        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            //qDebug()<<"abcd navaz Spoj existuje "<<;
            vdv301TripList<<xmlCommon1_0_new.TripInformation1_0new(tripList,vdv301ConnectionList,vehicleState,vehicleState.currentTripIndex+1,true);

        }
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);

    }

    allData.tripInformationList=vdv301TripList;
    allData.globalDisplayContentList=globalDisplayContentList;


    return allData;
}



QString XmlCustomerInformationService1_0_new::AllData1_0gen(QDomDocument xmlDocument, Vdv301AllData allData)//, VehicleState vehicleState )
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

    QDomProcessingInstruction dHlavicka=xmlCommon1_0_new.createProcessingInformation(xmlDocument,xmlCommon1_0_new.mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(xmlCommon1_0_new.TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef=xmlCommon1_0_new.ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=xmlCommon1_0_new.Value(xmlDocument,"DefaultLanguage",xmlCommon1_0_new.defaultLanguage2_3);
    dAllData.appendChild(dDefaultLanguage);


    if(!allData.tripInformationList.isEmpty())
    {
        // xxxx fix following connection
        int counter=0;
        foreach(Vdv301Trip vdv301trip, allData.tripInformationList)
        {

            QDomElement dTripInformation;
            bool isFollowing=(counter>0);
            dTripInformation=xmlCommon1_0_new.TripInformation1_0gen(xmlDocument,vdv301trip,isFollowing);
            dAllData.appendChild(dTripInformation);
            counter++;

        }



    }

    QDomElement dCurrentStopIndex=xmlCommon1_0_new.Value(xmlDocument,"CurrentStopIndex",QString::number(allData.currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(allData.vehicleInformationGroup.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=xmlCommon1_0_new.Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

   // dAllData.appendChild(xmlCommon1_0_new.MyOwnVehicleMode(xmlDocument,allData.vehicleInformationGroup.vehicleMode, allData.vehicleInformationGroup.vehicleSubMode));

    QDomElement dVehicleMode = xmlDocument.createElement("VehicleMode").appendChild(xmlDocument.createTextNode("bus")).toElement();


    dAllData.appendChild(dVehicleMode);



    foreach(Vdv301DisplayContent displayContent, allData.globalDisplayContentList)
    {
        dAllData.appendChild(xmlCommon1_0_new.DisplayContentViaPointDestination1_0gen(xmlDocument,"GlobalDisplayContent", displayContent));
    }




    return xmlCommon1_0_new.qDomDocumentToQString(xmlDocument);

}




QVector<Vdv301DisplayContent> XmlCustomerInformationService1_0_new::CurrentDisplayContentFromAllData1_0new(Vdv301AllData vdv301AllData )
{
    qDebug()<<Q_FUNC_INFO;
    QVector<Vdv301DisplayContent> output;

    if(!vdv301AllData.globalDisplayContentList.isEmpty())
    {
        return vdv301AllData.globalDisplayContentList;
    }

    if(vdv301AllData.tripInformationList.isEmpty())
    {
        return output;
    }
    else
    {
        Vdv301Trip currentTrip=vdv301AllData.tripInformationList.first();
        if(currentTrip.stopPointList.isEmpty())
        {
            return output;
        }
        else
        {
            if(xmlCommon1_0_new.isInRange(vdv301AllData.currentStopIndex-1,currentTrip.stopPointList.count(),Q_FUNC_INFO))
            {
                Vdv301StopPoint currentStop=currentTrip.stopPointList.at(vdv301AllData.currentStopIndex-1);
                return currentStop.displayContentList;
            }

        }
    }
    return output;
}



QString XmlCustomerInformationService1_0_new::CurrentDisplayContent1_0gen(QDomDocument xmlDocument, QVector<Vdv301DisplayContent> vdv301displayContentList )
{
    qDebug()<<Q_FUNC_INFO;

    QString language=xmlCommon1_0_new.defaultLanguage2_3;

    QDomProcessingInstruction dProcessingInformation=xmlCommon1_0_new.createProcessingInformation(xmlDocument,xmlCommon1_0_new.mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild(xmlCommon1_0_new.TimeStampTag1_0(xmlDocument));





    foreach(Vdv301DisplayContent displayContent, vdv301displayContentList )
    {
        dCurrentDisplayContentData.appendChild(xmlCommon1_0_new.DisplayContentViaPointDestination1_0gen(xmlDocument,"CurrentDisplayContent", displayContent));
    }


    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);





    return xmlCommon1_0_new.qDomDocumentToQString(xmlDocument);
}





