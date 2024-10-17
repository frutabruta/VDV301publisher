#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H

#include "httpservice.h"
#include "xmlcustomerinformationservice.h"
#include "xmlcustomerinformationservice2_2cz1_0.h"
#include "xmlcustomerinformationservice2_3.h"
#include "xmlcustomerinformationservice2_3cz1_0.h"

class CustomerInformationService : public HttpService
{
public:
    //constructor
    explicit CustomerInformationService(QString serviceName, QString serviceType, int portNumber, QString version);

    //functions
    void updateServiceContent(QVector<Connection> connectionList, VehicleState &vehicleState);
    void outOfService();

    void setGlobalDisplayContentList(const QVector<Vdv301DisplayContent> &newGlobalDisplayContentList);

private:
    //instance trid
    XmlCustomerInformationService xmlGenerator;
    XmlCustomerInformationService2_2CZ1_0 xmlGenerator2_2CZ1_0;
    XmlCustomerInformationService2_3 xmlGenerator2_3;
    XmlCustomerInformationService2_3CZ1_0 xmlGenerator2_3CZ1_0;
    //variables
    QVector<Connection> mConnectionList;
    QVector<Trip> mTripList;
    QVector<Vdv301DisplayContent> mGlobalDisplayContentList;
    VehicleState mVehicleState;


    //functions
    void updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<Trip> tripList , QVector<Vdv301DisplayContent> globalDisplayContentList);
    void updateInternalVariablesEmpty(VehicleState &vehicleState, QVector<Trip> tripList, QVector<Vdv301DisplayContent> globalDisplayContentList);


public slots:
    void slotSendDataToSubscribers();

signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
