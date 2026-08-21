#include "xmlcommon1_0_new.h"

#include "VDV301DataStructures/connectionmpv.h"

Q_LOGGING_CATEGORY(XmlCommon1_0_newLog, "XmlCommon1_0_new")

XmlCommon1_0_new::XmlCommon1_0_new() {}


Vdv301Connection XmlCommon1_0_new::connectionToVdv301Connection(Connection connection, DisplayContentClass displayClass)
{
    qCDebug(XmlCommon1_0_newLog)<<Q_FUNC_INFO;
    Vdv301Connection output;
    Vdv301DisplayContent displayContent;

    displayContent.displayContentType=displayClass;
    displayContent.displayContentRef=displayContent.displayContentClassEnumerationToQString(displayContent.displayContentType);

    displayContent.lineInformation=lineToVdv301Line1_0(connection.line,connection.subMode, addLineStyle);

    //displayContent.lineInformation.lineNameList<<Vdv301InternationalText(this->line.lineName,language);
    displayContent.destination.destinationNameList<<Vdv301InternationalText(connection.destinationName,defaultLanguage1_0);

    output.vdv301displayContentList<<displayContent;

    output.scheduledDepartureTime=connection.scheduledDepartureTime;
    output.expectedDepartureTime=connection.expectedDepartureTime;
    output.platform=connection.platform;

    output.mainMode=connection.mainMode;
    output.subMode=connection.subMode;

    QString wuppertalMeanOfTransport="";

    if (connection.subMode.contains("Bus"))
    {
        wuppertalMeanOfTransport="$01"; //Bus

    }
    if(connection.subMode.contains("metro"))
    {
        wuppertalMeanOfTransport="$03"; //metro

    }
    if(connection.subMode.contains("Tram"))
    {
        wuppertalMeanOfTransport="$02"; //tram

    }
    if(connection.subMode.contains("Rail"))
    {
        wuppertalMeanOfTransport="$04"; //train

    }

    output.vehicleTypeRef="3";
    output.vehicleStructureName=Vdv301InternationalText(wuppertalMeanOfTransport,defaultLanguage1_0);
    return output;

}

QDomElement XmlCommon1_0_new::Connection1_0gen(QDomDocument  &xmlDocument, Vdv301Connection connection)
{
    qCDebug(XmlCommon1_0_newLog)<<Q_FUNC_INFO;

    QDomElement dConnection=xmlDocument.createElement("Connection");
    xmlDocument.appendChild(dConnection);

    // StopRef" type="IBIS-IP.NMTOKEN"
    QDomElement dStopRef=Value(xmlDocument,"StopRef",connection.stopRef);
    dConnection.appendChild(dStopRef);

    // ConnectionRef" type="IBIS-IP.NMTOKEN">
    QDomElement dConnectionRef=Value(xmlDocument,"ConnectionRef",connection.connectionRef);
    dConnection.appendChild(dConnectionRef);

    // ConnectionType  type="ConnectionTypeEnumeration
    switch(connection.connectionType)
    {

    case ConnectionTypeInterchange:
        dConnection.appendChild(xmlDocument.createElement("ConnectionType")).appendChild(xmlDocument.createTextNode("Interchange"));

        break;
    case ConnectionTypeProtectedConnection:
        dConnection.appendChild(xmlDocument.createElement("ConnectionType")).appendChild(xmlDocument.createTextNode("ProtectedConnection"));

        break;
    }

    // DisplayContent" type="DisplayContentStructure">


    for(const Vdv301DisplayContent &displayContent : connection.vdv301displayContentList)
    {
        QDomElement dDisplayContent=DisplayContentViaPointDestination1_0gen(xmlDocument,"DisplayContent",displayContent);
        dConnection.appendChild(dDisplayContent);       
    }

    // Platform" type="IBIS-IP.string" minOccurs="0"
    if(connection.platform!="")
    {
        dConnection.appendChild(Value(xmlDocument,"Platform",connection.platform));
    }


    // ConnectionState" type="ConnectionStateEnumeration" minOccurs="0">
    //TransportMode" type="VehicleStructure" minOccurs="0">


    QDomElement dTransportMode = xmlDocument.createElement("TransportMode");

    //mean of transport
    dTransportMode.appendChild(this->ref(xmlDocument,"VehicleTypeRef",connection.vehicleTypeRef));
    dTransportMode.appendChild(this->internationalTextTypeToDom(xmlDocument,"Name",connection.vehicleStructureName));
    dConnection.appendChild(dTransportMode);



    // ExpectedDepatureTime" type="IBIS-IP.dateTime" minOccurs="0">
    QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepatureTime", connection.expectedDepartureTimeQString());
    dConnection.appendChild(dExpectedDepartureTime);


    return dConnection;
}

QVector<Vdv301DisplayContent> XmlCommon1_0_new::DisplayContentViaPointDestination1_0new(QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
{
    QVector<Vdv301DisplayContent> output;
    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);

    QString placeholder="";
    ConnectionMPV::ddDoVehicleMode(selectedStopPointDestination.line.kli,placeholder,placeholder,selectedStopPointDestination.line );

    // DisplayContentRef minOccurs="0"
    QString displayContentClassString=Vdv301DisplayContent::displayContentClassEnumerationToQString(displayContentClass);
    // LineInformation
    Vdv301Line selectedLine=lineToVdv301Line1_0(selectedStopPointDestination.line, addLineStyle);

    // Destination

    // ViaPoint minOccurs="0"
    QDomElement viaPointObsah;
    QVector<Vdv301ViaPoint> viaPointListVdv;

    QVector<StopPointDestination> viaPointList;

    if ((appendNextStopToViapoints==true)&&((currentStopIndex+1)<stopPointDestinationList.count()))
    {
        StopPointDestination nextStopPointDestination=stopPointDestinationList.at(currentStopIndex+1);
        if (nextStopPointDestination.stopPoint.isViapoint==false)
        {
            viaPointListVdv.append(stopPointDestinationToVdv301ViaPoint(nextStopPointDestination.stopPoint,language));
            viaPointList.append(nextStopPointDestination);
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == true)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            viaPointListVdv.append(stopPointDestinationToVdv301ViaPoint(viaPoint.stopPoint,language));
            viaPointList.append(viaPoint);
        }
    }
    // AdditionalInformation minOccurs="0"
    // RunNumber minOccurs="0"
    // DisplayPolicyGroup minOccurs="0"


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

    switch(displayContentClass)
    {
    case DisplayContentFront:
    {
        Vdv301DisplayContent frontDisplayContent;

        frontDisplayContent.displayContentType=displayContentClass;
        frontDisplayContent.lineInformation=selectedLine;
        frontDisplayContent.displayContentRef=displayContentClassString;

        Vdv301Destination frontDestination;

        frontDestination.destinationRef=selectedStopPointDestination.destination.ref();
        frontDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameFront+stopPropertiesToString1_0(selectedStopPointDestination.destination),language);

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

            sideDestination.destinationRef=selectedStopPointDestination.destination.ref();
            sideDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameSide+stopPropertiesToString1_0(selectedStopPointDestination.destination),language);

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
                sideDestination.destinationRef=selectedStopPointDestination.destination.ref();
                sideDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameSide+stopPropertiesToString1_0(selectedStopPointDestination.destination),language);

                StopPointDestination viaPoint=viaPointList.at(i);

                sideDestination.destinationNameList<<Vdv301InternationalText(viaPoint.stopPoint.NameSide+stopPropertiesToString1_0(viaPoint.stopPoint),language);

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
        rearDestination.destinationRef=selectedStopPointDestination.destination.ref();
        rearDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameRear+stopPropertiesToString1_0(selectedStopPointDestination.destination),language);
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

        lcdDestination.destinationRef=selectedStopPointDestination.destination.ref();
        lcdDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameLcd+stopPropertiesToString1_0(selectedStopPointDestination.destination),language);

        lcdDisplayContent.destination=lcdDestination;
        lcdDisplayContent.viaPointList=viaPointListVdv;
        output<<lcdDisplayContent;

        break;
    }
    case DisplayContentInterior: //copy of LCD
    {
        Vdv301DisplayContent lcdDisplayContent;
        lcdDisplayContent.displayContentRef=displayContentClassString;
        lcdDisplayContent.displayContentType=displayContentClass;
        lcdDisplayContent.lineInformation=selectedLine;

        Vdv301Destination lcdDestination;

        lcdDestination.destinationRef=selectedStopPointDestination.destination.ref();
        lcdDestination.destinationNameList<<Vdv301InternationalText(selectedStopPointDestination.destination.NameLcd+stopPropertiesToString1_0(selectedStopPointDestination.destination),language);

        lcdDisplayContent.destination=lcdDestination;
        lcdDisplayContent.viaPointList=viaPointListVdv;
        output<<lcdDisplayContent;

        break;
    }
    default:
        qCDebug(XmlCommon1_0_newLog)<<"break";
        //   break;
    }

    return output;
}

QDomElement XmlCommon1_0_new::DisplayContentViaPointDestination1_0gen(QDomDocument  &xmlDocument, QString tagName, Vdv301DisplayContent displayContent)
{

    // DisplayContentRef" type="IBIS-IP.NMTOKEN" minOccurs="0"


    // LineInformation" type="LineInformationStructure"
    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");
    dLineInformation.appendChild(ref(xmlDocument,"LineRef",displayContent.lineInformation.lineRef));

    for(const Vdv301InternationalText &lineName : displayContent.lineInformation.lineNameList)
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


    // Destination" type="DestinationStructure"
    QDomElement dDestination=xmlDocument.createElement("Destination");


    QDomElement dDisplayContent=xmlDocument.createElement(tagName);
    dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef",Vdv301DisplayContent::displayContentClassEnumerationToQString( displayContent.displayContentType)));
    dDisplayContent.appendChild(dLineInformation);

    dDestination.appendChild(ref(xmlDocument,"DestinationRef", displayContent.destination.destinationRef));

    for(const Vdv301InternationalText &destinationName : displayContent.destination.destinationNameList)
    {
        QDomElement dDestinationName;
        dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",destinationName.text,destinationName.language);
        dDestination.appendChild(dDestinationName);
    }

    dDisplayContent.appendChild(dDestination);


    // ViaPoint" type="ViaPointStructure" minOccurs="0" maxOccurs="unbounded"
    for(const Vdv301ViaPoint &viaPoint : displayContent.viaPointList)
    {
        dDisplayContent.appendChild(ViaPoint1_0def(xmlDocument,viaPoint));
    }

    // AdditionalInformation" type="InternationalTextType" minOccurs="0" maxOccurs="unbounded"

    // DisplayPolicyGroup" minOccurs="0"

    return dDisplayContent;
}


// to be modified
QStringList XmlCommon1_0_new::FareZoneInformationStructure1_0new( QVector<FareZone> fareZoneList)
{
    QMap<QString, QStringList> fareZoneByType;
    QStringList output;

    for(const FareZone &selectedFareZone : fareZoneList)
    {
        fareZoneByType[selectedFareZone.system].append(selectedFareZone.name);
    }

    for(const QString &key : fareZoneByType.keys())
    {
        QString result="";
        result+=key;
        result+=":";
        result+=fareZoneByType[key].join("_");

        output<<result;
    }
    return output;
}



// to be modified
QString XmlCommon1_0_new::xxxProperty1_0(QString icon, QString text,bool value)
{
    QString output="";
    if(value)
    {
        output="<icon type=\""+icon+"\" >"+text+"</icon>";

    }
    return output;
}

// to be modified
QString XmlCommon1_0_new::lineToIcon(Line &line, QString subMode)
{
    QString output="";

    if(subMode=="metro")
    {
        output="<icon type=\"c_Underground"+line.lineName+"\">["+line.lineName+"]</icon>";
    }
    else
    {
        output=line.lineName;
    }


    return output;
}


// to be modified
Vdv301Line XmlCommon1_0_new::lineToVdv301Line1_0(Line &line, bool addStyle)
{
    Vdv301Line output;

    QString lineName="";

    if(addStyle)
    {
        lineName=colorDisplayRules.styleToString(line.lineName,colorDisplayRules.lineToStyle(line));
    }
    else
    {
        lineName=line.lineName;
    }

    output.lineNumber=line.lineNumber;

    output.lineNameList<<Vdv301InternationalText(lineName,defaultLanguage1_0);
    output.lineRef=line.ref();

    return output;
}



// to be modified
Vdv301Line XmlCommon1_0_new::lineToVdv301Line1_0(Line &line, QString subMode, bool addStyle)
{
    Vdv301Line output;

    QString lineName="";
    /*
    if(subMode=="metro")
    {
        lineName=lineToIcon(line,subMode);
    }
    else
    {
        if(addStyle)
        {
            lineName=colorDisplayRules.styleToString(line.lineName,colorDisplayRules.lineToStyle(line,subMode));
        }
        else
        {
            lineName=line.lineName;
        }
    }
*/
    if(addStyle)
    {
        if(subMode=="metro")
        {
            lineName=lineToIcon(line,subMode);
        }
        else
        {
            lineName=colorDisplayRules.styleToString(line.lineName,colorDisplayRules.lineToStyle(line,subMode));

        }
    }
    else
    {
        lineName=line.lineName;
    }

    output.lineNumber=line.lineNumber;
    output.lineNameList<<Vdv301InternationalText(lineName,defaultLanguage1_0);
    output.lineRef=line.ref();
    return output;
}


// to be modified
QString XmlCommon1_0_new::stopPropertiesToString1_0(StopPoint stopPoint)
{
    QString output="";
    if(addIconsInline)
    {
        output+=xxxProperty1_0("c_UndergroundA","[A]",stopPoint.transferMetroA);
        output+=xxxProperty1_0("c_UndergroundB","[B]",stopPoint.transferMetroB );
        output+=xxxProperty1_0("c_UndergroundC","[C]",stopPoint.transferMetroC);
        output+=xxxProperty1_0("c_UndergroundD","[D]",stopPoint.transferMetroD);
        output+=xxxProperty1_0("c_Train","~",stopPoint.transferTrain);
        output+=xxxProperty1_0("c_Ferry","Ĺ",stopPoint.transferFerry);
        output+=xxxProperty1_0("c_Air","\\",stopPoint.transferAirplane);
        output+=xxxProperty1_0("c_RequestStop","ŕ",stopPoint.onRequest&&(!stopPoint.neozn));
    }

    if(addIconsWuppertal)
    {
        if(stopPoint.transferTrain==true)
        {
            output+="$04";
        }

        if(stopPoint.transferMetroA||stopPoint.transferMetroB||stopPoint.transferMetroC||stopPoint.transferMetroD )
        {
            output+="$03";
        }
    }
    return output;
}


Vdv301StopPoint XmlCommon1_0_new::StopPoint1_0new( QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language,int currentStopIndex)
{
    qCDebug(XmlCommon1_0_newLog)<<Q_FUNC_INFO;
    Vdv301StopPoint output;
    if (stopPointDestinationList.isEmpty())
    {
        qCDebug(XmlCommon1_0_newLog)<<"stop list is empty";
        return output;
    }
    if (stopPointIterator>=stopPointDestinationList.length())
    {
        qCDebug(XmlCommon1_0_newLog)<<"stop index is out of range";
        return output;
    }

    StopPointDestination currentStopPoinDestination=stopPointDestinationList.at(stopPointIterator);

    // StopIndex" type="IBIS-IP.int"
    output.stopIndex=stopPointIterator+1;

    // StopRef" type="IBIS-IP.NMTOKEN" minOccurs="0"
    output.stopRef=currentStopPoinDestination.stopPoint.ref();

    // StopName" type="InternationalTextType" minOccurs="0" maxOccurs="unbounded"
    output.stopNameList<<Vdv301InternationalText(currentStopPoinDestination.stopPoint.NameLcd+stopPropertiesToString1_0(currentStopPoinDestination.stopPoint), language);

    // StopAlternativeName" type="InternationalTextType" minOccurs="0" maxOccurs="unbounded" not implemented

    // Platform" type="IBIS-IP.string" minOccurs="0"
    output.platform=currentStopPoinDestination.stopPoint.platformName;

    // DisplayContent" type="DisplayContentStructure" maxOccurs="unbounded"
    QVector<Vdv301DisplayContent> vdvDisplayContentList;

    vdvDisplayContentList<<DisplayContentViaPointDestination1_0new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,lcdClass); //changed order because older LCD screeens use first occurance of display content
    vdvDisplayContentList<<DisplayContentViaPointDestination1_0new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentFront);
    vdvDisplayContentList<<DisplayContentViaPointDestination1_0new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentSide);
    vdvDisplayContentList<<DisplayContentViaPointDestination1_0new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,DisplayContentRear);
    // vdvDisplayContentList<<DisplayContentViaPointDestination1_0new(stopPointDestinationList, language,stopPointIterator,currentStopIndex,lcdClass);
    output.displayContentList=vdvDisplayContentList;

    // StopAnnouncement" type="AnnouncementStructure" minOccurs="0" maxOccurs="unbounded" not implemented

    // ArrivalScheduled" type="IBIS-IP.dateTime" minOccurs="0"  not implemented
    // DepartureScheduled" type="IBIS-IP.dateTime" minOccurs="0"
    output.departureScheduled=qDateTimeQString(currentStopPoinDestination.stopPoint.departureToQDateTime());

    // RecordedArrivalTime" type="IBIS-IP.dateTime" minOccurs="0" not implemented
    // DistanceToNextStop" type="IBIS-IP.int" minOccurs="0" not implemented

    // Connection" type="ConnectionStructure" minOccurs="0" maxOccurs="unbounded"
    if(currentStopIndex==currentStopPoinDestination.stopPoint.StopIndex)
    {
        output.connectionList=connectionList;
    }

    // FareZone" type="IBIS-IP.NMTOKEN" minOccurs="0" maxOccurs="unbounded"
    for(const QString &dFareZone : FareZoneInformationStructure1_0new(currentStopPoinDestination.stopPoint.fareZoneList) )
    {
        output.fareZoneList<<dFareZone;
    }


    return output;
}

QDomElement XmlCommon1_0_new::StopPoint1_0gen(QDomDocument &xmlDocument, Vdv301StopPoint vdv301StopPoint)
{
    qCDebug(XmlCommon1_0_newLog)<<Q_FUNC_INFO;
    QDomElement dStopPoint=xmlDocument.createElement("StopPoint");

    // StopIndex" type="IBIS-IP.int"
    dStopPoint.appendChild(Value(xmlDocument,"StopIndex",QString::number(vdv301StopPoint.stopIndex)));

    // StopRef" type="IBIS-IP.NMTOKEN" minOccurs="0"
    dStopPoint.appendChild(ref(xmlDocument, "StopRef",vdv301StopPoint.stopRef));

    // StopName" type="InternationalTextType" minOccurs="0" maxOccurs="unbounded"
    for(const Vdv301InternationalText &stopName : vdv301StopPoint.stopNameList) {

        QDomElement dStopLcdName=internationalTextTypeToDom(xmlDocument,"StopName",stopName);

        dStopPoint.appendChild(dStopLcdName);
    }

    // StopAlternativeName" type="InternationalTextType" minOccurs="0" maxOccurs="unbounded" not implemented

    // Platform" type="IBIS-IP.string" minOccurs="0"
    if(!vdv301StopPoint.platform.isEmpty())
    {
        dStopPoint.appendChild(Value(xmlDocument,"Platform",vdv301StopPoint.platform));
    }

    // DisplayContent" type="DisplayContentStructure" maxOccurs="unbounded"


    for(const Vdv301DisplayContent &displayContent : vdv301StopPoint.displayContentList)
    {
        dStopPoint.appendChild(DisplayContentViaPointDestination1_0gen(xmlDocument,"DisplayContent", displayContent));
    }


    // StopAnnouncement" type="AnnouncementStructure" minOccurs="0" maxOccurs="unbounded" not implemented

    // ArrivalScheduled" type="IBIS-IP.dateTime" minOccurs="0"  not implemented
    if(!vdv301StopPoint.arrivalScheduled.isEmpty())
    {
        QDomElement dArrivalScheduled=Value(xmlDocument,"ArrivalScheduled",vdv301StopPoint.arrivalScheduled);
        dStopPoint.appendChild(dArrivalScheduled);
    }


    // DepartureScheduled" type="IBIS-IP.dateTime" minOccurs="0"
    if(!vdv301StopPoint.departureScheduled.isEmpty())
    {
        QDomElement dDepartureScheduled=Value(xmlDocument,"DepartureScheduled",vdv301StopPoint.departureScheduled);
        dStopPoint.appendChild(dDepartureScheduled);
    }



    // RecordedArrivalTime" type="IBIS-IP.dateTime" minOccurs="0" not implemented

    // DistanceToNextStop" type="IBIS-IP.int" minOccurs="0" not implemented

    // Connection" type="ConnectionStructure" minOccurs="0" maxOccurs="unbounded"
    for(const Vdv301Connection &connection : vdv301StopPoint.connectionList)
    {
        dStopPoint.appendChild(Connection1_0gen(xmlDocument,connection));
    }

    // FareZone" type="IBIS-IP.NMTOKEN" minOccurs="0" maxOccurs="unbounded"
    for(const QString &fareZone : vdv301StopPoint.fareZoneList )
    {
        dStopPoint.appendChild(Value(xmlDocument,"FareZone",fareZone));
    }

    return dStopPoint;


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
}

QVector<Vdv301StopPoint> XmlCommon1_0_new::StopSequence1_0new(QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList)
{

    QVector<Vdv301StopPoint> output;

    // StopPoint" type="StopInformationStructure" minOccurs="2" maxOccurs="unbounded"
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        output<<StopPoint1_0new(stopPointDestinationList,i,connectionList,language,currentStopIndex);
    }
    return output;
}

QDomElement XmlCommon1_0_new::StopSequence1_0gen(QDomDocument &xmlDocument,QVector<Vdv301StopPoint> stopPointDestinationList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");

    // StopPoint" type="StopInformationStructure" minOccurs="2" maxOccurs="unbounded"
    for(const Vdv301StopPoint &stopPointDestination : stopPointDestinationList)
    {

        dStopSequence.appendChild(StopPoint1_0gen(xmlDocument,stopPointDestination));
    }
    return dStopSequence;
}


Vdv301ViaPoint XmlCommon1_0_new::stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language)
{
    Vdv301ViaPoint output;
    output.viaPointRef=stopPoint.ref();
    output.placeNameList<<Vdv301InternationalText(stopPoint.NameLcd+stopPropertiesToString1_0(stopPoint),language);

    return output;
}


Vdv301Trip XmlCommon1_0_new::TripInformation1_0new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
{

    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage1_0;
    Vdv301Trip vdv301trip;
    Trip thisTrip;
    if (isInRange(tripIndex,tripList.count(),Q_FUNC_INFO))
    {
        thisTrip=tripList.at(tripIndex);
    }
    else
    {
        return vdv301trip;
    }

    QString tripRef=thisTrip.ref();
    QVector<StopPointDestination> stopPointDestinationList=thisTrip.globalStopPointDestinationList;


    //TripRef" type="IBIS-IP.NMTOKEN"
    vdv301trip.tripRef=tripRef;

    //StopSequence" type="StopSequenceStructure">
    vdv301trip.stopPointList<<StopSequence1_0new(stopPointDestinationList,language,currentStopIndex,connectionList);


    //LocationState" type="LocationStateEnumeration" minOccurs="0"
    vdv301trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(Vdv301Enumerations::LocationStateEnumerationToQString(vehicleState.locationState));


    //TimetableDelay" type="IBIS-IP.int" minOccurs="0"
    //vdv301trip.timetableDelay

    //AdditionalTextMessage" type="IBIS-IP.string" minOccurs="0"
    //vdv301trip.additionalTextMessage=

    //AdditionalAnnouncement" type="AdditionalAnnouncementStructure" minOccurs="0" maxOccurs="unbounded"


    //  vdv301trip.runNumber=vehicleRunToRunNumber(vehicleState.currentVehicleRun);


    if (followingTrip==false)
    {

        /*
        QString specialAnnouncement=stopPointDestinationList.at(vehicleState.currentStopIndex0).stopPoint.additionalTextMessage;
        qCDebug(XmlCommon1_0_newLog)<<"special announcement="<<specialAnnouncement;

        if(vehicleState.isSpecialAnnoucementUsed)
        {
            Vdv301InternationalText additionalTextMessage(vehicleState.currentSpecialAnnoucement.text,language);
            vdv301trip.additionalTextMessageList<<additionalTextMessage;

            //   dTripInformation.appendChild(AdditionalTextMessage2_3(xmlDocument,  vehicleState.currentSpecialAnnoucement.text));
        }
        else if (specialAnnouncement!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
*/

        StopPointDestination currentStopPointDestination;
        QString specialAnnouncement="";

        if(vehicleState.currentStopIndex0<stopPointDestinationList.count()&&(vehicleState.currentStopIndex0>=0))
        {
            specialAnnouncement=currentStopPointDestination.stopPoint.additionalTextMessage;


            specialAnnouncement=stopPointDestinationList.at(vehicleState.currentStopIndex0).stopPoint.additionalTextMessage;
            qCDebug(XmlCommon1_0_newLog)<<"special announcement="<<specialAnnouncement;

            if(vehicleState.isSpecialAnnoucementUsed)
            {
                /*
            Vdv301AdditionalAnnouncement2_3CZ1_0 additionalAnnouncement;
            additionalAnnouncement.announcementTextList<<Vdv301InternationalText(vehicleState.currentSpecialAnnoucement.text,language);
            vdv301trip.additionalAnnouncementList<<additionalAnnouncement;
*/
                AdditionalAnnoucement currentAnnouncement=vehicleState.currentSpecialAnnoucement;

                vdv301trip.additionalTextMessageList<<Vdv301InternationalText(currentAnnouncement.text,language);

            }
        }
        else if (specialAnnouncement!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
    }
    else
    {
        qCDebug(XmlCommon1_0_newLog)<<"followingTrip==true";
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


QDomElement XmlCommon1_0_new::TripInformation1_0gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip)
{
    //TripRef" type="IBIS-IP.NMTOKEN"
    QString tripRef=trip.tripRef;

    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //StopSequence" type="StopSequenceStructure">
    dTripInformation.appendChild(StopSequence1_0gen(xmlDocument,trip.stopPointList));

    if (followingTrip==false)
    {
        //LocationState" type="LocationStateEnumeration" minOccurs="0"
        QDomElement dLocationState=xmlDocument.createElement("LocationState");
        dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString(trip.locationState)));
        dTripInformation.appendChild(dLocationState);

        if(!trip.additionalTextMessageList.isEmpty())
        {

            qCDebug(XmlCommon1_0_newLog)<<"special announcement="<<trip.additionalTextMessageList.first().text;
            dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage",trip.additionalTextMessageList.first()));
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
        qCDebug(XmlCommon1_0_newLog)<<"followingTrip==true";
    }

    //fareZone change, commented out to comply with VDV CIS 2.3
    /*
    if((currentStopIndex+1)<stopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
    }
    */



    //TimetableDelay" type="IBIS-IP.int" minOccurs="0" not implemented


    //AdditionalTextMessage" type="IBIS-IP.string" minOccurs="0" not implemented


    //AdditionalAnnouncement" type="AdditionalAnnouncementStructure" minOccurs="0" maxOccurs="unbounded" not implemented


    return dTripInformation;
}

QDomElement XmlCommon1_0_new::ViaPoint1_0def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");

    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",viaPoint.viaPointRef));


    for(const Vdv301InternationalText &viaPointName : viaPoint.placeNameList )
    {
        QDomElement dPlaceLcdName=internationalTextTypeToDom(xmlDocument,"PlaceName",viaPointName.text ,viaPointName.language);
        dViaPoint.appendChild(dPlaceLcdName);
    }


    return dViaPoint;
}


QString XmlCommon1_0_new::vehicleRunToRunNumber(VehicleRun vehicleRun) //unused
{
    //   return QString::number(vehicleRun.rootLine.c)+"_"+QString::number(vehicleRun.order);
    return QString::number(vehicleRun.rootLine.c)+QString::number(vehicleRun.order).rightJustified(3,'0');
}