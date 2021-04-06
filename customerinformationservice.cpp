#include "customerinformationservice.h"
#include "httpsluzba.h"


CustomerInformationService::CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{
    connect(timer, &QTimer::timeout, this, &CustomerInformationService::tedOdesliNaPanely);
    timer->start(60000);

}
