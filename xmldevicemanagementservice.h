#ifndef XMLDEVICEMANAGEMENTSERVICE_H
#define XMLDEVICEMANAGEMENTSERVICE_H
#include "xmlcommon.h"


class XmlDeviceManagementService : XmlCommon
{
public:
    XmlDeviceManagementService();
    QString devStatus();
    QString DeviceInformation(QString deviceName, QString manufacturer, QString serialNumber);
    QDomElement DeviceConfiguration();
    QDomElement DeviceStatus();
    QDomElement Restart();
    QDomElement DeviceInformationGroup(QString name, QString manufacturer, QString serialNumber);
    QDomElement DeviceName(QString vstup);
    QDomElement Manufacturer(QString vstup);
    QDomElement SerialNumber(QString vstup);
private:

};

#endif // XMLDEVICEMANAGEMENTSERVICE_H
