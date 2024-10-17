#include "xmlcommon2_3_new.h"

XmlCommon2_3_new::XmlCommon2_3_new() {}



QDomElement XmlCommon2_3_new::Connection2_3gen(QDomDocument  &xmlDocument, Vdv301Connection connection)
{
    qDebug()<<Q_FUNC_INFO;






    //   aktualniPrestup.lin=aktualniPrestup.lin.number(10);
    QDomElement dConnection=xmlDocument.createElement("Connection");
    //    Connection vdv301prestup=aktualniPrestup.toPrestup();

    xmlDocument.appendChild(dConnection);

    QDomElement dConnectionMode = xmlDocument.createElement("ConnectionMode");



    dConnection.appendChild(xmlDocument.createElement("ConnectionType")).appendChild(xmlDocument.createTextNode("Interchange"));



    foreach(Vdv301DisplayContent displayContent, connection.vdv301displayContentList)
    {


        QDomElement dDisplayContent=xmlDocument.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);

        QDomElement dLineInformation=xmlDocument.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);


        foreach (Vdv301InternationalText lineName, displayContent.lineInformation.lineNameList)
        {
            QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName.text,lineName.language);
            dLineInformation.appendChild(dLineName);
        }



        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",displayContent.lineInformation.lineNumber);
        dLineInformation.appendChild(dLineNumber);



        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);

        foreach(Vdv301InternationalText destinationName, displayContent.destination.destinationNameList)
        {
            QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",destinationName.text, destinationName.language);
            dDestination.appendChild(dDestinationName);
        }




    }





    dConnection.appendChild(Value(xmlDocument,"Platform",connection.platform));

    //dopravni prostredek
    dConnectionMode.appendChild(xmlDocument.createElement("PtMainMode")).appendChild(xmlDocument.createTextNode(connection.mainMode));
    dConnectionMode.appendChild(xmlDocument.createElement(connection.mainMode)).appendChild(xmlDocument.createTextNode(connection.subMode));
    dConnection.appendChild(dConnectionMode);


    //    qDebug()<<"connection "<<connection.line.lineName<<" "<<connection.destinationName<<" time:"<<connection.expectedDepartureTimeQString();

    QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepartureTime", connection.expectedDepartureTimeQString());
    dConnection.appendChild(dExpectedDepartureTime);

    QDomElement dScheduledDepartureTime=Value(xmlDocument,"ScheduledDepartureTime",connection.scheduledDepartureTimeQString());
    dConnection.appendChild(dScheduledDepartureTime);

    return dConnection;

}



QDomElement XmlCommon2_3_new::TripInformation2_3gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip)
{
    QString language=defaultLanguage2_3;
    QString tripRef=trip.tripRef;

    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_3gen(xmlDocument,trip.stopPointList));

    if (followingTrip==false)
    {
        QDomElement dLocationState=xmlDocument.createElement("LocationState");
        dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString(trip.locationState)));
        dTripInformation.appendChild(dLocationState);



        if(!trip.additionalTextMessage.text.isEmpty())
        {
            QString specialAnnouncement= trip.additionalTextMessage.text;
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

    return dTripInformation;
}




QDomElement XmlCommon2_3_new::DisplayContentViaPointDestination2_3gen(QDomDocument  &xmlDocument, QString tagName, Vdv301DisplayContent displayContent)
{

    QDomElement viaPointObsah;


    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");

    dLineInformation.appendChild(ref(xmlDocument,"LineRef",displayContent.lineInformation.lineRef));


    foreach(Vdv301InternationalText lineName, displayContent.lineInformation.lineNameList)
    {
        QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName.text,lineName.language);

        dLineInformation.appendChild(dLineName);
    }


    QString lineNumber=displayContent.lineInformation.lineNumber;
    if(!lineNumber.isEmpty())
    {
        QDomElement dLineNumber=Value(xmlDocument,"LineNumber",lineNumber);
        dLineInformation.appendChild(dLineNumber);
    }



    QDomElement dDestination=xmlDocument.createElement("Destination");


    QDomElement dDisplayContent=xmlDocument.createElement(tagName);
    dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef",Vdv301DisplayContent::displayContentClassEnumerationToQString( displayContent.displayContentType)));
    dDisplayContent.appendChild(dLineInformation);

    dDestination.appendChild(ref(xmlDocument,"DestinationRef", displayContent.destination.destinationRef));

    foreach(Vdv301InternationalText destinationName, displayContent.destination.destinationNameList)
    {
        QDomElement dDestinationName;
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",destinationName.text,destinationName.language);
        dDestination.appendChild(dDestinationName);
    }

    dDisplayContent.appendChild(dDestination);



    foreach(Vdv301ViaPoint viaPoint, displayContent.viaPointList)
    {
        dDisplayContent.appendChild(ViaPoint2_3def(xmlDocument,viaPoint));
    }
    return dDisplayContent;
}

QVector<Vdv301DisplayContent> XmlCommon2_3_new::DisplayContentViaPointDestination2_3new(QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
{


    // QVector<QDomElement> output;
    QVector<Vdv301DisplayContent> output;
    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);

    Vdv301Line selectedLine=lineToVdv301Line2_3(selectedStopPointDestination.line);




    bool appendNextStopToViapoints=true;

    QString placeholder="";
    ConnectionMPV::ddDoVehicleMode(selectedStopPointDestination.line.kli,placeholder,placeholder,selectedStopPointDestination.line );


    QDomElement viaPointObsah;

    QVector<Vdv301ViaPoint> viaPointListVdv;
    QVector<StopPointDestination> viaPointList;

    if ((appendNextStopToViapoints==true)&&((currentStopIndex+1)<stopPointDestinationList.count()))
    {
        StopPointDestination nextStopPointDestination=stopPointDestinationList.at(currentStopIndex+1);
        if (nextStopPointDestination.stopPoint.isViapoint==0)
        {
            viaPointListVdv.append(stopPointDestinationToVdv301ViaPoint(nextStopPointDestination.stopPoint,language));
            viaPointList.append(nextStopPointDestination);
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == 1)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            viaPointListVdv.append(stopPointDestinationToVdv301ViaPoint(viaPoint.stopPoint,language));
            viaPointList.append(viaPoint);
        }
    }



    if(selectedStopPointDestination.destination.NameFront.contains("|"))
    {
        QStringList frontNames=selectedStopPointDestination.destination.NameFront.split("|");
        if(frontNames.count()>0)
        {
            selectedStopPointDestination.destination.NameFront=frontNames.first();
        }
        if(frontNames.count()>1)
        {
            selectedStopPointDestination.destination.NameFront2=frontNames.at(1);
        }
    }

    QString displayContentClassString=Vdv301DisplayContent::displayContentClassEnumerationToQString(displayContentClass);


    switch(displayContentClass)
    {
    case DisplayContentFront:
    {
        Vdv301DisplayContent frontDisplayContent;

        frontDisplayContent.displayContentType=displayContentClass;
        frontDisplayContent.lineInformation=selectedLine;
        frontDisplayContent.displayContentRef=displayContentClassString;

        Vdv301Destination frontDestination;

        frontDestination.destinationRef=QString::number(selectedStopPointDestination.destination.idCis);
        frontDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameFront+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);

        QString destination2=selectedStopPointDestination.destination.NameFront2;
        if(!destination2.isEmpty())
        {
            frontDestination.destinationNameList<<Vdv301InternationalText(destination2,language);

        }

        frontDisplayContent.destination=frontDestination;

        output<<frontDisplayContent;

        break;
    }
    case DisplayContentSide:
    {
        if(viaPointListVdv.isEmpty())
        {
            Vdv301DisplayContent sideDisplayContent;
            sideDisplayContent.displayContentRef=displayContentClassString;
            sideDisplayContent.displayContentType=displayContentClass;

            sideDisplayContent.lineInformation=selectedLine;

            Vdv301Destination sideDestination;

            sideDestination.destinationRef=QString::number(selectedStopPointDestination.destination.idCis);
            sideDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);

            sideDisplayContent.destination=sideDestination;



            output<<sideDisplayContent;


        }
        else
        {
            /* foreach crashes the program for an unknown reason

            foreach(StopPointDestination viaPoint, viaPointList)
            {*/

            for(int i=0;i<viaPointListVdv.count();i++)
            {
                Vdv301DisplayContent sideDisplayContent;
                sideDisplayContent.displayContentRef=displayContentClassString;
                sideDisplayContent.displayContentType=displayContentClass;

                sideDisplayContent.lineInformation=selectedLine;

                Vdv301Destination sideDestination;
                sideDestination.destinationRef=QString::number(selectedStopPointDestination.destination.idCis);
                sideDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);



                StopPointDestination viaPoint=viaPointList.at(i);

                sideDestination.destinationNameList<<Vdv301InternationalText(viaPoint.stopPoint.NameSide+stopPropertiesToString2_3(viaPoint.stopPoint),language);

                sideDisplayContent.destination=sideDestination;
                output<<sideDisplayContent;

            }
        }


        break;
    }
    case DisplayContentRear:
    {
        Vdv301DisplayContent rearDisplayContent;
        rearDisplayContent.displayContentRef=displayContentClassString;
        rearDisplayContent.displayContentType=displayContentClass;
        rearDisplayContent.lineInformation=selectedLine;

        Vdv301Destination rearDestination;

        rearDestination.destinationRef=QString::number(selectedStopPointDestination.destination.idCis);
        rearDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameRear+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);

        rearDisplayContent.destination=rearDestination;
        output<<rearDisplayContent;

        break;
    }
    case DisplayContentLcd:
    {
        Vdv301DisplayContent lcdDisplayContent;
        lcdDisplayContent.displayContentRef=displayContentClassString;
        lcdDisplayContent.displayContentType=displayContentClass;
        lcdDisplayContent.lineInformation=selectedLine;

        Vdv301Destination lcdDestination;

        lcdDestination.destinationRef=QString::number(selectedStopPointDestination.destination.idCis);
        lcdDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameLcd+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);

        lcdDisplayContent.destination=lcdDestination;
        lcdDisplayContent.viaPointList=viaPointListVdv;
        output<<lcdDisplayContent;


        break;
    }
    default:
        qDebug()<<"break";
        //   break;
    }

    return output;

}


QStringList XmlCommon2_3_new::FareZoneInformationStructure2_3new( QVector<FareZone> fareZoneList)
{
    QMap<QString, QStringList> fareZoneByType;
    QStringList output;


    foreach( FareZone selectedFareZone, fareZoneList)
    {
        fareZoneByType[selectedFareZone.system].append(selectedFareZone.name);
    }

    foreach(QString key,fareZoneByType.keys())
    {
        QString result="";
        result+=key;
        result+=":";
        result+=fareZoneByType[key].join("_");

        output<<result;
    }

    return output;
}



Vdv301Trip XmlCommon2_3_new::TripInformation2_3new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
{

    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage2_3;
    QString tripRef=QString::number(tripList.at(tripIndex).idRopid);
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(tripIndex).globalStopPointDestinationList;


    Vdv301Trip vdv301trip;
    vdv301trip.tripRef=tripRef;
    vdv301trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(Vdv301Enumerations::LocationStateEnumerationToQString(vehicleState.locationState));
    //vdv301trip.additionalTextMessage=
    //vdv301trip.stopPointList=
    //vdv301trip.timetableDelay
    vdv301trip.runNumber=vehicleRunToRunNumber(vehicleState.currentVehicleRun);


    //stop sequence
    vdv301trip.stopPointList<<StopSequence2_3new(stopPointDestinationList,language,currentStopIndex,connectionList);


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




QVector<Vdv301StopPoint> XmlCommon2_3_new::StopSequence2_3new(QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList)
{

    QVector<Vdv301StopPoint> output;

    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        output<<StopPoint2_3new(stopPointDestinationList,i,connectionList,language,currentStopIndex);
    }
    return output;
}

QDomElement XmlCommon2_3_new::StopSequence2_3gen(QDomDocument &xmlDocument,QVector<Vdv301StopPoint> stopPointDestinationList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");


    foreach(Vdv301StopPoint stopPointDestination, stopPointDestinationList)
    {

        dStopSequence.appendChild(StopPoint2_3gen(xmlDocument,stopPointDestination));
    }
    return dStopSequence;
}



Vdv301StopPoint XmlCommon2_3_new::StopPoint2_3new( QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language,int currentStopIndex)
{
    qDebug()<<Q_FUNC_INFO;
    Vdv301StopPoint output;
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
    foreach(QString dFareZone, FareZoneInformationStructure2_3new(currentStopPoinDestination.stopPoint.fareZoneList) )
    {
        output.fareZoneList<<dFareZone;
    }


    return output;
}



QDomElement XmlCommon2_3_new::StopPoint2_3gen(QDomDocument &xmlDocument, Vdv301StopPoint stopPointDestination)
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement dStopPoint=xmlDocument.createElement("StopPoint");


    QDomElement dStopIndex=Value(xmlDocument,"StopIndex",QString::number(stopPointDestination.stopIndex));

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref(xmlDocument, "StopRef",stopPointDestination.stopRef));


    foreach (Vdv301InternationalText stopName, stopPointDestination.stopNameList) {

        QDomElement dStopLcdName=internationalTextTypeToDom(xmlDocument,"StopName",stopName.text,stopName.language);

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


    foreach(QString fareZone, stopPointDestination.fareZoneList )
    {
        dStopPoint.appendChild(Value(xmlDocument,"FareZone",fareZone));
    }

    return dStopPoint;
}


QDomElement XmlCommon2_3_new::ViaPoint2_3def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");

    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",viaPoint.viaPointRef));


    foreach(Vdv301InternationalText viaPointName, viaPoint.placeNameList )
    {
        QDomElement dPlaceLcdName=internationalTextTypeToDom(xmlDocument,"PlaceName",viaPointName.text ,viaPointName.language);
        dViaPoint.appendChild(dPlaceLcdName);
    }


    return dViaPoint;
}

Vdv301ViaPoint XmlCommon2_3_new::stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language)
{
    Vdv301ViaPoint output;
    output.viaPointRef=QString::number(stopPoint.idCis);
    output.placeNameList<<Vdv301InternationalText(stopPoint.NameLcd+stopPropertiesToString2_3(stopPoint),language);

    return output;
}
