#include "xmldevicemanagementservice.h"

XmlDeviceManagementService::XmlDeviceManagementService()
{
    qDebug() <<  Q_FUNC_INFO;
   // qDebug().noquote()<<"devifnormationtest "<<DeviceInformationResponse1_0("jmeno","vyrobce","XXX112233","InteriorDisplay","v1.2") ;
}



QDomElement XmlDeviceManagementService::DataVersionList1_0(QDomDocument xmlko, QString tagName, QVector<VerzeDat> verzeDat )
{
    QDomElement vystup;
    vystup=xmlko.createElement(tagName);

    foreach (VerzeDat jednaVerze, verzeDat)
    {
     vystup.appendChild(DataVersionStructure1_0(xmlko,"DataVersion",jednaVerze));
    }

    return vystup;
}

QDomElement XmlDeviceManagementService::DataVersionStructure1_0(QDomDocument xmlko, QString tagName, VerzeDat verzeDat )
{
    QDomElement vystup;
    vystup=xmlko.createElement(tagName);

    vystup.appendChild(Value(xmlko,"DataType",verzeDat.dataType ));
    vystup.appendChild(Value(xmlko,"VersionRef",verzeDat.versionRef ));

    return vystup;
}

QDomElement XmlDeviceManagementService::DeviceClass1_0(QString vstup)
{
    QDomDocument xmlko;

    QDomElement vystup=Value(xmlko,"DeviceClass",vstup);

    return vystup;
}

QString XmlDeviceManagementService::DeviceConfigurationResponseStructure1_0(QString deviceId)
{
    qDebug() << Q_FUNC_INFO;

    QDomDocument xmlko;
    QDomElement vystup;

    vystup=xmlko.createElement("DeviceManagementService.GetDeviceConfigurationResponse");
    xmlko.appendChild(vystup);
    vystup.appendChild(DeviceConfigurationResponseDataStructure1_0("DeviceManagementService.GetDeviceConfigurationResponseData",deviceId));
    QString retezec=xmlko.toString();
    qDebug()<<"test"<<retezec;
    return xmlko.toString();
}

QDomElement XmlDeviceManagementService::DeviceConfigurationResponseDataStructure1_0(QString tagName, QString deviceId)
{
    QDomElement vystup;
    QDomDocument xmlko;

    vystup=xmlko.createElement(tagName);
    vystup.appendChild(TimeStampTag1_0(xmlko));
    vystup.appendChild(Value(xmlko,"DeviceID",deviceId));

    return vystup;
}

QString XmlDeviceManagementService::DeviceInformationResponse1_0(QString deviceName,QString manufacturer, QString serialNumber,QString deviceClass,QString swVersion)
{
    QDomDocument xmlko;
    QDomElement vystup=xmlko.createElement("DeviceManagementService.GetDeviceInformationResponse");
    xmlko.appendChild(vystup);

    QDomElement getDeviceInformationData=xmlko.createElement("DeviceManagementService.GetDeviceInformationResponseData");

    getDeviceInformationData.appendChild(TimeStampTag1_0(xmlko));
    getDeviceInformationData.appendChild(DeviceInformationGroup1_0(deviceName,manufacturer,serialNumber,deviceClass,swVersion));
    vystup.appendChild(getDeviceInformationData);

    return xmlko.toString();
}

QDomElement XmlDeviceManagementService::DeviceInformationGroup1_0(QString deviceName,QString manufacturer, QString serialNumber,QString deviceClass,QString swVersion)
{
    QDomDocument xmlko;
    QDomElement vystup=xmlko.createElement("DeviceInformation");
    QVector<VerzeDat> versionVector;

   VerzeDat aktVerze;
   aktVerze.dataType="SwVersion";
   aktVerze.versionRef=swVersion;
   versionVector.append(aktVerze);

    vystup.appendChild(DeviceName1_0(deviceName));
    vystup.appendChild(Manufacturer1_0(manufacturer));
    vystup.appendChild(SerialNumber1_0(serialNumber));
    vystup.appendChild(DeviceClass1_0(deviceClass));
    vystup.appendChild(DataVersionList1_0(xmlko,"DataVersionList",versionVector));
    return vystup;
}

QDomElement XmlDeviceManagementService::DeviceName1_0(QString vstup)
{
    QDomDocument xmlko;

    QDomElement vystup=Value(xmlko,"DeviceName",vstup);

    return vystup;
}

QDomElement XmlDeviceManagementService::DeviceStatus()
{
    QDomElement vystup;

    return vystup;
}


QDomElement XmlDeviceManagementService::Manufacturer1_0(QString vstup)
{
    QDomDocument xmlko;
    QDomElement vystup=Value(xmlko,"Manufacturer",vstup);

    return vystup;
}

QDomElement XmlDeviceManagementService::SerialNumber1_0(QString vstup)
{
    QDomDocument xmlko;
    QDomElement vystup=xmlko.createElement("SerialNumber");
    QDomElement value=xmlko.createElement("Value");
    value.appendChild(xmlko.createTextNode(vstup));
    vystup.appendChild(value);
    return vystup;
}

QDomElement XmlDeviceManagementService::Restart()
{
    QDomElement vystup;

    return vystup;
}
