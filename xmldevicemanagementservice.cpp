#include "xmldevicemanagementservice.h"

XmlDeviceManagementService::XmlDeviceManagementService()
{

}


QString XmlDeviceManagementService::devStatus()
{
    qDebug()<<" XmlCommon::devStatus ";
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
