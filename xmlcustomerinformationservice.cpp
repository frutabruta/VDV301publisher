#include "xmlcustomerinformationservice.h"

XmlCustomerInformationService::XmlCustomerInformationService()
{

}


//QString XmlCustomerInformationService::AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<PrestupMPV> prestupy, CestaUdaje stav )
QString XmlCustomerInformationService::AllData1_0(QVector<Spoj> seznamSpoju,  QVector<Prestup> prestupy, CestaUdaje stav )
{
    qDebug()<<Q_FUNC_INFO;
    QVector<ZastavkaCil> docasnySeznamZastavek=seznamSpoju.at(stav.indexSpojeNaObehu).globalniSeznamZastavek;

    if (docasnySeznamZastavek.isEmpty())
    {
        qDebug()<<"nejsou zastavky";
        return "AllData1.0 nejsou zastavky";
    }

    QString deflanguage=defaultniJazyk1_0;
    QString vehicleref=QString::number(stav.cisloVozu);
    int currentStopIndex= stav.indexAktZastavky+1; //úprava pro indexování zastávek od 1 vs od 0 pro pole
    QString routeDeviation=stav.routeDeviation;
    QString vehicleStopRequested=QString::number(stav.VehicleStopRequested);
    QString exitSide="right";

    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(TimeStampTag1_0(xmlko));

    QDomElement dVehicleRef=ref("VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=Value(xmlko,"DefaultLanguage",deflanguage);
    dAllData.appendChild(dDefaultLanguage);

    QDomElement dTripInformation=TripInformation1_0(seznamSpoju,prestupy,stav,stav.indexSpojeNaObehu );
    dAllData.appendChild(dTripInformation);

    QDomElement dCurrentStopIndex=Value(xmlko,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(stav.doorState));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlko,"VehicleStopRequested",vehicleStopRequested);
    dAllData.appendChild(dVehicleStopRequested);

    QDomElement dExitSide = xmlko.createElement("ExitSide");

    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);


    return xmlko.toString();
}







QString XmlCustomerInformationService::AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<Prestup> prestupy, CestaUdaje stav )
{
    qDebug()<<Q_FUNC_INFO;
    QVector<ZastavkaCil> docasnySeznamZastavek=seznamSpoju.at(stav.indexSpojeNaObehu).globalniSeznamZastavek;

    if (docasnySeznamZastavek.isEmpty())
    {
        qDebug()<<"nejsou zastavky";
        return "AllData2.2CZ1.0 nejsou zastavky";
    }

    QString deflanguage=defaultniJazyk2_2CZ1_0;
    QString vehicleref=QString::number(stav.cisloVozu);
    int currentStopIndex= stav.indexAktZastavky+1; //úprava pro indexování zastávek od 1 vs od 0 pro pole
    QString routeDeviation=stav.routeDeviation;
      QString vehicleStopRequested=QString::number(stav.VehicleStopRequested);
    QString exitSide="right";

    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);

    dAllData.appendChild(TimeStampTag1_0(xmlko));

    QDomElement dVehicleRef=ref("VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);

    QDomElement dDefaultLanguage=Value(xmlko,"DefaultLanguage",deflanguage);
    dAllData.appendChild(dDefaultLanguage);

    QDomElement dTripInformation=this->TripInformation2_2CZ1_0(seznamSpoju,prestupy,stav,stav.indexSpojeNaObehu,false);
    dAllData.appendChild(dTripInformation);
    if (seznamSpoju.at(stav.indexSpojeNaObehu).navazujici)
    {
        //qDebug()<<"abcd navaz Spoj existuje "<<;
        dTripInformation=this->TripInformation2_2CZ1_0(seznamSpoju,prestupy,stav,stav.indexSpojeNaObehu+1,true);
        dAllData.appendChild(dTripInformation);
    }

    QDomElement dCurrentStopIndex=Value(xmlko,"CurrentStopIndex",QString::number(currentStopIndex));
    dAllData.appendChild(dCurrentStopIndex);

    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);

    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(stav.doorState));
    dAllData.appendChild(dDoorState);

    QDomElement dVehicleStopRequested=Value(xmlko,"VehicleStopRequested",vehicleStopRequested);
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

    dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlko,docasnySeznamZastavek,language,stav.indexAktZastavky,stav.indexAktZastavky));
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


QString XmlCustomerInformationService::AllData_empty2_2CZ1_0( )
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
    QDomElement dVehicleRef=Value(xmlko,"VehicleRef",vehicleref);
    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage=Value(xmlko,"DefaultLanguage",deflanguage);
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dCurrentStopIndex=Value(xmlko,"CurrentStopIndex",QString::number(currentStopIndex+1));
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
