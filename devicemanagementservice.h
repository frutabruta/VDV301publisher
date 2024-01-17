#ifndef DEVICEMANAGEMENTSERVICE_H
#define DEVICEMANAGEMENTSERVICE_H

#include "httpservice.h"
#include "xmldevicemanagementservice.h"






class DeviceManagementService : public HttpService
{
    Q_OBJECT
public:


    explicit DeviceManagementService(QString serviceName, QString serviceType, int portNumber, QString version);

    enum DeviceStatus
    {
        StateDefective, // 1.0
        StateWarning, // added in 2.2
        StateNotavailable, // 1.0
        StateRunning, //1.0
        StateReadyForShutdown // added in 2.2
    };


    void serviceContentUpdate();

    QMap<int,QString> deviceStates;



   // QMap<QString,QString> parametry;

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

    void setDeviceStatus(DeviceStatus newDeviceStatus);

    DeviceStatus deviceStatus() const;

public slots:
    void slotDataUpdate();
private slots:
    void slotSetParameters(QMap<QString, QString> parameters);

private:
    void updateInternalVariables();
    QString mDeviceName="";
    QString mDeviceManufacturer="";
    QString mDeviceSerialNumber="";
    QString mDeviceClass="";
    QString mDeviceId=0;
    QString mSwVersion="";
    DeviceStatus mDeviceStatus=StateRunning;

    XmlDeviceManagementService xmlGenerator;
signals:
    void signalParametersChanged();
};

#endif // DEVICEMANAGEMENTSERVICE_H
