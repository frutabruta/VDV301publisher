#include "xmlcommon2_3.h"

XmlCommon2_3::XmlCommon2_3() {}


QVector<QDomElement> XmlCommon2_3::Connections2_3(QDomDocument  &xmlDocument, QVector<Connection> connectionList)
{
    qDebug()<<Q_FUNC_INFO;

    // QString defaultLanguage2_3 ="cs";
    QVector<QDomElement> output;

    connectionList=Connection::orderConnectionsByExpectedDeparture(connectionList);
    /*
    for (int i=0;i<connectionList.count();i++)
    {Connection selectedConnection=connectionList.at(i); */

    foreach(Connection selectedConnection, connectionList)
    {

        //   aktualniPrestup.lin=aktualniPrestup.lin.number(10);
        QDomElement dConnection=xmlDocument.createElement("Connection");
        //    Connection vdv301prestup=aktualniPrestup.toPrestup();

        xmlDocument.appendChild(dConnection);

        QDomElement dStopRef=ref(xmlDocument,"StopRef","0");

        dConnection.appendChild(dStopRef);

        QDomElement dConnectionRef=ref(xmlDocument,"ConnectionRef","0");

        dConnection.appendChild(dConnectionRef);

        QDomElement dConnectionMode = xmlDocument.createElement("ConnectionMode");



        if(selectedConnection.connectionProperty=="accessible")
        {
            dConnection.appendChild(xmlDocument.createElement("ConnectionProperty")).appendChild(xmlDocument.createTextNode("Accessible"));
        }
        dConnection.appendChild(xmlDocument.createElement("ConnectionType")).appendChild(xmlDocument.createTextNode("Interchange"));

        QDomElement dDisplayContent=xmlDocument.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);

        QDomElement dLineInformation=xmlDocument.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);

        QString lineRef="noRef";
        dLineInformation.appendChild(ref(xmlDocument,"LineRef",lineRef));

        QString lineName=selectedConnection.line.lineName;

        if(selectedConnection.line.kli==0)
        {
            //golemio
            lineName=colorDisplayRules.styleToString(lineName,colorDisplayRules.lineToStyle(selectedConnection.line,selectedConnection.subMode));

        }
        else
        {
            //mpvnet
            lineName=colorDisplayRules.styleToString(lineName,colorDisplayRules.lineToStyle(selectedConnection.line));

        }


        if(selectedConnection.subMode=="metro")
        {

            lineName="<icon type=\"c_Underground"+selectedConnection.line.lineName+"\">="+selectedConnection.line.lineName+"=</icon>";

        }


        QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName,defaultLanguage2_3);
        dLineInformation.appendChild(dLineName);

        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",selectedConnection.line.lineNumber);
        dLineInformation.appendChild(dLineNumber);

        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);



        QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedConnection.destinationName,defaultLanguage2_3);
        dDestination.appendChild(dDestinationName);

        dConnection.appendChild(Value(xmlDocument,"Platform",selectedConnection.platform));

        //dopravni prostredek
        dConnectionMode.appendChild(xmlDocument.createElement("PtMainMode")).appendChild(xmlDocument.createTextNode(selectedConnection.mainMode));
        dConnectionMode.appendChild(xmlDocument.createElement(selectedConnection.mainMode)).appendChild(xmlDocument.createTextNode(selectedConnection.subMode));
        dConnection.appendChild(dConnectionMode);


        qDebug()<<"connection "<<selectedConnection.line.lineName<<" "<<selectedConnection.destinationName<<" time:"<<selectedConnection.expectedDepartureTimeQString();

        QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepartureTime", selectedConnection.expectedDepartureTimeQString());
        dConnection.appendChild(dExpectedDepartureTime);

        QDomElement dScheduledDepartureTime=Value(xmlDocument,"ScheduledDepartureTime",selectedConnection.scheduledDepartureTimeQString());
        dConnection.appendChild(dScheduledDepartureTime);

        output.push_back(dConnection);
    }
    return output;
}






QDomElement XmlCommon2_3::FareZone2_3(QDomDocument  &xmlDocument, QString shortName)
{

    QDomElement dFareZone=Value(xmlDocument,"FareZone",shortName);
    /*
    QDomElement zoneType=xmlDocument.createElement("FareZoneType");
    QDomElement zoneTypeName=internationalTextType(xmlDocument,"FareZoneTypeName",type,language);
    zoneType.appendChild(zoneTypeName);
    dFareZone.appendChild(zoneType);

    QDomElement zoneLongName=internationalTextType(xmlDocument,"FareZoneLongName",longName,language);
    QDomElement zoneShortName=internationalTextType(xmlDocument,"FareZoneShortName",shortName,language);

    dFareZone.appendChild(zoneLongName);
    dFareZone.appendChild(zoneShortName);*/

    return dFareZone;
}


QVector<QDomElement> XmlCommon2_3::FareZoneInformationStructure2_3(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneList,QString language)
{
    QVector<QDomElement> dFareZoneList;

    QMap<QString, QStringList> fareZoneByType;


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

        QDomElement dFareZone=FareZone2_3(xmlDocument,result);
        dFareZoneList.append(dFareZone);
    }

    return dFareZoneList;
}



QDomElement XmlCommon2_3::DisplayContent2_3(QDomDocument  &xmlDocument, QString tagName,QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
{
    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);
    QString lineNumber=selectedStopPointDestination.line.lineNumber;
    QString lineName=selectedStopPointDestination.line.lineName;
    QString lineRef=QString::number(selectedStopPointDestination.line.c);

    lineName=colorDisplayRules.styleToString(lineName,colorDisplayRules.lineToStyle(selectedStopPointDestination.line));

    bool appendNextStopToViapoints=true;
    QDomElement dDisplayContent=xmlDocument.createElement(tagName);


    QString placeholder="";
    ConnectionMPV::ddDoVehicleMode(selectedStopPointDestination.line.kli,placeholder,placeholder,selectedStopPointDestination.line );
    /* QVector<QDomElement> priznakyLinky=linkaToLineProperties( aktStopPointDestination.linka);

    foreach(QDomElement priznak,priznakyLinky)
    {
        dLineInformation.appendChild(priznak);
    }
*/

    QDomElement viaPointObsah;

    QVector<QDomElement> viaPointList;

    if ((appendNextStopToViapoints==true)&&((currentStopIndex+1)<stopPointDestinationList.count()))
    {
        StopPointDestination nextStopPointDestination=stopPointDestinationList.at(currentStopIndex+1);
        if (nextStopPointDestination.stopPoint.isViapoint==0)
        {
            viaPointList.append(ViaPoint2_3(xmlDocument,nextStopPointDestination.stopPoint,language));
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == 1)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            viaPointList.append(ViaPoint2_3(xmlDocument,viaPoint.stopPoint,language));
        }
    }




    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");

    dLineInformation.appendChild(ref(xmlDocument,"LineRef",lineRef));

    QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName,language);

    dLineInformation.appendChild(dLineName);
    QDomElement dLineNumber=Value(xmlDocument,"LineNumber",lineNumber);
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlDocument.createElement("Destination");

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

    QDomElement dDestinationName;
    QDomElement dDestinationName2;

    switch(displayContentClass)
    {
    case DisplayContentFront:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Front"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));

        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        if(!selectedStopPointDestination.destination.NameFront2.isEmpty())
        {
            dDestinationName2=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront2,language);
            dDestination.appendChild(dDestinationName2);
        }
        dDisplayContent.appendChild(dDestination);
        break;
    case DisplayContentSide:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Side"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        dDisplayContent.appendChild(viaPointObsah);
        break;
    case DisplayContentRear:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Rear"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameRear+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        break;
    case DisplayContentLcd:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Lcd"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameLcd+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        foreach(QDomElement dViaPoint, viaPointList)
        {
            dDisplayContent.appendChild(dViaPoint);
        }

        break;

    default:

        break;
    }

    return dDisplayContent;
}



QVector<QDomElement> XmlCommon2_3::DisplayContentViaPointDestination2_3(QDomDocument  &xmlDocument, QString tagName,QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
{

    QVector<QDomElement> output;
    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);
    QString lineNumber=selectedStopPointDestination.line.lineNumber;
    QString lineName=selectedStopPointDestination.line.lineName;
    QString lineRef=QString::number(selectedStopPointDestination.line.c);

    lineName=colorDisplayRules.styleToString(lineName,colorDisplayRules.lineToStyle(selectedStopPointDestination.line));

    bool appendNextStopToViapoints=true;
    // QDomElement dDisplayContent=xmlDocument.createElement(tagName);


    QString placeholder="";
    ConnectionMPV::ddDoVehicleMode(selectedStopPointDestination.line.kli,placeholder,placeholder,selectedStopPointDestination.line );
    /* QVector<QDomElement> priznakyLinky=linkaToLineProperties( aktStopPointDestination.linka);

    foreach(QDomElement priznak,priznakyLinky)
    {
        dLineInformation.appendChild(priznak);
    }
*/

    QDomElement viaPointObsah;

    QVector<QDomElement> viaPointListDom;
    QVector<StopPointDestination> viaPointList;

    if ((appendNextStopToViapoints==true)&&((currentStopIndex+1)<stopPointDestinationList.count()))
    {
        StopPointDestination nextStopPointDestination=stopPointDestinationList.at(currentStopIndex+1);
        if (nextStopPointDestination.stopPoint.isViapoint==0)
        {
            viaPointListDom.append(ViaPoint2_3(xmlDocument,nextStopPointDestination.stopPoint,language));
            viaPointList.append(nextStopPointDestination);
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == 1)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            viaPointListDom.append(ViaPoint2_3(xmlDocument,viaPoint.stopPoint,language));
            viaPointList.append(viaPoint);
        }
    }
    /*
    QStringList viaPointSideDisplayNames;
    for (int k=currentStopIndex+1;k<stopPointDestinationList.count() ;k++)
    {
        if(stopPointDestinationList.at(k).stopPoint.isViapoint == 1)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(k);
            viaPointSideDisplayNames.append(viaPoint.stopPoint.NameSide);

        }
    }
*/

    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");

    dLineInformation.appendChild(ref(xmlDocument,"LineRef",lineRef));


    QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName,language);
    dLineInformation.appendChild(dLineName);

    QDomElement dLineNumber=Value(xmlDocument,"LineNumber",lineNumber);
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlDocument.createElement("Destination");

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

    QDomElement dDestinationName;
    QDomElement dDestinationName2;

    switch(displayContentClass)
    {
    case DisplayContentFront:
    {
        QDomElement dDisplayContent=xmlDocument.createElement(tagName);
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Front"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));

        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        if(!selectedStopPointDestination.destination.NameFront2.isEmpty())
        {
            dDestinationName2=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront2,language);
            dDestination.appendChild(dDestinationName2);
        }

        dDisplayContent.appendChild(dDestination);
        output<<dDisplayContent;
        break;
    }
    case DisplayContentSide:
    {
        if(viaPointListDom.isEmpty())
        {
            QDomElement dDisplayContent=xmlDocument.createElement(tagName);
            dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Side"));
            QDomElement dLineInformationCopy=dLineInformation;
            dDisplayContent.appendChild(dLineInformationCopy);
            QDomElement dDestinationCopy=dDestination;
            dDestinationCopy.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
            dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
            dDestination.appendChild(dDestinationName);
            // dDestinationName=internationalTextType(xmlDocument,"DestinationName",viaPoint.stopPoint.NameSide+stopPropertiesToString2_3(viaPoint.stopPoint),language);
            dDestinationCopy.appendChild(dDestinationName);
            dDisplayContent.appendChild(dDestinationCopy);
            //   dDisplayContent.appendChild(viaPointObsah);
            output<<dDisplayContent;

        }
        else
        {
            /* foreach crashes the program for an unknown reason

            foreach(StopPointDestination viaPoint, viaPointList)
            {*/

            for(int i=0;i<viaPointList.count();i++)
            {
                StopPointDestination viaPoint=viaPointList.at(i);
                QDomElement dDisplayContent=xmlDocument.createElement(tagName);
                dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Side"));
                QDomElement dLineInformationCopy=dLineInformation.cloneNode().toElement();
                dDisplayContent.appendChild(dLineInformationCopy);
                QDomElement dDestinationCopy=dDestination.cloneNode().toElement();
                dDestinationCopy.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
                dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
                dDestinationCopy.appendChild(dDestinationName);
                dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",viaPoint.stopPoint.NameSide+stopPropertiesToString2_3(viaPoint.stopPoint),language);
                dDestinationCopy.appendChild(dDestinationName);
                dDisplayContent.appendChild(dDestinationCopy);
                //dDisplayContent.appendChild(viaPointObsah);
                output<<dDisplayContent;
            }
        }


        break;
    }
    case DisplayContentRear:
    {
        QDomElement dDisplayContent=xmlDocument.createElement(tagName);
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Rear"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameRear+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        output<<dDisplayContent;
        break;
    }
    case DisplayContentLcd:
    {
        QDomElement dDisplayContent=xmlDocument.createElement(tagName);
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Lcd"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameLcd+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        foreach(QDomElement dViaPoint, viaPointListDom)
        {
            dDisplayContent.appendChild(dViaPoint);
        }
        output<<dDisplayContent;
        break;
    }
    default:

        break;
    }

    return output;
}

Vdv301Line XmlCommon2_3::lineToVdv301Line2_3(Line &line)
{
    Vdv301Line output;

    output.lineNumber=line.lineNumber;

    output.lineNameList<<Vdv301InternationalText(line.lineName,defaultLanguage2_3);
    output.lineRef=QString::number(line.c);

    return output;
}





QDomElement XmlCommon2_3::TripInformation2_3(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
{
    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage2_3;
    QString tripRef=QString::number(tripList.at(tripIndex).idRopid);
    QVector<StopPointDestination> stopPointDestinationList=tripList.at(tripIndex).globalStopPointDestinationList;
    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_3(xmlDocument,stopPointDestinationList,language,currentStopIndex,connectionList));

    if (followingTrip==false)
    {
        QDomElement dLocationState=xmlDocument.createElement("LocationState");
        dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString( vehicleState.locationState)));
        dTripInformation.appendChild(dLocationState);

        QString specialAnnouncement=stopPointDestinationList.at(vehicleState.currentStopIndex0).stopPoint.additionalTextMessage;
        qDebug()<<"special announcement="<<specialAnnouncement;

        if(vehicleState.isSpecialAnnoucementUsed)
        {
            dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage", vehicleState.currentSpecialAnnoucement.text,language));
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
    QDomElement dRunNumber=Value(xmlDocument,"RunNumber",vehicleRunToRunNumber(vehicleState.currentVehicleRun));
    dTripInformation.appendChild(dRunNumber);

    return dTripInformation;
}


QDomElement XmlCommon2_3::StopSequence2_3(QDomDocument &xmlDocument,QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Connection> connectionList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        dStopSequence.appendChild(StopPoint2_3(xmlDocument,stopPointDestinationList,i,connectionList,language,currentStopIndex));
    }
    return dStopSequence;
}




QDomElement XmlCommon2_3::StopPoint2_3(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Connection> connectionList, QString language,int currentStopIndex)
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement dStopPoint=xmlDocument.createElement("StopPoint");
    if (stopPointDestinationList.isEmpty())
    {
        qDebug()<<"stop list is empty";
        return dStopPoint;
    }
    if (stopPointIterator>=stopPointDestinationList.length())
    {
        qDebug()<<"stop index is out of range";
        return dStopPoint;
    }
    StopPointDestination currentStopPoinDestination=stopPointDestinationList.at(stopPointIterator);

    QByteArray cCurrentStopIndex=QByteArray::number(stopPointIterator+1);
    //QString cStopName= currentStopPoinDestination.stopPoint.StopName;

    QDomElement dStopIndex=Value(xmlDocument,"StopIndex",cCurrentStopIndex);

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref(xmlDocument, "StopRef",QString::number(currentStopPoinDestination.stopPoint.idCis)));


    /*
    QDomElement dStopName=internationalTextTypeToDom("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);
    */


    QDomElement dStopLcdName=internationalTextTypeToDom(xmlDocument,"StopName",currentStopPoinDestination.stopPoint.NameLcd+stopPropertiesToString2_3(currentStopPoinDestination.stopPoint),language);

    dStopPoint.appendChild(dStopLcdName);




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
    dDisplayContentVector<<DisplayContentViaPointDestination2_3(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentFront);
    dDisplayContentVector<<DisplayContentViaPointDestination2_3(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentSide);
    dDisplayContentVector<<DisplayContentViaPointDestination2_3(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentRear);
    dDisplayContentVector<<DisplayContentViaPointDestination2_3(xmlDocument,"DisplayContent",stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentLcd);
    foreach(QDomElement dDisplayContentSide, dDisplayContentVector)
    {
        dStopPoint.appendChild(dDisplayContentSide);
    }




    QDomElement dExpectedDepartureTime=Value(xmlDocument,"ArrivalScheduled",qTimeToQDateTimeToday( StopPoint::secondsToQtime(currentStopPoinDestination.stopPoint.ArrivalTime)).toString("yyyy-MM-ddThh:mm:ss"));
    dStopPoint.appendChild(dExpectedDepartureTime);

    QDomElement dScheduledDepartureTime=Value(xmlDocument,"DepartureScheduled",qTimeToQDateTimeToday( currentStopPoinDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss"));
    dStopPoint.appendChild(dScheduledDepartureTime);



    // qDebug()<<"cCurrentStopIndex.toInt() "<< cCurrentStopIndex.toInt()<<" (currentStopIndex+1) " << (currentStopIndex+1);


    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {

        foreach(QDomElement elementPrestupu,Connections2_3(xmlDocument,connectionList))
        {
            dStopPoint.appendChild(elementPrestupu );
        }

    }


    foreach(QDomElement dFareZone, FareZoneInformationStructure2_3(xmlDocument,currentStopPoinDestination.stopPoint.fareZoneList,language) )
    {
        dStopPoint.appendChild(dFareZone);
    }

    return dStopPoint;
}



QDomElement XmlCommon2_3::ViaPoint2_3(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");

    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",QString::number(viaPoint.idCis)));


    QDomElement dPlaceLcdName=internationalTextTypeToDom(xmlDocument,"PlaceName",viaPoint.NameLcd+stopPropertiesToString2_3(viaPoint),language);
    dViaPoint.appendChild(dPlaceLcdName);

    return dViaPoint;
}





QDomElement XmlCommon2_3::AdditionalTextMessage2_3(QDomDocument &xmlDocument, QString messageContent)
{

    /*
    if (isScrolling)
    {
        messageContent="$LS$"+messageContent;
    }*/
    QDomElement TextMessage=Value(xmlDocument,"AdditionalTextMessage",messageContent);

    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}

QString XmlCommon2_3::stopPropertiesToString2_3(StopPoint stopPoint)
{
    QString output="";

    output+=xxxProperty2_3("c_RequestStop","ŕ",stopPoint.onRequest);
    output+=xxxProperty2_3("c_Air","\\",stopPoint.transferAirplane);
    output+=xxxProperty2_3("c_Ferry","Ĺ",stopPoint.transferFerry);
    output+=xxxProperty2_3("c_UndergroundA","[A]",stopPoint.transferMetroA);
    output+=xxxProperty2_3("c_UndergroundB","[B]",stopPoint.transferMetroB );
    output+=xxxProperty2_3("c_UndergroundC","[C]",stopPoint.transferMetroC);
    output+=xxxProperty2_3("c_UndergroundD","[D]",stopPoint.transferMetroD);
    output+=xxxProperty2_3("c_Train","~",stopPoint.transferTrain);
    return output;
}


QString XmlCommon2_3::xxxProperty2_3(QString icon, QString text,bool value)
{
    QString output="";
    if(value)
    {
        output="<icon type=\""+icon+"\" >"+text+"</icon>";

    }
    return output;
}


