#include "devicemanagementservice.h"


DeviceManagementService::DeviceManagementService(QString serviceName, QString serviceType, int portNumber,QString version):HttpService( serviceName,serviceType, portNumber,version)
{
    qDebug()<<Q_FUNC_INFO;
    // connect(timer, &QTimer::timeout, this, &CustomerInformationService::slotTedOdesliNaPanely);
    deviceStates.insert(StateDefective,"defective");
    deviceStates.insert(StateWarning,"warning");
    deviceStates.insert(StateNotavailable,"notavailable");
    deviceStates.insert(StateRunning,"running");
    deviceStates.insert(StateReadyForShutdown ,"readyForShutdown");




    updateInternalVariables();

    connect(this, &HttpService::signalParameterChange,this, &DeviceManagementService::slotSetParameters);
}



void DeviceManagementService::serviceContentUpdate() //deprecated?
{
    qDebug() <<  Q_FUNC_INFO;

}




void DeviceManagementService::updateInternalVariables()
{
    qDebug() <<  Q_FUNC_INFO<<" "<<mServiceName<<" "<<mVersion;

    QString bodyDeviceInformationResponse="";
    QString bodyAllSubdeviceInformationResponse="";
    QString bodyDeviceConfigurationResponse="";
    QString bodyDeviceStatusInformationResponse="";
    QString bodyAllSubdeviceStatusInformationResponse="";
    QString bodyDeviceErrorMessagesResponse="";
    QString bodyAllSubdeviceErrorMessagesResponse="";
    QString bodyServiceStatusResponse="";
    QString bodyRestartDeviceResponse="";

    if (mVersion=="2.2")
    {
        QDomDocument xmlDocument;
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformationResponse1_0(xmlDocument,mDeviceName,mDeviceManufacturer,mDeviceSerialNumber,mDeviceClass,mSwVersion);
        bodyDeviceConfigurationResponse=xmlGenerator.DeviceConfigurationResponseStructure1_0(xmlDocument,mDeviceId);
        bodyDeviceStatusInformationResponse=xmlGenerator.DeviceStatusResponse1_0(xmlDocument,deviceStates[mDeviceStatus] );
    }
    else
    {
        QDomDocument xmlDocument;
        bodyDeviceInformationResponse=xmlGenerator.DeviceInformationResponse1_0(xmlDocument,mDeviceName,mDeviceManufacturer,mDeviceSerialNumber,mDeviceClass,mSwVersion);
        bodyDeviceConfigurationResponse=xmlGenerator.DeviceConfigurationResponseStructure1_0(xmlDocument,mDeviceId);
        bodyDeviceStatusInformationResponse=xmlGenerator.DeviceStatusResponse1_0(xmlDocument,deviceStates[mDeviceStatus]);
    }

    this->setBodyContent("DeviceInformation",bodyDeviceInformationResponse);
    this->setBodyContent("DeviceConfiguration",bodyDeviceConfigurationResponse);
    this->setBodyContent("DeviceStatus",bodyDeviceStatusInformationResponse);

    this->updateServerContent(structureContentMap);

    for(int i=0;i<subscriberList.count();i++ )
    {
        postToSubscriber(subscriberList[i].address,structureContentMap.value(subscriberList[i].structure));
    }

}

DeviceManagementService::DeviceStatus DeviceManagementService::deviceStatus() const
{
    return mDeviceStatus;
}

void DeviceManagementService::setDeviceStatus(DeviceStatus newDeviceStatus)
{
    mDeviceStatus = newDeviceStatus;
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

void DeviceManagementService::slotDataUpdate()
{
    updateInternalVariables();
}

void DeviceManagementService::slotSetParameters(QMap<QString,QString> parameters)
{
    qDebug()<<Q_FUNC_INFO;
    qDebug()<<"list contains "<<parameters.count()<<" parameters";
    if(parameters.contains("DeviceID"))
    {
        mDeviceId=parameters["DeviceID"];
        qDebug()<<"setting ID: "<<mDeviceId;


    }
    updateInternalVariables();
    emit signalParametersChanged();
}
