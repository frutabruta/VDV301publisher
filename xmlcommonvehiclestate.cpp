#include "xmlcommonvehiclestate.h"

XmlCommonVehicleState::XmlCommonVehicleState() {}



QVector<QDomElement> XmlCommonVehicleState::Connections1_0(QDomDocument  &xmlDocument, QVector<Connection> connectionList)
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
    for( Connection &selectedConnection : connectionList) //possible problem with connections not being overwritten
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


QDomElement XmlCommonVehicleState::DisplayContent1_0(QString tagName, QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList, QString language,  int stopPointIterator, int currentStopIndex)
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



                for (const QString &selectedDestination : frontDestinations)
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
        if (nextStopPoint.stopPoint.isViapoint==false)
        {
            dDisplayContent.appendChild(ViaPoint1_0(xmlDocument,nextStopPoint.stopPoint,language));
        }

    }

    for (int j=currentStopIndex+1;j<stopPointDestinationList.count() ;j++)
    {
        if(stopPointDestinationList.at(j).stopPoint.isViapoint == true)
        {
            StopPointDestination viaPoint=stopPointDestinationList.at(j);
            dDisplayContent.appendChild(ViaPoint1_0(xmlDocument,viaPoint.stopPoint,language));

        }
    }

    return dDisplayContent;
}


QVector<QDomElement> XmlCommonVehicleState::FareZoneInformationStructure1_0(QDomDocument  &xmlDocument, QVector<FareZone> fareZoneList)
{
    QVector<QDomElement> dFareZoneList;

    for(const FareZone &selectedFareZone : fareZoneList)
    {
        QDomElement dFareZone=FareZone1_0(xmlDocument,selectedFareZone.name );
        dFareZoneList.append(dFareZone);
    }


    return dFareZoneList;
}


QDomElement XmlCommonVehicleState::StopPoint1_0(QDomDocument &xmlDocument, QVector<StopPointDestination> stopPointDestinationList,int stopPointIterator, QVector<Connection> connectionList, QString language,int currentStopIndex,VehicleState vehicleState)
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

        for(const QDomElement &dConnection : Connections1_0(xmlDocument,connectionList))
        {
            dStopPoint.appendChild(dConnection );
        }
    }

    QVector<QDomElement> dFareZoneList=FareZoneInformationStructure1_0(xmlDocument,selectedStopPointDestination.stopPoint.fareZoneList);

    for (const QDomElement &selectedFareZone : dFareZoneList)
    {
           dStopPoint.appendChild(selectedFareZone);
    }


    return dStopPoint;
}


QDomElement XmlCommonVehicleState::StopSequence1_0(QDomDocument &xmlDocument,QVector<StopPointDestination> stopPointDestinationList,QString language, int currentStopIndex, QVector<Connection> connectionList,VehicleState vehicleState)
{
    QDomElement dStopSequence=xmlDocument.createElement("StopSequence");
    for (int i=0 ; i<stopPointDestinationList.count();i++)
    {

        dStopSequence.appendChild(StopPoint1_0(xmlDocument,stopPointDestinationList,i,connectionList,language,currentStopIndex,vehicleState));

    }
    return dStopSequence;
}


QDomElement XmlCommonVehicleState::TripInformation1_0(QDomDocument &xmlDocument, QVector<Trip> tripList, QVector<Connection> connectionList, VehicleState vehicleState, int indexSpoje)
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


QString XmlCommonVehicleState::vehicleRunToRunNumber(VehicleRun vehicleRun)
{
    //   return QString::number(vehicleRun.rootLine.c)+"_"+QString::number(vehicleRun.order);
    return QString::number(vehicleRun.rootLine.c)+QString::number(vehicleRun.order).rightJustified(3,'0');
}


QDomElement XmlCommonVehicleState::ViaPoint1_0(QDomDocument &xmlDocument, StopPoint viaPoint,QString language)
{
    QDomElement dViaPoint=xmlDocument.createElement("ViaPoint");
    dViaPoint.appendChild(ref(xmlDocument,"ViaPointRef",QString::number(viaPoint.idCis)));

    QDomElement dPlaceName=internationalTextTypeToDom(xmlDocument,"PlaceName",viaPoint.StopName,language);

    dViaPoint.appendChild(dPlaceName);
    return dViaPoint;
}
