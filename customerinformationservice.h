#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpservice.h"

#include "xmlcustomerinformationservice.h"
/*
enum DeviceState
*/
class CustomerInformationService : public HttpService
{
public:
    //constructor
    explicit CustomerInformationService(QString serviceName, QString serviceType, int portNumber, QString version);

    //functions
    void updateServiceContent(QVector<Connection> connectionList, VehicleState &vehicleState);
    void outOfService();

private:
    //instance trid
    XmlCustomerInformationService xmlGenerator;
    //variables
    QVector<Connection> mConnectionList;
    QVector<Trip> mTripList;
    VehicleState mVehicleState;

    //functions
    void updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<Trip> tripList );
    void updateInternalVariablesEmpty(VehicleState &vehicleState, QVector<Trip> tripList);


public slots:
    void slotSendDataToSubscribers();

signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
