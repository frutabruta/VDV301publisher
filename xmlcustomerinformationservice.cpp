#include "xmlcustomerinformationservice.h"

XmlCustomerInformationService::XmlCustomerInformationService()
{

}


//QString XmlCustomerInformationService::AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<PrestupMPV> prestupy, CestaUdaje stav )
QString XmlCustomerInformationService::AllData1_0(QDomDocument xmlDocument, QVector<Trip> tripList,  QVector<Connection> connectionList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"empty stop list";
        return "AllData1.0 empty stop list";
    }

    QString deflanguage=defaultLanguage1_0;
    QString vehicleref=QString::number(vehicleState.vehicleNumber);
    int currentStopIndex= vehicleState.currentStopIndex0+1; //indexing fix from c++ array to VDV301
    QString routeDeviation=vehicleState.routeDeviation;
    QString vehicleStopRequested=QString::number(vehicleState.isVehicleStopRequested);
    QString exitSide="right";


    QDomProcessingInstruction dProcessingInstruction=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInstruction);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef=ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=Value(xmlDocument,"DefaultLanguage",deflanguage);
    dAllData.appendChild(dDefaultLanguage);

    QDomElement dTripInformation=TripInformation1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex );
    dAllData.appendChild(dTripInformation);

    QDomElement dCurrentStopIndex=Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(vehicleState.doorState));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);


    return xmlDocument.toString();
}




QString XmlCustomerInformationService::AllData2_2CZ1_0( QDomDocument xmlDocument,QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

    xmlDocument.clear();

    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        return "stop list is empty";
    }


    QString vehicleref=QString::number(vehicleState.vehicleNumber);
    int currentStopIndex= vehicleState.currentStopIndex0+1; //modification for stop indexing from 0 (c++ arrays) to 1 (VDV301)
    QString routeDeviation=vehicleState.routeDeviation;
    QString vehicleStopRequested=QString::number(vehicleState.isVehicleStopRequested);
    QString exitSide="right";

    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef=ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=Value(xmlDocument,"DefaultLanguage",defaultLanguage2_2CZ1_0);
    dAllData.appendChild(dDefaultLanguage);

    QDomElement dTripInformation=this->TripInformation2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex,false);
    dAllData.appendChild(dTripInformation);
    if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
    {
        dTripInformation=this->TripInformation2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex+1,true);
        dAllData.appendChild(dTripInformation);
    }

    QDomElement dCurrentStopIndex=Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(vehicleState.doorState));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);
    dAllData.appendChild(this->MyOwnVehicleMode(xmlDocument,vehicleState.vehicleMode,vehicleState.vehicleSubMode));

    return xmlDocument.toString();
}


QString XmlCustomerInformationService::AllData2_3(QDomDocument xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState )
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
    QString routeDeviation=vehicleState.routeDeviation;
    QString vehicleStopRequested=QString::number(vehicleState.isVehicleStopRequested);
    QString exitSide="right";

    QDomProcessingInstruction dHlavicka=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(TimeStampTag1_0(xmlDocument));

    QDomElement dVehicleRef=ref(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=Value(xmlDocument,"DefaultLanguage",defaultLanguage2_3);
    dAllData.appendChild(dDefaultLanguage);


    if(!tripList.isEmpty())
    {
        QVector<StopPointDestination> stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;

        QDomElement dTripInformation=this->TripInformation2_3(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex,false);
        dAllData.appendChild(dTripInformation);
        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            //qDebug()<<"abcd navaz Spoj existuje "<<;
            dTripInformation=this->TripInformation2_3(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex+1,true);
            dAllData.appendChild(dTripInformation);
        }
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);

    }



    QDomElement dCurrentStopIndex=Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(vehicleState.doorState));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    dAllData.appendChild(this->MyOwnVehicleMode(xmlDocument,vehicleState.vehicleMode,vehicleState.vehicleSubMode));

    return xmlDocument.toString();
}


QString XmlCustomerInformationService::CurrentDisplayContent1_0(QDomDocument xmlDocument, QVector <StopPointDestination> stopPointDestinationList, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;

    if (stopPointDestinationList.size()==0)
    {
        qDebug()<<"currentDisplayContent stop list is empty";
        return "stop list is empty";
    }



    qDebug()<<"  ";


    QDomProcessingInstruction dProcessingInstruction=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInstruction);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlDocument));

    dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlDocument,stopPointDestinationList,defaultLanguage1_0,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);

    return xmlDocument.toString();
}

//rozpracovano
QString XmlCustomerInformationService::CurrentDisplayContent2_2CZ1_0(QDomDocument xmlDocument, QVector <StopPointDestination> stopPointDestinationList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;
    if (stopPointDestinationList.size()==0)
    {
        qDebug()<<"currentDisplayContent stop list is empty";
        return "stop list is empty";
    }


    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlDocument));

    dCurrentDisplayContentData.appendChild(DisplayContent2_2CZ1_0(xmlDocument,"CurrentDisplayContent",stopPointDestinationList,defaultLanguage2_2CZ1_0,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);

    return xmlDocument.toString();
}


//rozpracovano
QString XmlCustomerInformationService::CurrentDisplayContent2_3(QDomDocument xmlDocument, QVector <StopPointDestination> stopPointDestinationList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;

    if (stopPointDestinationList.size()==0)
    {
        qDebug()<<"currentDisplayContent empty stop list";
        return "empty stop list";
    }


    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlDocument));

    // dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlko,docasnySeznamZastavek,language,stav.indexAktZastavky,stav.indexAktZastavky));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentFront));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentSide));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentRear));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentLcd));

    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);

    return xmlDocument.toString();
}




QString XmlCustomerInformationService::AllData_empty_1_0(QDomDocument xmlDocument)
{
    //needs to be fixed to compose empty message with correct time etc.
    QString output="<CustomerInformationService.GetAllDataResponse><AllData><TimeStamp><Value>2016-09-01T14:27:04</Value></TimeStamp><VehicleRef><Value>0</Value></VehicleRef><DefaultLanguage><Value>de</Value></DefaultLanguage><TripInformation><TripRef><Value>0</Value></TripRef><StopSequence><StopPoint><StopIndex><Value>0</Value></StopIndex><StopRef><Value>noRef</Value></StopRef><StopName><Value> </Value><Language>de</Language></StopName><DisplayContent><LineInformation><LineRef><Value>noRef</Value></LineRef></LineInformation><Destination><DestinationRef><Value>noRef</Value></DestinationRef></Destination></DisplayContent></StopPoint><StopPoint><StopIndex><Value>0</Value></StopIndex><StopRef><Value>noRef</Value></StopRef><StopName><Value> </Value><Language>de</Language></StopName><DisplayContent><LineInformation><LineRef><Value>noRef</Value></LineRef></LineInformation><Destination><DestinationRef><Value>noRef</Value></DestinationRef></Destination></DisplayContent></StopPoint></StopSequence></TripInformation><CurrentStopIndex><Value>0</Value></CurrentStopIndex><RouteDeviation>unknown</RouteDeviation><DoorState>AllDoorsClosed</DoorState><VehicleStopRequested><Value>false</Value></VehicleStopRequested><ExitSide>unknown</ExitSide></AllData></CustomerInformationService.GetAllDataResponse>";
    /*
      QDomElement output;
xmlDocument.setContent(obsahPrazdny);
    output=xmlDocument.firstChildElement();*/
    return output;
}


QString XmlCustomerInformationService::AllData_empty2_2CZ1_0(QDomDocument xmlDocument)
{
    qDebug()<<Q_FUNC_INFO;


    QString vehicleref="33";
    int currentStopIndex= 1;

    QString routeDeviation="onroute";

    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);
    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlDocument.createElement("AllData");
    xmlDocument.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);
    dAllData.appendChild(TimeStampTag1_0(xmlDocument));
    QDomElement dVehicleRef=Value(xmlDocument,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage=Value(xmlDocument,"DefaultLanguage",defaultLanguage2_2CZ1_0);
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dCurrentStopIndex=Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex+1));
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
    return xmlDocument.toString();
}



