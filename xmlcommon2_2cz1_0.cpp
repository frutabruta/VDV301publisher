#include "xmlcommon2_2cz1_0.h"

XmlCommon2_2CZ1_0::XmlCommon2_2CZ1_0() {}



QDomElement XmlCommon2_2CZ1_0::AdditionalTextMessage2_2CZ1_0(QDomDocument  &xmlDocument,QString messageContent)
{

    QDomElement TextMessage=xmlDocument.createElement("AdditionalTextMessage");
    QDomElement value=internationalTextTypeToDom(xmlDocument,"AdditionalTextMessageText",messageContent,defaultLanguage2_2CZ1_0);
    TextMessage.appendChild(value);
    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}


QDomElement XmlCommon2_2CZ1_0::AdditionalTextMessage2_2CZ1_0(QDomDocument  &xmlDocument,QString type, QString headline, QString text)
{

    QDomElement TextMessage=xmlDocument.createElement("AdditionalTextMessage");

    QDomElement TextMessageType=internationalTextTypeToDom(xmlDocument,"AdditionalTextMessageType",type,defaultLanguage2_2CZ1_0);
    QDomElement TextMessageHeadline=internationalTextTypeToDom(xmlDocument,"AdditionalTextMessageHeadline",headline,defaultLanguage2_2CZ1_0);
    QDomElement TextMessageText=internationalTextTypeToDom(xmlDocument,"AdditionalTextMessageText",text,defaultLanguage2_2CZ1_0);
    TextMessage.appendChild(TextMessageType);
    TextMessage.appendChild(TextMessageHeadline);
    TextMessage.appendChild(TextMessageText);

    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}


QVector<QDomElement> XmlCommon2_2CZ1_0::Connections2_2CZ1_0(QDomDocument  &xmlDocument, QVector<Connection> connectionList)
{
    qDebug()<<Q_FUNC_INFO;

    QString language ="cs";
    QVector<QDomElement> vystup;

    connectionList=Connection::orderConnectionsByExpectedDeparture(connectionList);
    /*
    for (int i=0;i<connectionList.count();i++)
    {*/
    foreach(Connection selectedConnection,connectionList)
    {
        //   aktualniPrestup.lin=aktualniPrestup.lin.number(10);
        QDomElement dConnection=xmlDocument.createElement("Connection");
        //    Connection vdv301prestup=aktualniPrestup.toPrestup();

        xmlDocument.appendChild(dConnection);

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

        QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",selectedConnection.line.lineName,language);
        dLineInformation.appendChild(dLineName);
        //        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",selectedConnection.line.lineNumber);
        QDomElement dLineNumber=Value(xmlDocument, "LineNumber","1");
        dLineInformation.appendChild(dLineNumber);
        QVector<QDomElement> linePropertyList=lineToLineProperties(xmlDocument, selectedConnection.line);

        foreach(QDomElement lineProperty,linePropertyList)
        {
            dLineInformation.appendChild(lineProperty);
        }

        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);


        QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedConnection.destinationName,language);
        dDestination.appendChild(dDestinationName);

        dConnection.appendChild(Value(xmlDocument,"Platform",selectedConnection.platform));

        //dopravni prostredek
        dConnectionMode.appendChild(xmlDocument.createElement("PtMainMode")).appendChild(xmlDocument.createTextNode(selectedConnection.mainMode));
        dConnectionMode.appendChild(xmlDocument.createElement(selectedConnection.mainMode)).appendChild(xmlDocument.createTextNode(selectedConnection.subMode));
        dConnection.appendChild(dConnectionMode);

        QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepartureTime", selectedConnection.expectedDepartureTimeQString());
        dConnection.appendChild(dExpectedDepartureTime);

        QDomElement dScheduledDepartureTime=Value(xmlDocument,"ScheduledDepartureTime",selectedConnection.scheduledDepartureTimeQString());
        dConnection.appendChild(dScheduledDepartureTime);

        vystup.push_back(dConnection);
        qDebug()<<"connection "<<selectedConnection.line.lineName<<" "<<selectedConnection.destinationName<<" departure:"<<selectedConnection.expectedDepartureTimeQString();

    }
    return vystup;
}



QDomElement XmlCommon2_2CZ1_0::DisplayContent2_2CZ1_0(QDomDocument  &xmlDocument,QString tagName,QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex)
{

    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);
    QString lineNumber=selectedStopPointDestination.line.lineNumber;
    QString lineName=selectedStopPointDestination.line.lineName;
    bool appendNextStopToViapoints=true;
    QDomElement dDisplayContent=xmlDocument.createElement(tagName);

    dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","1234"));

    //LINKA
    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);


    QString placeholder="";
    ConnectionMPV::ddDoVehicleMode(selectedStopPointDestination.line.kli,placeholder,placeholder,selectedStopPointDestination.line );
    QVector<QDomElement> linePropertiesDom=lineToLineProperties(xmlDocument, selectedStopPointDestination.line);

    foreach(QDomElement dProperty,linePropertiesDom)
    {
        dLineInformation.appendChild(dProperty);
    }


    QDomElement dLineName;
    //attempt to display 4 character line names in different font set
    if(lineName.length()>3)
    {
        //lineName="v &#x0A; &#x1B; &#x53; &#x0D; &#x34; "+lineName;

        QDomElement ctyrmistnaLinka=xmlDocument.createElement("test");


        QString escapeCharacter="";
        escapeCharacter+=QChar(0x1B);
        QDomCDATASection codeSection=xmlDocument.createCDATASection("<element>&#x1B;&#x53; ahoj</element>");


        dLineName=internationalTextTypeToDom(xmlDocument,"LineName",  lineName ,language);
        // dLineName.appendChild(rawInsert(lineName));


    }
    else
    {
        dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName,language);
    }

    dLineInformation.appendChild(dLineName);
    QDomElement dLineNumber=Value(xmlDocument,"LineNumber",lineNumber);
    dLineInformation.appendChild(dLineNumber);

    //CIL
    QDomElement dDestination=xmlDocument.createElement("Destination");
    //  dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktStopPointDestination.destination.naZnameni,"RequestStop"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferAirplane ,"Air"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferFerry ,"Ferry"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferMetroA ,"UndergroundA"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferMetroB ,"UndergroundB"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferMetroC ,"UndergroundC"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferMetroD ,"UndergroundD"));
    dDestination.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"DestinationProperty",selectedStopPointDestination.destination.transferTrain ,"Train"));
    /*
nedodelane priznaky:
            <xs:enumeration value="Bus"/>
            <xs:enumeration value="Funicular"/>
            <xs:enumeration value="Night"/>
            <xs:enumeration value="ReplacementService"/>
            <xs:enumeration value="ReplacementStop"/>
            <xs:enumeration value="RequestStop"/>
            <xs:enumeration value="Telecabin"/>
            <xs:enumeration value="Train"/>
            <xs:enumeration value="Tram"/>
            <xs:enumeration value="Trolleybus"/>

            */


    if (selectedStopPointDestination.destination.NameFront2=="")
    {
        if (selectedStopPointDestination.destination.NameFront.contains("|"))
        {
            QStringList frontDestinationNameList=selectedStopPointDestination.destination.NameFront.split("|");



            foreach ( QString selectedDestinationName, frontDestinationNameList)
            {
                QDomElement dDestinationFrontName=internationalTextTypeToDom(xmlDocument,"DestinationFrontName",selectedDestinationName,language);
                dDestination.appendChild(dDestinationFrontName);
            }

        }
        else
        {
            QDomElement dDestinationFrontName=internationalTextTypeToDom(xmlDocument,"DestinationFrontName",selectedStopPointDestination.destination.NameFront,language);
            dDestination.appendChild(dDestinationFrontName);
        }
    }
    else
    {
        QDomElement dDestinationFrontName=internationalTextTypeToDom(xmlDocument,"DestinationFrontName",selectedStopPointDestination.destination.NameFront,language);
        dDestination.appendChild(dDestinationFrontName);
        QDomElement dDestinationFrontName2=internationalTextTypeToDom(xmlDocument,"DestinationFrontName",selectedStopPointDestination.destination.NameFront2,language);
        dDestination.appendChild(dDestinationFrontName2);
    }

    QDomElement dDestinationSideName=internationalTextTypeToDom(xmlDocument,"DestinationSideName",selectedStopPointDestination.destination.NameSide,language);
    dDestination.appendChild(dDestinationSideName);
    QDomElement dDestinationRearName=internationalTextTypeToDom(xmlDocument,"DestinationRearName",selectedStopPointDestination.destination.NameRear,language);
    dDestination.appendChild(dDestinationRearName);
    QDomElement dDestinationLcdName=internationalTextTypeToDom(xmlDocument,"DestinationLcdName",selectedStopPointDestination.destination.NameLcd,language);
    dDestination.appendChild(dDestinationLcdName);
    QDomElement dDestinationInnerName=internationalTextTypeToDom(xmlDocument,"DestinationInnerName",selectedStopPointDestination.destination.NameInner,language);
    dDestination.appendChild(dDestinationInnerName);
    dDisplayContent.appendChild(dDestination);
    if ((appendNextStopToViapoints==true)&&((currentStopIndex+1)<stopPointDestinationList.count()))
    {
        StopPointDestination nextStopPointDestination=stopPointDestinationList.at(currentStopIndex+1);
        if (nextStopPointDestination.stopPoint.isViapoint==0)
        {
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlDocument,nextStopPointDestination.stopPoint,language));
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == 1)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlDocument,viaPoint.stopPoint,language));

        }
    }

    return dDisplayContent;
}

QDomElement XmlCommon2_2CZ1_0::FareZone2_2CZ1_0(QDomDocument  &xmlDocument, QString shortName,QString longName, QString type, QString language)
{

    QDomElement dFareZone=xmlDocument.createElement("FareZone");
    QDomElement zoneType=xmlDocument.createElement("FareZoneType");
    QDomElement zoneTypeName=internationalTextTypeToDom(xmlDocument,"FareZoneTypeName",type,language);
    zoneType.appendChild(zoneTypeName);
    dFareZone.appendChild(zoneType);

    QDomElement zoneLongName=internationalTextTypeToDom(xmlDocument,"FareZoneLongName",longName,language);
    QDomElement zoneShortName=internationalTextTypeToDom(xmlDocument,"FareZoneShortName",shortName,language);

    dFareZone.appendChild(zoneLongName);
    dFareZone.appendChild(zoneShortName);

    return dFareZone;
}


QDomElement XmlCommon2_2CZ1_0::FareZoneChange2_2CZ1_0(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneListFrom,QVector<FareZone> fareZoneListTo,QString language)
{

    QDomElement fareZoneChange=xmlDocument.createElement("FareZoneChange");
    QDomElement fromFareZones=xmlDocument.createElement("FromFareZones");
    QDomElement toFareZones=xmlDocument.createElement("ToFareZones");

    foreach (FareZone selectedFareZone, fareZoneListFrom)
    {
        QDomElement dFareZone=FareZone2_2CZ1_0(xmlDocument,selectedFareZone.name,selectedFareZone.name,selectedFareZone.system,language );
        fromFareZones.appendChild(dFareZone);
    }
    fareZoneChange.appendChild(fromFareZones);


    foreach (FareZone selectedFareZone, fareZoneListTo)
    {
        QDomElement dFareZone=FareZone2_2CZ1_0(xmlDocument,selectedFareZone.name,selectedFareZone.name,selectedFareZone.system,language );
        toFareZones.appendChild(dFareZone);
    }
    fareZoneChange.appendChild(toFareZones);

    return fareZoneChange;
}


QVector<QDomElement> XmlCommon2_2CZ1_0::FareZoneInformationStructure2_2CZ1_0(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneList,QString language)
{
    QVector<QDomElement> dFareZoneList;

    foreach( FareZone selectedFareZone, fareZoneList)
    {
        QDomElement dFareZone=FareZone2_2CZ1_0(xmlDocument,selectedFareZone.name,selectedFareZone.name,selectedFareZone.system,language );
        dFareZoneList.append(dFareZone);
    }

    return dFareZoneList;
}

QDomElement XmlCommon2_2CZ1_0::MyOwnVehicleMode2_2CZ1_0(QDomDocument  &xmlDocument, QString mainMode, QString subMode)
{
    QDomElement myOwnVehicleMode=xmlDocument.createElement("MyOwnVehicleMode");
    QDomElement ptMainModeElement=xmlDocument.createElement("PtMainMode");
    ptMainModeElement.appendChild( xmlDocument.createTextNode( mainMode  ));
    QDomElement subModeElement=xmlDocument.createElement(mainMode);
    subModeElement.appendChild( xmlDocument.createTextNode( subMode ));
    myOwnVehicleMode.appendChild(ptMainModeElement);
    myOwnVehicleMode.appendChild(subModeElement);
    return myOwnVehicleMode;

}



QDomElement XmlCommon2_2CZ1_0::TripInformation2_2CZ1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionsList, VehicleState vehicleState, int tripIndex, bool followingTrip)
{

    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage2_2CZ1_0;
    QString tripRef="";
    QVector<StopPointDestination> selectedStopPointDestinationList;
    QString specialAnnoucement="";

    if(isInRange(tripIndex,tripList.count(),Q_FUNC_INFO))
    {
        tripRef=QString::number(tripList.at(tripIndex).idRopid);
        selectedStopPointDestinationList=tripList.at(tripIndex).globalStopPointDestinationList;

        if(isInRange(vehicleState.currentStopIndex0,selectedStopPointDestinationList.count(),Q_FUNC_INFO))
        {
            specialAnnoucement=selectedStopPointDestinationList.at(vehicleState.currentStopIndex0).stopPoint.additionalTextMessage;
        }

    }



    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");
    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_2CZ1_0(xmlDocument,selectedStopPointDestinationList,language,currentStopIndex,connectionsList));

    if (followingTrip==false)
    {
        QDomElement dLocationState=xmlDocument.createElement("LocationState");
        dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString( vehicleState.locationState)));
        dTripInformation.appendChild(dLocationState);


        qDebug()<<"special announcement="<<specialAnnoucement;

        if(vehicleState.isSpecialAnnoucementUsed)
        {
            dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(xmlDocument,vehicleState.currentSpecialAnnoucement.type, vehicleState.currentSpecialAnnoucement.title, vehicleState.currentSpecialAnnoucement.text));
        }
        else if (specialAnnoucement!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
    }
    else
    {
        qDebug()<<"navazny=true";
    }

    //změna tarifního pásma
    if((currentStopIndex+1)<selectedStopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        if(isInRange(currentStopIndex-1,selectedStopPointDestinationList.count(),Q_FUNC_INFO)&&isInRange(currentStopIndex,selectedStopPointDestinationList.count(),Q_FUNC_INFO))
        {
            dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,selectedStopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,selectedStopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
        }


    }

    return dTripInformation;
}


QDomElement XmlCommon2_2CZ1_0::StopSequence2_2CZ1_0(QDomDocument &xmlDocument,QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Connection> connectionList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        dStopSequence.appendChild(StopPoint2_2CZ1_0(xmlDocument,stopPointDestinationList,i,connectionList,language,currentStopIndex));
    }
    return dStopSequence;
}



QDomElement XmlCommon2_2CZ1_0::StopPoint2_2CZ1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Connection> connectionList, QString language,int currentStopIndex)
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
    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);

    QByteArray cCurrentStopIndex=QByteArray::number(stopPointIterator+1);
    QString cStopName=selectedStopPointDestination.stopPoint.StopName;

    QDomElement dStopIndex=Value(xmlDocument,"StopIndex",cCurrentStopIndex);

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref(xmlDocument,"StopRef",QString::number(selectedStopPointDestination.stopPoint.idCis)));


    QDomElement dStopName=internationalTextTypeToDom(xmlDocument,"StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);

    QDomElement dStopFrontName=internationalTextTypeToDom(xmlDocument,"StopFrontName",selectedStopPointDestination.stopPoint.NameFront,language);
    dStopPoint.appendChild(dStopFrontName);
    QDomElement dStopSideName=internationalTextTypeToDom(xmlDocument,"StopSideName",selectedStopPointDestination.stopPoint.NameSide,language);
    dStopPoint.appendChild(dStopSideName);
    QDomElement dStopRearName=internationalTextTypeToDom(xmlDocument,"StopRearName",selectedStopPointDestination.stopPoint.NameRear,language);
    dStopPoint.appendChild(dStopRearName);
    QDomElement dStopLcdName=internationalTextTypeToDom(xmlDocument,"StopLcdName",selectedStopPointDestination.stopPoint.NameLcd,language);
    dStopPoint.appendChild(dStopLcdName);
    QDomElement dStopInnerName=internationalTextTypeToDom(xmlDocument,"StopInnerName",selectedStopPointDestination.stopPoint.NameInner,language);
    dStopPoint.appendChild(dStopInnerName);

    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.onRequest,"RequestStop"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferAirplane ,"Air"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferFerry ,"Ferry"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferMetroA ,"UndergroundA"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferMetroB ,"UndergroundB"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferMetroC ,"UndergroundC"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferMetroD ,"UndergroundD"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"StopProperty",selectedStopPointDestination.stopPoint.transferTrain ,"Train"));
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

    QDomElement dDisplayContent=DisplayContent2_2CZ1_0(xmlDocument,"DisplayContent",stopPointDestinationList,language,stopPointIterator,currentStopIndex);

    dStopPoint.appendChild(dDisplayContent);


    QDomElement dExpectedDepartureTime=Value(xmlDocument,"ArrivalScheduled",qTimeToQDateTimeToday( StopPoint::secondsToQtime(selectedStopPointDestination.stopPoint.ArrivalTime)).toString("yyyy-MM-ddThh:mm:ss"));
    dStopPoint.appendChild(dExpectedDepartureTime);

    QDomElement dScheduledDepartureTime=Value(xmlDocument,"DepartureScheduled",qTimeToQDateTimeToday( selectedStopPointDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss"));
    dStopPoint.appendChild(dScheduledDepartureTime);

    /*
    QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepartureTime",qTimeToQDateTimeToday( selectedStopPointDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss"));
    dStopPoint.appendChild(dExpectedDepartureTime);


    QDomElement dScheduledDepartureTime=Value(xmlDocument,"ScheduledDepartureTime",qTimeToQDateTimeToday( selectedStopPointDestination.stopPoint.departureToQTime()).toString("yyyy-MM-ddThh:mm:ss"));
    dStopPoint.appendChild(dScheduledDepartureTime);
*/
    // qDebug()<<"cCurrentStopIndex.toInt() "<< cCurrentStopIndex.toInt()<<" (currentStopIndex+1) " << (currentStopIndex+1);


    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {

        foreach(QDomElement dConnection,Connections2_2CZ1_0(xmlDocument,connectionList))
        {
            dStopPoint.appendChild(dConnection );
        }

    }


    foreach(QDomElement dFareZone, FareZoneInformationStructure2_2CZ1_0(xmlDocument,selectedStopPointDestination.stopPoint.fareZoneList,language) )
    {
        dStopPoint.appendChild(dFareZone);
    }

    return dStopPoint;
}

QDomElement XmlCommon2_2CZ1_0::xxxProperty2_2CZ1_0(QDomDocument &xmlDocument,QString propertyName,bool valueBoolean,QString valueName)
{
    QDomElement output;
    if(valueBoolean)
    {
        output=xmlDocument.createElement(propertyName);
        output.appendChild(xmlDocument.createTextNode(valueName));
    }

    return output;
}



QDomElement XmlCommon2_2CZ1_0::ViaPoint2_2CZ1_0(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.onRequest,"RequestStop"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.transferAirplane ,"Air"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.transferFerry ,"Ferry"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.transferMetroA ,"UndergroundA"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.transferMetroB ,"UndergroundB"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.transferMetroC ,"UndergroundC"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0(xmlDocument,"ViaPointProperty",viaPoint.transferMetroD ,"UndergroundD"));
    /*
nedodelane priznaky:
            <xs:enumeration value="Bus"/>
            <xs:enumeration value="Funicular"/>
            <xs:enumeration value="Night"/>
            <xs:enumeration value="ReplacementService"/>
            <xs:enumeration value="ReplacementStop"/>
            <xs:enumeration value="RequestStop"/>
            <xs:enumeration value="Telecabin"/>
            <xs:enumeration value="Train"/>
            <xs:enumeration value="Tram"/>
            <xs:enumeration value="Trolleybus"/>
            <xs:enumeration value="UndergroundA"/>
            <xs:enumeration value="UndergroundB"/>
            <xs:enumeration value="UndergroundC"/>
            <xs:enumeration value="UndergroundD"/>
            */
    QDomElement dPlaceName=internationalTextTypeToDom(xmlDocument,"PlaceName",viaPoint.StopName,language);
    dViaPoint.appendChild(dPlaceName);

    QDomElement dPlaceSideName=internationalTextTypeToDom(xmlDocument,"PlaceSideName",viaPoint.NameSide,language);
    dViaPoint.appendChild(dPlaceSideName);

    QDomElement dPlaceLcdName=internationalTextTypeToDom(xmlDocument,"PlaceLcdName",viaPoint.NameLcd,language);
    dViaPoint.appendChild(dPlaceLcdName);


    QDomElement dPlaceInnerName=internationalTextTypeToDom(xmlDocument,"PlaceInnerName",viaPoint.NameInner,language);
    dViaPoint.appendChild(dPlaceInnerName);
    return dViaPoint;
}


QVector<QDomElement> XmlCommon2_2CZ1_0::lineToLineProperties(QDomDocument xmlDocument, Line line)
{
    QVector<QDomElement> output;

    output.push_back(xxxProperty2_2CZ1_0(xmlDocument,"LineProperty",line.isDiversion ,"Diversion"));
    output.push_back(xxxProperty2_2CZ1_0(xmlDocument,"LineProperty",!line.isNight ,"Day"));
    output.push_back(xxxProperty2_2CZ1_0(xmlDocument,"LineProperty",line.isNight ,"Night"));
    output.push_back(xxxProperty2_2CZ1_0(xmlDocument,"LineProperty",line.isReplacement ,"Replacement"));
    output.push_back(xxxProperty2_2CZ1_0(xmlDocument,"LineProperty",line.isSpecial ,"Special"));
    output.push_back(xxxProperty2_2CZ1_0(xmlDocument,"LineProperty",line.isWheelchair ,"WheelChair"));

    return output;
}
