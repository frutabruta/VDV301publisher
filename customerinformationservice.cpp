#include "customerinformationservice.h"
#include "httpservice.h"


/*!
 * \brief CustomerInformationService::CustomerInformationService
 * \param nazevSluzby
 * \param typSluzby
 * \param cisloPortu
 * \param verze
 */
CustomerInformationService::CustomerInformationService(QString serviceName, QString serviceType, int portNumber,QString version):HttpService( serviceName,serviceType, portNumber,version)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<serviceName<<" "<<version;
    connect(&timer, &QTimer::timeout, this, &CustomerInformationService::slotSendDataToSubscribers);

    //filling of empty data structures

    outOfService();
    //start of periodic data sending
    timer.start(60000);

}



/*!
 * \brief CustomerInformationService::aktualizaceIntProm
 * \param prestupy
 * \param stav
 * \param seznamSpoju
 */
void CustomerInformationService::updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<Trip>  tripList, QVector<Vdv301DisplayContent> globalDisplayContentList ) //novy
{
    qDebug() <<  Q_FUNC_INFO<<" "<<mServiceName<<" "<<mVersion;
    qDebug()<<"velikost seznamTripu"<<tripList.size()<<" index"<<vehicleState.currentTripIndex;

    QVector<StopPointDestination>  stopPointDestinationList;


    if (tripList.isEmpty())
    {
        qDebug()<<"current triplist is empty";

    }
    else
    {
        if(isInRange(vehicleState.currentTripIndex,tripList.count(),Q_FUNC_INFO))
        {
            stopPointDestinationList=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;
        }
    }

    /*
    if(!MainWindowPomocne::jeVRozsahu(stav.indexSpojeNaObehu,seznamSpoju.size(),"CustomerInformationService::aktualizaceIntProm"))
    {
        return;
    }
    */



    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";
    
    if (mVersion=="2.2CZ1.0")
    {
        qDebug()<<"VERSION 2.2CZ1.0 IS DEPRECATED";
    }
    else if (mVersion=="2.3")
    {
        //Work in progress
        QDomDocument xmlDocument;
        //special options for XML in this version can be placed here




        Vdv301AllData vdv301allData=xmlGenerator2_3new.AllData2_3new(tripList,connectionList,vehicleState,globalDisplayContentList);

        QDomDocument xmlDocument2;
        bodyAllData=xmlGenerator2_3new.AllData2_3gen(xmlDocument2,vdv301allData);
        // bodyCurrentDisplayContent=xmlGenerator2_3new.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);
        QVector<Vdv301DisplayContent> currentDisplayContentList=xmlGenerator2_3new.CurrentDisplayContentFromAllData2_3new(vdv301allData);
        bodyCurrentDisplayContent=xmlGenerator2_3new.CurrentDisplayContent2_3gen(xmlDocument,currentDisplayContentList);

        // bodyAllData=xmlGenerator2_3.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);
        // bodyCurrentDisplayContent=xmlGenerator2_3.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);

    }
    else if (mVersion=="2.3CZ1.0")
    {
        //Work in progress
        QDomDocument xmlDocument;
        //special options for XML in this version can be placed here

        // bodyCurrentDisplayContent=xmlGenerator2_3CZ1_0.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);

        Vdv301AllData2_3CZ1_0 vdv301allData=xmlGenerator2_3CZ1_0.AllData2_3CZ1_0new(tripList,connectionList,vehicleState,globalDisplayContentList);

        QDomDocument xmlDocument2;
        bodyAllData=xmlGenerator2_3CZ1_0.AllData2_3CZ1_0gen(xmlDocument2,vdv301allData);

        QVector<Vdv301DisplayContent> currentDisplayContentList=xmlGenerator2_3CZ1_0.CurrentDisplayContentFromAllData2_3new(vdv301allData);
        bodyCurrentDisplayContent=xmlGenerator2_3CZ1_0.CurrentDisplayContent2_3gen(xmlDocument,currentDisplayContentList);


    }
    else
    {
        // Version 1.0!

        //     bodyAllData=xmlGenerator.AllData1_0(xmlDocument,tripList,connectionList,vehicleState);
        //     bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent1_0(xmlDocument,stopPointDestinationList,vehicleState);


        //Work in progress
        QDomDocument xmlDocument;
        //special options for XML in this version can be placed here




        Vdv301AllData vdv301allData=xmlGenerator1_0new.AllData1_0new(tripList,connectionList,vehicleState,globalDisplayContentList);

        QDomDocument xmlDocument2;
        bodyAllData=xmlGenerator1_0new.AllData1_0gen(xmlDocument2,vdv301allData);
        // bodyCurrentDisplayContent=xmlGenerator2_3new.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);
        QVector<Vdv301DisplayContent> currentDisplayContentList=xmlGenerator1_0new.CurrentDisplayContentFromAllData1_0new(vdv301allData);
        bodyCurrentDisplayContent=xmlGenerator1_0new.CurrentDisplayContent1_0gen(xmlDocument,currentDisplayContentList);

        // bodyAllData=xmlGenerator2_3.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);
        // bodyCurrentDisplayContent=xmlGenerator2_3.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);

    }

    this->setBodyContent("AllData",bodyAllData);
    this->setBodyContent("CurrentDisplayContent",bodyCurrentDisplayContent);


    updateStructureMap();

}


/*!
 * \brief CustomerInformationService::updateServiceContent
 * \param prestup
 * \param stav
 */
void CustomerInformationService::updateServiceContent(QVector<Connection> connectionList, VehicleState &vehicleState ) //novy
{
    qDebug() <<  Q_FUNC_INFO;
    mConnectionList=connectionList;
    mVehicleState=vehicleState;
    mTripList=vehicleState.currentVehicleRun.tripList;
    slotSendDataToSubscribers();
    timer.start(60000);
}


void CustomerInformationService::outOfService()
{
    qDebug() <<  Q_FUNC_INFO;
    // updateInternalVariablesEmpty(mVehicleState,mTripList,mGlobalDisplayContentList);
    updateInternalVariables(mConnectionList,mVehicleState,mTripList,mGlobalDisplayContentList);
}

void CustomerInformationService::setGlobalDisplayContentList(const QVector<Vdv301DisplayContent> &newGlobalDisplayContentList)
{
    mGlobalDisplayContentList = newGlobalDisplayContentList;
}


/*!
 * \brief CustomerInformationService::slotTedOdesliNaPanely
 */

void CustomerInformationService::slotSendDataToSubscribers()
{
    qDebug() <<  Q_FUNC_INFO;
    updateInternalVariables(mConnectionList,mVehicleState,mTripList,mGlobalDisplayContentList );
    /*
    if (mTripList.isEmpty())
    {
        updateInternalVariablesEmpty(mVehicleState,mTripList,mGlobalDisplayContentList);
    }
    else
    {
        updateInternalVariables(mConnectionList,mVehicleState,mTripList,mGlobalDisplayContentList );
    }
    */
}
