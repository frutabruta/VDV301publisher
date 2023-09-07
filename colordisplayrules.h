#ifndef COLORDISPLAYRULES_H
#define COLORDISPLAYRULES_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>
#include "VDV301struktury/linka.h"


class StylLinky
{
public:
    QColor pozadi=QColor(0,0,0);
    QColor text=QColor(255,255,255);
};


class ColorDisplayRules
{
public:
    ColorDisplayRules();

    void naplnMapBarev();



    //nezarazeno
    QMap<QString, QColor> barvaTextu;
    QMap<QString, QColor> barvaPozadi;
    //definice barev

    QColor barva_PozadiA_25_25_25 = QColor(25,25,25);
    QColor barva_PozadiB_50_50_50 =QColor(50,50,50); //tmave seda
    QColor barva_PozadiC_100_100_100 =QColor(100,100,100);
    QColor barva_PozadiD_150_150_150 =QColor(150,150,150); //Pozadí D
    QColor barva_Zastavka_180_180_180 =QColor(180,180,180); //Zastávka
    QColor barva_bila_255_255_255 =QColor(255,255,255); //bila
    QColor barva_cerna_0_0_0 =QColor(0,0,0); //cerna

    QColor barva_Vyluky_255_170_30 =QColor(255,170,30);
    QColor barva_Cervena_200_0_20 =QColor(200,0,20);
    QColor barva_CervenaTexty_220_40_40 =QColor(220,40,40);
    QColor barva_Zelena_210_215_15 =QColor(210,215,15);

    QColor barva_MetroA_0_165_98 =QColor(0,165,98);
    QColor barva_MetroB_248_179_34 =QColor(248,179,34);
    QColor barva_MetroC_207_0_61 =QColor(207,0,61);
    QColor barva_MetroD_0_140_190 =QColor(0,140,190);
    QColor barva_Tramvaj_120_2_0 =QColor(120,2,0);
    QColor barva_Trolejbus_128_22_111 =QColor(128,22,111);
    QColor  barva_Autobus_0_120_160 =QColor(0,120,160);
    QColor barva_Vlak_15_30_65 =QColor(15,30,65);
    QColor barva_Lanovka_201_208_34 =QColor(201,208,34);
    QColor barva_Privoz_0_164_167 =QColor(0,164,167);
    QColor barva_Nocni_9_0_62 =QColor(9,0,62);
    QColor barva_Letiste_155_203_234 =QColor(155,203,234);
    QColor barva_Specialni_143_188_25 =QColor(143,188,25);


    QString styleToString(QString text, StylLinky style);

    StylLinky linkaDoStylu(Linka linka);
    StylLinky linkaDoStylu(Linka linka, QString subMode);
    QString qColorToRgbString(QColor input);
    void ddDoVehicleMode(QString &mainMode, QString &subMode, Linka &linka);

};

#endif // COLORDISPLAYRULES_H



