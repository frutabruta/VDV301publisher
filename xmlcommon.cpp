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

        QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",selectedConnection.line.lineName,language);
        dLineInformation.appendChild(dLineName);

        QDomElement dLineNumber=Value(xmlDocument, "LineNumber",selectedConnection.line.lineNumber);
        dLineInformation.appendChild(dLineNumber);

        QDomElement dDestination=xmlDocument.createElement("Destination");
        dDisplayContent.appendChild(dDestination);

        QDomElement dDestinationRef=Value(xmlDocument,"DestinationRef",destinationRef);

        dDestination.appendChild(dDestinationRef);

        QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedConnection.destinationName,language);
        dDestination.appendChild(dDestinationName);

        dConnection.appendChild(Value(xmlDocument,"Platform",selectedConnection.platform));

        //mean of transport
        dConnectionMode.appendChild(this->ref(xmlDocument,"VehicleTypeRef","3"));
        dConnectionMode.appendChild(this->internationalTextTypeToDom(xmlDocument,"Name",wuppertalMeanOfTransport,defaultLanguage1_0));
        dConnection.appendChild(dConnectionMode);

        QDomElement dExpectedDepartureTime=Value(xmlDocument,"ExpectedDepatureTime", selectedConnection.expectedDepartureTimeQString());
        dConnection.appendChild(dExpectedDepartureTime);
        output.push_back(dConnection);
        // qDebug()<<"connection "<<vdv301connection.line.lineName<<" "<<vdv301connection.destinationName<<" has delay"<<selectedConnection.zpoz<<" cas:"<<selectedConnection.odjReal;

    }
    return output;
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

    QDomElement dLineName=internationalTextTypeToDom(xmlDocument,"LineName",lineName,language);


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
        QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameLcd,language);
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
                    QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedDestination,language);
                    dDestination.appendChild(dDestinationName);
                }

            }
            else
            {
                QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront,language);
                dDestination.appendChild(dDestinationName);
            }
        }
        else
        {
            QDomElement dDestinationName=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront,language);
            dDestination.appendChild(dDestinationName);
            QDomElement dDestinationName2=internationalTextTypeToDom(xmlDocument,"DestinationName",selectedStopPointDestination.destination.NameFront2,language);
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


//work in progress






QDomElement XmlCommon::DoorOpenState(QDomDocument &xmlDocument,QString content)
{
    QDomElement dRouteDeviation = xmlDocument.createElement("DoorOpenState");
    dRouteDeviation.appendChild(xmlDocument.createTextNode(content));
    return dRouteDeviation;
}





/////////////////////////////////////////////
QDomElement XmlCommon::FareZone1_0(QDomDocument  &xmlDocument, QString shortName)
{

    QDomElement pasmo=ref(xmlDocument,"FareZone",shortName);

    return pasmo;
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
    QDomElement dStopName=internationalTextTypeToDom(xmlDocument,"StopName",cStopName,language);
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







QDomElement XmlCommon::TimeStampTag1_0(QDomDocument &xmlDocument)
{
    QDomElement dTimeStamp=Value(xmlDocument,"TimeStamp",this->createTimestamp());
    return dTimeStamp;

}

QDomElement XmlCommon::ViaPoint1_0(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");
    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",QString::number(viaPoint.idCis)));

    QDomElement dPlaceName=internationalTextTypeToDom(xmlDocument,"PlaceName",viaPoint.StopName,language);

    dViaPoint.appendChild(dPlaceName);
    return dViaPoint;
}




QDomElement XmlCommon::internationalTextTypeToDom(QDomDocument &xmlDocument,QString name,QString value,QString language)
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

QDomElement XmlCommon::internationalTextTypeToDom(QDomDocument &xmlDocument,QString name,Vdv301InternationalText internationalText)
{
    QDomElement output=xmlDocument.createElement(name);
    QDomElement xvalue=xmlDocument.createElement("Value");

    xvalue.appendChild(createEscapedValueCdata(xmlDocument,internationalText.text));

    output.appendChild(xvalue);
    QDomElement xlanguage=xmlDocument.createElement("Language");
    xlanguage.appendChild(xmlDocument.createTextNode(internationalText.language));
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
