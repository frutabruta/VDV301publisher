#ifndef COLORDISPLAYRULES_H
#define COLORDISPLAYRULES_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>
#include "VDV301DataStructures/line.h"


class StylLinky
{
public:
    QColor background=QColor(0,0,0);
    QColor text=QColor(255,255,255);
};


class ColorDisplayRules
{
public:
    ColorDisplayRules();

    void fillColorMap();



    //nezarazeno
    QMap<QString, QColor> colorsText;
    QMap<QString, QColor> colorsBackground;
    //definice barev

    //colors defined by PID LCD Display design manual, naming is left in czech to comply with the definitions in design manual

    QColor color_BackgroundA_25_25_25 = QColor(25,25,25);
    QColor color_BackgroundB_50_50_50 =QColor(50,50,50); //tmave seda(Dark grey)
    QColor color_BackgroundC_100_100_100 =QColor(100,100,100);
    QColor color_PozadiD_150_150_150 =QColor(150,150,150); //Pozadí D (Background D variant)
    QColor color_Zastavka_180_180_180 =QColor(180,180,180); //Zastávka (BusStop)
    QColor color_white_255_255_255 =QColor(255,255,255); //bila (white)
    QColor color_black_0_0_0 =QColor(0,0,0); //cerna (black)

    QColor color_Vyluky_255_170_30 =QColor(255,170,30); // disruptions
    QColor color_Cervena_200_0_20 =QColor(200,0,20); // red
    QColor color_CervenaTexty_220_40_40 =QColor(220,40,40); // red texts
    QColor color_Zelena_210_215_15 =QColor(210,215,15); //green

    QColor color_MetroA_0_165_98 =QColor(0,165,98);
    QColor color_MetroB_248_179_34 =QColor(248,179,34);
    QColor color_MetroC_207_0_61 =QColor(207,0,61);
    QColor color_MetroD_0_140_190 =QColor(0,140,190);
    QColor color_Tramvaj_120_2_0 =QColor(120,2,0); // tram
    QColor color_Trolejbus_128_22_111 =QColor(128,22,111); //trolleybus
    QColor color_Autobus_0_120_160 =QColor(0,120,160); // bus
    QColor color_Vlak_15_30_65 =QColor(15,30,65); // train
    QColor color_Lanovka_201_208_34 =QColor(201,208,34); //funicular
    QColor color_Privoz_0_164_167 =QColor(0,164,167); //ferry
    QColor color_Nocni_9_0_62 =QColor(9,0,62); //ngiht
    QColor color_Letiste_155_203_234 =QColor(155,203,234); //airport
    QColor color_Specialni_143_188_25 =QColor(143,188,25); //special


    QString styleToString(QString text, StylLinky style);

    StylLinky lineToStyle(Line line);
    StylLinky lineToStyle(Line line, QString subMode);
    QString qColorToRgbString(QColor input);
    void ddDoVehicleMode(QString &mainMode, QString &subMode, Line &line);

};

#endif // COLORDISPLAYRULES_H



