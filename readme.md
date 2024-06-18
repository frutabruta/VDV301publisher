# VDV301publisher
Qt library for VDV301 devices used as publisher

- CustomerInformationService (1.0, 2.2CZ1.0, 2.3)
    - GetAllData
    - GetCurrentDisplayContent
- DeviceManagementService (1.0)


## Changelog:
- 20240618
    - new approcah to XML generating from VDV301structures
    - VDV301DataStructures
        - dev branch
        - new class Vdv301AllData
        - new class Vdv301VehicleInformationGroup
        - new class Vdv301Connection
        - new class Vdv301Enumerations
    - XmlCommon
        - XmlCommon::DisplayContentViaPointDestination2_3
            - removed ViaPoint element generation
        - new function XmlCommon::DisplayContentViaPointDestination2_3new
        - new function XmlCommon::lineToVdv301Line2_3
        - new function XmlCommon::stopPointDestinationToVdv301ViaPoint
        - new function XmlCommon::TripInformation2_3new
        - new function XmlCommon::StopSequence2_3new
        - new function XmlCommon::StopPoint2_3new

        - XmlCommon::StopPoint2_3
            - simplified using DisplayContentViaPointDestination2_3
    - XmlCustomerInformationService
        - new functionXmlCustomerInformationService::AllData2_3new

- 20240617
    - VDV301DataStructures
        - added ArrivalTime to StopPoint
    - XmlCommon
        - removed FareZoneChange from XmlCommon::TripInformation2_3 to comply with VDV.de XSD files
        - foreach changed to for in XmlCommon::DisplayContentViaPointDestination2_3 (caused crash for unknown reason)
- 20240607
    - included VDV301DataStructures as a submodule
    - added examples folder
        - Vdv301PublisherMinimalExample with CustomerInformationService 2.2CZ1.0
            - pregenerated XML content
        - Vdv301PublisherCisExample with CustomerInformationService 2.2CZ1.0
            - generating of data using VDV301Structures
    - new functions
        - HttpService::retrieveStructureContentMapValue
        - HttpService::updateStructureMap
        - HttpService::postToAllSubscribers

- 20240514
    - added conditions to succesfully compile with 5.15 (functionality with 5.15 not tested!)
- 20240506
    - fix of escaping < in international text type by CDATA section (used for icon and color tags)
        - new functions
            - XmlCommon::createEscapedValueCdata
            - XmlCommon::qStringXmlEscape
            - XmlCommon::qDomDocumentToQString
- 20240422
    - globalVersion changed to private (mVersion), added getter and setter
- 20240208
    - 2.3
        - CurrentDisplayContent fix
- 20240203
    - 2.3 out of service Xml generator fix
- 20240131
    - XmlCommon 
        - XmlCommon::DisplayContent2_3
            - two row destination fix
        - XmlCommon::DisplayContentViaPointDestination2_3
            - new function to accomodate storing viaPoints as second row of destination, cycling through different DisplayContents 
        - XmlCommon::StopPoint2_3
            - modified to accomodate storing viaPoints as second row of destination, cycling through different DisplayContents 
        - XmlCommon::StopPoint2_2CZ1_0
            - expected departure added
            - scheduled departure added (now same value is stored in both)
        
- 20240117
    - DeviceManagementService
        - device status support
            - status can be changed externally
- 20240104
    - application of functions
        - HttpServerPublisher::createSubscribeResponse
        - HttpServerPublisher::createUnsubscribeResponse
    - HttpServerPublisher
        - Active=false if unsubscription is successful 
        - changed response header from UTF-16 to UTF-8


- 20231214
    - HttpServerPublisher
        - HttpServerPublisher::route
            - now reacts to Unsubscribe requests
        - HttpService
            - HttpService::slotDumpRequestContent
            - new overloaded function HttpService::removeSubscriber(Subscriber selectedSubscriber)
        - Subscriber
            - added == operator
        - XmlCommon
            - fixed two row destination generator for front display 
    

- 20231108
    - all functions in version 2.4 have been renamed to 2.4, because they were made to comply with 2.3 version XSDs and 2.4 specification is not finished yet
    - 2.3
        - AdditionalTextMessageFix

- 20231103
    - XmlCommon::AdditionalTextMessage1_0
        - display of AdditionalAnouncements (scrolling/not scrolling)
    - XmlCommon::Connections1_0
        - fix of bus pictogram
    - XmlCommon::DisplayContent1_0
        - fix of Destination name for LCD
    - XmlCommon::FareZone2_3
        - new function
    - XmlCommon::FareZoneInformationStructure2_3
        - new function
- 20231102
    - VDV301 1.0 Connections fix
    - VDV301 2.4 added required tags to comply with official XSD files for VDV301 2.3
- 20231030
    - fix of generating Xml responses (change of passing xmlDocument by reference)
    
- 20231006
    - complete translation of sourcecode to English
    - passing XmlDocument as parameter
    - generation of processingInformation by separate function

- 20230907
    - ColorDisplayRules
        - fix of unknown submode colors
        - new function linkaDoStylu(Linka linka, QString subMode)
    - XmlCommon 
        - metroSubmode icon replacement

- 20230831
    - 2.4
        - inline color formatting (new class ColorDisplayRules)
        - removal of line property

- 20230622
    - 2.4
        - DisplayContent
- 20230607
    - nová verze QtZeroConf
    - příprava pro verzi 2.4
    - příprava pro start v 
    - HttpSluzba
        - nový slot HttpSluzba::slotSluzbaPublikovana
        - nový signál signalSluzbaPublikovana(QString nazevSluzby)


