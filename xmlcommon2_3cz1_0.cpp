#include "xmlcommon2_3cz1_0.h"

XmlCommon2_3CZ1_0::XmlCommon2_3CZ1_0() {}


QDomElement XmlCommon2_3CZ1_0::AddtitionalAnnouncement2_3CZ1_0gen(QDomDocument  &xmlDocument, Vdv301AdditionalAnnouncement2_3CZ1_0 vdv301AdditionalAnnouncement)
{
    QDomElement additionaAnnoucement=xmlDocument.createElement("AdditionalAnnouncement");
    additionaAnnoucement.appendChild(ref(xmlDocument,"AnnouncementRef",vdv301AdditionalAnnouncement.announcementRef));

    foreach (Vdv301InternationalText announcementText, vdv301AdditionalAnnouncement.announcementTextList)
    {
        additionaAnnoucement.appendChild(internationalTextTypeToDom(xmlDocument,"AnnouncementText",announcementText));
    }

    foreach (Vdv301InternationalText announcementTtsText, vdv301AdditionalAnnouncement.announcementTTSTextList)
    {
        additionaAnnoucement.appendChild(internationalTextTypeToDom(xmlDocument,"AnnouncementTTSText",announcementTtsText));
    }

    if(vdv301AdditionalAnnouncement.immediateInformation)
    {
        additionaAnnoucement.appendChild(Value(xmlDocument,"ImmediateInformation","true"));
    }

    if(vdv301AdditionalAnnouncement.periodicalInformation>0)
    {
        additionaAnnoucement.appendChild(Value(xmlDocument,"ImmediateInformation",QString::number(vdv301AdditionalAnnouncement.periodicalInformation)));
    }


    /*
    foreach (Vdv301InternationalText announcementTextHeader, vdv301AdditionalAnnoucement.announcementTextList) {
        additionaAnnoucement.appendChild(internationalTextTypeToDom(xmlDocument,"AnnouncementText",announcementTextHeader));
    }

*/
    return additionaAnnoucement;

}


QDomElement XmlCommon2_3CZ1_0::FareZoneChange2_3CZ1_0gen(QDomDocument  &xmlDocument,Vdv301FareZoneChange2_3CZ1_0 vdv301FareZoneChange)// QVector<Vdv301InternationalText> fareZoneFrom,QVector<Vdv301InternationalText> fareZoneTo)
{

    QDomElement fareZoneChange=xmlDocument.createElement("FareZoneChange");


    QDomElement fromFareZones=xmlDocument.createElement("FromFareZones");


    foreach(Vdv301InternationalText selectedFareZone, vdv301FareZoneChange.fromFareZone )
    {
        fromFareZones.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",selectedFareZone));
    }

    fareZoneChange.appendChild(fromFareZones);



    QDomElement toFareZones=xmlDocument.createElement("ToFareZones");




    foreach(Vdv301InternationalText selectedFareZone, vdv301FareZoneChange.toFareZone )
    {
        toFareZones.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",selectedFareZone));
    }


    fareZoneChange.appendChild(toFareZones);

    return fareZoneChange;
}



QStringList XmlCommon2_3CZ1_0::FareZoneInformationStructure2_3CZ1_0new( QVector<FareZone> fareZoneList)
{
    QMap<QString, QStringList> fareZoneByType;
    QStringList output;


    foreach( FareZone selectedFareZone, fareZoneList)
    {
        fareZoneByType[selectedFareZone.system].append(selectedFareZone.name);
    }

    //bool generateSystemName=if(farezonebyt)

    QStringList systems=fareZoneByType.keys();
    foreach(QString key,systems)
    {
        QString result="";
        if(systems.count()>1)
        {
            result+=key;
            result+=" ";
        }
        result+=fareZoneByType[key].join(",");

        output<<result;
    }

    return output;
}

QVector<Vdv301InternationalText> XmlCommon2_3CZ1_0::fareZoneListToVdv301FareZoneList(QVector<FareZone> fareZoneList, QString language)
{
    QVector<Vdv301InternationalText> output;


    foreach(QString dFareZone, FareZoneInformationStructure2_3CZ1_0new(fareZoneList) )
    {
        Vdv301InternationalText fareZone;
        fareZone.text=dFareZone;
        fareZone.language=language;
        output<<fareZone;
    }
    return output;

}





Vdv301StopPoint2_3CZ1_0 XmlCommon2_3CZ1_0::StopPoint2_3CZ1_0new( QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language,int currentStopIndex)
{
    qDebug()<<Q_FUNC_INFO;
    Vdv301StopPoint2_3CZ1_0 output;
    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        return output;
    }
    if (stopPointIterator>=stopPointDestinationList.length())
    {
        qDebug()<<"stop index is out of range";
        return output;
    }

    StopPointDestination selectedStopPoinDestination=stopPointDestinationList.at(stopPointIterator);

    // StopIndex
    output.stopIndex=stopPointIterator+1;

    // StopRef
    output.stopRef=selectedStopPoinDestination.stopPoint.ref();

    // GlobalStopRef
    output.globalStopRef=QString::number(selectedStopPoinDestination.stopPoint.idCis);

    // StopName
    output.stopNameList<<Vdv301InternationalText(selectedStopPoinDestination.stopPoint.NameLcd+stopPropertiesToString2_3(selectedStopPoinDestination.stopPoint), language);

    // StopAlternativeName not implemented

    // Platform
    output.platform=selectedStopPoinDestination.stopPoint.platformName;

    // DisplayContent
    QVector<Vdv301DisplayContent> vdvDisplayContentList;
    vdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentFront);
    vdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentSide);
    vdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentRear);
    vdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,lcdClass);
    output.displayContentList=vdvDisplayContentList;

    // StopAnnouncement not implemented

    // ArrivalScheduled
    // ArrivalExpected
    // DepartureScheduled
    output.departureScheduled=qTimeToQDateTimeToday( selectedStopPoinDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss");

    // DepartureExpected
    output.departureExpected=qTimeToQDateTimeToday( selectedStopPoinDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss");

    // RecordedArrivalTime not implemented
    // DistanceToNextStop not implemented

    // Connection
    if(currentStopIndex==stopPointIterator)
    {
        output.connectionList=connectionList;
    }

    // FareZone
    foreach(QString dFareZone, FareZoneInformationStructure2_3CZ1_0new(selectedStopPoinDestination.stopPoint.fareZoneList) )
    {
        Vdv301InternationalText fareZone;
        fareZone.text=dFareZone;
        fareZone.language=language;
        output.fareZoneList<<fareZone;
    }


    return output;
}






QDomElement XmlCommon2_3CZ1_0::StopSequence2_3CZ1_0gen(QDomDocument &xmlDocument,QVector<Vdv301StopPoint2_3CZ1_0> stopPointDestinationList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");


    foreach(Vdv301StopPoint2_3CZ1_0 stopPointDestination, stopPointDestinationList)
    {

        dStopSequence.appendChild(StopPoint2_3CZ1_0gen(xmlDocument,stopPointDestination));
    }
    return dStopSequence;
}


QDomElement XmlCommon2_3CZ1_0::StopPoint2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301StopPoint2_3CZ1_0 stopPointDestination)
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement dStopPoint=xmlDocument.createElement("StopPoint");

    // StopIndex
    dStopPoint.appendChild(Value(xmlDocument,"StopIndex",QString::number(stopPointDestination.stopIndex)));

    // StopRef
    dStopPoint.appendChild(ref(xmlDocument, "StopRef",stopPointDestination.stopRef));

    // StopRef
    dStopPoint.appendChild(ref(xmlDocument, "GlobalStopRef",stopPointDestination.globalStopRef));

    // StopName
    foreach (Vdv301InternationalText stopName, stopPointDestination.stopNameList) {

        QDomElement dStopLcdName=internationalTextTypeToDom(xmlDocument,"StopName",stopName);

        dStopPoint.appendChild(dStopLcdName);
    }

    // StopAlternativeName minOccurs="0" not implemented

    // Platform minOccurs="0"
    if(!stopPointDestination.platform.isEmpty())
    {
        dStopPoint.appendChild(Value(xmlDocument,"Platform",stopPointDestination.platform));
    }

    // DisplayContent
    QVector<QDomElement> dDisplayContentList;

    foreach(Vdv301DisplayContent displayContent, stopPointDestination.displayContentList)
    {
        dStopPoint.appendChild(DisplayContentViaPointDestination2_3gen(xmlDocument,"DisplayContent", displayContent));
    }

    foreach(QDomElement dDisplayContentSide, dDisplayContentList)
    {
        dStopPoint.appendChild(dDisplayContentSide);
    }

    // StopAnnouncement minOccurs="0" not implemented

    // ArrivalScheduled minOccurs="0"
    if(!stopPointDestination.arrivalScheduled.isEmpty())
    {
        QDomElement dArrivalScheduled=Value(xmlDocument,"ArrivalScheduled",stopPointDestination.arrivalScheduled);
        dStopPoint.appendChild(dArrivalScheduled);
    }

    // ArrivalExpected minOccurs="0"
    if(!stopPointDestination.arrivalExpected.isEmpty())
    {
        QDomElement dArrivalExpected=Value(xmlDocument,"ArrivalExpected",stopPointDestination.arrivalExpected);
        dStopPoint.appendChild(dArrivalExpected);
    }

    // DepartureScheduled minOccurs="0"
    if(!stopPointDestination.departureScheduled.isEmpty())
    {
        QDomElement dDepartureScheduled=Value(xmlDocument,"DepartureScheduled",stopPointDestination.departureScheduled);
        dStopPoint.appendChild(dDepartureScheduled);
    }

    // DepartureExpected minOccurs="0"
    if(!stopPointDestination.departureExpected.isEmpty())
    {
        QDomElement dDepartureExpected=Value(xmlDocument,"DepartureExpected",stopPointDestination.departureExpected);
        dStopPoint.appendChild(dDepartureExpected);
    }

    // RecordedArrivalTime minOccurs="0" not implemented

    // DistanceToNextStop minOccurs="0" not implemented

    // Connection minOccurs="0"
    foreach(Vdv301Connection connection, stopPointDestination.connectionList)
    {
        dStopPoint.appendChild(Connection2_3gen(xmlDocument,connection));
    }

    // FareZone minOccurs="0"
    foreach(Vdv301InternationalText fareZone, stopPointDestination.fareZoneList )
    {
        dStopPoint.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",fareZone));
    }

    return dStopPoint;
}


QVector<Vdv301StopPoint2_3CZ1_0> XmlCommon2_3CZ1_0::StopSequence2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList)
{

    QVector<Vdv301StopPoint2_3CZ1_0> output;

    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        output<<StopPoint2_3CZ1_0new(stopPointDestinationList,i,connectionList,language,currentStopIndex);
    }
    return output;
}



QDomElement XmlCommon2_3CZ1_0::TripInformation2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301Trip2_3CZ1_0 trip, bool followingTrip)
{
    QString language=defaultLanguage2_3;
    QString tripRef=trip.tripRef;

    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_3CZ1_0gen(xmlDocument,trip.stopPointList));

    if (followingTrip==false)
    {
        QDomElement dLocationState=xmlDocument.createElement("LocationState");
        dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString(trip.locationState)));
        dTripInformation.appendChild(dLocationState);
        

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessageList)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage1List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage1",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage2List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage2",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage3List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage3",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage4List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage4",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage5List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage5",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage6List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage6",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage7List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage7",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage8List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage8",selectedAdditionalTextMessage));
            }
        }

        foreach (Vdv301InternationalText selectedAdditionalTextMessage, trip.additionalTextMessage9List)
        {
            if(!selectedAdditionalTextMessage.text.isEmpty())
            {
                dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage9",selectedAdditionalTextMessage));
            }
        }

        foreach(Vdv301AdditionalAnnouncement2_3CZ1_0 announcement,trip.additionalAnnouncementList)
        {
            dTripInformation.appendChild(AddtitionalAnnouncement2_3CZ1_0gen(xmlDocument,announcement));
        }

    }
    else
    {
        qDebug()<<"followingTrip==true";
    }


    QDomElement dRunNumber=Value(xmlDocument,"RunNumber",trip.runNumber);
    dTripInformation.appendChild(dRunNumber);

    if(trip.fareZoneChange.active)
    {
        /*
        dTripInformation.appendChild(FareZoneChange2_3CZ1_0gen(xmlDocument,trip.fareZoneChange));
    */
    }

    return dTripInformation;
}




Vdv301Trip2_3CZ1_0 XmlCommon2_3CZ1_0::TripInformation2_3CZ1_0new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
{

    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage2_3;
    Vdv301Trip2_3CZ1_0 vdv301trip;
    Trip selectedTrip;

    if (isInRange(tripIndex,tripList.count(),Q_FUNC_INFO))
    {
        selectedTrip=tripList.at(tripIndex);
    }
    else
    {
        return vdv301trip;
    }

    QString tripRef=selectedTrip.ref();
    QVector<StopPointDestination> stopPointDestinationList=selectedTrip.globalStopPointDestinationList;


    vdv301trip.tripRef=tripRef;
    vdv301trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(Vdv301Enumerations::LocationStateEnumerationToQString(vehicleState.locationState));
    //vdv301trip.additionalTextMessage=
    //vdv301trip.stopPointList=
    //vdv301trip.timetableDelay
    vdv301trip.runNumber=vehicleRunToRunNumber(vehicleState.currentVehicleRun);


    //stop sequence
    vdv301trip.stopPointList<<StopSequence2_3CZ1_0new(stopPointDestinationList,language,currentStopIndex,connectionList);


    if (followingTrip==false)
    {


        QString specialAnnouncement=stopPointDestinationList.at(vehicleState.currentStopIndex0).stopPoint.additionalTextMessage;
        qDebug()<<"special announcement="<<specialAnnouncement;

        if(vehicleState.isSpecialAnnoucementUsed)
        {
            /*
            Vdv301AdditionalAnnouncement2_3CZ1_0 additionalAnnouncement;
            additionalAnnouncement.announcementTextList<<Vdv301InternationalText(vehicleState.currentSpecialAnnoucement.text,language);
            vdv301trip.additionalAnnouncementList<<additionalAnnouncement;
*/
            vdv301trip.additionalTextMessageList<<Vdv301InternationalText(vehicleState.currentSpecialAnnoucement.text,language);
            vdv301trip.additionalTextMessage1List<<Vdv301InternationalText(vehicleState.currentSpecialAnnoucement.type,language);

        }
        else if (specialAnnouncement!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
    }
    else
    {
        qDebug()<<"followingTrip==true";
    }


    if((currentStopIndex+1)<stopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        vdv301trip.fareZoneChange.active=true;
        

        QString fareZoneChangeText=R"(
<font size="90"><color fg="#ffffff">Prosím pozor! Změna tarifního pásma.</color></font><br>
<font size="68"><color fg="#969696">Attention please! Change of fare zone.</color></font>
        )";


        vdv301trip.additionalTextMessageList<<Vdv301InternationalText(fareZoneChangeText,language);

        vdv301trip.additionalTextMessage4List<<Vdv301InternationalText("FareZoneChange",language);


        if(isInRange(currentStopIndex-1,stopPointDestinationList.count(),Q_FUNC_INFO))
        {

            //vdv301trip.fareZoneChange.fromFareZone=fareZoneListToVdv301FareZoneList(FareZone::filterZonesFromSystem(stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,"PID"),language);
            if(!fareZoneListToVdv301FareZoneList(FareZone::filterZonesFromSystem(stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,"PID"),language).isEmpty())
            {
                vdv301trip.additionalTextMessage2List=fareZoneListToVdv301FareZoneList(FareZone::filterZonesFromSystem(stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,"PID"),language);
            }
        }
        if(isInRange(currentStopIndex,stopPointDestinationList.count(),Q_FUNC_INFO))
        {
            if(!fareZoneListToVdv301FareZoneList(FareZone::filterZonesFromSystem(stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,"PID"),language).isEmpty())
            {
                vdv301trip.additionalTextMessage3List=fareZoneListToVdv301FareZoneList(FareZone::filterZonesFromSystem(stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,"PID"),language);
            }

            //   vdv301trip.fareZoneChange.toFareZone=fareZoneListToVdv301FareZoneList(FareZone::filterZonesFromSystem(stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,"PID"),language);

        }

     }
    else
    {
        vdv301trip.fareZoneChange.active=false;
        vdv301trip.fareZoneChange.fromFareZone.clear();
        vdv301trip.fareZoneChange.toFareZone.clear();
    }


    return vdv301trip;
}

QString XmlCommon2_3CZ1_0::vehicleRunToRunNumber(VehicleRun vehicleRun)
{
    //   return QString::number(vehicleRun.rootLine.c)+"_"+QString::number(vehicleRun.order);
    return QString::number(vehicleRun.rootLine.c)+"_"+QString::number(vehicleRun.order);
}




