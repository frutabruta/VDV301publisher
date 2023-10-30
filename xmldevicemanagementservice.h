#ifndef XMLDEVICEMANAGEMENTSERVICE_H
#define XMLDEVICEMANAGEMENTSERVICE_H
#include "xmlcommon.h"

class DeviceDataVersion
{
public:
    QString dataType="";
    QString versionRef="";
};

class XmlDeviceManagementService : XmlCommon
{
public:
    XmlDeviceManagementService();
    QString DeviceInformationResponse1_0(QDomDocument xmlDocument, QString deviceName, QString manufacturer, QString serialNumber, QString deviceClass, QString swVersion);
    QString DeviceConfigurationResponseStructure1_0(QDomDocument xmlDocument, QString deviceId);
    QString DeviceStatusResponse1_0(QDomDocument xmlDocument, QString status);
    QDomElement DeviceStatus(QDomDocument &xmlDocument, QString status);
    QDomElement Restart();
    QDomElement DeviceInformationGroup1_0(QDomDocument &xmlDocument, QString name, QString manufacturer, QString serialNumber, QString deviceClass, QString swVersion);
    QDomElement DeviceName1_0(QDomDocument &xmlDocument, QString deviceName);
    QDomElement Manufacturer1_0(QDomDocument &xmlDocument, QString manufacturerName);
    QDomElement SerialNumber1_0(QDomDocument &xmlDocument, QString vstup);
    QDomElement DeviceConfigurationResponseDataStructure1_0(QDomDocument &xmlDocument,QString tagName, QString deviceId);
    QDomElement DeviceClass1_0(QDomDocument &xmlDocument, QString vstup);
    QDomElement DataVersionStructure1_0(QDomDocument &xmlDocument, QString tagName, DeviceDataVersion dataVersion);
    QDomElement DataVersionList1_0(QDomDocument &xmlDocument, QString tagName, QVector<DeviceDataVersion> dataVersionList);

private:

};

#endif // XMLDEVICEMANAGEMENTSERVICE_H
