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












QDomElement XmlCommon::TimeStampTag1_0(QDomDocument &xmlDocument)
{
    QDomElement dTimeStamp=Value(xmlDocument,"TimeStamp",this->createTimestamp());
    return dTimeStamp;

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


QString XmlCommon::qTimeToQDateTimeTodayQString(QTime input)
{
    // over midnight fix is not implemented!

    if(input.isValid())
    {
        QDateTime output;
        output=QDateTime::currentDateTime();
        output.setTime(input);
        return output.toString("yyyy-MM-ddThh:mm:ss");
    }

    return "";
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
