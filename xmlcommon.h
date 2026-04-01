#ifndef XMLCOMMON_H
#define XMLCOMMON_H
#include <QMainWindow>
#include <QObject>
#include <QTime>
#include <QCoreApplication>
#include <QtDebug>
#include <QtXml>
#include <QDomDocument>


#include "colordisplayrules.h"
#include "VDV301DataStructures/vdv301internationaltext.h"


class XmlCommon : public QObject
{
    Q_OBJECT
public:

    ColorDisplayRules colorDisplayRules;

    XmlCommon();

    //constants
    QString defaultLanguage1_0="de";
    QString defaultLanguage2_2CZ1_0="cs";
    QString defaultLanguage2_3="cs";
    QString defaultLanguage2_3CZ1_0="cs";
    QString mDefaultEncoding="utf-8";


    //pomocneFce
    QString createTimestamp();
    QDomElement internationalTextTypeToDom(QDomDocument &xmlDocument, QString name, QString value, QString language);

    QDomElement rawInsert(QString input); //unused
    QDomElement ref(QDomDocument &xmlDocument, QString name, QString value);
    QDomProcessingInstruction createProcessingInformation(QDomDocument &xmlDocument, QString encoding);


    //VDV301 struktury
    QDomElement AdditionalTextMessage1_0(QString messageContent, bool isScrolling);


     QDomElement DoorOpenState(QDomDocument &xmlDocument, QString content);

    QDomElement FareZone1_0(QDomDocument &xmlDocument, QString shortName);

    QDomElement MyOwnVehicleMode(QDomDocument &xmlDocument, QString mode, QString subMode);


    QDomElement RouteDeviation(QDomDocument &xmlDocument, QString content);

    QDomElement TimeStampTag1_0(QDomDocument &xmlDocument);
     QDomElement Value(QDomDocument &xmlDocument, QString elementName, QString content);

    //WORK IN PROGRESS
    QString escapeHtml(QString input); //unused
    QDateTime qTimeToQDateTimeToday(QTime input);
    QString qDomDocumentToQString(QDomDocument &input);
    QString qStringXmlEscape(QString input);

    QDomElement namedElement(QDomDocument &xmlDocument, QString name, QString value); //unused

    int isInRange(int index, int valueCount, QString nameOfFunction);

    QDomElement internationalTextTypeToDom(QDomDocument &xmlDocument, QString name, Vdv301InternationalText internationalText);

    QString qTimeToQDateTimeTodayQString(QTime input);
private:

    QDomCDATASection createEscapedValueCdata(QDomDocument &document, QString input);


public slots:
signals:
    void signalErrorMessage(QString message);

};

#endif // XMLCOMMON_H
