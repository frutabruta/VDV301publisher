#ifndef XMLCOMMON_H
#define XMLCOMMON_H
#include <QMainWindow>
#include <QObject>
#include <QTime>
#include <QCoreApplication>
#include <QtDebug>
#include <QtXml>
#include <QDomDocument>

#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/pasmo.h"

#include "VDV301struktury/prestupmpv.h"
#include "VDV301publisher/colordisplayrules.h"
//#include "xmlmpvparser.h"


class XmlCommon :public QMainWindow
{
    //  Q_OBJECT
public:
    enum DisplayContentClass
    {
        DisplayContentFront,
        DisplayContentSide,
        DisplayContentRear,
        DisplayContentLcd
    };

    ColorDisplayRules colorDisplayRules;

    XmlCommon();

    //konstanty
    QString defaultniJazyk1_0="de";
    QString defaultniJazyk2_2CZ1_0="cs";

    //pomocneFce
    QString devStatus();
    QString createTimestamp();
    QDomElement internationalTextType(QString name, QString value, QString language);
    QVector<QDomElement> linkaToLineProperties(Linka linka);
    QDomElement rawInsert(QString vstup);
    QDomElement ref(QString name, QString value);
    QDomElement xxxProperty2_2CZ1_0(QString nazev, bool vysledek, QString hodnota);

    //VDV301 struktury
    QDomElement AdditionalTextMessage1_0(QString obsahZpravy);
    QDomElement AdditionalTextMessage2_2CZ1_0(QString obsahZpravy);
    QDomElement AdditionalTextMessage2_2CZ1_0(QString type, QString headline, QString text);

    QString AllData1_0(QVector<ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<PrestupMPV> prestupy, CestaUdaje stav);
    QString AllData_empty_1_0();
    QString AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<PrestupMPV> prestupy, CestaUdaje stav);
    QString AllData_empty2_2CZ1_0();

    QVector<QDomElement> Connections1_0( QVector<PrestupMPV> seznamPrestupu);
    QVector<QDomElement> Connections2_2CZ1_0(QVector<Prestup> seznamPrestupu);
    QVector<QDomElement> Connections2_4(QVector<Prestup> seznamPrestupu);
    QString CurrentDisplayContent1_0(int poradi, QVector<ZastavkaCil> docasnySeznamZastavek, CestaUdaje stav);

    QDomElement DisplayContent1_0(QString tagName, QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int iteracniIndex, int currentStopIndex);
    QDomElement DisplayContent2_2CZ1_0(QString tagName, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int iteracniIndex, int currentStopIndex);
    QDomElement DoorOpenState(QDomDocument xmlko, QString obsah);

    QDomElement FareZone1_0(QString shortName);
    QDomElement FareZone2_2CZ1_0(QString shortName, QString longName, QString type, QString language);
    QVector<QDomElement> FareZoneInformationStructure2_2CZ1_0(QVector<Pasmo> seznamPasem, QString language);
    QVector<QDomElement> FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem);
    QDomElement FareZoneChange2_2CZ1_0(QVector<Pasmo> seznamPasemZ, QVector<Pasmo> seznamPasemNa, QString language);

    QDomElement MyOwnVehicleMode(QDomDocument xmlko, QString mode, QString subMode);
    QDomElement MyOwnVehicleMode2_2CZ1_0(QString mainMode, QString subMode);

    QDomElement StopPoint1_0(QVector<ZastavkaCil> docasnySeznamZastavek, int indexZpracZastavky, QVector<Prestup> seznamPrestupu, QString language, int currentStopIndex, CestaUdaje stav);
    QDomElement StopPoint2_2CZ1_0(QVector<ZastavkaCil> docasnySeznamZastavek, int indexZpracZastavky, QVector<Prestup> seznamPrestupu, QString language, int currentStopIndex);
    QDomElement StopSequence2_2CZ1_0(QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int currentStopIndex, QVector<Prestup> seznamPrestupu);
    QDomElement StopSequence1_0(QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int currentStopIndex, QVector<Prestup> prestupy, CestaUdaje stav);

    QDomElement RouteDeviation(QDomDocument xmlko, QString obsah);

    QString TicketValidationService_GetVehicleDataResponse2_2CZ1_0(CestaUdaje stav);
    QString TicketValidationService_GetRazziaResponse2_2CZ1_0(CestaUdaje stav);
    QString TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(int poradi, QVector<ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<PrestupMPV> prestupy);
    QDomElement TimeStampTag1_0(QDomDocument xmlko);
    QDomElement TripInformation1_0(QVector<Spoj> docasnySeznamSpoju, QVector<Prestup> prestupy, CestaUdaje stav, int indexSpoje);
    QDomElement TripInformation2_2CZ1_0(QVector<Spoj> docasnySeznamTripu, QVector<Prestup> prestupy, CestaUdaje stav, int indexSpoje, bool navazny);

    QDomElement ViaPoint2_2CZ1_0(QDomDocument xmlko, Zastavka nacestnaZastavka, QString language);
    QDomElement ViaPoint1_0(QDomDocument xmlko, Zastavka nacestnaZastavka, QString language);
    QDomElement Value(QDomDocument &xmlko, QString elementName, QString content);

    //rozdelano
    QDomElement DisplayContent2_4(QString tagName, QVector<ZastavkaCil> docasnySeznamZastavek, QString destinationName, QString language, int iteracniIndex, int currentStopIndex, DisplayContentClass displayContentClass);
    QDomElement StopPoint2_4(QVector<ZastavkaCil> docasnySeznamZastavek, int indexZpracZastavky, QVector<Prestup> seznamPrestupu, QString language, int currentStopIndex);
    QDomElement ViaPoint2_4(QDomDocument xmlko, Zastavka nacestnaZastavka, QString language);


    QDomElement TripInformation2_4(QVector<Spoj> docasnySeznamSpoju, QVector<Prestup> prestupy, CestaUdaje stav, int indexSpoje, bool navazny);
    QDomElement StopSequence2_4(QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int currentStopIndex, QVector<Prestup> seznamPrestupu);
    QString xxxProperty2_4(QString ikona, QString text, bool hodnota);
    QString priznakyDoStringu2_4(Zastavka zastavka);

private:

signals:

public slots:
};

#endif // XMLCOMMON_H
