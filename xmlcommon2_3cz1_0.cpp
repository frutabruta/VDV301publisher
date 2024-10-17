#include "xmlcommon2_3cz1_0.h"

XmlCommon2_3CZ1_0::XmlCommon2_3CZ1_0() {}




QDomElement XmlCommon2_3CZ1_0::TripInformation2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip)
{
    QString language=defaultLanguage2_3;
    QString tripRef=trip.tripRef;

    QDomElement dTripInformation=xmlDocument.createElement("TripInformation");

    QDomElement dTripRef=Value(xmlDocument,"TripRef",tripRef);

    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_3gen(xmlDocument,trip.stopPointList));

    if (followingTrip==false)
    {
        QDomElement dLocationState=xmlDocument.createElement("LocationState");
        dLocationState.appendChild(xmlDocument.createTextNode(Vdv301Enumerations::LocationStateEnumerationToQString(trip.locationState)));
        dTripInformation.appendChild(dLocationState);



        if(!trip.additionalTextMessage.text.isEmpty())
        {
            QString specialAnnouncement=trip.additionalTextMessage.text;
            qDebug()<<"special announcement="<<specialAnnouncement;
            dTripInformation.appendChild( internationalTextTypeToDom(xmlDocument,"AdditionalTextMessage",specialAnnouncement,trip.additionalTextMessage.language));
            //   dTripInformation.appendChild(AdditionalTextMessage2_3(xmlDocument,  vehicleState.currentSpecialAnnoucement.text));
        }
        /*
        else if (specialAnnouncement!="")
        {
            //   dTripInformation.appendChild(AdditionalTextMessage2_2CZ1_0(specialniOznameni));
        }
        */
    }
    else
    {
        qDebug()<<"followingTrip==true";
    }

    //fareZone change, commented out to comply with VDV CIS 2.3
    /*
    if((currentStopIndex+1)<stopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,stopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,stopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
    }
    */
    QDomElement dRunNumber=Value(xmlDocument,"RunNumber",trip.runNumber);
    dTripInformation.appendChild(dRunNumber);

    /*
    if((currentStopIndex+1)<selectedStopPointDestinationList.length()&&(vehicleState.showFareZoneChange==true))
    {
        if(isInRange(currentStopIndex-1,selectedStopPointDestinationList.count(),Q_FUNC_INFO)&&isInRange(currentStopIndex,selectedStopPointDestinationList.count(),Q_FUNC_INFO))
        {
            dTripInformation.appendChild(FareZoneChange2_2CZ1_0(xmlDocument,selectedStopPointDestinationList.at(currentStopIndex-1).stopPoint.fareZoneList,selectedStopPointDestinationList.at(currentStopIndex).stopPoint.fareZoneList,language));
        }


    }*/

    return dTripInformation;
}





QDomElement XmlCommon2_3CZ1_0::FareZoneChange2_3CZ1_0gen(QDomDocument  &xmlDocument, QVector<Vdv301InternationalText> fareZoneFrom,QVector<Vdv301InternationalText> fareZoneTo)
{

    QDomElement fareZoneChange=xmlDocument.createElement("FareZoneChange");


    QDomElement fromFareZones=xmlDocument.createElement("FromFareZones");


    foreach(Vdv301InternationalText selectedFareZone, fareZoneFrom )
    {
        fromFareZones.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",selectedFareZone));
    }

    fareZoneChange.appendChild(fromFareZones);



    QDomElement toFareZones=xmlDocument.createElement("ToFareZones");




    foreach(Vdv301InternationalText selectedFareZone, fareZoneTo )
    {
        toFareZones.appendChild(internationalTextTypeToDom(xmlDocument,"FareZone",selectedFareZone));
    }


    fareZoneChange.appendChild(toFareZones);

    return fareZoneChange;
}
