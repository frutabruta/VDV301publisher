#ifndef DEVICEMANAGEMENTSERVICE_H
#define DEVICEMANAGEMENTSERVICE_H

#include "httpsluzba.h"
#include "xmldevicemanagementservice.h"

class DeviceManagementService : public HttpSluzba
{
public:
    explicit DeviceManagementService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    void aktualizaceObsahuSluzby();

    QString deviceName="";
    QString deviceManufacturer="";
    QString deviceSerialNumber="";
    QString deviceClass="";
    QString deviceId=0;
    QString swVersion="";

    QMap<QString,QString> parametry;

public slots:
    void slotAktualizaceDat();
private:
    void aktualizaceIntProm();

    XmlDeviceManagementService xmlGenerator;

};

#endif // DEVICEMANAGEMENTSERVICE_H
