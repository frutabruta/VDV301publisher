#include "xmlcustomerinformationservice.h"

XmlCustomerInformationService::XmlCustomerInformationService()
{

}


//QString XmlCustomerInformationService::AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<PrestupMPV> prestupy, CestaUdaje stav )
QString XmlCustomerInformationService::AllData1_0(QDomDocument xmlDocument, QVector<Trip> tripList,  QVector<Connection> connectionList, VehicleState vehicleState )
{
    qDebug()<<Q_FUNC_INFO;
    QVector<StopPointDestination> stopPointDestinationList;
    if(isInRange(vehicleState.currentTripIndex,tripList.count(),Q_FUNC_INFO))
    {
        stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;
    }


    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"empty stop list";
        //return "AllData1.0 empty stop list";
    }

    QString deflanguage=defaultLanguage1_0;
    QString vehicleref=QString::number(vehicleState.vehicleNumber);
    int currentStopIndex= vehicleState.currentStopIndex0+1; //indexing fix from c++ array to VDV301
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleState.routeDeviation);
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
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleState.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);


    return qDomDocumentToQString(xmlDocument);
}




QString XmlCustomerInformationService::AllData2_2CZ1_0( QDomDocument xmlDocument,QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState)
{
    qDebug()<<Q_FUNC_INFO;
    QString vehicleref=QString::number(vehicleState.vehicleNumber);
    int currentStopIndex= vehicleState.currentStopIndex0+1; //modification for stop indexing from 0 (c++ arrays) to 1 (VDV301)
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleState.routeDeviation);
    QString vehicleStopRequested=QString::number(vehicleState.isVehicleStopRequested);
    QString exitSide="right";
    xmlDocument.clear();


    QVector<StopPointDestination> stopPointDestinationList;







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


    if(isInRange(vehicleState.currentTripIndex,tripList.count(),Q_FUNC_INFO))
    {
        stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;
        QDomElement dTripInformation=this->TripInformation2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex,false);
        dAllData.appendChild(dTripInformation);


        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            dTripInformation=this->TripInformation2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState,vehicleState.currentTripIndex+1,true);
            dAllData.appendChild(dTripInformation);
        }
    }

    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        // return "stop list is empty";
    }







    QDomElement dCurrentStopIndex=Value(xmlDocument,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleState.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    if(isInRange(vehicleState.currentStopIndex0,stopPointDestinationList.count(),Q_FUNC_INFO))
    {
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);
        dAllData.appendChild(this->MyOwnVehicleMode(xmlDocument,vehicleState.vehicleMode,vehicleState.vehicleSubMode));
    }

    return qDomDocumentToQString(xmlDocument);
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
    QString routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationToQString(vehicleState.routeDeviation);
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
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(vehicleState.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    dAllData.appendChild(this->MyOwnVehicleMode(xmlDocument,vehicleState.vehicleMode,vehicleState.vehicleSubMode));

    return qDomDocumentToQString(xmlDocument);

}
//xx

Vdv301AllData XmlCustomerInformationService::AllData2_3new( QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, QVector<Vdv301DisplayContent> globalDisplayContentList )
{
    qDebug()<<Q_FUNC_INFO;


    Vdv301AllData allData;

    QVector<Vdv301Connection> vdv301ConnectionList;

    foreach(Connection connection, connectionList)
    {
        vdv301ConnectionList<<connection.toVdv301Connection();
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
    allData.defaultLanguage=defaultLanguage2_3;
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

        vdv301TripList<<this->TripInformation2_3new(tripList,vdv301ConnectionList,vehicleState,vehicleState.currentTripIndex,false);

        if (tripList.at(vehicleState.currentTripIndex).continuesWithNextTrip)
        {
            //qDebug()<<"abcd navaz Spoj existuje "<<;
            vdv301TripList<<this->TripInformation2_3new(tripList,vdv301ConnectionList,vehicleState,vehicleState.currentTripIndex+1,true);

        }
        ConnectionMPV::ddDoVehicleMode(stopPointDestinationList.at(vehicleState.currentStopIndex0).line.kli,vehicleState.vehicleMode,vehicleState.vehicleSubMode,stopPointDestinationList[vehicleState.currentStopIndex0].line);

    }

    allData.tripInformationList=vdv301TripList;
    allData.globalDisplayContentList=globalDisplayContentList;


    return allData;
}




QString XmlCustomerInformationService::AllData2_3gen(QDomDocument xmlDocument, Vdv301AllData allData)//, VehicleState vehicleState )
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


    if(!allData.tripInformationList.isEmpty())
    {
        // xxxx fix following connection
        int counter=0;
        foreach(Vdv301Trip vdv301trip, allData.tripInformationList)
        {

            QDomElement dTripInformation;
            bool isFollowing=(counter>0);
            dTripInformation=this->TripInformation2_3gen(xmlDocument,vdv301trip,isFollowing);
            dAllData.appendChild(dTripInformation);
            counter++;

        }



    }

    QDomElement dCurrentStopIndex=Value(xmlDocument,"CurrentStopIndex",QString::number(allData.currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlDocument.createElement("DoorState");
    dDoorState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::DoorOpenStateEnumerationToQString(allData.vehicleInformationGroup.doorState)));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlDocument,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlDocument.createElement("ExitSide");

    dExitSide.appendChild(xmlDocument.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);

    dAllData.appendChild(this->MyOwnVehicleMode(xmlDocument,allData.vehicleInformationGroup.vehicleMode, allData.vehicleInformationGroup.vehicleSubMode));



    foreach(Vdv301DisplayContent displayContent, allData.globalDisplayContentList)
    {
        dAllData.appendChild(DisplayContentViaPointDestination2_3gen(xmlDocument,"GlobalDisplayContent", displayContent));
    }


    return qDomDocumentToQString(xmlDocument);

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

    return qDomDocumentToQString(xmlDocument);
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

    return qDomDocumentToQString(xmlDocument);

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
    QString language=defaultLanguage2_3;

    QDomProcessingInstruction dProcessingInformation=createProcessingInformation(xmlDocument,mDefaultEncoding);
    xmlDocument.appendChild(dProcessingInformation);

    QDomElement dCustomerInformationService=xmlDocument.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlDocument.createElement("CurrentDisplayContentData");

    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlDocument));

    /*
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentFront));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentSide));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentRear));
    dCurrentDisplayContentData.appendChild(DisplayContent2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, defaultLanguage2_3,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentLcd));
*/

    QVector<QDomElement> displayContentDomVector;


    displayContentDomVector<<DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentFront);
    displayContentDomVector<<DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentSide);
    displayContentDomVector<<DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentRear);
    displayContentDomVector<<DisplayContentViaPointDestination2_3(xmlDocument,"CurrentDisplayContent",stopPointDestinationList, language,vehicleState.currentStopIndex0,vehicleState.currentStopIndex0,DisplayContentLcd);


    foreach(QDomElement dDisplayContentSide, displayContentDomVector)
    {
        dCurrentDisplayContentData.appendChild(dDisplayContentSide);
    }
    

    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlDocument.appendChild(dCustomerInformationService);

    return qDomDocumentToQString(xmlDocument);
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

    return qDomDocumentToQString(xmlDocument);
}



