#include "xmlcommon.h"




XmlCommon::XmlCommon()
{

}

QDomElement XmlCommon::AdditionalTextMessage1_0(QString messageContent,bool isScrolling)
{
    QDomDocument xmlDocument;

    if (isScrolling)
    {
        messageContent="$LS$"+messageContent;
    }
    QDomElement TextMessage=Value(xmlDocument,"AdditionalTextMessage",messageContent);

    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}



QDomElement XmlCommon::AdditionalTextMessage2_2CZ1_0(QDomDocument  &xmlDocument,QString messageContent)
{

    QDomElement TextMessage=xmlDocument.createElement("AdditionalTextMessage");
    QDomElement value=internationalTextType(xmlDocument,"AdditionalTextMessageText",messageContent,defaultLanguage2_2CZ1_0);
    TextMessage.appendChild(value);
    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}


QDomElement XmlCommon::AdditionalTextMessage2_2CZ1_0(QDomDocument  &xmlDocument,QString type, QString headline, QString text)
{

    QDomElement TextMessage=xmlDocument.createElement("AdditionalTextMessage");

    QDomElement TextMessageType=internationalTextType(xmlDocument,"AdditionalTextMessageType",type,defaultLanguage2_2CZ1_0);
    QDomElement TextMessageHeadline=internationalTextType(xmlDocument,"AdditionalTextMessageHeadline",headline,defaultLanguage2_2CZ1_0);
    QDomElement TextMessageText=internationalTextType(xmlDocument,"AdditionalTextMessageText",text,defaultLanguage2_2CZ1_0);
    TextMessage.appendChild(TextMessageType);
    TextMessage.appendChild(TextMessageHeadline);
    TextMessage.appendChild(TextMessageText);

    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}

QDomElement XmlCommon::AdditionalTextMessage2_3(QDomDocument &xmlDocument, QString messageContent)
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


QString XmlCommon::createTimestamp()
{
    qDebug()<<Q_FUNC_INFO;
    QDateTime timeStamp = QDateTime::currentDateTime();
    QString formattedTimeStamp= timeStamp.toString("yyyy-MM-ddThh:mm:ss");
    return formattedTimeStamp;
}


QVector<QDomElement> XmlCommon::Connections1_0(QDomDocument  &xmlDocument, QVector<Connection> connectionList)
{

    qDebug()<<Q_FUNC_INFO;

    QString language ="cs";
    QVector<QDomElement> output;

    connectionList=Connection::orderConnectionsByExpectedDeparture(connectionList);

    QString wuppertalMeanOfTransport="";
    QString destinationRef="1";
    /*
    for (int i=0;i<connectionMpvList.count();i++)
    {
*/
    foreach(Connection selectedConnection, connectionList)
    {
        //selectedConnection.lin=selectedConnection.lin.number(10);
        QDomElement dConnection=xmlDocument.createElement("Connection");
        xmlDocument.appendChild(dConnection);

        if(selectedConnection.line.lineNumber=="")
        {
            selectedConnection.line.lineNumber=QString::number(selectedConnection.line.lc);
        }
        if(selectedConnection.line.lineName=="")
        {
            selectedConnection.line.lineName=QString::number(selectedConnection.line.c);
        }


        QDomElement dConnectionMode = xmlDocument.createElement("TransportMode");
        wuppertalMeanOfTransport="";
        // Bus, RegBus,Metro, NTram, Tram, NBus, Os, EC, R, Ex

        if (selectedConnection.subMode.contains("Bus"))
        {
            wuppertalMeanOfTransport="$01"; //Bus

        }
        if(selectedConnection.subMode.contains("metro"))
        {
            wuppertalMeanOfTransport="$03"; //metro

        }
        if(selectedConnection.subMode.contains("Tram"))
        {
            wuppertalMeanOfTransport="$02"; //tram

        }
        if(selectedConnection.subMode.contains("Rail"))
        {
            wuppertalMeanOfTransport="$04"; //train

        }

        dConnection.appendChild(ref(xmlDocument,"StopRef","XX"));
        dConnection.appendChild(ref(xmlDocument,"ConnectionRef","yy"));

        dConnection.appendChild(xmlDocument.createElement("ConnectionType")).appendChild(xmlDocument.createTextNode("Interchange"));

        QDomElement dDisplayContent=xmlDocument.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);
        dDisplayContent.appendChild(Value(xmlDocument,"DisplayContentRef","2244"));
        QDomElement dLineInformation=xmlDocument.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
        dLineInformation.appendChild(ref(xmlDocument,"LineRef",selectedConnection.line.lineName));

        QDomElement dLineName=internationalTextType(xmlDocument,"LineName",selectedConnection.line.lineName,language);
        dLineInformation.appendChild(dLineName);

        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",selectedConnection.line.lineNumber);
        dLineInformation.appendChild(dLineNumber);

        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);

        QDomElement dDestinationRef=Value(xmlDocument,"DestinationRef",destinationRef);

        dDestination.appendChild(dDestinationRef);

        QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedConnection.destinationName,language);
        dDestination.appendChild(dDestinationName);

        dConnection.appendChild(Value(xmlDocument,"Platform",selectedConnection.platform));

        //mean of transport
        dConnectionMode.appendChild(this->ref(xmlDocument,"VehicleTypeRef","3"));
        dConnectionMode.appendChild(this->internationalTextType(xmlDocument,"Name",wuppertalMeanOfTransport,defaultLanguage1_0));
        dConnection.appendChild(dConnectionMode);

        QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepatureTime", selectedConnection.expectedDepartureTimeQString());
        dConnection.appendChild(dExpectedDepartureTime);
        output.push_back(dConnection);
        // qDebug()<<"connection "<<vdv301connection.line.lineName<<" "<<vdv301connection.destinationName<<" has delay"<<selectedConnection.zpoz<<" cas:"<<selectedConnection.odjReal;

    }
    return output;
}


QVector<QDomElement> XmlCommon::Connections2_2CZ1_0(QDomDocument  &xmlDocument, QVector<Connection> connectionList)
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

        QDomElement dLineName=internationalTextType(xmlDocument,"LineName",selectedConnection.line.lineName,language);
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


        QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedConnection.destinationName,language);
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


QVector<QDomElement> XmlCommon::Connections2_3(QDomDocument  &xmlDocument, QVector<Connection> connectionList)
{
    qDebug()<<Q_FUNC_INFO;

    QString language ="cs";
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


        QDomElement dLineName=internationalTextType(xmlDocument,"LineName",lineName,language);
        dLineInformation.appendChild(dLineName);

        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",selectedConnection.line.lineNumber);
        dLineInformation.appendChild(dLineNumber);

        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);



        QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedConnection.destinationName,language);
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



QDomElement XmlCommon::Connection2_3gen(QDomDocument  &xmlDocument, Vdv301Connection connection)
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
            QDomElement dLineName=internationalTextType(xmlDocument,"LineName",lineName.text,lineName.language);
            dLineInformation.appendChild(dLineName);
        }



        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",displayContent.lineInformation.lineNumber);
        dLineInformation.appendChild(dLineNumber);



        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);

        foreach(Vdv301InternationalText destinationName, displayContent.destination.destinationNameList)
        {
            QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",destinationName.text, destinationName.language);
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


QDomElement XmlCommon::DisplayContent1_0(QString tagName, QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language,  int stopPointIterator, int currentStopIndex)
{
    StopPointDestination selectedStopPointDestination=stopPointDestinationList.at(stopPointIterator);
    QString lineNumber=selectedStopPointDestination.line.lineNumber;
    QString lineName=selectedStopPointDestination.line.lineName;
    bool appendNextStopToViaPoints=true;
    QDomElement dDisplayContent=xmlDocument.createElement(tagName);

    dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","1234"));

    //LINKA
    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");
    dLineInformation.appendChild(ref(xmlDocument,"LineRef",lineNumber));
    dDisplayContent.appendChild(dLineInformation);

    QDomElement dLineName=internationalTextType(xmlDocument,"LineName",lineName,language);


    dLineInformation.appendChild(dLineName);
    QDomElement dLineNumber=Value(xmlDocument,"LineNumber",lineNumber);
    dLineInformation.appendChild(dLineNumber);

    //CIL
    QDomElement dDestination=xmlDocument.createElement("Destination");
    // QString destinationName=selectedStopPointDestination.destination.NameLcd;
    QString destinationRef=QString::number(stopPointDestinationList.at(stopPointIterator).destination.idCis);
    dDestination.appendChild(ref(xmlDocument,"DestinationRef",destinationRef));
    bool lcdOnly=true;
    if(lcdOnly)
    {
        QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameLcd,language);
        dDestination.appendChild(dDestinationName);
    }
    else
    {
        if (selectedStopPointDestination.destination.NameFront2=="")
        {
            if (selectedStopPointDestination.destination.NameFront.contains("|"))
            {
                QStringList frontDestinations=selectedStopPointDestination.destination.NameFront.split("|");



                foreach (QString selectedDestination, frontDestinations)
                {
                    QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedDestination,language);
                    dDestination.appendChild(dDestinationName);
                }

            }
            else
            {
                QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront,language);
                dDestination.appendChild(dDestinationName);
            }
        }
        else
        {
            QDomElement dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront,language);
            dDestination.appendChild(dDestinationName);
            QDomElement dDestinationName2=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront2,language);
            dDestination.appendChild(dDestinationName2);
        }
    }


    dDisplayContent.appendChild(dDestination);
    if ((appendNextStopToViaPoints==true)&&((currentStopIndex+1)<stopPointDestinationList.count()))
    {
        StopPointDestination nextStopPoint=stopPointDestinationList.at(currentStopIndex+1);
        if (nextStopPoint.stopPoint.isViapoint==0)
        {
            dDisplayContent.appendChild(ViaPoint1_0(xmlDocument,nextStopPoint.stopPoint,language));
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == 1)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            dDisplayContent.appendChild(ViaPoint1_0(xmlDocument,viaPoint.stopPoint,language));

        }
    }

    return dDisplayContent;
}

QDomElement XmlCommon::DisplayContent2_2CZ1_0(QDomDocument  &xmlDocument,QString tagName,QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex)
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


        dLineName=internationalTextType(xmlDocument,"LineName",  lineName ,language);
        // dLineName.appendChild(rawInsert(lineName));


    }
    else
    {
        dLineName=internationalTextType(xmlDocument,"LineName",lineName,language);
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
                QDomElement dDestinationFrontName=internationalTextType(xmlDocument,"DestinationFrontName",selectedDestinationName,language);
                dDestination.appendChild(dDestinationFrontName);
            }

        }
        else
        {
            QDomElement dDestinationFrontName=internationalTextType(xmlDocument,"DestinationFrontName",selectedStopPointDestination.destination.NameFront,language);
            dDestination.appendChild(dDestinationFrontName);
        }
    }
    else
    {
        QDomElement dDestinationFrontName=internationalTextType(xmlDocument,"DestinationFrontName",selectedStopPointDestination.destination.NameFront,language);
        dDestination.appendChild(dDestinationFrontName);
        QDomElement dDestinationFrontName2=internationalTextType(xmlDocument,"DestinationFrontName",selectedStopPointDestination.destination.NameFront2,language);
        dDestination.appendChild(dDestinationFrontName2);
    }

    QDomElement dDestinationSideName=internationalTextType(xmlDocument,"DestinationSideName",selectedStopPointDestination.destination.NameSide,language);
    dDestination.appendChild(dDestinationSideName);
    QDomElement dDestinationRearName=internationalTextType(xmlDocument,"DestinationRearName",selectedStopPointDestination.destination.NameRear,language);
    dDestination.appendChild(dDestinationRearName);
    QDomElement dDestinationLcdName=internationalTextType(xmlDocument,"DestinationLcdName",selectedStopPointDestination.destination.NameLcd,language);
    dDestination.appendChild(dDestinationLcdName);
    QDomElement dDestinationInnerName=internationalTextType(xmlDocument,"DestinationInnerName",selectedStopPointDestination.destination.NameInner,language);
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

//work in progress


QDomElement XmlCommon::DisplayContent2_3(QDomDocument  &xmlDocument, QString tagName,QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
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

    QDomElement dLineName=internationalTextType(xmlDocument,"LineName",lineName,language);

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

        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        if(!selectedStopPointDestination.destination.NameFront2.isEmpty())
        {
            dDestinationName2=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront2,language);
            dDestination.appendChild(dDestinationName2);
        }
        dDisplayContent.appendChild(dDestination);
        break;
    case DisplayContentSide:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Side"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        dDisplayContent.appendChild(viaPointObsah);
        break;
    case DisplayContentRear:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Rear"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameRear+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        dDisplayContent.appendChild(dDestination);
        break;
    case DisplayContentLcd:
        dDisplayContent.appendChild(ref(xmlDocument,"DisplayContentRef","Lcd"));
        dDisplayContent.appendChild(dLineInformation);
        dDestination.appendChild(ref(xmlDocument,"DestinationRef",QString::number(selectedStopPointDestination.destination.idCis)));
        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameLcd+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
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



QVector<QDomElement> XmlCommon::DisplayContentViaPointDestination2_3(QDomDocument  &xmlDocument, QString tagName,QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
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


    QDomElement dLineName=internationalTextType(xmlDocument,"LineName",lineName,language);
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

        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
        dDestination.appendChild(dDestinationName);
        if(!selectedStopPointDestination.destination.NameFront2.isEmpty())
        {
            dDestinationName2=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront2,language);
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
            dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
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
                dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameSide+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
                dDestinationCopy.appendChild(dDestinationName);
                dDestinationName=internationalTextType(xmlDocument,"DestinationName",viaPoint.stopPoint.NameSide+stopPropertiesToString2_3(viaPoint.stopPoint),language);
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
        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameRear+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
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
        dDestinationName=internationalTextType(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameLcd+stopPropertiesToString2_3(selectedStopPointDestination.destination),language);
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

QDomElement XmlCommon::DisplayContentViaPointDestination2_3gen(QDomDocument  &xmlDocument, QString tagName, Vdv301DisplayContent displayContent)
{

    QDomElement viaPointObsah;


    QDomElement dLineInformation=xmlDocument.createElement("LineInformation");

    dLineInformation.appendChild(ref(xmlDocument,"LineRef",displayContent.lineInformation.lineRef));


    foreach(Vdv301InternationalText lineName, displayContent.lineInformation.lineNameList)
    {
        QDomElement dLineName=internationalTextType(xmlDocument,"LineName",lineName.text,lineName.language);

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
        dDestinationName=internationalTextType(xmlDocument,"DestinationName",destinationName.text,destinationName.language);
        dDestination.appendChild(dDestinationName);
    }

    dDisplayContent.appendChild(dDestination);



    foreach(Vdv301ViaPoint viaPoint, displayContent.viaPointList)
    {
        dDisplayContent.appendChild(ViaPoint2_3def(xmlDocument,viaPoint));
    }
    return dDisplayContent;
}

QVector<Vdv301DisplayContent> XmlCommon::DisplayContentViaPointDestination2_3new(QVector<StopPointDestination> stopPointDestinationList, QString language,int stopPointIterator,int currentStopIndex, DisplayContentClass displayContentClass)
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

Vdv301Line XmlCommon::lineToVdv301Line2_3(Line &line)
{
    Vdv301Line output;

    output.lineNumber=line.lineNumber;

    output.lineNameList<<Vdv301InternationalText(line.lineName,defaultLanguage2_3);
    output.lineRef=QString::number(line.c);

    return output;
}

Vdv301ViaPoint XmlCommon::stopPointDestinationToVdv301ViaPoint(StopPoint stopPoint, QString &language)
{
    Vdv301ViaPoint output;
    output.viaPointRef=QString::number(stopPoint.idCis);
    output.placeNameList<<Vdv301InternationalText(stopPoint.NameLcd+stopPropertiesToString2_3(stopPoint),language);

    return output;
}


QDomElement XmlCommon::DoorOpenState(QDomDocument &xmlDocument,QString content)
{
    QDomElement dRouteDeviation = xmlDocument.createElement("DoorOpenState");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(content));
    return dRouteDeviation;
}


QDomElement XmlCommon::FareZoneChange2_2CZ1_0(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneListFrom,QVector<FareZone> fareZoneListTo,QString language)
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

/////////////////////////////////////////////
QDomElement XmlCommon::FareZone1_0(QDomDocument  &xmlDocument, QString shortName)
{

    QDomElement pasmo=ref(xmlDocument,"FareZone",shortName);

    return pasmo;
}

QDomElement XmlCommon::FareZone2_2CZ1_0(QDomDocument  &xmlDocument, QString shortName,QString longName, QString type, QString language)
{

    QDomElement dFareZone=xmlDocument.createElement("FareZone");
    QDomElement zoneType=xmlDocument.createElement("FareZoneType");
    QDomElement zoneTypeName=internationalTextType(xmlDocument,"FareZoneTypeName",type,language);
    zoneType.appendChild(zoneTypeName);
    dFareZone.appendChild(zoneType);

    QDomElement zoneLongName=internationalTextType(xmlDocument,"FareZoneLongName",longName,language);
    QDomElement zoneShortName=internationalTextType(xmlDocument,"FareZoneShortName",shortName,language);

    dFareZone.appendChild(zoneLongName);
    dFareZone.appendChild(zoneShortName);

    return dFareZone;
}

QDomElement XmlCommon::FareZone2_3(QDomDocument  &xmlDocument, QString shortName)
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

QVector<QDomElement> XmlCommon::FareZoneInformationStructure1_0(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneList)
{
    QVector<QDomElement> dFareZoneList;

    foreach( FareZone selectedFareZone, fareZoneList)
    {
        QDomElement dFareZone=FareZone1_0(xmlDocument,selectedFareZone.name );
        dFareZoneList.append(dFareZone);
    }


    return dFareZoneList;
}
QVector<QDomElement> XmlCommon::FareZoneInformationStructure2_2CZ1_0(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneList,QString language)
{
    QVector<QDomElement> dFareZoneList;

    foreach( FareZone selectedFareZone, fareZoneList)
    {
        QDomElement dFareZone=FareZone2_2CZ1_0(xmlDocument,selectedFareZone.name,selectedFareZone.name,selectedFareZone.system,language );
        dFareZoneList.append(dFareZone);
    }

    return dFareZoneList;
}

QVector<QDomElement> XmlCommon::FareZoneInformationStructure2_3(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneList,QString language)
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

QStringList XmlCommon::FareZoneInformationStructure2_3new( QVector<FareZone> fareZoneList)
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

QVector<QDomElement> XmlCommon::lineToLineProperties(QDomDocument xmlDocument, Line line)
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


QDomElement XmlCommon::MyOwnVehicleMode(QDomDocument &xmlDocument, QString subMode, QString mode)
{
    QDomElement output=xmlDocument.createElement("MyOwnVehicleMode");
    QDomElement dPtMainMode=xmlDocument.createElement("PtMainMode");
    dPtMainMode.appendChild(xmlDocument.createTextNode(subMode));
    output.appendChild(dPtMainMode);
    QDomElement dSubMode=xmlDocument.createElement(subMode);
    dSubMode.appendChild(xmlDocument.createTextNode(mode));
    output.appendChild(dSubMode);
    return output;
}


QDomElement XmlCommon::MyOwnVehicleMode2_2CZ1_0(QDomDocument  &xmlDocument, QString mainMode, QString subMode)
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
///////////////////////////////

QDomElement XmlCommon::rawInsert(QString input)
{
    QDomElement output;
    QDomDocument specialQDomDocument; //new qdom document due to different settings
    QDomImplementation impl;
    impl.setInvalidDataPolicy( QDomImplementation::AcceptInvalidChars );
    input="&#12;";
    //vstup=vstup.toHtmlEscaped();
    QString rawElement="<?xml version=\"1.0\" encoding=\"utf-8\" ?><wrapper>"+input+"</wrapper>";
    specialQDomDocument.setContent(rawElement,false);
    output=specialQDomDocument.firstChildElement();

    return output;
}


QDomElement XmlCommon::RouteDeviation(QDomDocument &xmlDocument,QString content)
{
    QDomElement dRouteDeviation = xmlDocument.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(content));
    return dRouteDeviation;
}


QDomElement XmlCommon::TripInformation1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int indexSpoje)
{
    int currentStopIndex= vehicleState.currentStopIndex0;
    QString language=defaultLanguage1_0;
    QString tripRef="0";
    QString specialAnnouncement="";
    QVector<StopPointDestination> stopPointDestinationList;

    if(isInRange(indexSpoje,tripList.count(),Q_FUNC_INFO))
    {
        tripRef=QString::number(tripList.at(indexSpoje).idRopid);
        stopPointDestinationList=tripList.at(indexSpoje).globalStopPointDestinationList;
        specialAnnouncement=stopPointDestinationList.at(vehicleState.currentStopIndex0).stopPoint.additionalTextMessage;
        qDebug()<<"special announcement="<<specialAnnouncement;
    }
    else
    {
        StopPointDestination dummyStopPointDestination1;
        dummyStopPointDestination1.stopPoint.StopIndex=0;
        dummyStopPointDestination1.stopPoint.StopName="";
        dummyStopPointDestination1.line.lineNumber="0";
        dummyStopPointDestination1.destination.idCis=0;

        StopPointDestination dummyStopPointDestination2;
        dummyStopPointDestination2.stopPoint.StopIndex=0;
        dummyStopPointDestination2.stopPoint.StopName="";
        dummyStopPointDestination2.line.lineNumber="0";
        dummyStopPointDestination2.destination.idCis=0;

        stopPointDestinationList<<dummyStopPointDestination1;
        stopPointDestinationList<<dummyStopPointDestination2;

    }


    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence1_0(xmlDocument,stopPointDestinationList,language,currentStopIndex,connectionList,vehicleState));


    QDomElement dLocationState=xmlDocument.createElement("LocationState");
    dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString(vehicleState.locationState)));
    dTripInformation.appendChild(dLocationState);


    if(vehicleState.isSpecialAnnoucementUsed)
    {
        dTripInformation.appendChild(AdditionalTextMessage1_0(vehicleState.currentSpecialAnnoucement.text,false));
    }
    else if (specialAnnouncement!="")
    {
        dTripInformation.appendChild(AdditionalTextMessage1_0(specialAnnouncement,true));
    }

    else
    {
        qDebug()<<"specialAnnouncement is empty";
    }

    return dTripInformation;
}

QDomElement XmlCommon::TripInformation2_2CZ1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionsList, VehicleState vehicleState, int tripIndex, bool followingTrip)
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



QDomElement XmlCommon::TripInformation2_3(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
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
            dTripInformation.appendChild( internationalTextType(xmlDocument,"AdditionalTextMessage", vehicleState.currentSpecialAnnoucement.text,language));
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

Vdv301Trip XmlCommon::TripInformation2_3new(QVector<Trip> tripList, QVector<Vdv301Connection> connectionList, VehicleState vehicleState, int tripIndex, bool followingTrip)
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



QDomElement XmlCommon::TripInformation2_3gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip)
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
            dTripInformation.appendChild( internationalTextType(xmlDocument,"AdditionalTextMessage",specialAnnouncement,trip.additionalTextMessage.language));
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

QString XmlCommon::vehicleRunToRunNumber(VehicleRun vehicleRun)
{
    //   return QString::number(vehicleRun.rootLine.c)+"_"+QString::number(vehicleRun.order);
    return QString::number(vehicleRun.rootLine.c)+QString::number(vehicleRun.order).rightJustified(3,'0');
}

QDomElement XmlCommon::StopSequence1_0(QDomDocument &xmlDocument,QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Connection> connectionList,VehicleState vehicleState)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {

        dStopSequence.appendChild(StopPoint1_0(xmlDocument,stopPointDestinationList,i,connectionList,language,currentStopIndex,vehicleState));

    }
    return dStopSequence;
}

QDomElement XmlCommon::StopSequence2_2CZ1_0(QDomDocument &xmlDocument,QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Connection> connectionList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        dStopSequence.appendChild(StopPoint2_2CZ1_0(xmlDocument,stopPointDestinationList,i,connectionList,language,currentStopIndex));
    }
    return dStopSequence;
}


QDomElement XmlCommon::StopSequence2_3(QDomDocument &xmlDocument,QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Connection> connectionList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        dStopSequence.appendChild(StopPoint2_3(xmlDocument,stopPointDestinationList,i,connectionList,language,currentStopIndex));
    }
    return dStopSequence;
}

QVector<Vdv301StopPoint> XmlCommon::StopSequence2_3new(QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Vdv301Connection> connectionList)
{

    QVector<Vdv301StopPoint> output;

    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {
        output<<StopPoint2_3new(stopPointDestinationList,i,connectionList,language,currentStopIndex);
    }
    return output;
}

QDomElement XmlCommon::StopSequence2_3gen(QDomDocument &xmlDocument,QVector<Vdv301StopPoint> stopPointDestinationList)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");


    foreach(Vdv301StopPoint stopPointDestination, stopPointDestinationList)
    {

        dStopSequence.appendChild(StopPoint2_3gen(xmlDocument,stopPointDestination));
    }
    return dStopSequence;
}


QDomElement XmlCommon::StopPoint1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Connection> connectionList, QString language,int currentStopIndex,VehicleState vehicleState)
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
    QString cStopName= selectedStopPointDestination.stopPoint.NameLcd;

    QDomElement dStopIndex=Value(xmlDocument,"StopIndex",cCurrentStopIndex);

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref(xmlDocument,"StopRef",QString::number(selectedStopPointDestination.stopPoint.idCis)));

    if(selectedStopPointDestination.stopPoint.transferTrain==true)
    {
        cStopName=cStopName+"$04";
    }

    if(selectedStopPointDestination.stopPoint.transferMetroA||selectedStopPointDestination.stopPoint.transferMetroB||selectedStopPointDestination.stopPoint.transferMetroC||selectedStopPointDestination.stopPoint.transferMetroD )
    {
        cStopName=cStopName+"$03";
    }
    QDomElement dStopName=internationalTextType(xmlDocument,"StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);



    QDomElement dDisplayContent=DisplayContent1_0("DisplayContent",xmlDocument,stopPointDestinationList,language, stopPointIterator,currentStopIndex);
    dStopPoint.appendChild(dDisplayContent);


    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {

        foreach(QDomElement dConnection,Connections1_0(xmlDocument,connectionList))
        {
            dStopPoint.appendChild(dConnection );
        }
    }

    QVector<QDomElement> dFareZoneList=FareZoneInformationStructure1_0(xmlDocument,selectedStopPointDestination.stopPoint.fareZoneList);
    for (int i=0;i<dFareZoneList.length();i++)
    {
        dStopPoint.appendChild(dFareZoneList.at(i));
    }

    return dStopPoint;
}


QDomElement XmlCommon::StopPoint2_2CZ1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Connection> connectionList, QString language,int currentStopIndex)
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


    QDomElement dStopName=internationalTextType(xmlDocument,"StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);

    QDomElement dStopFrontName=internationalTextType(xmlDocument,"StopFrontName",selectedStopPointDestination.stopPoint.NameFront,language);
    dStopPoint.appendChild(dStopFrontName);
    QDomElement dStopSideName=internationalTextType(xmlDocument,"StopSideName",selectedStopPointDestination.stopPoint.NameSide,language);
    dStopPoint.appendChild(dStopSideName);
    QDomElement dStopRearName=internationalTextType(xmlDocument,"StopRearName",selectedStopPointDestination.stopPoint.NameRear,language);
    dStopPoint.appendChild(dStopRearName);
    QDomElement dStopLcdName=internationalTextType(xmlDocument,"StopLcdName",selectedStopPointDestination.stopPoint.NameLcd,language);
    dStopPoint.appendChild(dStopLcdName);
    QDomElement dStopInnerName=internationalTextType(xmlDocument,"StopInnerName",selectedStopPointDestination.stopPoint.NameInner,language);
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



QDomElement XmlCommon::StopPoint2_3(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Connection> connectionList, QString language,int currentStopIndex)
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
    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);
    */


    QDomElement dStopLcdName=internationalTextType(xmlDocument,"StopName",currentStopPoinDestination.stopPoint.NameLcd+stopPropertiesToString2_3(currentStopPoinDestination.stopPoint),language);

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


QDomElement XmlCommon::StopPoint2_3gen(QDomDocument &xmlDocument, Vdv301StopPoint stopPointDestination)
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement dStopPoint=xmlDocument.createElement("StopPoint");


    QDomElement dStopIndex=Value(xmlDocument,"StopIndex",QString::number(stopPointDestination.stopIndex));

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref(xmlDocument, "StopRef",stopPointDestination.stopRef));


    foreach (Vdv301InternationalText stopName, stopPointDestination.stopNameList) {

        QDomElement dStopLcdName=internationalTextType(xmlDocument,"StopName",stopName.text,stopName.language);

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

Vdv301StopPoint XmlCommon::StopPoint2_3new( QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Vdv301Connection> connectionList, QString language,int currentStopIndex)
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


QString XmlCommon::stopPropertiesToString2_3(StopPoint stopPoint)
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

QDomElement XmlCommon::TimeStampTag1_0(QDomDocument &xmlDocument)
{
    QDomElement dTimeStamp=Value(xmlDocument,"TimeStamp",this->createTimestamp());
    return dTimeStamp;

}

QDomElement XmlCommon::ViaPoint1_0(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");
    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",QString::number(viaPoint.idCis)));

    QDomElement dPlaceName=internationalTextType(xmlDocument,"PlaceName",viaPoint.StopName,language);

    dViaPoint.appendChild(dPlaceName);
    return dViaPoint;
}

QDomElement XmlCommon::ViaPoint2_2CZ1_0(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
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
    QDomElement dPlaceName=internationalTextType(xmlDocument,"PlaceName",viaPoint.StopName,language);
    dViaPoint.appendChild(dPlaceName);

    QDomElement dPlaceSideName=internationalTextType(xmlDocument,"PlaceSideName",viaPoint.NameSide,language);
    dViaPoint.appendChild(dPlaceSideName);

    QDomElement dPlaceLcdName=internationalTextType(xmlDocument,"PlaceLcdName",viaPoint.NameLcd,language);
    dViaPoint.appendChild(dPlaceLcdName);


    QDomElement dPlaceInnerName=internationalTextType(xmlDocument,"PlaceInnerName",viaPoint.NameInner,language);
    dViaPoint.appendChild(dPlaceInnerName);
    return dViaPoint;
}


QDomElement XmlCommon::ViaPoint2_3(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");

    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",QString::number(viaPoint.idCis)));


    QDomElement dPlaceLcdName=internationalTextType(xmlDocument,"PlaceName",viaPoint.NameLcd+stopPropertiesToString2_3(viaPoint),language);
    dViaPoint.appendChild(dPlaceLcdName);

    return dViaPoint;
}


QDomElement XmlCommon::ViaPoint2_3def(QDomDocument &xmlDocument, Vdv301ViaPoint viaPoint)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");

    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",viaPoint.viaPointRef));


    foreach(Vdv301InternationalText viaPointName, viaPoint.placeNameList )
    {
        QDomElement dPlaceLcdName=internationalTextType(xmlDocument,"PlaceName",viaPointName.text ,viaPointName.language);
        dViaPoint.appendChild(dPlaceLcdName);
    }


    return dViaPoint;
}


QDomElement XmlCommon::internationalTextType(QDomDocument &xmlDocument,QString name,QString value,QString language)
{
    QDomElement output=xmlDocument.createElement(name);
    QDomElement xvalue=xmlDocument.createElement("Value");

    xvalue.appendChild(createEscapedValueCdata(xmlDocument,value));

    output.appendChild(xvalue);
    QDomElement xlanguage=xmlDocument.createElement("Language");
    xlanguage.appendChild(xmlDocument.createTextNode(language));
    output.appendChild(xlanguage);
    return output;
}


QDomCDATASection XmlCommon::createEscapedValueCdata(QDomDocument &document, QString input)
{
    // based on https://stackoverflow.com/a/48481806

    input=qStringXmlEscape(input);

    QDomCDATASection data = document.createCDATASection(input);
    return data;
}


QString XmlCommon::qStringXmlEscape(QString input)
{
    input.replace("'","&apos;");
    input.replace("&","&amp;");
    input.replace("\"","&quot;");
    input.replace("<","&lt;");
    input.replace(">","&gt;");

    return input;
}


/*!
 * \brief XmlCommon::qDomDocumentToQString
 * serves to remove CDATA, which was used to properly escape character
 * fixes escaping of > to &gt;
 * \param input
 * \return
 */
QString XmlCommon::qDomDocumentToQString(QDomDocument &input)
{

    // https://stackoverflow.com/a/48481806
    QString result = input.toString();
    result.replace("<![CDATA[", "");
    result.replace("]]>", "");

    return result;
}


QString XmlCommon::escapeHtml(QString input)
{
    QString output=input;
    output=output.replace("&","&amp;");
    output=output.replace("\"","&quot;");
    output=output.replace("'","&apos;");
    output=output.replace("<","&lt");
    output=output.replace(">","&gt;");

    return output;
}

QDomElement XmlCommon::ref(QDomDocument &xmlDocument,QString name, QString value)
{
    QDomElement ref=xmlDocument.createElement(name);
    QDomElement xvalue=xmlDocument.createElement("Value");
    xvalue.appendChild(xmlDocument.createTextNode(value));
    ref.appendChild(xvalue);
    return ref;
}

QDomElement XmlCommon::namedElement(QDomDocument &xmlDocument,QString name, QString value)
{
    QDomElement xvalue=xmlDocument.createElement(name);
    xvalue.appendChild(xmlDocument.createTextNode(value));
    return xvalue;
}


QDomElement XmlCommon::Value(QDomDocument &xmlDocument, QString elementName, QString content)
{
    QDomElement result=xmlDocument.createElement(elementName); //verze 2.2CZ1.0
    result.appendChild(xmlDocument.createElement("Value")).appendChild( xmlDocument.createTextNode(content));
    return result;
}

QDomElement XmlCommon::xxxProperty2_2CZ1_0(QDomDocument &xmlDocument,QString propertyName,bool valueBoolean,QString valueName)
{
    QDomElement output;
    if(valueBoolean)
    {
        output=xmlDocument.createElement(propertyName);
        output.appendChild(xmlDocument.createTextNode(valueName));
    }

    return output;
}

QString XmlCommon::xxxProperty2_3(QString icon, QString text,bool value)
{
    QString output="";
    if(value)
    {
        output="<icon type=\""+icon+"\" >"+text+"</icon>";

    }
    return output;
}


QDomProcessingInstruction XmlCommon::createProcessingInformation(QDomDocument &xmlDocument, QString encoding)
{
    return xmlDocument.createProcessingInstruction("xml","version=\"1.0\" encoding=\""+encoding+"\" ");
}

QDateTime XmlCommon::qTimeToQDateTimeToday(QTime input)
{
    // over midnight fix is not implemented!
    QDateTime output;
    output=QDateTime::currentDateTime();
    output.setTime(input);
    return output;

}

/*
QTime StopPoint::secondsToQtime(QString vstup)
{
    int seconds=vstup.toInt();
    seconds=seconds%86400; //fix for connection through midnight
    int hours=seconds/3600;
    int minutes=(seconds%3600)/60;
    return QTime(hours,minutes);
}
*/


int XmlCommon::isInRange(int index, int valueCount, QString nameOfFunction)
{
    qDebug()<<Q_FUNC_INFO;
    if((index<valueCount)&&(index>=0))
    {
        return 1;
    }
    else
    {
        QString errorText="value "+QString::number(index)+" is out of range "+ QString::number(valueCount)+" "+nameOfFunction;
        emit signalErrorMessage(errorText);
        qDebug()<<errorText;
        return 0;
    }

}
