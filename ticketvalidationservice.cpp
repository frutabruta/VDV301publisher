#include "ticketvalidationservice.h"



TicketValidationService::TicketValidationService(QString serviceName, QString serviceType, int portNumber, QString version, QString serviceNamePostfix):HttpService( serviceName,serviceType, portNumber,version,serviceNamePostfix)
{
    connect(&timer, &QTimer::timeout, this, &TicketValidationService::slotSendDataToSubscribers);
    timer.start(60000);

}




void TicketValidationService::updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<StopPointDestination>  stopDestinationList ) //novy
{
    qDebug()<<Q_FUNC_INFO<<" "<<mServiceName<<" "<<mVersion;
    mConnectionList=connectionList;
    mVehicleState=vehicleState;
    mStopPointDestinationList=stopDestinationList;

    // QByteArray zpracovanoMPV="";
    QString bodyCurrentTariffStopResponse="";
    QString bodyVehicleDataResponse="";
    QString bodyRazziaResponse="";
    
    
    
    if(mVersion=="1.0")
    {
        qDebug()<<"VERSION "<<mVersion<<" NOT IMPLEMENTED";
    }
    else if (mVersion=="2.2CZ1.0")
    {
        qDebug()<<"VERSION 2.2CZ1.0 IS DEPRACATED";
        /*
        QDomDocument xmlDocument;
        bodyCurrentTariffStopResponse=xmlGenerator2_2CZ1_0.TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(xmlDocument,vehicleState.currentStopIndex0,stopDestinationList,connectionList);
        bodyVehicleDataResponse=xmlGenerator2_2CZ1_0.TicketValidationService_GetVehicleDataResponse2_2CZ1_0(xmlDocument,vehicleState);
        bodyRazziaResponse=xmlGenerator2_2CZ1_0.TicketValidationService_GetRazziaResponse2_2CZ1_0(xmlDocument,vehicleState);
*/
    }
    else if (mVersion=="2.2")
    {
        QDomDocument xmlDocument;

        bool isCurrentStopEmpty=true;
        StopPointDestination currentStop=mVehicleState.getCurrentStopPointDestination(isCurrentStopEmpty);


        Vdv301VehicleData vehicleData=xmlGenerator2_2.vehicleData(vehicleState);
        if(!isCurrentStopEmpty)
        {
            QVector<Vdv301Connection> emptyConnectionList;
            Vdv301StopPoint stopPoint=xmlGenerator2_2.StopPoint2_3new(
                mStopPointDestinationList,
                mVehicleState.currentStopIndex0,
                emptyConnectionList,
                xmlGenerator2_2.defaultLanguage2_3,
                mVehicleState.currentStopIndex0+1 );

            bodyCurrentTariffStopResponse=xmlGenerator2_2.currentTariffStopGen(
                xmlDocument,
                stopPoint,
                mVehicleState.currentTrip.ref());
        }
        else
        {
            bodyCurrentTariffStopResponse="";
        }

        bodyRazziaResponse=xmlGenerator2_2.razziaGen(xmlDocument,mVehicleState.razziaState);
        bodyVehicleDataResponse=xmlGenerator2_2.vehicleDataGen(xmlDocument,vehicleData);

        //bodyCurrentTariffStopResponse=xmlGenerator2_2.TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(xmlDocument,vehicleState.currentStopIndex0,stopDestinationList,connectionList);
        //bodyVehicleDataResponse=xmlGenerator2_2.TicketValidationService_GetVehicleDataResponse2_2CZ1_0(xmlDocument,vehicleState);
        //bodyRazziaResponse=xmlGenerator2_2.TicketValidationService_GetRazziaResponse2_2CZ1_0(xmlDocument,vehicleState);

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
        qDebug()<<"VERSION "<<mVersion<<" NOT IMPLEMENTED";
    }
    else if(mVersion=="2.3CZ1.0")
    {
        qDebug()<<"VERSION "<<mVersion<<" NOT IMPLEMENTED";
    }

    else
    {
        qDebug()<<"unsupported version!";
    }


    this->setBodyContent("CurrentTariffStop",bodyCurrentTariffStopResponse);
    this->setBodyContent("VehicleData",bodyVehicleDataResponse);
    this->setBodyContent("Razzia",bodyRazziaResponse);
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
    mConnectionList=connectionList;
    mVehicleState=vehicleState;
    if(!vehicleState.currentVehicleRun.tripList.isEmpty())
    {
        mStopPointDestinationList=vehicleState.getCurrentTrip().globalStopPointDestinationList;
    }
    else
    {
        mStopPointDestinationList.clear();
    }

    slotSendDataToSubscribers();
    timer.start(60000);
}


