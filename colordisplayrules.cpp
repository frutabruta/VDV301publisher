#include "colordisplayrules.h"

ColorDisplayRules::ColorDisplayRules()
{
    fillColorMap();
}




void ColorDisplayRules::fillColorMap()
{
    qDebug() <<  Q_FUNC_INFO;
    //dd1 Metro, nahrazuje se piktogramem (metro, replaced with icon)
    colorsText["metro"]=color_black_0_0_0;
    colorsBackground["metro"]=color_white_255_255_255;

    //dd2 Denní tramvaj (day tram)
    colorsText["localTram"]=color_Tramvaj_120_2_0;
    colorsBackground["localTram"]=color_white_255_255_255;

    colorsText["localTramDiversion"]=color_Tramvaj_120_2_0;
    colorsBackground["localTramDiversion"]=color_Vyluky_255_170_30;

    //dd3 Denní městská autobusová linka  (day city bus)
    colorsText["localBus"]=color_Autobus_0_120_160;
    colorsBackground["localBus"]=color_white_255_255_255;

    colorsText["localBusDiversion"]=color_Autobus_0_120_160;
    colorsBackground["localBusDiversion"]=color_Vyluky_255_170_30;


    //dd4 Denní příměstská nebo regionální linka (day regional bus)
    colorsText["regionalBus"]=color_black_0_0_0;
    colorsBackground["regionalBus"]=color_white_255_255_255;


    colorsText["regionalBusDiversion"]=color_black_0_0_0;
    colorsBackground["regionalBusDiversion"]=color_Vyluky_255_170_30;

    //dd5 Noční městská autobusová linka (night city bus)
    colorsText["localBusNight"]=color_white_255_255_255;
    colorsBackground["localBusNight"]=color_Autobus_0_120_160;


    colorsText["localBusNightDiversion"]=color_Vyluky_255_170_30;
    colorsBackground["localBusNightDiversion"]=color_Autobus_0_120_160;

    //dd6 Noční tramvaj (night tram)

    colorsText["localTramNight"]=color_white_255_255_255;
    colorsBackground["localTramNight"]=color_Tramvaj_120_2_0;

    colorsText["localTramNightDiversion"]=color_Vyluky_255_170_30;
    colorsBackground["localTramNightDiversion"]=color_Tramvaj_120_2_0;

    //dd7 Linka náhradní dopravy, městský autobus
    colorsText["localBusReplacement"]=color_Vyluky_255_170_30;
    colorsBackground["localBusReplacement"]=color_white_255_255_255;

    //dd8 Lanovka (funicular)
    colorsText["funicular"]=color_Lanovka_201_208_34;
    colorsBackground["funicular"]=color_white_255_255_255;
    //dd9 Školní linka (school bus)
    colorsText["schoolBus"]=color_Autobus_0_120_160;
    colorsBackground["schoolBus"]=color_white_255_255_255;
    //dd10 Invalidní (PRM line)
    colorsText["specialNeedsBus"]=color_Specialni_143_188_25;
    colorsBackground["specialNeedsBus"]=color_white_255_255_255;
    //dd11 Smluvni (contract line)
    colorsText["localBusSpecial"]=color_Specialni_143_188_25;
    colorsBackground["localBusSpecial"]=color_white_255_255_255;
    //dd12 Přívoz (ferry)
    colorsText["localPassengerFerry"]=color_Privoz_0_164_167;
    colorsBackground["localPassengerFerry"]=color_white_255_255_255;
    //dd13 Vlaky PID – linky S nebo R (PID system  trains)
    colorsText["regionalRail"]=color_white_255_255_255;
    colorsBackground["regionalRail"]=color_Vlak_15_30_65;
    //dd14 Linka náhradní dopravy, NAD za vlak (rail replacement bus)
    colorsText["railReplacementBus"]=color_Vyluky_255_170_30;
    colorsBackground["railReplacementBus"]=color_white_255_255_255;

    colorsText["railReplacementBusReplacement"]=color_Vyluky_255_170_30;
    colorsBackground["railReplacementBusReplacement"]=color_white_255_255_255;



    //dd15 Linka náhradní dopravy, Tram
    colorsText["localTramReplacement"]=color_Vyluky_255_170_30;
    colorsBackground["localTramReplacement"]=color_white_255_255_255;
    //dd16 Noční příměstská nebo regionální linka
    colorsText["regionalBusNight"]=color_white_255_255_255;
    colorsBackground["regionalBusNight"]=color_Nocni_9_0_62;

    colorsText["regionalBusNightDiversion"]=color_Vyluky_255_170_30;
    colorsBackground["regionalBusNightDiversion"]=color_Nocni_9_0_62;

    //dd17 Linka mimo systém PID (3 znaky)
    //  barvaTextu[""]=barva_PozadiD_150_150_150;
    //  barvaPozadi[""]=barva_bila_255_255_255;
    colorsText["unknown"]=color_white_255_255_255;
    colorsBackground["unknown"]=color_PozadiD_150_150_150;

    colorsText["undefined"]=color_PozadiD_150_150_150;
    colorsBackground["undefined"]=color_white_255_255_255;
    //dd18 Denní trolejbusová linka
    colorsText["localTrolleybus"]=color_Trolejbus_128_22_111;
    colorsBackground["localTrolleybus"]=color_white_255_255_255;


    /*
    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

*/

}


StylLinky ColorDisplayRules::lineToStyle(Line line )
{
    qDebug()<<Q_FUNC_INFO;
    StylLinky vystup;



    QString vehicleMode="";
    QString subMode="";


    this->ddDoVehicleMode(vehicleMode,subMode, line);




    if(line.isNight==true)
    {
        subMode=subMode+"Night";
    }

    if(line.isDiversion)
    {
        subMode=subMode+"Diversion";
        //  pozadi="background-color:"+barva_Vyluky_255_170_30+";";
        qDebug()<<"linka je vylukova";
    }
    if(line.isReplacement)
    {
        subMode=subMode+"Replacement";
    }
    if(line.isSpecial)
    {
        subMode=subMode+"Special";
    }


    if(colorsBackground.contains(subMode))
    {
        vystup.background=colorsBackground[subMode];
    }
    else
    {
        vystup.background=color_white_255_255_255;
    }

    if(colorsText.contains(subMode))
    {
        vystup.text=colorsText[subMode];
    }
    else
    {
        vystup.text=color_black_0_0_0;
    }

    qDebug()<<"linka "<<line.lineName<<" submode "<<subMode;

    return vystup;

}

StylLinky ColorDisplayRules::lineToStyle(Line line , QString subMode )
{
    qDebug()<<Q_FUNC_INFO;
    StylLinky vystup;




    if(line.isNight==true)
    {
        subMode=subMode+"Night";
    }

    if(line.isDiversion)
    {
        subMode=subMode+"Diversion";
        //  pozadi="background-color:"+barva_Vyluky_255_170_30+";";
        qDebug()<<"linka je vylukova";
    }
    if(line.isReplacement)
    {
        subMode=subMode+"Replacement";
    }
    if(line.isSpecial)
    {
        subMode=subMode+"Special";
    }


    if(colorsBackground.contains(subMode))
    {
        vystup.background=colorsBackground[subMode];
    }
    if(colorsText.contains(subMode))
    {
        vystup.text=colorsText[subMode];
    }
    qDebug()<<"linka "<<line.lineName<<" submode "<<subMode;

    return vystup;

}

QString ColorDisplayRules::styleToString(QString text, StylLinky style)
{
    QString vystup="";

    vystup="<color fg=\""+style.text.name()+"\" bg=\""+style.background.name()+"\">"+text+"</color>";

    return vystup;
}

QString ColorDisplayRules::qColorToRgbString(QColor input)
{
    return "rgb("+QString::number(input.red())+","+QString::number(input.green())+","+QString::number(input.blue())+")";
}



void ColorDisplayRules::ddDoVehicleMode(QString &mainMode, QString &subMode, Line &line)
{
    qDebug()<<"PrestupMPV::ddDoVehicleMode "<<line.kli;

    /*
    bool isDiversion=false;
    bool isNight=false;
    bool isReplacement=false;
*/




    switch(line.kli)
    {
    case 1: //Metro
        mainMode="MetroSubmode";
        subMode="metro";

        break;
    case 2: //Denní tramvaj
        mainMode="TramSubmode";
        subMode="localTram";

        break;

    case 3: //Denní městská autobusová linka
        mainMode="BusSubmode";
        subMode="localBus";

        break;
    case 4: //Denní příměstská nebo regionální linka
        mainMode="BusSubmode";
        subMode="regionalBus";

        break;
    case 5: //Noční městská autobusová linka
        mainMode="BusSubmode";
        subMode="localBus";
        line.isNight=true;

        break;
    case 6: //Noční tramvaj
        mainMode="TramSubmode";
        subMode="localTram";
        line.isNight=true;

        break;
    case 7: //Linka náhradní dopravy, městský autobus
        mainMode="BusSubmode";
        subMode="localBus";
        line.isReplacement=true;

        break;

    case 8: //Lanovka
        mainMode="FunicularSubmode";
        subMode="funicular";

        break;
    case 9: //Školní linka
        mainMode="BusSubmode";
        subMode="schoolBus";
        line.isSchool=true;

        break;

    case 10: //Invalidní
        mainMode="BusSubmode";
        subMode="specialNeedsBus";
        line.isWheelchair=true;

        break;
    case 11: //Smluvni
        mainMode="BusSubmode";
        subMode="localBus";
        line.isSpecial=true;
        qDebug()<<"linka je specialni";


        break;
    case 12: //Přívoz
        mainMode="WaterSubmode";
        subMode="localPassengerFerry";

        break;
    case 13: //Vlaky PID – linky S nebo R
        mainMode="RailSubmode";
        subMode="regionalRail";

        break;
    case 14: //Linka náhradní dopravy, NAD za vlak
        mainMode="BusSubmode";
        subMode="railReplacementBus";
        line.isReplacement=true;

        break;
    case 15: //Linka náhradní dopravy, Tram
        mainMode="TramSubmode";
        subMode="localTram";
        line.isReplacement=true;

        break;

    case 16: //Noční příměstská nebo regionální linka
        mainMode="BusSubmode";
        subMode="regionalBus";
        line.isNight=true;

        break;

    case 17: //Linka mimo systém PID (3 znaky)
        mainMode="BusSubmode";
        subMode="undefined";

        break;
    case 18: //Denní trolejbusová linka
        mainMode="TrolleybusSubmode";
        subMode="localTrolleybus";

        break;

        /*
    case XX: //Lanovka do Bohnic
        mainMode="TelecabinSubmode";
        subMode="telecabin";

        break;
        */


    default:
        mainMode="BusSubmode";
        subMode="undefined";
        break;

    }

}
