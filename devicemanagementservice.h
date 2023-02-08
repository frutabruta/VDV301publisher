#ifndef DEVICEMANAGEMENTSERVICE_H
#define DEVICEMANAGEMENTSERVICE_H

#include "httpsluzba.h"
#include "xmldevicemanagementservice.h"

class DeviceManagementService : public HttpSluzba
{
public:
    explicit DeviceManagementService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);

    void aktualizaceObsahuSluzby();



    QMap<QString,QString> parametry;

    QString deviceName() const;
    void setDeviceName(const QString &newDeviceName);

    QString deviceManufacturer() const;
    void setDeviceManufacturer(const QString &newDeviceManufacturer);

    QString deviceSerialNumber() const;
    void setDeviceSerialNumber(const QString &newDeviceSerialNumber);

    QString deviceClass() const;
    void setDeviceClass(const QString &newDeviceClass);

    QString deviceId() const;
    void setDeviceId(const QString &newDeviceId);

    QString swVersion() const;
    void setSwVersion(const QString &newSwVersion);

public slots:
    void slotAktualizaceDat();
private:
    void aktualizaceIntProm();
    QString mDeviceName="";
    QString mDeviceManufacturer="";
    QString mDeviceSerialNumber="";
    QString mDeviceClass="";
    QString mDeviceId=0;
    QString mSwVersion="";

    XmlDeviceManagementService xmlGenerator;

};

#endif // DEVICEMANAGEMENTSERVICE_H
