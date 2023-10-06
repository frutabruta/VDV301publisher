#ifndef TICKETVALIDATIONSERVICE_H
#define TICKETVALIDATIONSERVICE_H

#include "httpservice.h"
#include "xmlticketvalidationservice.h"
#include "VDV301DataStructures/connectionmpv.h"

class TicketValidationService : public HttpService
{
public:
    //konstruktor
    TicketValidationService();
    explicit TicketValidationService(QString serviceName, QString serviceType, int portNumber, QString version);


    //instance knihoven


    //promenne


    //funkce
    void updateServiceContent(QVector<Connection> connectionList, VehicleState &vehicleState);


private:

    //instance knihoven
    XmlTicketValidationService xmlGenerator;

    //variables
    VehicleState mVehicleState;
    QVector<StopPointDestination> mStopPointDestinationList ;

    //functions
    void updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<StopPointDestination> stopDestinationList);

    QVector<Connection> mConnectionList;

private slots:
    void slotSendDataToSubscribers();
};

#endif // TICKETVALIDATIONSERVICE_H
