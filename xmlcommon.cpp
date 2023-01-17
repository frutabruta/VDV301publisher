#include "xmlcommon.h"




XmlCommon::XmlCommon()
{

}

QDomElement XmlCommon::AdditionalTextMessage1_0(QString obsahZpravy)
{
    QDomDocument xmlko;
    QDomElement TextMessage=Value(xmlko,"AdditionalTextMessage","$LS$"+obsahZpravy);

    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}


QDomElement XmlCommon::AdditionalTextMessage2_2CZ1_0(QString obsahZpravy)
{
    QDomDocument xmlko;
    QDomElement TextMessage=xmlko.createElement("AdditionalTextMessage");
    QDomElement value=internationalTextType("AdditionalTextMessageText",obsahZpravy,defaultniJazyk2_2CZ1_0);
    TextMessage.appendChild(value);
    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}


QDomElement XmlCommon::AdditionalTextMessage2_2CZ1_0(QString type, QString headline, QString text)
{
    QDomDocument xmlko;
    QDomElement TextMessage=xmlko.createElement("AdditionalTextMessage");

    QDomElement TextMessageType=internationalTextType("AdditionalTextMessageType",type,defaultniJazyk2_2CZ1_0);
    QDomElement TextMessageHeadline=internationalTextType("AdditionalTextMessageHeadline",headline,defaultniJazyk2_2CZ1_0);
    QDomElement TextMessageText=internationalTextType("AdditionalTextMessageText",text,defaultniJazyk2_2CZ1_0);
    TextMessage.appendChild(TextMessageType);
    TextMessage.appendChild(TextMessageHeadline);
    TextMessage.appendChild(TextMessageText);

    //<TextMessage> <Value>$LS$This is  text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></TextMessage>
    return TextMessage;
}

QString XmlCommon::createTimestamp()
{
    qDebug()<<" XmlCommon::createTimestamp  ";
    QDateTime casovaZnacka = QDateTime::currentDateTime();
    QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");
    return casnaformatovanoString;
}


QVector<QDomElement> XmlCommon::Connections1_0( QVector<PrestupMPV> seznamPrestupu)
{

    qDebug()<<Q_FUNC_INFO;
    QDomDocument xmlko;
    QString language ="cs";
    QVector<QDomElement> vystup;

    seznamPrestupu=PrestupMPV::seradPrestupyExpectedDeparture(seznamPrestupu);

    QString dopravniProstredek="";
    QString destinationRef="1";

    for (int i=0;i<seznamPrestupu.count();i++)
    {
        PrestupMPV aktualniPrestup=seznamPrestupu.at(i);
        aktualniPrestup.lin=aktualniPrestup.lin.number(10);
        QDomElement dConnection=xmlko.createElement("Connection");
        Prestup vdv301prestup=aktualniPrestup.toPrestup();

        xmlko.appendChild(dConnection);

        QDomElement dConnectionMode = xmlko.createElement("TransportMode");
        dopravniProstredek="";
        // Bus, RegBus,Metro, NTram, Tram, NBus, Os, EC, R, Ex

        if (aktualniPrestup.t=="Bus")
        {
            dopravniProstredek="$01";

        }
        if(aktualniPrestup.t=="Metro")
        {
            dopravniProstredek="$03";

        }
        if(aktualniPrestup.t=="Tram")
        {
            dopravniProstredek="$02";

        }
        if((aktualniPrestup.t=="Os")||(aktualniPrestup.t=="R")||(aktualniPrestup.t=="Sp")||(aktualniPrestup.t=="Ex")||(aktualniPrestup.t=="EC"))
        {
            dopravniProstredek="$04";

        }

        dConnection.appendChild(ref("StopRef","XX"));
        dConnection.appendChild(ref("ConnectionRef","yy"));

        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));

        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);
        dDisplayContent.appendChild(Value(xmlko,"DisplayContentRef","2244"));
        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
        dLineInformation.appendChild(ref("LineRef",aktualniPrestup.alias));

        QDomElement dLineName=internationalTextType("LineName",vdv301prestup.line.LineName,language);
        dLineInformation.appendChild(dLineName);

        QDomElement dLineNumber=Value(xmlko, "LineNumber",aktualniPrestup.lin);
        dLineInformation.appendChild(dLineNumber);

        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);

        QDomElement dDestinationRef=Value(xmlko,"DestinationRef",destinationRef);

        dDestination.appendChild(dDestinationRef);

        QDomElement dDestinationName=internationalTextType("DestinationName",vdv301prestup.destinationName,language);
        dDestination.appendChild(dDestinationName);

        dConnection.appendChild(Value(xmlko,"Platform",aktualniPrestup.stan));

        //dopravni prostredek
        dConnectionMode.appendChild(this->ref("VehicleTypeRef","3"));
        dConnectionMode.appendChild(this->internationalTextType("Name",dopravniProstredek,defaultniJazyk1_0));
        dConnection.appendChild(dConnectionMode);
        qDebug()<<"přestup "<<vdv301prestup.line.LineName<<" "<<vdv301prestup.destinationName<<" ma zpozdeni"<<aktualniPrestup.zpoz<<" cas:"<<aktualniPrestup.odjReal;

        QDomElement dExpectedDepartureTime=Value(xmlko,"ExpectedDepatureTime", vdv301prestup.expectedDepartureTimeQString());
        dConnection.appendChild(dExpectedDepartureTime);
        vystup.push_back(dConnection);
    }
    return vystup;
}


QVector<QDomElement> XmlCommon::Connections2_2CZ1_0( QVector<Prestup> seznamPrestupu)
{
    qDebug()<<Q_FUNC_INFO;
    QDomDocument xmlko;
    QString language ="cs";
    QVector<QDomElement> vystup;

    seznamPrestupu=Prestup::seradPrestupyExpectedDeparture(seznamPrestupu);

    for (int i=0;i<seznamPrestupu.count();i++)
    {
        Prestup aktualniPrestup=seznamPrestupu.at(i);
     //   aktualniPrestup.lin=aktualniPrestup.lin.number(10);
        QDomElement dConnection=xmlko.createElement("Connection");
    //    Prestup vdv301prestup=aktualniPrestup.toPrestup();

        xmlko.appendChild(dConnection);

        QDomElement dConnectionMode = xmlko.createElement("ConnectionMode");





        if(aktualniPrestup.connectionProperty=="accessible")
        {
            dConnection.appendChild(xmlko.createElement("ConnectionProperty")).appendChild(xmlko.createTextNode("Accessible"));
        }
        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));

        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);

        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);

        QDomElement dLineName=internationalTextType("LineName",aktualniPrestup.line.LineName,language);
        dLineInformation.appendChild(dLineName);

        QDomElement dLineNumber=Value(xmlko, "LineNumber",aktualniPrestup.line.LineNumber);
        dLineInformation.appendChild(dLineNumber);
        QVector<QDomElement> priznakyLinky=linkaToLineProperties( aktualniPrestup.line);

        foreach(QDomElement priznak,priznakyLinky)
        {
            dLineInformation.appendChild(priznak);
        }

        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);



        QDomElement dDestinationName=internationalTextType("DestinationName",aktualniPrestup.destinationName,language);
        dDestination.appendChild(dDestinationName);

        dConnection.appendChild(Value(xmlko,"Platform",aktualniPrestup.platform));

        //dopravni prostredek
        dConnectionMode.appendChild(xmlko.createElement("PtMainMode")).appendChild(xmlko.createTextNode(aktualniPrestup.mainMode));
        dConnectionMode.appendChild(xmlko.createElement(aktualniPrestup.mainMode)).appendChild(xmlko.createTextNode(aktualniPrestup.subMode));
        dConnection.appendChild(dConnectionMode);


        qDebug()<<"přestup "<<aktualniPrestup.line.LineName<<" "<<aktualniPrestup.destinationName<<" cas:"<<aktualniPrestup.expectedDepartureTimeQString();

        QDomElement dExpectedDepartureTime=Value(xmlko,"ExpectedDepartureTime", aktualniPrestup.expectedDepartureTimeQString());
        dConnection.appendChild(dExpectedDepartureTime);

        QDomElement dScheduledDepartureTime=Value(xmlko,"ScheduledDepartureTime",aktualniPrestup.scheduledDepartureTimeQString());
        dConnection.appendChild(dScheduledDepartureTime);

        vystup.push_back(dConnection);
    }
    return vystup;
}

QDomElement XmlCommon::DisplayContent1_0(QString tagName,QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek, QString language,  int iteracniIndex,int currentStopIndex)
{
    ZastavkaCil aktZastavkaCil=docasnySeznamZastavek.at(iteracniIndex);
    QString lineNumber=aktZastavkaCil.linka.LineNumber;
    QString lineName=aktZastavkaCil.linka.LineName;
    bool pridatPristi=true;
    QDomElement dDisplayContent=xmlko.createElement(tagName);

    dDisplayContent.appendChild(ref("DisplayContentRef","1234"));

    //LINKA
    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dLineInformation.appendChild(ref("LineRef",lineNumber));
    dDisplayContent.appendChild(dLineInformation);

    QDomElement dLineName=internationalTextType("LineName",lineName,language);













    dLineInformation.appendChild(dLineName);
    QDomElement dLineNumber=Value(xmlko,"LineNumber",lineNumber);
    dLineInformation.appendChild(dLineNumber);

    //CIL
    QDomElement dDestination=xmlko.createElement("Destination");
    QString destinationName=aktZastavkaCil.cil.NameLcd;
    QString destinationRef=QString::number(docasnySeznamZastavek.at(iteracniIndex).cil.cisloCis);
    dDestination.appendChild(ref("DestinationRef",destinationRef));
    //QDomElement dDestinationName=internationalTextType("DestinationName", destinationName,language);
    //dDestination.appendChild(dDestinationName);
    //dDisplayContent.appendChild(dDestination);

    if (aktZastavkaCil.cil.NameFront2=="")
    {
        if (aktZastavkaCil.cil.NameFront.contains("|"))
        {
            QStringList predniCile=aktZastavkaCil.cil.NameFront.split("|");

            QString iteracniCil;

            foreach (iteracniCil, predniCile)
            {
                QDomElement dDestinationName=internationalTextType("DestinationName",iteracniCil,language);
                dDestination.appendChild(dDestinationName);
            }

        }
        else
        {
            QDomElement dDestinationName=internationalTextType("DestinationName",aktZastavkaCil.cil.NameFront,language);
            dDestination.appendChild(dDestinationName);
        }
    }
    else
    {
        QDomElement dDestinationName=internationalTextType("DestinationName",aktZastavkaCil.cil.NameFront,language);
        dDestination.appendChild(dDestinationName);
        QDomElement dDestinationName2=internationalTextType("DestinationName",aktZastavkaCil.cil.NameFront2,language);
        dDestination.appendChild(dDestinationName2);
    }

    dDisplayContent.appendChild(dDestination);
    if ((pridatPristi==true)&&((currentStopIndex+1)<docasnySeznamZastavek.count()))
    {
        ZastavkaCil pristi=docasnySeznamZastavek.at(currentStopIndex+1);
        if (pristi.zastavka.nacestna==0)
        {
            dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi.zastavka,language));
        }

    }

    for (int j=currentStopIndex+1;j<docasnySeznamZastavek.count() ;j++)
    {
        if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
        {
            ZastavkaCil nacestnaZastavka=docasnySeznamZastavek.at(j);
            dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka.zastavka,language));

        }
    }

    return dDisplayContent;
}

QDomElement XmlCommon::DisplayContent2_2CZ1_0(QString tagName,QVector<ZastavkaCil> docasnySeznamZastavek, QString language,int iteracniIndex,int currentStopIndex)
{
    QDomDocument xmlko;
    ZastavkaCil aktZastavkaCil=docasnySeznamZastavek.at(iteracniIndex);
    QString lineNumber=aktZastavkaCil.linka.LineNumber;
    QString lineName=aktZastavkaCil.linka.LineName;
    bool pridatPristi=true;
    QDomElement dDisplayContent=xmlko.createElement(tagName);

    dDisplayContent.appendChild(ref("DisplayContentRef","1234"));

    //LINKA
    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);


    QString placeholder="";
    PrestupMPV::ddDoVehicleMode(aktZastavkaCil.linka.kli,placeholder,placeholder,aktZastavkaCil.linka );
    QVector<QDomElement> priznakyLinky=linkaToLineProperties( aktZastavkaCil.linka);

    foreach(QDomElement priznak,priznakyLinky)
    {
        dLineInformation.appendChild(priznak);
    }


    QDomElement dLineName;

    if(lineName.length()>3)
    {
        //lineName="v &#x0A; &#x1B; &#x53; &#x0D; &#x34; "+lineName;

        QDomElement ctyrmistnaLinka=xmlko.createElement("test");


        QString ridiciZnak="";
        ridiciZnak+=0x1B;
        QDomCDATASection sekceKodu=xmlko.createCDATASection("<element>&#x1B;&#x53; ahoj</element>");


        dLineName=internationalTextType("LineName",  lineName ,language);
        // dLineName.appendChild(rawInsert(lineName));


    }
    else
    {
        dLineName=internationalTextType("LineName",lineName,language);
    }

    dLineInformation.appendChild(dLineName);
    QDomElement dLineNumber=Value(xmlko,"LineNumber",lineNumber);
    dLineInformation.appendChild(dLineNumber);

//CIL
    QDomElement dDestination=xmlko.createElement("Destination");
    //  dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.naZnameni,"RequestStop"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.prestupLetadlo ,"Air"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.prestupPrivoz ,"Ferry"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.prestupMetroA ,"UndergroundA"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.prestupMetroB ,"UndergroundB"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.prestupMetroC ,"UndergroundC"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.prestupMetroD ,"UndergroundD"));
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


    if (aktZastavkaCil.cil.NameFront2=="")
    {
        if (aktZastavkaCil.cil.NameFront.contains("|"))
        {
            QStringList predniCile=aktZastavkaCil.cil.NameFront.split("|");

            QString iteracniCil;

            foreach (iteracniCil, predniCile)
            {
                QDomElement dDestinationFrontName=internationalTextType("DestinationFrontName",iteracniCil,language);
                dDestination.appendChild(dDestinationFrontName);
            }

        }
        else
        {
            QDomElement dDestinationFrontName=internationalTextType("DestinationFrontName",aktZastavkaCil.cil.NameFront,language);
            dDestination.appendChild(dDestinationFrontName);
        }
    }
    else
    {
        QDomElement dDestinationFrontName=internationalTextType("DestinationFrontName",aktZastavkaCil.cil.NameFront,language);
        dDestination.appendChild(dDestinationFrontName);
        QDomElement dDestinationFrontName2=internationalTextType("DestinationFrontName",aktZastavkaCil.cil.NameFront2,language);
        dDestination.appendChild(dDestinationFrontName2);
    }

    QDomElement dDestinationSideName=internationalTextType("DestinationSideName",aktZastavkaCil.cil.NameSide,language);
    dDestination.appendChild(dDestinationSideName);
    QDomElement dDestinationRearName=internationalTextType("DestinationRearName",aktZastavkaCil.cil.NameRear,language);
    dDestination.appendChild(dDestinationRearName);
    QDomElement dDestinationLcdName=internationalTextType("DestinationLcdName",aktZastavkaCil.cil.NameLcd,language);
    dDestination.appendChild(dDestinationLcdName);
    QDomElement dDestinationInnerName=internationalTextType("DestinationInnerName",aktZastavkaCil.cil.NameInner,language);
    dDestination.appendChild(dDestinationInnerName);
    dDisplayContent.appendChild(dDestination);
    if ((pridatPristi==true)&&((currentStopIndex+1)<docasnySeznamZastavek.count()))
    {
        ZastavkaCil pristi=docasnySeznamZastavek.at(currentStopIndex+1);
        if (pristi.zastavka.nacestna==0)
        {
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlko,pristi.zastavka,language));
        }

    }

    for (int j=currentStopIndex+1;j<docasnySeznamZastavek.count() ;j++)
    {
        if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
        {
            ZastavkaCil nacestnaZastavka=docasnySeznamZastavek.at(j);
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlko,nacestnaZastavka.zastavka,language));

        }
    }

    return dDisplayContent;
}


QDomElement XmlCommon::DoorOpenState(QDomDocument xmlko,QString obsah)
{
    QDomElement dRouteDeviation = xmlko.createElement("DoorOpenState");
    dRouteDeviation.appendChild(xmlko.createTextNode(obsah));
    return dRouteDeviation;
}


QDomElement XmlCommon::FareZoneChange2_2CZ1_0(QVector<Pasmo> seznamPasemZ,QVector<Pasmo> seznamPasemNa,QString language)
{
    QDomDocument xmlko;

    QDomElement fareZoneChange=xmlko.createElement("FareZoneChange");
    QDomElement fromFareZones=xmlko.createElement("FromFareZones");
    QDomElement toFareZones=xmlko.createElement("ToFareZones");

    foreach (Pasmo aktPasmo, seznamPasemZ)
    {
        QDomElement pasmo=FareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        fromFareZones.appendChild(pasmo);
    }
    fareZoneChange.appendChild(fromFareZones);


    foreach (Pasmo aktPasmo, seznamPasemNa)
    {
        QDomElement pasmo=FareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        toFareZones.appendChild(pasmo);
    }
    fareZoneChange.appendChild(toFareZones);

    return fareZoneChange;
}

/////////////////////////////////////////////
QDomElement XmlCommon::FareZone1_0(QString shortName)
{
    QDomDocument xmlko;

    QDomElement pasmo=ref("FareZone",shortName);

    return pasmo;
}

QDomElement XmlCommon::FareZone2_2CZ1_0(QString shortName,QString longName, QString type, QString language)
{
    QDomDocument xmlko;

    QDomElement pasmo=xmlko.createElement("FareZone");
    QDomElement zoneType=xmlko.createElement("FareZoneType");
    QDomElement zoneTypeName=internationalTextType("FareZoneTypeName",type,language);
    zoneType.appendChild(zoneTypeName);
    pasmo.appendChild(zoneType);

    QDomElement zoneLongName=internationalTextType("FareZoneLongName",longName,language);
    QDomElement zoneShortName=internationalTextType("FareZoneShortName",shortName,language);

    pasmo.appendChild(zoneLongName);
    pasmo.appendChild(zoneShortName);

    return pasmo;
}

QVector<QDomElement> XmlCommon::FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem)
{
    QDomDocument xmlko;

    QVector<QDomElement> seznamFareZone;

    for (int i=0;i<seznamPasem.length() ;i++ )
    {
        Pasmo aktPasmo=seznamPasem.at(i);
        QDomElement pasmo=FareZone1_0(aktPasmo.nazev );
        seznamFareZone.append(pasmo);

    }
    return seznamFareZone;
}
QVector<QDomElement> XmlCommon::FareZoneInformationStructure2_2CZ1_0(QVector<Pasmo> seznamPasem,QString language)
{
    QDomDocument xmlko;

    QVector<QDomElement> seznamFareZone;

    for (int i=0;i<seznamPasem.length() ;i++ )
    {
        Pasmo aktPasmo=seznamPasem.at(i);
        QDomElement pasmo=FareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        seznamFareZone.append(pasmo);
    }
    return seznamFareZone;
}

QVector<QDomElement> XmlCommon::linkaToLineProperties(Linka linka)
{
    QVector<QDomElement> vystup;

    vystup.push_back(xxxProperty2_2CZ1_0("LineProperty",linka.isDiversion ,"Diversion"));
    vystup.push_back(xxxProperty2_2CZ1_0("LineProperty",!linka.isNight ,"Day"));
    vystup.push_back(xxxProperty2_2CZ1_0("LineProperty",linka.isNight ,"Night"));
    vystup.push_back(xxxProperty2_2CZ1_0("LineProperty",linka.isReplacement ,"Replacement"));
    vystup.push_back(xxxProperty2_2CZ1_0("LineProperty",linka.isSpecial ,"Special"));
    vystup.push_back(xxxProperty2_2CZ1_0("LineProperty",linka.isWheelchair ,"WheelChair"));

    return vystup;
}


QDomElement XmlCommon::MyOwnVehicleMode(QDomDocument xmlko,QString subMode, QString mode)
{
    QDomElement vystup=xmlko.createElement("MyOwnVehicleMode");
    QDomElement dPtMainMode=xmlko.createElement("PtMainMode");
    dPtMainMode.appendChild(xmlko.createTextNode(subMode));
    vystup.appendChild(dPtMainMode);
    QDomElement dSubMode=xmlko.createElement(subMode);
    dSubMode.appendChild(xmlko.createTextNode(mode));
    vystup.appendChild(dSubMode);
    return vystup;
}


QDomElement XmlCommon::MyOwnVehicleMode2_2CZ1_0(QString mainMode, QString subMode)
{
    QDomDocument xmlko;
    QDomElement myOwnVehicleMode=xmlko.createElement("MyOwnVehicleMode");
    QDomElement ptMainModeElement=xmlko.createElement("PtMainMode");
    ptMainModeElement.appendChild( xmlko.createTextNode( mainMode  ));
    QDomElement subModeElement=xmlko.createElement(mainMode);
    subModeElement.appendChild( xmlko.createTextNode( subMode ));
    myOwnVehicleMode.appendChild(ptMainModeElement);
    myOwnVehicleMode.appendChild(subModeElement);
    return myOwnVehicleMode;

}
///////////////////////////////

QDomElement XmlCommon::rawInsert(QString vstup)
{
    QDomElement vystup;
    QDomDocument novy;
    QDomImplementation impl;
    impl.setInvalidDataPolicy( QDomImplementation::AcceptInvalidChars );
    vstup="&#12;";
    //vstup=vstup.toHtmlEscaped();
    QString rawElement="<?xml version=\"1.0\" encoding=\"utf-8\" ?><wrapper>"+vstup+"</wrapper>";
    novy.setContent(rawElement,false);
    vystup=novy.firstChildElement();

    return vystup;
}


QDomElement XmlCommon::RouteDeviation(QDomDocument xmlko,QString obsah)
{
    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(obsah));
    return dRouteDeviation;
}


QDomElement XmlCommon::TripInformation1_0(QVector<Spoj> docasnySeznamSpoju, QVector<Prestup> prestupy, CestaUdaje stav, int indexSpoje)
{
    QDomDocument xmlko;
    int currentStopIndex= stav.indexAktZastavky;
    QString language=defaultniJazyk1_0;
    QString tripRef=QString::number(docasnySeznamSpoju.at(indexSpoje).cisloRopid);
    QVector<ZastavkaCil> docasnySeznamZastavek=docasnySeznamSpoju.at(indexSpoje).globalniSeznamZastavek;
    QDomElement dTripInformation=xmlko.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlko,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,prestupy,stav));


    QDomElement dLocationState=xmlko.createElement("LocationState");
    dLocationState.appendChild(xmlko.createTextNode( stav.locationState));
    dTripInformation.appendChild(dLocationState);

    QString specialniOznameni=docasnySeznamZastavek.at(stav.indexAktZastavky).zastavka.additionalTextMessage;
    qDebug()<<"spec oznameni="<<specialniOznameni;

    if(stav.jeSpecialniHlaseni)
    {
        dTripInformation.appendChild(AdditionalTextMessage1_0(stav.aktivniSpecialniHlaseni.text));
    }
    else if (specialniOznameni!="")
    {
        dTripInformation.appendChild(AdditionalTextMessage1_0(specialniOznameni));
    }

    else
    {
        qDebug()<<"specOznJePrazdne";
    }

    return dTripInformation;

}

QDomElement XmlCommon::TripInformation2_2CZ1_0(QVector<Spoj> docasnySeznamSpoju, QVector<Prestup> prestupy, CestaUdaje stav, int indexSpoje, bool navazny)
{
    QDomDocument xmlko;
    int currentStopIndex= stav.indexAktZastavky;
    QString language=defaultniJazyk2_2CZ1_0;
    QString tripRef=QString::number(docasnySeznamSpoju.at(indexSpoje).cisloRopid);
    QVector<ZastavkaCil> docasnySeznamZastavek=docasnySeznamSpoju.at(indexSpoje).globalniSeznamZastavek;
    QDomElement dTripInformation=xmlko.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlko,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_2CZ1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,prestupy));

    if (navazny==false)
    {
        QDomElement dLocationState=xmlko.createElement("LocationState");
        dLocationState.appendChild(xmlko.createTextNode( stav.locationState));
        dTripInformation.appendChild(dLocationState);

        QString specialniOznameni=docasnySeznamZastavek.at(stav.indexAktZastavky).zastavka.additionalTextMessage;
        qDebug()<<"spec oznameni="<<specialniOznameni;

        if(stav.jeSpecialniHlaseni)
        {
            dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(stav.aktivniSpecialniHlaseni.type, stav.aktivniSpecialniHlaseni.title, stav.aktivniSpecialniHlaseni.text));
        }
        else if (specialniOznameni!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
    }
    else
    {
        qDebug()<<"navazny=true";
    }

    //změna tarifního pásma
    if((currentStopIndex+1)<docasnySeznamZastavek.length()&&(stav.zobrazZmenuPasma==true))
    {
        qDebug()<<"pred bum";
        dTripInformation.appendChild(FareZoneChange2_2CZ1_0(docasnySeznamZastavek.at(currentStopIndex-1).zastavka.seznamPasem,docasnySeznamZastavek.at(currentStopIndex).zastavka.seznamPasem,language));
        qDebug()<<"bum";
    }

    return dTripInformation;

}

QDomElement XmlCommon::StopSequence1_0(QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek,QString language, int currentStopIndex, QVector<Prestup> prestupy,CestaUdaje stav)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {

        dStopSequence.appendChild(StopPoint1_0(docasnySeznamZastavek,i,prestupy,language,currentStopIndex,stav));

    }
    return dStopSequence;
}

QDomElement XmlCommon::StopSequence2_2CZ1_0(QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek,QString language, int currentStopIndex, QVector<Prestup> seznamPrestupu)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        dStopSequence.appendChild(StopPoint2_2CZ1_0(docasnySeznamZastavek,i,seznamPrestupu,language,currentStopIndex));
    }
    return dStopSequence;
}
QDomElement XmlCommon::StopPoint1_0(QVector<ZastavkaCil> docasnySeznamZastavek,int indexZpracZastavky, QVector<Prestup> seznamPrestupu, QString language,int currentStopIndex,CestaUdaje stav)
{
    qDebug()<<Q_FUNC_INFO;
    QDomDocument xmlko;
    QDomElement dStopPoint=xmlko.createElement("StopPoint");
    if (docasnySeznamZastavek.isEmpty())
    {
        qDebug()<<"seznam zastávek je prázdný";
        return dStopPoint;
    }
    if (indexZpracZastavky>=docasnySeznamZastavek.length())
    {
        qDebug()<<"index zastavky je mimo rozsah";
        return dStopPoint;
    }
    ZastavkaCil aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);

    QByteArray cCurrentStopIndex=QByteArray::number(indexZpracZastavky+1);
    QString cStopName= aktZastavka.zastavka.StopName;

    QDomElement dStopIndex=Value(xmlko,"StopIndex",cCurrentStopIndex);

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.zastavka.cisloCis)));

    if(aktZastavka.zastavka.prestupVlak==true)
    {
        cStopName=cStopName+"$04";
    }

    if(aktZastavka.zastavka.prestupMetroA||aktZastavka.zastavka.prestupMetroB||aktZastavka.zastavka.prestupMetroC||aktZastavka.zastavka.prestupMetroD )
    {
        cStopName=cStopName+"$03";
    }
    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);



    QDomElement dDisplayContent=DisplayContent1_0("DisplayContent",xmlko,docasnySeznamZastavek,language, indexZpracZastavky,currentStopIndex);
    dStopPoint.appendChild(dDisplayContent);


    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {
        QVector<QDomElement> prestupy=Connections2_2CZ1_0(seznamPrestupu);
        foreach(QDomElement elementPrestupu,prestupy)
        {
            dStopPoint.appendChild(elementPrestupu );
        }
    }

    QVector<QDomElement> domPasma=FareZoneInformationStructure1_0(aktZastavka.zastavka.seznamPasem);
    for (int i=0;i<domPasma.length();i++)
    {
        dStopPoint.appendChild(domPasma.at(i));
    }

    return dStopPoint;
}


QDomElement XmlCommon::StopPoint2_2CZ1_0(QVector<ZastavkaCil> docasnySeznamZastavek,int indexZpracZastavky, QVector<Prestup> seznamPrestupu, QString language,int currentStopIndex)
{
    qDebug()<<Q_FUNC_INFO;
    QDomDocument xmlko;
    QDomElement dStopPoint=xmlko.createElement("StopPoint");
    if (docasnySeznamZastavek.isEmpty())
    {
        qDebug()<<"seznam zastávek je prázdný";
        return dStopPoint;
    }
    if (indexZpracZastavky>=docasnySeznamZastavek.length())
    {
        qDebug()<<"index zastavky je mimo rozsah";
        return dStopPoint;
    }
    ZastavkaCil aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);

    QByteArray cCurrentStopIndex=QByteArray::number(indexZpracZastavky+1);
    QString cStopName= aktZastavka.zastavka.StopName;

    QDomElement dStopIndex=Value(xmlko,"StopIndex",cCurrentStopIndex);

    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.zastavka.cisloCis)));


    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);

    QDomElement dStopFrontName=internationalTextType("StopFrontName",aktZastavka.zastavka.NameFront,language);
    dStopPoint.appendChild(dStopFrontName);
    QDomElement dStopSideName=internationalTextType("StopSideName",aktZastavka.zastavka.NameSide,language);
    dStopPoint.appendChild(dStopSideName);
    QDomElement dStopRearName=internationalTextType("StopRearName",aktZastavka.zastavka.NameRear,language);
    dStopPoint.appendChild(dStopRearName);
    QDomElement dStopLcdName=internationalTextType("StopLcdName",aktZastavka.zastavka.NameLcd,language);
    dStopPoint.appendChild(dStopLcdName);
    QDomElement dStopInnerName=internationalTextType("StopInnerName",aktZastavka.zastavka.NameInner,language);
    dStopPoint.appendChild(dStopInnerName);

    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.naZnameni,"RequestStop"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupLetadlo ,"Air"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupPrivoz ,"Ferry"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroA ,"UndergroundA"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroB ,"UndergroundB"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroC ,"UndergroundC"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroD ,"UndergroundD"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupVlak ,"Train"));
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

    QDomElement dDisplayContent=DisplayContent2_2CZ1_0("DisplayContent",docasnySeznamZastavek,language,indexZpracZastavky,currentStopIndex);

    dStopPoint.appendChild(dDisplayContent);


   // qDebug()<<"cCurrentStopIndex.toInt() "<< cCurrentStopIndex.toInt()<<" (currentStopIndex+1) " << (currentStopIndex+1);


    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {
        QVector<QDomElement> prestupy=Connections2_2CZ1_0(seznamPrestupu);
        foreach(QDomElement elementPrestupu,prestupy)
        {
            dStopPoint.appendChild(elementPrestupu );
        }

    }

    QVector<QDomElement> domPasma=FareZoneInformationStructure2_2CZ1_0(aktZastavka.zastavka.seznamPasem,language);
    for (int i=0;i<domPasma.length();i++)
    {
        dStopPoint.appendChild(domPasma.at(i));
    }

    return dStopPoint;
}


QDomElement XmlCommon::TimeStampTag1_0(QDomDocument xmlko)
{
    QDomElement dTimeStamp=Value(xmlko,"TimeStamp",this->createTimestamp());
    return dTimeStamp;

}

QDomElement XmlCommon::ViaPoint1_0(QDomDocument xmlko, Zastavka nacestnaZastavka,QString language)
{
    QDomElement dViaPoint=xmlko.createElement("ViaPoint");
    dViaPoint.appendChild(ref("ViaPointRef",QString::number(nacestnaZastavka.cisloCis)));

    QDomElement dPlaceName=internationalTextType("PlaceName",nacestnaZastavka.StopName,language);

    dViaPoint.appendChild(dPlaceName);
    return dViaPoint;
}

QDomElement XmlCommon::ViaPoint2_2CZ1_0(QDomDocument xmlko, Zastavka nacestnaZastavka,QString language)
{
    QDomElement dViaPoint=xmlko.createElement("ViaPoint");
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.naZnameni,"RequestStop"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupLetadlo ,"Air"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupPrivoz ,"Ferry"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroA ,"UndergroundA"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroB ,"UndergroundB"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroC ,"UndergroundC"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroD ,"UndergroundD"));
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
    QDomElement dPlaceName=internationalTextType("PlaceName",nacestnaZastavka.StopName,language);
    dViaPoint.appendChild(dPlaceName);

    QDomElement dPlaceSideName=internationalTextType("PlaceSideName",nacestnaZastavka.NameSide,language);
    dViaPoint.appendChild(dPlaceSideName);

    QDomElement dPlaceLcdName=internationalTextType("PlaceLcdName",nacestnaZastavka.NameLcd,language);
    dViaPoint.appendChild(dPlaceLcdName);


    QDomElement dPlaceInnerName=internationalTextType("PlaceInnerName",nacestnaZastavka.NameInner,language);
    dViaPoint.appendChild(dPlaceInnerName);
    return dViaPoint;
}


QDomElement XmlCommon::internationalTextType(QString name,QString value,QString language)
{
    QDomDocument xmlko;
    QDomElement vysledek=xmlko.createElement(name);
    QDomElement xvalue=xmlko.createElement("Value");
    xvalue.appendChild(xmlko.createTextNode(value));

    vysledek.appendChild(xvalue);
    QDomElement xlanguage=xmlko.createElement("Language");
    xlanguage.appendChild(xmlko.createTextNode(language));
    vysledek.appendChild(xlanguage);
    return vysledek;
}

QDomElement XmlCommon::ref(QString name, QString value)
{
    QDomDocument xmlko;
    QDomElement ref=xmlko.createElement(name);
    QDomElement xvalue=xmlko.createElement("Value");
    xvalue.appendChild(xmlko.createTextNode(value));
    ref.appendChild(xvalue);
    return ref;
}


QDomElement XmlCommon::Value(QDomDocument &xmlko, QString elementName, QString content)
{
    QDomElement result=xmlko.createElement(elementName); //verze 2.2CZ1.0
    result.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(content));
    return result;
}

QDomElement XmlCommon::xxxProperty2_2CZ1_0(QString nazev,bool vysledek,QString hodnota)
{
    QDomDocument xmlko;
    if(vysledek)
    {
        QDomElement stopProperty=xmlko.createElement(nazev);
        stopProperty.appendChild(xmlko.createTextNode(hodnota));
        return stopProperty;
    }

    QDomElement prazdny;
    return prazdny;
}
