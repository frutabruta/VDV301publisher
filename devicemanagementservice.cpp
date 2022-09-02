#include "devicemanagementservice.h"


DeviceManagementService::DeviceManagementService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
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
    // QByteArray zpracovanoMPV="";
    //QString bodyCurrentTariffStopResponse="";
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
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformation("LCD panel","vyrobce","123456789");


    }
    else
    {
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformation("LCD panel","vyrobce","123456789");


    }


    this->nastavObsahTela("DeviceInformation",bodyDeviceInformationResponse);

    this->asocPoleDoServeru(obsahTelaPole);

    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }

}

