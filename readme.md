# VDV301publisher
Qt library for VDV301 devices used as publisher

- CustomerInformationService (1.0, 2.2CZ1.0, 2.3)
    - GetAllData
    - GetCurrentDisplayContent
- DeviceManagementService (1.0)


## Changelog:
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


