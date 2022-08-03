#include "xmlcommon.h"




XmlCommon::XmlCommon()
{

}




QString XmlCommon::createTimestamp()
{
    qDebug()<<" XmlCommon::createTimestamp  ";
    QDateTime casovaZnacka = QDateTime::currentDateTime();
    QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");
    return casnaformatovanoString;
}


QDomElement XmlCommon::TripInformation2_2CZ1_0(QVector<Spoj> docasnySeznamSpoju, QVector<PrestupMPV> prestupy, CestaUdaje stav, int indexSpoje, bool navazny)
{
    QVector<ZastavkaCil> docasnySeznamZastavek=docasnySeznamSpoju.at(indexSpoje).globalniSeznamZastavek;
    QDomDocument xmlko;
    QString locationState=stav.locationState;

    QString tripRef=QString::number(docasnySeznamSpoju.at(indexSpoje).cisloRopid);
    QString language=defaultniJazyk2_2CZ1_0;

    int currentStopIndex= stav.indexAktZastavky;

    QDomElement dTripInformation=xmlko.createElement("TripInformation");

    QDomElement dTripRef=xmlko.createElement("TripRef");
    dTripRef.appendChild(xmlko.createElement("Value"));
    dTripRef.firstChildElement("Value").appendChild(xmlko.createTextNode(tripRef));
    dTripInformation.appendChild(dTripRef);



    //stop sequence
    dTripInformation.appendChild(StopSequence2_2CZ1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,prestupy));




    if (navazny==false)
    {
        QDomElement dLocationState=xmlko.createElement("LocationState");
        dLocationState.appendChild(xmlko.createTextNode( locationState));
        dTripInformation.appendChild(dLocationState);

        QString specialniOznameni=docasnySeznamZastavek.at(currentStopIndex).zastavka.additionalTextMessage;
        qDebug()<<"spec oznameni="<<specialniOznameni;

        if(stav.jeSpecialniHlaseni)
        {
            dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(stav.aktivniSpecialniHlaseni.type, stav.aktivniSpecialniHlaseni.title, stav.aktivniSpecialniHlaseni.text));
        }

        if (specialniOznameni!="")
        {
            dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
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







QDomElement XmlCommon::StopSequence1_0(QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek,QString language, int currentStopIndex, QVector<PrestupMPV> prestupy,CestaUdaje stav)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {

        dStopSequence.appendChild(stopPoint1_0(docasnySeznamZastavek,i,prestupy,language,currentStopIndex,stav));

    }
    return dStopSequence;
}

QDomElement XmlCommon::StopSequence2_2CZ1_0(QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek,QString language, int currentStopIndex, QVector<PrestupMPV> seznamPrestupu)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {


        dStopSequence.appendChild(StopPoint2_2CZ1_0(docasnySeznamZastavek,i,seznamPrestupu,language,currentStopIndex));

    }
    return dStopSequence;
}


QDomElement XmlCommon::stopPoint1_0(QVector<ZastavkaCil> docasnySeznamZastavek,int indexZpracZastavky, QVector<PrestupMPV> seznamPrestupu, QString language,int currentStopIndex,CestaUdaje stav)
{
    qDebug()<<"XmlCommon::stopPoint1_0";
    ZastavkaCil aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);
    QDomDocument xmlko;
    QByteArray cCurrentStopIndex=QByteArray::number(indexZpracZastavky);
    QString cStopName= aktZastavka.zastavka.StopName;

    //STOP
    QDomElement dStopPoint=xmlko.createElement("StopPoint");

    QDomElement dStopIndex=xmlko.createElement("StopIndex");
    dStopIndex.appendChild(xmlko.createElement("Value"));
    dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
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




    QDomElement dDisplayContent=DisplayContent1_0("DisplayContent",xmlko,docasnySeznamZastavek,language, stav);
    dStopPoint.appendChild(dDisplayContent);



    QVector<QDomElement> domPasma=FareZoneInformationStructure1_0(aktZastavka.zastavka.seznamPasem);
    for (int i=0;i<domPasma.length();i++)
    {
        dStopPoint.appendChild(domPasma.at(i));
    }






    if (cCurrentStopIndex.toInt()==currentStopIndex)
    {
        QDomDocument Connections=this->Connections1_0(seznamPrestupu);
        // qDebug()<<" prestupy "<<Connections.toString();

        QDomNodeList seznamPrestupu = Connections.elementsByTagName("Connection");
        for (int j=0;j<seznamPrestupu.count();j++)
        {
            dStopPoint.appendChild(seznamPrestupu.at(indexZpracZastavky).toElement() );
        }
    }
    return dStopPoint;
}

QDomElement XmlCommon::StopPoint2_2CZ1_0(QVector<ZastavkaCil> docasnySeznamZastavek,int indexZpracZastavky, QVector<PrestupMPV> seznamPrestupu, QString language,int currentStopIndex)
{
    qDebug()<<"XmlCommon::stopPoint2_2CZ1_0";
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
    //QByteArray cCurrentStopIndex=QByteArray::number(aktZastavka.zastavka.StopIndex+1);
    QString cStopName= aktZastavka.zastavka.StopName;
    //STOP


    QDomElement dStopIndex=xmlko.createElement("StopIndex");
    dStopIndex.appendChild(xmlko.createElement("Value"));
    dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.cil.cisloCis)));

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

    QDomElement dDisplayContent=DisplayContent2_2CZ1_0("DisplayContent",docasnySeznamZastavek,language,indexZpracZastavky,currentStopIndex);

    dStopPoint.appendChild(dDisplayContent);



    QVector<QDomElement> domPasma=FareZoneInformationStructure2_2CZ1_0(aktZastavka.zastavka.seznamPasem,language);
    for (int i=0;i<domPasma.length();i++)
    {
        dStopPoint.appendChild(domPasma.at(i));
    }



    qDebug()<<"cCurrentStopIndex.toInt() "<< cCurrentStopIndex.toInt()<<" (currentStopIndex+1) " << (currentStopIndex+1);

    if (cCurrentStopIndex.toInt()==(currentStopIndex+1))
    {

        QVector<QDomElement> prestupy=Connections2_2CZ1_0(seznamPrestupu);
        foreach(QDomElement elementPrestupu,prestupy)
        {
            dStopPoint.appendChild(elementPrestupu );
        }


        /*
        QDomNodeList seznamPrestupu = Connections.elementsByTagName("Connection");

        for (int j=0;j<seznamPrestupu.count();j++)
        {
            dStopPoint.appendChild(seznamPrestupu.at(indexZpracZastavky).toElement() );
        }
        */
    }
    return dStopPoint;
}

QDomElement XmlCommon::DisplayContent1_0(QString tagName,QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek, QString language,  CestaUdaje stav)
{

    int indexAktZastavky=stav.indexAktZastavky;
    ZastavkaCil aktZastCil=docasnySeznamZastavek.at(indexAktZastavky);


    QString destinationName=aktZastCil.cil.NameLcd;
    QString lineNumber=aktZastCil.linka.LineNumber;
    QString lineName=aktZastCil.linka.LineName;
    QString destinationRef=QString::number(docasnySeznamZastavek.at(indexAktZastavky).cil.cisloCis);
    bool pridatPristi=true;
    QDomElement dDisplayContent=xmlko.createElement(tagName);

    dDisplayContent.appendChild(ref("DisplayContentRef","1234"));

    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);

    dLineInformation.appendChild(ref("LineRef",lineNumber));


    QDomElement dLineName=internationalTextType("LineName",lineName,language);
    dLineInformation.appendChild(dLineName);

    QDomElement dLineNumber=xmlko.createElement("LineNumber");
    dLineNumber.appendChild(xmlko.createElement("Value"));
    dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlko.createElement("Destination");


    dDestination.appendChild(ref("DestinationRef",destinationRef));


    QDomElement dDestinationName=internationalTextType("DestinationName",destinationName,language);
    dDestination.appendChild(dDestinationName);

    dDisplayContent.appendChild(dDestination);

    if(stav.locationState=="AtStop")
    {
        if ((pridatPristi==true)&&((indexAktZastavky+1)<docasnySeznamZastavek.count()))
        {
            ZastavkaCil pristi=docasnySeznamZastavek.at(indexAktZastavky+1);
            if (pristi.zastavka.nacestna==0)
            {
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi.zastavka,language));
            }

        }

        for (int j=indexAktZastavky+1;j<docasnySeznamZastavek.count() ;j++)
        {
            if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
            {
                Zastavka nacestnaZastavka=docasnySeznamZastavek.at(j).zastavka;
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
            }
        }
    }
    else
    {
        if ((pridatPristi==true)&&((indexAktZastavky)<docasnySeznamZastavek.count()))
        {
            Zastavka pristi=docasnySeznamZastavek.at(indexAktZastavky).zastavka;
            if (pristi.nacestna==0)
            {
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi,language));
            }

        }

        for (int j=indexAktZastavky;j<docasnySeznamZastavek.count() ;j++)
        {
            if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
            {
                Zastavka nacestnaZastavka=docasnySeznamZastavek.at(j).zastavka;
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
            }
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

    //linka

    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);

   // QDomElement dLineProperty=xmlko.createElement("LineProperty");


    QString dummy1="";
    QString dummy2="";
    PrestupMPV::ddDoVehicleMode(aktZastavkaCil.linka.kli,dummy1,dummy2,aktZastavkaCil.linka );
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
        dLineName.appendChild(rawInsert(lineName));

    }
    else
    {
        dLineName=internationalTextType("LineName",lineName,language);
    }




    dLineInformation.appendChild(dLineName);

    QDomElement dLineNumber=xmlko.createElement("LineNumber");
    dLineNumber.appendChild(xmlko.createElement("Value"));
    dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));

    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlko.createElement("Destination");

    dDestination.appendChild(xxxProperty2_2CZ1_0("DestinationProperty",aktZastavkaCil.cil.naZnameni,"RequestStop"));
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
            <xs:enumeration value="UndergroundA"/>
            <xs:enumeration value="UndergroundB"/>
            <xs:enumeration value="UndergroundC"/>
            <xs:enumeration value="UndergroundD"/>
            */
    //dDestination.appendChild(ref("DestinationRef",destinationRef));


    //QDomElement dDestinationName=internationalTextType("DestinationName",destinationName,language);
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

QDomElement XmlCommon::ViaPoint1_0(QDomDocument xmlko, Zastavka nacestnaZastavka,QString language)
{
    QDomElement dViaPoint=xmlko.createElement("ViaPoint");
    dViaPoint.appendChild(ref("ViaPointRef",QString::number(nacestnaZastavka.cisloCis)));
    QDomElement dPlaceName=xmlko.createElement("PlaceName");
    dPlaceName.appendChild(xmlko.createElement("Value"));
    dPlaceName.firstChildElement("Value").appendChild(xmlko.createTextNode(nacestnaZastavka.StopName));
    dPlaceName.appendChild(xmlko.createElement("Language"));
    dPlaceName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
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

QDomElement XmlCommon::TimeStampTag1_0(QDomDocument xmlko)
{
    QDomElement dTimeStamp=xmlko.createElement("TimeStamp");
    QDomElement dTimeStampValue =xmlko.createElement("Value");
    dTimeStampValue.appendChild(xmlko.createTextNode(this->createTimestamp()));
    dTimeStamp.appendChild(dTimeStampValue);

    return dTimeStamp;

}


QVector<QDomElement> XmlCommon::FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem)
{
    QDomDocument xmlko;


    QVector<QDomElement> seznamFareZone;

    for (int i=0;i<seznamPasem.length() ;i++ )
    {
        Pasmo aktPasmo=seznamPasem.at(i);
        QDomElement pasmo=fareZone1_0(aktPasmo.nazev );
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
        QDomElement pasmo=fareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        seznamFareZone.append(pasmo);
    }
    return seznamFareZone;
}
///////////////////////////////

QDomElement XmlCommon::FareZoneChange2_2CZ1_0(QVector<Pasmo> seznamPasemZ,QVector<Pasmo> seznamPasemNa,QString language)
{
    QDomDocument xmlko;

    QDomElement fareZoneChange=xmlko.createElement("FareZoneChange");
    QDomElement fromFareZones=xmlko.createElement("FromFareZones");
    QDomElement toFareZones=xmlko.createElement("ToFareZones");

    foreach (Pasmo aktPasmo, seznamPasemZ)
    {
        QDomElement pasmo=fareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        fromFareZones.appendChild(pasmo);
    }
    fareZoneChange.appendChild(fromFareZones);


    foreach (Pasmo aktPasmo, seznamPasemNa)
    {
        QDomElement pasmo=fareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        toFareZones.appendChild(pasmo);
    }
    fareZoneChange.appendChild(toFareZones);


    return fareZoneChange;



}

/////////////////////////////////////////////
QDomElement XmlCommon::fareZone1_0(QString shortName)
{
    QDomDocument xmlko;

    QDomElement pasmo=ref("FareZone",shortName);


    return pasmo;
}

QDomElement XmlCommon::fareZone2_2CZ1_0(QString shortName,QString longName, QString type, QString language)
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

QDomElement XmlCommon::AdditionalTextMessage1_0(QString obsahZpravy)
{
    QDomDocument xmlko;
    QDomElement TextMessage=xmlko.createElement("AdditionalTextMessage");
    QDomElement value=xmlko.createElement("Value");
    value.appendChild(xmlko.createTextNode("$LS$"+obsahZpravy));
    TextMessage.appendChild(value);
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

QDomElement XmlCommon::DoorOpenState(QDomDocument xmlko,QString obsah)
{
    QDomElement dRouteDeviation = xmlko.createElement("DoorOpenState");
    dRouteDeviation.appendChild(xmlko.createTextNode(obsah));
    return dRouteDeviation;
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







QDomDocument XmlCommon::Connections1_0( QVector<PrestupMPV> lokPrestupy)
{

    qDebug()<<"XmlCommon::connections1_0";
    QDomDocument xmlko;
    QDomElement root=xmlko.createElement("wrapper");


    QString dopravniProstredek="";
    QString language ="cs";
    QString destinationRef="1";

    for (int i=0;i<lokPrestupy.count();i++)
    {
        PrestupMPV prestup=lokPrestupy.at(i);
        dopravniProstredek="";
        QDomElement dConnectionMode = xmlko.createElement("TransportMode");

        // Bus, RegBus,Metro, NTram, Tram, NBus, Os, EC, R, Ex

        if (prestup.t=="Bus")
        {
            dopravniProstredek="$01";

        }
        if(prestup.t=="Metro")
        {
            dopravniProstredek="$03";

        }
        if(prestup.t=="Tram")
        {
            dopravniProstredek="$02";

        }
        if((prestup.t=="Os")||(prestup.t=="R")||(prestup.t=="Sp")||(prestup.t=="Ex")||(prestup.t=="EC"))
        {
            dopravniProstredek="$04";

        }


        QDomElement dConnection=xmlko.createElement("Connection");
        xmlko.appendChild(dConnection);
        dConnection.appendChild(ref("StopRef","XX"));
        dConnection.appendChild(ref("ConnectionRef","yy"));
        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));
        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);
        dDisplayContent.appendChild(xmlko.createElement("DisplayContentRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("2244"));
        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
        dLineInformation.appendChild(ref("LineRef",prestup.alias));
        QDomElement dLineName=xmlko.createElement("LineName");
        dLineName.appendChild(xmlko.createElement("Value"));
        dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(prestup.alias));
        dLineInformation.appendChild(dLineName);
        dLineName.appendChild(xmlko.createElement("Language"));
        dLineName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        QDomElement dLineNumber=xmlko.createElement("LineNumber");
        dLineNumber.appendChild(xmlko.createElement("Value"));
        dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode("1"));
        dLineInformation.appendChild(dLineNumber);
        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);
        QDomElement dDestinationRef=xmlko.createElement("DestinationRef");
        dDestinationRef.appendChild(xmlko.createElement("Value"));
        dDestinationRef.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationRef));
        dDestination.appendChild(dDestinationRef);
        QDomElement dDestinationName=xmlko.createElement("DestinationName");
        dDestinationName.appendChild(xmlko.createElement("Value"));
        dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(prestup.smer));
        dDestination.appendChild(dDestinationName);
        dDestinationName.appendChild(xmlko.createElement("Language"));
        dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        dConnection.appendChild(xmlko.createElement("Platform")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(prestup.stan));
        dConnectionMode.appendChild(this->ref("VehicleTypeRef","3"));
        dConnectionMode.appendChild(this->internationalTextType("Name",dopravniProstredek,defaultniJazyk1_0));

        dConnection.appendChild(dConnectionMode);
        QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepatureTime"); //verze 1.0
        // QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepartureTime"); verze 2.0
        dExpectedDepartureTime.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(  PrestupMPV::qDateTimeToString(prestup.odj)));
        dConnection.appendChild(dExpectedDepartureTime);

    }
    return xmlko;

}

QVector<QDomElement> XmlCommon::Connections2_2CZ1_0( QVector<PrestupMPV> seznamPrestupu)
{
    qDebug()<<"XmlCommon::connections2_2CZ1_0";
    QDomDocument xmlko;
    QDomElement root=xmlko.createElement("wrapper");
    QString language ="cs";

    QVector<QDomElement> vystup;


    seznamPrestupu=PrestupMPV::seradPrestupyExpectedDeparture(seznamPrestupu);



    for (int i=0;i<seznamPrestupu.count();i++)
    {
        PrestupMPV aktualniPrestup=seznamPrestupu.at(i);
        aktualniPrestup.lin=aktualniPrestup.lin.number(10);

        /*
        QString mainMode="";
        QString subMode="";
        Linka linka;
      */

        Prestup vdv301prestup=aktualniPrestup.toPrestup();


        QDomElement dConnectionMode = xmlko.createElement("ConnectionMode");


       // PrestupMPV::ddDoVehicleMode(aktualniPrestup.dd,mainMode,subMode,linka);

        QDomElement dConnection=xmlko.createElement("Connection");
        xmlko.appendChild(dConnection);

        if(aktualniPrestup.np==true)
        {
            dConnection.appendChild(xmlko.createElement("ConnectionProperty")).appendChild(xmlko.createTextNode("Accessible"));
        }
        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));

        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);

        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);

        QDomElement dLineName=xmlko.createElement("LineName");
        dLineName.appendChild(xmlko.createElement("Value"));
        dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(vdv301prestup.line.LineName));
        dLineInformation.appendChild(dLineName);
        dLineName.appendChild(xmlko.createElement("Language"));
        dLineName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        QDomElement dLineNumber=xmlko.createElement("LineNumber");
        dLineNumber.appendChild(xmlko.createElement("Value"));
        dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode("1"));
        dLineInformation.appendChild(dLineNumber);
        QVector<QDomElement> priznakyLinky=linkaToLineProperties( vdv301prestup.line);


        foreach(QDomElement priznak,priznakyLinky)
        {
            dLineInformation.appendChild(priznak);
        }

        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);

        QDomElement dDestinationName=xmlko.createElement("DestinationName");
        dDestinationName.appendChild(xmlko.createElement("Value"));
        dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(vdv301prestup.destinationName));
        dDestination.appendChild(dDestinationName);

        dDestinationName.appendChild(xmlko.createElement("Language"));
        dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));

        dConnection.appendChild(xmlko.createElement("Platform")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(aktualniPrestup.stan));

        dConnectionMode.appendChild(xmlko.createElement("PtMainMode")).appendChild(xmlko.createTextNode(vdv301prestup.mainMode));
        dConnectionMode.appendChild(xmlko.createElement(vdv301prestup.mainMode)).appendChild(xmlko.createTextNode(vdv301prestup.subMode));
        dConnection.appendChild(dConnectionMode);

        //  QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepatureTime"); verze 1.0



        qDebug()<<"přestup "<<vdv301prestup.line.LineName<<" "<<vdv301prestup.destinationName<<" ma zpozdeni"<<aktualniPrestup.zpoz<<" cas:"<<aktualniPrestup.odjReal;



        //QString expectedTime= cas.toString(Qt::ISODate);


        QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepartureTime"); //verze 2.2CZ1.0
        dExpectedDepartureTime.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(  vdv301prestup.expectedDepartureTimeQString()));
        dConnection.appendChild(dExpectedDepartureTime);

        QDomElement dScheduledDepartureTime=xmlko.createElement("ScheduledDepartureTime"); //verze 2.2CZ1.0
        dScheduledDepartureTime.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(  vdv301prestup.scheduledDepartureTimeQString() ));
        dConnection.appendChild(dScheduledDepartureTime);

        vystup.push_back(dConnection);
    }

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



