#include "xmlcommon2_3cz1_0.h"

XmlCommon2_3CZ1_0::XmlCommon2_3CZ1_0() {}




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



        if(!trip.additionalTextMessage.text.isEmpty())
        {
            QString specialAnnouncement=trip.additionalTextMessage.text;
            qDebug()<<"special announcement="<<specialAnnouncement;
            dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage",specialAnnouncement,trip.additionalTextMessage.language));
            //   dTripInformation.appendChild(AdditionalTextMessage2_3(xmlDocument,  vehicleState.currentSpecialAnnoucement.text));
        }
        /*
        else if (specialAnnouncement!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
        */
    }
    else
    {
        qDebug()<<"followingTrip==true";
    }

    //fareZone change, commented out to comply with VDV CIS 2.3
    /*
    if((currentStopIndex+1)<stopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
    }
    */
    QDomElement dRunNumber=Value(xmlDocument,"RunNumber",trip.runNumber);
    dTripInformation.appendChild(dRunNumber);

    /*
    if((currentStopIndex+1)<selectedStopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        if(isInRange(currentStopIndex-1,selectedStopPointDestinationList.count(),Q_FUNC_INFO)&&isInRange(currentStopIndex,selectedStopPointDestinationList.count(),Q_FUNC_INFO))
        {
            dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,selectedStopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,selectedStopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
        }


    }*/

    return dTripInformation;
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
        result+=": ";
        }
        result+=fareZoneByType[key].join(",");

        output<<result;
    }

    return output;
}

QDomElement XmlCommon2_3CZ1_0::FareZoneChange2_3CZ1_0gen(QDomDocument  &xmlDocument, QVector<Vdv301InternationalText> fareZoneFrom,QVector<Vdv301InternationalText> fareZoneTo)
{

    QDomElement fareZoneChange=xmlDocument.createElement("FareZoneChange");


    QDomElement fromFareZones=xmlDocument.createElement("FromFareZones");


    foreach(Vdv301InternationalText selectedFareZone, fareZoneFrom )
    {
        fromFareZones.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",selectedFareZone));
    }

    fareZoneChange.appendChild(fromFareZones);



    QDomElement toFareZones=xmlDocument.createElement("ToFareZones");




    foreach(Vdv301InternationalText selectedFareZone, fareZoneTo )
    {
        toFareZones.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",selectedFareZone));
    }


    fareZoneChange.appendChild(toFareZones);

    return fareZoneChange;
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
    StopPointDestination currentStopPoinDestination=stopPointDestinationList.at(stopPointIterator);

    QByteArray cCurrentStopIndex=QByteArray::number(stopPointIterator+1);

    output.stopIndex=cCurrentStopIndex.toInt();
    output.stopRef=QString::number(currentStopPoinDestination.stopPoint.idCis);

    output.stopNameList<<Vdv301InternationalText(currentStopPoinDestination.stopPoint.NameLcd+stopPropertiesToString2_3(currentStopPoinDestination.stopPoint), language);

    QVector<Vdv301DisplayContent> testVdvDisplayContentList;


    testVdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentFront);
    testVdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentSide);
    testVdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentRear);
    testVdvDisplayContentList<<DisplayContentViaPointDestination2_3new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentLcd);

    output.displayContentList=testVdvDisplayContentList;

    output.departureExpected=qTimeToQDateTimeToday( currentStopPoinDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss");
    output.departureScheduled=qTimeToQDateTimeToday( currentStopPoinDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss");


    if(currentStopIndex==currentStopPoinDestination.stopPoint.StopIndex)
    {
        output.connectionList=connectionList;
    }

    /*
    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {

        foreach(QDomElement elementPrestupu,Connections2_3(xmlDocument,connectionList))
        {
            dStopPoint.appendChild(elementPrestupu );
        }

    }

*/
    foreach(QString dFareZone, FareZoneInformationStructure2_3CZ1_0new(currentStopPoinDestination.stopPoint.fareZoneList) )
    {
        Vdv301InternationalText fareZone;
        fareZone.text=dFareZone;
        fareZone.language=language;
        output.fareZoneList<<fareZone;
    }


    return output;
}



QDomElement XmlCommon2_3CZ1_0::StopPoint2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301StopPoint2_3CZ1_0 stopPointDestination)
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement dStopPoint=xmlDocument.createElement("StopPoint");


    QDomElement dStopIndex=Value(xmlDocument,"StopIndex",QString::number(stopPointDestination.stopIndex));

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref(xmlDocument, "StopRef",stopPointDestination.stopRef));


    foreach (Vdv301InternationalText stopName, stopPointDestination.stopNameList) {

        QDomElement dStopLcdName=internationalTextTypeToDom(xmlDocument,"StopName",stopName);

        dStopPoint.appendChild(dStopLcdName);
    }





    /* nedodelane priznaky:
            <xs:enumeration value="Bus"/>
            <xs:enumeration value="Funicular"/>
            <xs:enumeration value="Night"/>
            <xs:enumeration value="ReplacementService"/>
            <xs:enumeration value="ReplacementStop"/>
            <xs:enumeration value="RequestStop"/>
            <xs:enumeration value="Telecabin"/>
            <xs:enumeration value="Tram"/>
            <xs:enumeration value="Trolleybus"/>
            */





    // MOVE ALL TO DisplayContentViaPointDestination2_3new !!!!!!



    QVector<QDomElement> dDisplayContentVector;


    foreach(Vdv301DisplayContent displayContent, stopPointDestination.displayContentList)
    {
        dStopPoint.appendChild(DisplayContentViaPointDestination2_3gen(xmlDocument,"DisplayContent", displayContent));
    }


    /*
    dDisplayContentVector<<DisplayContentViaPointDestination2_3gen(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentFront);
    dDisplayContentVector<<DisplayContentViaPointDestination2_3gen(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentSide);
    dDisplayContentVector<<DisplayContentViaPointDestination2_3gen(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentRear);
    dDisplayContentVector<<DisplayContentViaPointDestination2_3gen(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentLcd);
   */
    foreach(QDomElement dDisplayContentSide, dDisplayContentVector)
    {
        dStopPoint.appendChild(dDisplayContentSide);
    }



    if(!stopPointDestination.arrivalScheduled.isEmpty())
    {
        QDomElement dExpectedDepartureTime=Value(xmlDocument,"ArrivalScheduled",stopPointDestination.arrivalScheduled);
        dStopPoint.appendChild(dExpectedDepartureTime);
    }

    if(!stopPointDestination.departureScheduled.isEmpty())
    {
        QDomElement dScheduledDepartureTime=Value(xmlDocument,"DepartureScheduled",stopPointDestination.departureScheduled);
        dStopPoint.appendChild(dScheduledDepartureTime);
    }




    // qDebug()<<"cCurrentStopIndex.toInt() "<< cCurrentStopIndex.toInt()<<" (currentStopIndex+1) " << (currentStopIndex+1);




    foreach(Vdv301Connection connection, stopPointDestination.connectionList)
    {
        dStopPoint.appendChild(Connection2_3gen(xmlDocument,connection));
    }


    foreach(Vdv301InternationalText fareZone, stopPointDestination.fareZoneList )
    {
        dStopPoint.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",fareZone));
    }

    return dStopPoint;
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

QVector<Vdv301StopPoint2_3CZ1_0> XmlCommon2_3CZ1_0::StopSequence2_3CZ1_0new(QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList)
{

    QVector<Vdv301StopPoint2_3CZ1_0> output;

    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        output<<StopPoint2_3CZ1_0new(stopPointDestinationList,i,connectionList,language,currentStopIndex);
    }
    return output;
}



Vdv301Trip2_3CZ1_0 XmlCommon2_3CZ1_0::TripInformation2_3CZ1_0new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
{

    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage2_3;
    QString tripRef=QString::number(tripList.at(tripIndex).idRopid);
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(tripIndex).globalStopPointDestinationList;


    Vdv301Trip2_3CZ1_0 vdv301trip;
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
            vdv301trip.additionalTextMessage.text=vehicleState.currentSpecialAnnoucement.text;
            vdv301trip.additionalTextMessage.language=language;

            //   dTripInformation.appendChild(AdditionalTextMessage2_3(xmlDocument,  vehicleState.currentSpecialAnnoucement.text));
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

    //fareZone change, commented out to comply with VDV CIS 2.3
    /*
    if((currentStopIndex+1)<stopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
    }
    */

    return vdv301trip;
}

