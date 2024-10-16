# VDV301publisher
Qt library for VDV301 devices used as publisher

- CustomerInformationService (1.0, 2.2CZ1.0, 2.3)
    - GetAllData
    - GetCurrentDisplayContent
- DeviceManagementService (1.0)


## Changelog:
- 20241016
    - XmlCommon
        - XmlCommon::Connections2_3
            - default language fix
            - StopRef fix
            - ConnectionRef fix
            - LineRef fix

- 20240823
    - CustomerInformationService
        - CustomerInformationService::updateInternalVariables
            - fixed not generating any XML when the stoplist is empty
            - empty triplist out of range fix
            - empty stopPointDestination out of range fix
        - CustomerInformationService::outOfService()
            - change from updateInternalVariablesEmpty to updateInternalVariables
        - CustomerInformationService::slotSendDataToSubscribers
            - change from updateInternalVariablesEmpty to updateInternalVariables

    - HttpService
        - new function HttpService::isInRange
    - TicketValidationService
        - TicketValidationService::updateServiceContent
            - empty triplist out of range fix
    - XmlCommon
        - XmlCommon::TripInformation1_0
            - empty triplist out of range fix
            - create two dummy stops when the triplist is empty to comply with XSD
        - XmlCommon::TripInformation2_2CZ1_0
            - empty triplist out of range fix
        - new function XmlCommon::isInRange
        - now inherits from QObject instead of QMainWindow
        - new signal signalErrorMessage
    - XmlCustomerInformationService
        -  XmlCustomerInformationService::AllData1_0
            - empty triplist out of range fix
        - XmlCustomerInformationService::AllData2_2CZ1_0
            - empty triplist out of range fix


- 20240823_2
    - Vdv301DataStructures
        - new function DoorOpenStateEnumerationFromQString
- 20240823
    - CustomerInformationService
        - CustomerInformationService::updateInternalVariables
            - added 2.3CZ1.0 option  
        - test implementation of xmlGenerator.AllData2_3gen
        - new variable mGlobalDisplayContentList
        - new function CustomerInformationService::setGlobalDisplayContentList
        - CustomerInformationService::updateInternalVariables
            - new parameter globalDisplayContentList
        - CustomerInformationService::updateInternalVariablesEmpty
            - new parameter globalDisplayContentList
   
    - XmlCommon
        - new variable defaultLanguage2_3CZ1_0
        - XmlCommon::DisplayContentViaPointDestination2_3new
            - displayContentRefFix       
        - XmlCommon::DisplayContentViaPointDestination2_3
            - empty second Destination element fixed
        - XmlCommon::DisplayContentViaPointDestination2_3new
            - empty displayContentRef fix
        - XmlCommon::stopPointDestinationToVdv301ViaPoint
            - viapoint icon fix
        - XmlCommon::TripInformation2_3new
            - removed unused QDomDocument
        - XmlCommon::StopPoint2_3new
            - FareZone fix
         - new functions
            - XmlCommon::Connection2_3gen
            - XmlCommon::DisplayContentViaPointDestination2_3gen
            - XmlCommon::FareZoneInformationStructure2_3new
            - XmlCommon::TripInformation2_3gen
            - XmlCommon::StopSequence2_3gen
            - XmlCommon::StopPoint2_3gen
            - XmlCommon::ViaPoint2_3def
            - XmlCommon::namedElement
    - XmlCustomerInformationService
        - XmlCustomerInformationService::CurrentDisplayContent2_3¨
            - all Displays now generated with DisplayContentViaPointDestination2_3
            - XmlCustomerInformationService::AllData2_3new
            - removed unused QDomDocument
            - vehicleMode and vehicleSubMode moved farther in the function to ensure correct data (ddDoVehicleMode)
        - new function XmlCustomerInformationService::AllData2_3gen
    - VDV301DataStructures
        - displayContentClassEnumerationToQString
  
- 20240702
    - CustomerInformationService::updateInternalVariables
        - usage of xmlGenerator.AllData2_3new
    
    - XmlCommon::DisplayContentViaPointDestination2_3new
        - QDomDocument removed from function parameters
        - added RunNumber
    - XmlCommon::TripInformation2_3new
    - new function XmlCommon::vehicleRunToRunNumber
    - XmlCommon::StopSequence2_3new
        - QDomDocument removed from function parameters
        - removed ExpectedDepartureTime
        - changed ScheduledDepartureTime to DepartureScheduled
        - added ArrivalScheduled
    - XmlCommon::StopPoint2_3new
        - QDomDocument removed from function parameters
        - adding connections to current stop only
    - XmlCustomerInformationService::AllData2_3new
        - fix of  allData.tripInformationList

- 20240620
    - VDV301DataStructures
        - VehicleState::doorState changed to Vdv301Enumerations
    - XmlCustomerInformationService
        - applied changes ov doorState data type
        - XmlCustomerInformationService::AllData2_3new
            - removed remnats of QDomElements    
            - changed result data type to Vdv301AllData
        


- 20240619_2
    - RouteDeviationEnumeration
    - XmlCustomerInformationService::AllData2_3new
        - removed unnecessary DOM elements
- 20240619
    - VDV301DataStructures
        - vehicleState.locationState changed to VDV301LocationStateEnumeration
    - XmlCommon
        - changes to comply with the data tye change above
    - XmlCustomerInformationService
        - XmlCustomerInformationService::AllData2_3new
            - few changes to create Vdv301AllData allData
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


