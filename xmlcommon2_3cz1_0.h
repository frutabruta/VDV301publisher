#ifndef XMLCOMMON2_3CZ1_0_H
#define XMLCOMMON2_3CZ1_0_H


#include "xmlcommon2_3_new.h"
class XmlCommon2_3CZ1_0 : public XmlCommon2_3_new
{
public:
    XmlCommon2_3CZ1_0();
    QDomElement TripInformation2_3CZ1_0gen(QDomDocument &xmlDocument, Vdv301Trip trip, bool followingTrip);
    QDomElement FareZoneChange2_3CZ1_0gen(QDomDocument &xmlDocument, QVector<Vdv301InternationalText> fareZoneFrom, QVector<Vdv301InternationalText> fareZoneTo);
};

#endif // XMLCOMMON2_3CZ1_0_H
