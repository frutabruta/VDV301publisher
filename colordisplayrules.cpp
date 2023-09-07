#include "colordisplayrules.h"

ColorDisplayRules::ColorDisplayRules()
{
    naplnMapBarev();
}




void ColorDisplayRules::naplnMapBarev()
{
    qDebug() <<  Q_FUNC_INFO;
    //dd1 Metro, nahrazuje se piktogramem
    barvaTextu["metro"]=barva_cerna_0_0_0;
    barvaPozadi["metro"]=barva_bila_255_255_255;

    //dd2 Denní tramvaj
    barvaTextu["localTram"]=barva_Tramvaj_120_2_0;
    barvaPozadi["localTram"]=barva_bila_255_255_255;

    barvaTextu["localTramDiversion"]=barva_Tramvaj_120_2_0;
    barvaPozadi["localTramDiversion"]=barva_Vyluky_255_170_30;

    //dd3 Denní městská autobusová linka
    barvaTextu["localBus"]=barva_Autobus_0_120_160;
    barvaPozadi["localBus"]=barva_bila_255_255_255;

    barvaTextu["localBusDiversion"]=barva_Autobus_0_120_160;
    barvaPozadi["localBusDiversion"]=barva_Vyluky_255_170_30;


    //dd4 Denní příměstská nebo regionální linka
    barvaTextu["regionalBus"]=barva_cerna_0_0_0;
    barvaPozadi["regionalBus"]=barva_bila_255_255_255;


    barvaTextu["regionalBusDiversion"]=barva_cerna_0_0_0;
    barvaPozadi["regionalBusDiversion"]=barva_Vyluky_255_170_30;

    //dd5 Noční městská autobusová linka
    barvaTextu["localBusNight"]=barva_bila_255_255_255;
    barvaPozadi["localBusNight"]=barva_Autobus_0_120_160;


    barvaTextu["localBusNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["localBusNightDiversion"]=barva_Autobus_0_120_160;

    //dd6 Noční tramvaj

    barvaTextu["localTramNight"]=barva_bila_255_255_255;
    barvaPozadi["localTramNight"]=barva_Tramvaj_120_2_0;

    barvaTextu["localTramNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["localTramNightDiversion"]=barva_Tramvaj_120_2_0;

    //dd7 Linka náhradní dopravy, městský autobus
    barvaTextu["localBusReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["localBusReplacement"]=barva_bila_255_255_255;

    //dd8 Lanovka
    barvaTextu["funicular"]=barva_Lanovka_201_208_34;
    barvaPozadi["funicular"]=barva_bila_255_255_255;
    //dd9 Školní linka
    barvaTextu["schoolBus"]=barva_Autobus_0_120_160;
    barvaPozadi["schoolBus"]=barva_bila_255_255_255;
    //dd10 Invalidní
    barvaTextu["specialNeedsBus"]=barva_Specialni_143_188_25;
    barvaPozadi["specialNeedsBus"]=barva_bila_255_255_255;
    //dd11 Smluvni
    barvaTextu["localBusSpecial"]=barva_Specialni_143_188_25;
    barvaPozadi["localBusSpecial"]=barva_bila_255_255_255;
    //dd12 Přívoz
    barvaTextu["localPassengerFerry"]=barva_Privoz_0_164_167;
    barvaPozadi["localPassengerFerry"]=barva_bila_255_255_255;
    //dd13 Vlaky PID – linky S nebo R
    barvaTextu["regionalRail"]=barva_bila_255_255_255;
    barvaPozadi["regionalRail"]=barva_Vlak_15_30_65;
    //dd14 Linka náhradní dopravy, NAD za vlak
    barvaTextu["railReplacementBus"]=barva_Vyluky_255_170_30;
    barvaPozadi["railReplacementBus"]=barva_bila_255_255_255;

    barvaTextu["railReplacementBusReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["railReplacementBusReplacement"]=barva_bila_255_255_255;



    //dd15 Linka náhradní dopravy, Tram
    barvaTextu["localTramReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["localTramReplacement"]=barva_bila_255_255_255;
    //dd16 Noční příměstská nebo regionální linka
    barvaTextu["regionalBusNight"]=barva_bila_255_255_255;
    barvaPozadi["regionalBusNight"]=barva_Nocni_9_0_62;

    barvaTextu["regionalBusNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["regionalBusNightDiversion"]=barva_Nocni_9_0_62;

    //dd17 Linka mimo systém PID (3 znaky)
    //  barvaTextu[""]=barva_PozadiD_150_150_150;
    //  barvaPozadi[""]=barva_bila_255_255_255;
    barvaTextu["unknown"]=barva_bila_255_255_255;
    barvaPozadi["unknown"]=barva_PozadiD_150_150_150;

    barvaTextu["undefined"]=barva_PozadiD_150_150_150;
    barvaPozadi["undefined"]=barva_bila_255_255_255;
    //dd18 Denní trolejbusová linka
    barvaTextu["localTrolleybus"]=barva_Trolejbus_128_22_111;
    barvaPozadi["localTrolleybus"]=barva_bila_255_255_255;


    /*
    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

*/

}


StylLinky ColorDisplayRules::linkaDoStylu( Linka linka )
{
    qDebug()<<Q_FUNC_INFO;
    StylLinky vystup;



    QString vehicleMode="";
    QString subMode="";


    this->ddDoVehicleMode(vehicleMode,subMode, linka);




    if(linka.isNight==true)
    {
        subMode=subMode+"Night";
    }

    if(linka.isDiversion)
    {
        subMode=subMode+"Diversion";
        //  pozadi="background-color:"+barva_Vyluky_255_170_30+";";
        qDebug()<<"linka je vylukova";
    }
    if(linka.isReplacement)
    {
        subMode=subMode+"Replacement";
    }
    if(linka.isSpecial)
    {
        subMode=subMode+"Special";
    }


    if(barvaPozadi.contains(subMode))
    {
        vystup.pozadi=barvaPozadi[subMode];
    }
    else
    {
        vystup.pozadi=barva_bila_255_255_255;
    }

    if(barvaTextu.contains(subMode))
    {
        vystup.text=barvaTextu[subMode];
    }
    else
    {
        vystup.text=barva_cerna_0_0_0;
    }

    qDebug()<<"linka "<<linka.LineName<<" submode "<<subMode;

    return vystup;

}

StylLinky ColorDisplayRules::linkaDoStylu( Linka linka , QString subMode )
{
    qDebug()<<Q_FUNC_INFO;
    StylLinky vystup;




    if(linka.isNight==true)
    {
        subMode=subMode+"Night";
    }

    if(linka.isDiversion)
    {
        subMode=subMode+"Diversion";
        //  pozadi="background-color:"+barva_Vyluky_255_170_30+";";
        qDebug()<<"linka je vylukova";
    }
    if(linka.isReplacement)
    {
        subMode=subMode+"Replacement";
    }
    if(linka.isSpecial)
    {
        subMode=subMode+"Special";
    }


    if(barvaPozadi.contains(subMode))
    {
        vystup.pozadi=barvaPozadi[subMode];
    }
    if(barvaTextu.contains(subMode))
    {
        vystup.text=barvaTextu[subMode];
    }
    qDebug()<<"linka "<<linka.LineName<<" submode "<<subMode;

    return vystup;

}

QString ColorDisplayRules::styleToString(QString text, StylLinky style)
{
    QString vystup="";

    vystup="<color fg=\""+style.text.name()+"\" bg=\""+style.pozadi.name()+"\">"+text+"</color>";

    return vystup;
}

QString ColorDisplayRules::qColorToRgbString(QColor input)
{
    return "rgb("+QString::number(input.red())+","+QString::number(input.green())+","+QString::number(input.blue())+")";
}



void ColorDisplayRules::ddDoVehicleMode(QString &mainMode, QString &subMode, Linka &linka)
{
    qDebug()<<"PrestupMPV::ddDoVehicleMode "<<linka.kli;

    /*
    bool isDiversion=false;
    bool isNight=false;
    bool isReplacement=false;
*/




    switch(linka.kli)
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
        linka.isNight=true;

        break;
    case 6: //Noční tramvaj
        mainMode="TramSubmode";
        subMode="localTram";
        linka.isNight=true;

        break;
    case 7: //Linka náhradní dopravy, městský autobus
        mainMode="BusSubmode";
        subMode="localBus";
        linka.isReplacement=true;

        break;

    case 8: //Lanovka
        mainMode="FunicularSubmode";
        subMode="funicular";

        break;
    case 9: //Školní linka
        mainMode="BusSubmode";
        subMode="schoolBus";
        linka.isSchool=true;

        break;

    case 10: //Invalidní
        mainMode="BusSubmode";
        subMode="specialNeedsBus";
        linka.isWheelchair=true;

        break;
    case 11: //Smluvni
        mainMode="BusSubmode";
        subMode="localBus";
        linka.isSpecial=true;
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
        linka.isReplacement=true;

        break;
    case 15: //Linka náhradní dopravy, Tram
        mainMode="TramSubmode";
        subMode="localTram";
        linka.isReplacement=true;

        break;

    case 16: //Noční příměstská nebo regionální linka
        mainMode="BusSubmode";
        subMode="regionalBus";
        linka.isNight=true;

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
