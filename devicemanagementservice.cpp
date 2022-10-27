#include "devicemanagementservice.h"


DeviceManagementService::DeviceManagementService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
    qDebug()<<Q_FUNC_INFO;
    // connect(timer, &QTimer::timeout, this, &CustomerInformationService::slotTedOdesliNaPanely);
    aktualizaceIntProm();

}

void DeviceManagementService::aktualizaceObsahuSluzby()
{
qDebug() <<  Q_FUNC_INFO;

}




void DeviceManagementService::aktualizaceIntProm()
{
    qDebug() <<  Q_FUNC_INFO<<" "<<nazevSluzbyInterni<<" "<<globVerze;

    QString bodyDeviceInformationResponse="";
    QString bodyAllSubdeviceInformationResponse="";
    QString bodyDeviceConfigurationResponse="";
    QString bodyDeviceStatusInformationResponse="";
    QString bodyAllSubdeviceStatusInformationResponse="";
    QString bodyDeviceErrorMessagesResponse="";
    QString bodyAllSubdeviceErrorMessagesResponse="";
    QString bodyServiceStatusResponse="";
    QString bodyRestartDeviceResponse="";

    if (globVerze=="2.2CZ1.0")
    {
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformationResponse1_0(deviceName,deviceManufacturer,deviceSerialNumber,deviceClass,swVersion);
        bodyDeviceConfigurationResponse=xmlGenerator.DeviceConfigurationResponseStructure1_0(deviceId);
    }
    else
    {
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformationResponse1_0(deviceName,deviceManufacturer,deviceSerialNumber,deviceClass,swVersion);
        bodyDeviceConfigurationResponse=xmlGenerator.DeviceConfigurationResponseStructure1_0(deviceId);
    }

    this->nastavObsahTela("DeviceInformation",bodyDeviceInformationResponse);
    this->nastavObsahTela("DeviceConfiguration",bodyDeviceConfigurationResponse);

    this->asocPoleDoServeru(obsahTelaPole);

    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }

}

void DeviceManagementService::slotAktualizaceDat()
{
    aktualizaceIntProm();
}

