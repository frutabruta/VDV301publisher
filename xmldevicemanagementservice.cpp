#include "xmldevicemanagementservice.h"

XmlDeviceManagementService::XmlDeviceManagementService()
{
    qDebug() <<  Q_FUNC_INFO;
    qDebug().noquote()<<"devifnormationtest "<<DeviceInformation("jmeno","vyrobce","XXX112233") ;
}


QString XmlDeviceManagementService::devStatus()
{
    qDebug() <<  Q_FUNC_INFO;
    QString  pozadavek ="";
    QString  hlavicka="";
    QString  telo="";
    QString  deviceState="running";
    QString  TgetDeviceStatusResponse="";
    QString  TgetDeviceStatusResponseData="";
    QString  TtimeStamp="";
    QString  TdeviceState="";

    TtimeStamp+="<TimeStamp>"+this->createTimestamp()+"</TimeStamp>";
    TdeviceState+="<DeviceState>"+deviceState+"</DeviceState>";
    TgetDeviceStatusResponseData+="<DeviceManagementService.GetDeviceStatusResponseData>"+TtimeStamp+TdeviceState+"</DeviceManagementService.GetDeviceStatusResponseData>";
    TgetDeviceStatusResponse+="<DeviceManagementService.GetDeviceStatusResponse>"+TgetDeviceStatusResponseData+"</DeviceManagementService.GetDeviceStatusResponse>";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    telo+=("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  ")+TgetDeviceStatusResponse;
    pozadavek=hlavicka+telo;
    return pozadavek;
}

QDomElement XmlDeviceManagementService::DeviceConfiguration()
{
    QDomElement vystup;
    QDomDocument xmlko;
    return vystup;
}

QDomElement XmlDeviceManagementService::DeviceConfigurationResponseDataStructure()
{
    QDomElement vystup;
    QDomDocument xmlko;

    vystup=xmlko.createElement("DeviceManagementService.GetDeviceConfigurationResponseData");
    vystup.appendChild(TimeStampTag1_0(xmlko));



    return vystup;
}

QString XmlDeviceManagementService::DeviceInformation(QString deviceName,QString manufacturer, QString serialNumber)
{
    QDomDocument xmlko;
    QDomElement vystup=xmlko.createElement("DeviceManagementService.GetDeviceInformationResponse");
    xmlko.appendChild(vystup);


    QDomElement getDeviceInformationData=xmlko.createElement("GetDeviceInformationData");

    getDeviceInformationData.appendChild(TimeStampTag1_0(xmlko));
    getDeviceInformationData.appendChild(DeviceInformationGroup(deviceName,manufacturer,serialNumber));
    vystup.appendChild(getDeviceInformationData);

    return xmlko.toString();
}

QDomElement XmlDeviceManagementService::DeviceInformationGroup(QString deviceName,QString manufacturer, QString serialNumber)
{
    QDomDocument xmlko;
    QDomElement vystup=xmlko.createElement("DeviceInformation");
    vystup.appendChild(DeviceName(deviceName));
    vystup.appendChild(Manufacturer(manufacturer));
    vystup.appendChild(SerialNumber(serialNumber));
    return vystup;
}

QDomElement XmlDeviceManagementService::DeviceName(QString vstup)
{
    QDomDocument xmlko;

    QDomElement vystup=Value(xmlko,"DeviceName",vstup);

    return vystup;
}

QDomElement XmlDeviceManagementService::DeviceStatus()
{
    QDomElement vystup;

    return vystup;
}


QDomElement XmlDeviceManagementService::Manufacturer(QString vstup)
{
    QDomDocument xmlko;
    QDomElement vystup=Value(xmlko,"Manufacturer",vstup);

    return vystup;
}

QDomElement XmlDeviceManagementService::SerialNumber(QString vstup)
{
    QDomDocument xmlko;
    QDomElement vystup=xmlko.createElement("SerialNumber");
    QDomElement value=xmlko.createElement("Value");
    value.appendChild(xmlko.createTextNode(vstup));
    vystup.appendChild(value);
    return vystup;
}

QDomElement XmlDeviceManagementService::Restart()
{
    QDomElement vystup;

    return vystup;
}

/*
<?xml version="1.0" encoding="utf-8"?>
<DeviceManagementService.GetDeviceInformationResponse>
    <DeviceManagementService.GetDeviceInformationResponseData>
        <TimeStamp>
            <Value>2019-08-02T10:04:20.1863897+02:00</Value>
        </TimeStamp>
        <DeviceInformation>
            <DeviceName>
                <Value>TFT_LCD</Value>
            </DeviceName>
            <Manufacturer>
                <Value>Bustec</Value>
            </Manufacturer>
            <SerialNumber>
                <Value>0</Value>
            </SerialNumber>
            <DeviceClass>InteriorDisplay</DeviceClass>
            <DataVersionList>
                <DataVersion>
                    <DataType>
                        <Value>SwVersion</Value>
                    </DataType>
                    <VersionRef>
                        <Value>0.11.1684.18065</Value>
                    </VersionRef>
                </DataVersion>
            </DataVersionList>
        </DeviceInformation>
    </DeviceManagementService.GetDeviceInformationResponseData>
</DeviceManagementService.GetDeviceInformationResponse>
*/
