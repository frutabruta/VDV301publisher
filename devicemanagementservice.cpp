#include "devicemanagementservice.h"


DeviceManagementService::DeviceManagementService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
    qDebug()<<Q_FUNC_INFO;
    // connect(timer, &QTimer::timeout, this, &CustomerInformationService::slotTedOdesliNaPanely);
    aktualizaceIntProm();

    connect(this, &HttpSluzba::signalZmenaParametru,this, &DeviceManagementService::slotNastavParametry);
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
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformationResponse1_0(mDeviceName,mDeviceManufacturer,mDeviceSerialNumber,mDeviceClass,mSwVersion);
        bodyDeviceConfigurationResponse=xmlGenerator.DeviceConfigurationResponseStructure1_0(mDeviceId);
        bodyDeviceStatusInformationResponse=xmlGenerator.DeviceStatusResponse1_0("running");
    }
    else
    {
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformationResponse1_0(mDeviceName,mDeviceManufacturer,mDeviceSerialNumber,mDeviceClass,mSwVersion);
        bodyDeviceConfigurationResponse=xmlGenerator.DeviceConfigurationResponseStructure1_0(mDeviceId);
        bodyDeviceStatusInformationResponse=xmlGenerator.DeviceStatusResponse1_0("running");
    }

    this->nastavObsahTela("DeviceInformation",bodyDeviceInformationResponse);
    this->nastavObsahTela("DeviceConfiguration",bodyDeviceConfigurationResponse);
    this->nastavObsahTela("DeviceStatus",bodyDeviceStatusInformationResponse);

    this->asocPoleDoServeru(obsahTelaPole);

    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i].adresa,obsahTelaPole.value(seznamSubscriberu[i].struktura));
    }

}

QString DeviceManagementService::swVersion() const
{
    return mSwVersion;
}

void DeviceManagementService::setSwVersion(const QString &newSwVersion)
{
    mSwVersion = StringToNmToken(newSwVersion);
}




QString DeviceManagementService::deviceId() const
{
    return mDeviceId;
}

void DeviceManagementService::setDeviceId(const QString &newDeviceId)
{
    mDeviceId = newDeviceId;
}

QString DeviceManagementService::deviceClass() const
{
    return mDeviceClass;
}

void DeviceManagementService::setDeviceClass(const QString &newDeviceClass)
{
    mDeviceClass = newDeviceClass;
}

QString DeviceManagementService::deviceSerialNumber() const
{
    return mDeviceSerialNumber;
}

void DeviceManagementService::setDeviceSerialNumber(const QString &newDeviceSerialNumber)
{
    mDeviceSerialNumber = newDeviceSerialNumber;
}

QString DeviceManagementService::deviceManufacturer() const
{
    return mDeviceManufacturer;
}

void DeviceManagementService::setDeviceManufacturer(const QString &newDeviceManufacturer)
{
    mDeviceManufacturer = newDeviceManufacturer;
}

QString DeviceManagementService::deviceName() const
{
    return mDeviceName;
}

void DeviceManagementService::setDeviceName(const QString &newDeviceName)
{
    mDeviceName = newDeviceName;
}

void DeviceManagementService::slotAktualizaceDat()
{
    aktualizaceIntProm();
}

void DeviceManagementService::slotNastavParametry(QMap<QString,QString> parametry)
{
    qDebug()<<Q_FUNC_INFO;
    qDebug()<<"seznam obsahuje "<<parametry.count()<<" parametru";
    if(parametry.contains("DeviceID"))
    {
        mDeviceId=parametry["DeviceID"];
        qDebug()<<"nastavuji ID: "<<mDeviceId;


    }
    aktualizaceIntProm();
    emit signalZmenaParametruVen();
}
