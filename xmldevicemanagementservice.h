#ifndef XMLDEVICEMANAGEMENTSERVICE_H
#define XMLDEVICEMANAGEMENTSERVICE_H
#include "xmlcommon.h"

class VerzeDat
{
public:
    QString dataType="";
    QString versionRef="";
};

class XmlDeviceManagementService : XmlCommon
{
public:
    XmlDeviceManagementService();
    QString DeviceInformationResponse1_0(QString deviceName, QString manufacturer, QString serialNumber, QString deviceClass, QString swVersion);
    QString DeviceConfigurationResponseStructure1_0(QString deviceId);
    QDomElement DeviceStatus();
    QDomElement Restart();
    QDomElement DeviceInformationGroup1_0(QString name, QString manufacturer, QString serialNumber, QString deviceClass, QString swVersion);
    QDomElement DeviceName1_0(QString vstup);
    QDomElement Manufacturer1_0(QString vstup);
    QDomElement SerialNumber1_0(QString vstup);
    QDomElement DeviceConfigurationResponseDataStructure1_0(QString tagName, QString deviceId);
    QDomElement DeviceClass1_0(QString vstup);
    QDomElement DataVersionStructure1_0(QDomDocument xmlko, QString tagName, VerzeDat verzeDat);
    QDomElement DataVersionList1_0(QDomDocument xmlko, QString tagName, QVector<VerzeDat> verzeDat);
private:

};

#endif // XMLDEVICEMANAGEMENTSERVICE_H
