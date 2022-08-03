#include "xmlcustomerinformationservice.h"

XmlCustomerInformationService::XmlCustomerInformationService()
{

}



QString XmlCustomerInformationService::AllData1_0(  QVector <ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<PrestupMPV> prestupy, CestaUdaje stav )
{
    qDebug()<<" XmlCustomerInformationService::AllData1_0 ";
    int poradi=stav.indexAktZastavky;
    Zastavka cilovaZastavka;
    if (docasnySeznamZastavek.size()==0)
    {
        qDebug()<<"nejsou zastavky";
        return "AllData1.0 nejsou zastavky";
    }
    QString language=this->defaultniJazyk1_0;
    QString deflanguage=this->defaultniJazyk1_0;
    QString vehicleref=QString::number(stav.cisloVozu);
    int currentStopIndex= poradi;
    QString routeDeviation=stav.routeDeviation;
    QString vehicleStopRequested=QString::number(stav.VehicleStopRequested);
    QString exitSide="right";
    QString tripRef=QString::number(stav.aktspoj.cisloRopid);
    QString destinationName=docasnySeznamZastavek[poradi].cil.StopName;

    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(TimeStampTag1_0(xmlko));

    dAllData.appendChild(ref("VehicleRef",vehicleref));
    QDomElement dDefaultLanguage=xmlko.createElement("DefaultLanguage");
    dDefaultLanguage.appendChild(xmlko.createElement("Value"));
    dDefaultLanguage.firstChildElement("Value").appendChild(xmlko.createTextNode(deflanguage));
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dTripInformation=xmlko.createElement("TripInformation");
    dAllData.appendChild(dTripInformation);

    dTripInformation.appendChild(ref("TripRef",tripRef));
    QString specialniOznameni=docasnySeznamZastavek.at(stav.indexAktZastavky).zastavka.additionalTextMessage;
    if (specialniOznameni!="")
    {
        dTripInformation.appendChild(AdditionalTextMessage1_0(specialniOznameni));
    }
    else
    {
        qDebug()<<"specOznJePrazdne";
    }



    //stop sequence
    dTripInformation.appendChild(StopSequence1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,prestupy,stav));
    //dTripInformation.appendChild(dStopSequence);


    QDomElement dLocationState=xmlko.createElement("LocationState");
    dLocationState.appendChild(xmlko.createTextNode( locationState));
    dTripInformation.appendChild(dLocationState);

    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(QString::number(currentStopIndex)));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(doorState));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=xmlko.createElement("VehicleStopRequested");
    dVehicleStopRequested.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(vehicleStopRequested));
    dAllData.appendChild(dVehicleStopRequested);
    QDomElement dExitSide = xmlko.createElement("ExitSide");

    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);


    return xmlko.toString();
}





QString XmlCustomerInformationService::AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<PrestupMPV> prestupy, CestaUdaje stav )
{
    qDebug()<<"XmlCustomerInformationService::AllData2_2CZ1_0";
    QVector<ZastavkaCil> docasnySeznamZastavek=seznamSpoju.at(stav.indexSpojeNaObehu).globalniSeznamZastavek;

    if (docasnySeznamZastavek.size()>0)
    {
        //cilovaZastavka=docasnySeznamZastavek.last();
    }
    else
    {
        qDebug()<<"nejsou zastavky";
        return "prazdnyString";
    }


    QString doorState=stav.doorState;


    QString deflanguage=defaultniJazyk2_2CZ1_0;
    QString vehicleref=QString::number(stav.cisloVozu);
    int currentStopIndex= stav.indexAktZastavky+1; //úprava pro indexování zastávek od 1 vs od 0 pro pole
    QString routeDeviation="onroute";
    QString vehicleStopRequested="0";
    QString exitSide="right";


    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);


    dAllData.appendChild(TimeStampTag1_0(xmlko));

    QDomElement dVehicleRef=ref("VehicleRef",vehicleref);// xmlko.createElement("VehicleRef");

    /*
    QDomElement dVehicleRef=xmlko.createElement("VehicleRef");

    dVehicleRef.appendChild(xmlko.createElement("Value"));
    dVehicleRef.firstChildElement("Value").appendChild(xmlko.createTextNode(vehicleref));
    */

    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage=xmlko.createElement("DefaultLanguage");
    dDefaultLanguage.appendChild(xmlko.createElement("Value"));
    dDefaultLanguage.firstChildElement("Value").appendChild(xmlko.createTextNode(deflanguage));
    dAllData.appendChild(dDefaultLanguage);

    QDomElement dTripInformation=this->TripInformation2_2CZ1_0(seznamSpoju,prestupy,stav,stav.indexSpojeNaObehu,false);
    dAllData.appendChild(dTripInformation);
    if (seznamSpoju.at(stav.indexSpojeNaObehu).navazujici)
    {
        //qDebug()<<"abcd navaz Spoj existuje "<<;
        dTripInformation=this->TripInformation2_2CZ1_0(seznamSpoju,prestupy,stav,stav.indexSpojeNaObehu+1,true);
        dAllData.appendChild(dTripInformation);
    }

    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(QString::number(currentStopIndex)));
    dAllData.appendChild(dCurrentStopIndex);
    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);
    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(doorState));
    dAllData.appendChild(dDoorState);
    QDomElement dVehicleStopRequested=xmlko.createElement("VehicleStopRequested");
    dVehicleStopRequested.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(vehicleStopRequested));
    dAllData.appendChild(dVehicleStopRequested);
    QDomElement dExitSide = xmlko.createElement("ExitSide");
    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);
    PrestupMPV::ddDoVehicleMode(docasnySeznamZastavek.at(stav.indexAktZastavky).linka.kli,stav.vehicleMode,stav.vehicleSubMode,docasnySeznamZastavek[stav.indexAktZastavky].linka);
    dAllData.appendChild(this->MyOwnVehicleMode(xmlko,stav.vehicleMode,stav.vehicleSubMode));

    return xmlko.toString();
}



QString XmlCustomerInformationService::CurrentDisplayContent1_0(int poradi, QVector <ZastavkaCil> docasnySeznamZastavek, CestaUdaje stav )
{
    qDebug()<<"XmlCustomerInformationService::CurrentDisplayContent1_0";
    Zastavka cilovaZastavka;
    if (docasnySeznamZastavek.size()==0)
    {
        qDebug()<<"currentDisplayContent NejsouZastavky";
        return "nejsou zastavky";
    }

    ZastavkaCil aktualniZastavka=docasnySeznamZastavek.at(poradi);

    qDebug()<<"  ";
    QString  language="cz";
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);

    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlko.createElement("CurrentDisplayContentData");


    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlko));


    dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlko,docasnySeznamZastavek,language,stav));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlko.appendChild(dCustomerInformationService);






    return xmlko.toString();
}




QString XmlCustomerInformationService::AllData_empty_1_0()
{
    QDomDocument xmlko;
    QDomElement vysledek;
    QString obsahPrazdny="<CustomerInformationService.GetAllDataResponse><AllData><TimeStamp><Value>2016-09-01T14:27:04</Value></TimeStamp><VehicleRef><Value>0</Value></VehicleRef><DefaultLanguage><Value>de</Value></DefaultLanguage><TripInformation><TripRef><Value>0</Value></TripRef><StopSequence><StopPoint><StopIndex><Value>0</Value></StopIndex><StopRef><Value>noRef</Value></StopRef><StopName><Value> </Value><Language>de</Language></StopName><DisplayContent><LineInformation><LineRef><Value>noRef</Value></LineRef></LineInformation><Destination><DestinationRef><Value>noRef</Value></DestinationRef></Destination></DisplayContent></StopPoint><StopPoint><StopIndex><Value>0</Value></StopIndex><StopRef><Value>noRef</Value></StopRef><StopName><Value> </Value><Language>de</Language></StopName><DisplayContent><LineInformation><LineRef><Value>noRef</Value></LineRef></LineInformation><Destination><DestinationRef><Value>noRef</Value></DestinationRef></Destination></DisplayContent></StopPoint></StopSequence></TripInformation><CurrentStopIndex><Value>0</Value></CurrentStopIndex><RouteDeviation>unknown</RouteDeviation><DoorState>AllDoorsClosed</DoorState><VehicleStopRequested><Value>false</Value></VehicleStopRequested><ExitSide>unknown</ExitSide></AllData></CustomerInformationService.GetAllDataResponse>";
    xmlko.setContent(obsahPrazdny);
    vysledek=xmlko.firstChildElement();
    return obsahPrazdny;
}


QString XmlCustomerInformationService::AllDataEmpty2_2CZ1_0( )
{
    qDebug()<<"XmlCustomerInformationService::AllData2_2CZ1_0";
    int poradi=1;
    QString deflanguage=defaultniJazyk2_2CZ1_0;
    QString vehicleref="33";
    int currentStopIndex= poradi;
    QString routeDeviation="onroute";

    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);
    dAllData.appendChild(TimeStampTag1_0(xmlko));
    QDomElement dVehicleRef=xmlko.createElement("VehicleRef");
    dVehicleRef.appendChild(xmlko.createElement("Value"));
    dVehicleRef.firstChildElement("Value").appendChild(xmlko.createTextNode(vehicleref));
    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage=xmlko.createElement("DefaultLanguage");
    dDefaultLanguage.appendChild(xmlko.createElement("Value"));
    dDefaultLanguage.firstChildElement("Value").appendChild(xmlko.createTextNode(deflanguage));
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(QString::number(currentStopIndex+1)));
    dAllData.appendChild(dCurrentStopIndex);
    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
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
    return xmlko.toString();
}
