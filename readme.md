# VDV301publisher
Qt library for VDV301 devices used as publisher


## Changelog:
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


