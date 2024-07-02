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
void CustomerInformationService::updateInternalVariables(QVector<Connection> connectionList, VehicleState &vehicleState, QVector<Trip>  tripList ) //novy
{
    qDebug() <<  Q_FUNC_INFO<<" "<<mServiceName<<" "<<mVersion;
    qDebug()<<"velikost seznamTripu"<<tripList.size()<<" index"<<vehicleState.currentTripIndex;

    if (tripList.isEmpty())
    {
        qDebug()<<"seznam spoju je prazdny, ukoncuji CustomerInformationService::aktualizaceIntProm";
        return;
    }

    /*
    if(!MainWindowPomocne::jeVRozsahu(stav.indexSpojeNaObehu,seznamSpoju.size(),"CustomerInformationService::aktualizaceIntProm"))
    {
        return;
    }
    */


    QVector<StopPointDestination>  seznamZastavek=tripList.at(vehicleState.currentTripIndex).globalStopPointDestinationList;
    QString bodyAllData="";
    QString bodyCurrentDisplayContent="";
    
    if (mVersion=="2.2CZ1.0")
    {
         QDomDocument xmlDocument;
        bodyAllData=xmlGenerator.AllData2_2CZ1_0(xmlDocument,tripList,connectionList,vehicleState);
        bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent2_2CZ1_0(xmlDocument,seznamZastavek,vehicleState);
    }
    else if (mVersion=="2.3")
    {
        //Work in progress
         QDomDocument xmlDocument;
        //special options for XML in this version can be placed here
        bodyAllData=xmlGenerator.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);
        bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent2_3(xmlDocument,seznamZastavek,vehicleState);

        Vdv301AllData vdv301allData=xmlGenerator.AllData2_3new(xmlDocument, tripList,connectionList,vehicleState);


    }
    else
    {
        QDomDocument xmlDocument;
        bodyAllData=xmlGenerator.AllData1_0(xmlDocument,tripList,connectionList,vehicleState);
        bodyCurrentDisplayContent=xmlGenerator.CurrentDisplayContent1_0(xmlDocument,seznamZastavek,vehicleState);
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
void CustomerInformationService::updateInternalVariablesEmpty(VehicleState &vehicleState, QVector<Trip>  tripList ) //novy
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
        bodyAllData=xmlGenerator.AllData_empty2_2CZ1_0(xmlDocument);
    }
    else if(mVersion=="2.3")
    {
        //bodyAllData=xmlGenerator.AllData_empty2_3(xmlDocument);
        QDomDocument xmlDocument;

        bodyAllData=xmlGenerator.AllData2_3(xmlDocument, tripList,connectionList,vehicleState);
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
    updateInternalVariablesEmpty(mVehicleState,mTripList);

}


/*!
 * \brief CustomerInformationService::slotTedOdesliNaPanely
 */

void CustomerInformationService::slotSendDataToSubscribers()
{
    qDebug() <<  Q_FUNC_INFO;
    if (mTripList.isEmpty())
    {
        updateInternalVariablesEmpty(mVehicleState,mTripList);
    }
    else
    {
        updateInternalVariables(mConnectionList,mVehicleState,mTripList );
    }

}
