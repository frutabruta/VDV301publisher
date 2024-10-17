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
        QDomDocument xmlDocument;
        bodyAllData=xmlGenerator2_2CZ1_0.AllData2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState);
        bodyCurrentDisplayContent=xmlGenerator2_2CZ1_0.CurrentDisplayContent2_2CZ1_0(xmlDocument,stopPointDestinationList,vehicleState);
    }
    else if (mVersion=="2.3")
    {
        //Work in progress
        QDomDocument xmlDocument;
        //special options for XML in this version can be placed here
        bodyAllData=xmlGenerator2_3.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);
        bodyCurrentDisplayContent=xmlGenerator2_3.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);

        /*
        Vdv301AllData vdv301allData=xmlGenerator.AllData2_3new(tripList,connectionList,vehicleState);


        QDomDocument xmlDocument2;
        qDebug()<<"XXX TEST";

        qDebug().noquote()<<xmlGenerator.AllData2_3gen(xmlDocument2,vdv301allData);

        qDebug()<<"XXX TEST";
*/


    }
    else if (mVersion=="2.3CZ1.0")
    {
        //Work in progress
        QDomDocument xmlDocument;
        //special options for XML in this version can be placed here

        bodyCurrentDisplayContent=xmlGenerator2_3CZ1_0.CurrentDisplayContent2_3(xmlDocument,stopPointDestinationList,vehicleState);

        // bodyAllData=xmlGenerator.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);
        Vdv301AllData vdv301allData=xmlGenerator2_3CZ1_0.AllData2_3CZ1_0new(tripList,connectionList,vehicleState,globalDisplayContentList);

        QDomDocument xmlDocument2;
        bodyAllData=xmlGenerator2_3CZ1_0.AllData2_3CZ1_0gen(xmlDocument2,vdv301allData);

        /*
        qDebug()<<"XXX TEST";

        qDebug().noquote()<<bodyAllData;

        qDebug()<<"XXX TEST";

*/
    }
    else
    {
        QDomDocument xmlDocument;
        bodyAllData=xmlGenerator.AllData1_0(xmlDocument,tripList,connectionList,vehicleState);
        bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent1_0(xmlDocument,stopPointDestinationList,vehicleState);
    }

    this->setBodyContent("AllData",bodyAllData);
    this->setBodyContent("CurrentDisplayContent",bodyCurrentDisplayContent);


    updateStructureMap();

}


/*!
 * \brief CustomerInformationService::aktualizaceIntPromEmpty
 * \param stav
 * \param seznamSpoju
 */
void CustomerInformationService::updateInternalVariablesEmpty(VehicleState &vehicleState, QVector<Trip>  tripList, QVector<Vdv301DisplayContent> globalDisplayContentList ) //novy
{
    qDebug() <<  Q_FUNC_INFO<<" "<<mServiceName<<" "<<mVersion;

    qDebug()<<"size of triplist "<<tripList.size()<<" index"<<vehicleState.currentTripIndex;

    tripList.clear();
    QVector<Connection> connectionList;

    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";
    
    if (mVersion=="2.2CZ1.0")
    {
        QDomDocument xmlDocument;
        bodyAllData=xmlGenerator2_2CZ1_0.AllData_empty2_2CZ1_0(xmlDocument);
    }
    else if(mVersion=="2.3")
    {
        //bodyAllData=xmlGenerator.AllData_empty2_3(xmlDocument);
        QDomDocument xmlDocument;

        bodyAllData=xmlGenerator2_3.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);

        /*
        Vdv301AllData vdv301allData=xmlGenerator2_3CZ1_0.AllData2_3new(tripList,connectionList,vehicleState, globalDisplayContentList);

        bodyAllData=xmlGenerator2_3CZ1_0.AllData2_3gen(xmlDocument,vdv301allData);
*/
    }
    else if(mVersion=="2.3CZ1.0")
    {
        //bodyAllData=xmlGenerator.AllData_empty2_3(xmlDocument);
        QDomDocument xmlDocument;

        Vdv301AllData vdv301allData=xmlGenerator2_3CZ1_0.AllData2_3CZ1_0new (tripList,connectionList,vehicleState, globalDisplayContentList);

        bodyAllData=xmlGenerator2_3CZ1_0.AllData2_3CZ1_0gen(xmlDocument,vdv301allData);


    }
    else
    {
        QDomDocument xmlDocument;
        bodyAllData=xmlGenerator.AllData_empty_1_0(xmlDocument);
    }


    this->setBodyContent("AllData",bodyAllData);
    this->setBodyContent("CurrentDisplayContent",bodyCurrentDisplayContent);


    updateStructureMap();

}


/*!
 * \brief CustomerInformationService::aktualizaceObsahuSluzby
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
