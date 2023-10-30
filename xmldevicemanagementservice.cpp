#include "xmldevicemanagementservice.h"

XmlDeviceManagementService::XmlDeviceManagementService()
{
    qDebug() <<  Q_FUNC_INFO;
    // qDebug().noquote()<<"devifnormationtest "<<DeviceInformationResponse1_0("jmeno","vyrobce","XXX112233","InteriorDisplay","v1.2") ;
}



QDomElement XmlDeviceManagementService::DataVersionList1_0(QDomDocument &xmlDocument, QString tagName, QVector<DeviceDataVersion> dataVersionList )
{
    QDomElement output;
    output=xmlDocument.createElement(tagName);

    foreach (DeviceDataVersion selectedDataVersion, dataVersionList)
    {
        output.appendChild(DataVersionStructure1_0(xmlDocument,"DataVersion",selectedDataVersion));
    }

    return output;
}

QDomElement XmlDeviceManagementService::DataVersionStructure1_0(QDomDocument &xmlDocument, QString tagName, DeviceDataVersion dataVersion )
{
    QDomElement output;
    output=xmlDocument.createElement(tagName);

    output.appendChild(Value(xmlDocument,"DataType",dataVersion.dataType ));
    output.appendChild(Value(xmlDocument,"VersionRef",dataVersion.versionRef ));

    return output;
}

QDomElement XmlDeviceManagementService::DeviceClass1_0(QDomDocument &xmlDocument,QString vstup)
{

    QDomElement vystup=xmlDocument.createElement("DeviceClass");
    vystup.appendChild( xmlDocument.createTextNode(vstup));

    /*
    QDomElement result=xmlko.createElement(elementName); //verze 2.2CZ1.0
    result.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(content));
*/
    return vystup;
}

QString XmlDeviceManagementService::DeviceConfigurationResponseStructure1_0(QDomDocument xmlDocument, QString deviceId)
{
    qDebug() << Q_FUNC_INFO;
    xmlDocument.appendChild(createProcessingInformation(xmlDocument,mDefaultEncoding));
    QDomElement output;

    output=xmlDocument.createElement("DeviceManagementService.GetDeviceConfigurationResponse");
    xmlDocument.appendChild(output);
    output.appendChild(DeviceConfigurationResponseDataStructure1_0(xmlDocument,"DeviceManagementService.GetDeviceConfigurationResponseData",deviceId));
    QString outputString=xmlDocument.toString();
    qDebug()<<"test"<<outputString;
    return outputString;
}



QString XmlDeviceManagementService::DeviceStatusResponse1_0(QDomDocument xmlDocument, QString status)
{
    xmlDocument.appendChild(createProcessingInformation(xmlDocument,mDefaultEncoding));
    QDomElement output=xmlDocument.createElement("DeviceManagementService.GetDeviceStatusResponse");
    xmlDocument.appendChild(output);

    QDomElement getDeviceInformationData=xmlDocument.createElement("DeviceManagementService.GetDeviceStatusResponseData");

    getDeviceInformationData.appendChild(TimeStampTag1_0(xmlDocument));
    getDeviceInformationData.appendChild(DeviceStatus(xmlDocument,status));
    output.appendChild(getDeviceInformationData);

    return xmlDocument.toString();
}

QDomElement XmlDeviceManagementService::DeviceStatus(QDomDocument &xmlDocument,QString status)
{
    QDomElement output=xmlDocument.createElement("DeviceState");
    output.appendChild(xmlDocument.createTextNode(status));
    return output;
}



QDomElement XmlDeviceManagementService::DeviceConfigurationResponseDataStructure1_0(QDomDocument &xmlDocument,QString tagName, QString deviceId)
{
    QDomElement output;

    output=xmlDocument.createElement(tagName);
    output.appendChild(TimeStampTag1_0(xmlDocument));
    output.appendChild(Value(xmlDocument,"DeviceID",deviceId));

    return output;
}

QString XmlDeviceManagementService::DeviceInformationResponse1_0(QDomDocument xmlDocument, QString deviceName, QString manufacturer, QString serialNumber, QString deviceClass, QString swVersion)
{
    xmlDocument.appendChild(createProcessingInformation(xmlDocument,mDefaultEncoding));

    QDomElement output=xmlDocument.createElement("DeviceManagementService.GetDeviceInformationResponse");
    xmlDocument.appendChild(output);

    QDomElement getDeviceInformationData=xmlDocument.createElement("DeviceManagementService.GetDeviceInformationResponseData");

    getDeviceInformationData.appendChild(TimeStampTag1_0(xmlDocument));
    getDeviceInformationData.appendChild(DeviceInformationGroup1_0(xmlDocument,deviceName,manufacturer,serialNumber,deviceClass,swVersion));
    output.appendChild(getDeviceInformationData);

    return xmlDocument.toString();
}

QDomElement XmlDeviceManagementService::DeviceInformationGroup1_0(QDomDocument &xmlDocument, QString deviceName,QString manufacturer, QString serialNumber,QString deviceClass,QString swVersion)
{

    QDomElement output=xmlDocument.createElement("DeviceInformation");
    QVector<DeviceDataVersion> versionVector;

    DeviceDataVersion dataVersion;
    dataVersion.dataType="SwVersion";
    dataVersion.versionRef=swVersion;
    versionVector.append(dataVersion);

    output.appendChild(DeviceName1_0(xmlDocument,deviceName));
    output.appendChild(Manufacturer1_0(xmlDocument,manufacturer));
    output.appendChild(SerialNumber1_0(xmlDocument,serialNumber));
    output.appendChild(DeviceClass1_0(xmlDocument,deviceClass));
    output.appendChild(DataVersionList1_0(xmlDocument,"DataVersionList",versionVector));
    return output;
}

QDomElement XmlDeviceManagementService::DeviceName1_0(QDomDocument &xmlDocument,QString deviceName)
{
    QDomElement output=Value(xmlDocument,"DeviceName",deviceName);
    return output;
}



QDomElement XmlDeviceManagementService::Manufacturer1_0(QDomDocument &xmlDocument,QString manufacturerName)
{
    QDomElement output=Value(xmlDocument,"Manufacturer",manufacturerName);

    return output;
}

QDomElement XmlDeviceManagementService::SerialNumber1_0(QDomDocument &xmlDocument,QString vstup)
{
    QDomElement output=xmlDocument.createElement("SerialNumber");
    QDomElement value=xmlDocument.createElement("Value");
    value.appendChild(xmlDocument.createTextNode(vstup));
    output.appendChild(value);
    return output;
}

//work in progress
QDomElement XmlDeviceManagementService::Restart()
{
    QDomElement output;

    return output;
}
