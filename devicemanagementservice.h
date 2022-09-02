#ifndef DEVICEMANAGEMENTSERVICE_H
#define DEVICEMANAGEMENTSERVICE_H

#include "httpsluzba.h"
#include "xmldevicemanagementservice.h"

class DeviceManagementService : public HttpSluzba
{
public:
    explicit DeviceManagementService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);


    XmlDeviceManagementService xmlGenerator;

    void aktualizaceIntProm();
private:

};

#endif // DEVICEMANAGEMENTSERVICE_H
