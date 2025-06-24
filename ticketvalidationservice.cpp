#include "ticketvalidationservice.h"



TicketValidationService::TicketValidationService(QString serviceName, QString serviceType, int portNumber,QString version):HttpService( serviceName,serviceType, portNumber,version)
{
    connect(&timer, &QTimer::timeout, this, &TicketValidationService::slotSendDataToSubscribers);
    timer.start(60000);

}




void TicketValidationService::updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<StopPointDestination>  stopDestinationList ) //novy
{
    qDebug()<<Q_FUNC_INFO<<" "<<mServiceName<<" "<<mVersion;
    // QByteArray zpracovanoMPV="";
    QString bodyCurrentTariffStopResponse="";
    QString bodyVehicleDataResponse="";
    QString bodyRazziaResponse="";
    
    
    
    if(mVersion=="1.0")
    {

    }
    else if (mVersion=="2.2CZ1.0")
    {
        qDebug()<<"VERISON 2.2CZ1.0 IS DEPRACATED";
        /*
        QDomDocument xmlDocument;
        bodyCurrentTariffStopResponse=xmlGenerator2_2CZ1_0.TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(xmlDocument,vehicleState.currentStopIndex0,stopDestinationList,connectionList);
        bodyVehicleDataResponse=xmlGenerator2_2CZ1_0.TicketValidationService_GetVehicleDataResponse2_2CZ1_0(xmlDocument,vehicleState);
        bodyRazziaResponse=xmlGenerator2_2CZ1_0.TicketValidationService_GetRazziaResponse2_2CZ1_0(xmlDocument,vehicleState);
*/
    }
    else if(mVersion=="2.3")
    {

    }
    else if(mVersion=="2.3CZ1.0")
    {

    }

    else
    {
        qDebug()<<"unsupported version!";
    }


    this->setBodyContent("CurrentTariffStopResponse",bodyCurrentTariffStopResponse);
    this->setBodyContent("VehicleDataResponse",bodyVehicleDataResponse);
    this->setBodyContent("RazziaResponse",bodyRazziaResponse);
    this->updateServerContent(structureContentMap);

    for(int i=0;i<subscriberList.count();i++ )
    {
        postToSubscriber(subscriberList[i].address,structureContentMap.value(subscriberList[i].structure));
    }

}



void TicketValidationService::slotSendDataToSubscribers()
{
    qDebug()<<Q_FUNC_INFO;
    updateInternalVariables( mConnectionList,mVehicleState, mStopPointDestinationList);
}

void TicketValidationService::updateServiceContent(QVector<Connection> connectionList, VehicleState &vehicleState ) //novy
{
    qDebug()<<Q_FUNC_INFO;
    mConnectionList =connectionList;
    mVehicleState=vehicleState;
    if(!vehicleState.currentVehicleRun.tripList.isEmpty())
    {
        mStopPointDestinationList=vehicleState.currentVehicleRun.tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;
    }
    else
    {
        mStopPointDestinationList.clear();
    }

    slotSendDataToSubscribers();
    timer.start(60000);
}


