#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(MainWindowLog, "MainWindow")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , remoteControlService2_3CZ1_0 ("RemoteControlService","_ibisip_http._tcp",47461,"2.3CZ1.0","_ropid_vdv301remotecontrol")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_version->setText(textVerze());
    ui->label_version->setTextInteractionFlags(Qt::TextSelectableByMouse);



    createMessage(Vdv301Enumerations::RemoteControlOk,"");

    connect(&remoteControlService2_3CZ1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribersRcs2_3CZ1_0);

    remoteControlService2_3CZ1_0.slotStartServer();


   // qDebug().noquote()<<xmlGen.AllData2_3CZ1_0gen(document,RemoteControlStartRazzia,"8866");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createMessage(Vdv301Enumerations::RemoteControlMessageTypeEnumeration messageType, QString messageParameter)
{
    QDomDocument document;
    QString vysledek=xmlGen.AllData2_3CZ1_0gen(document,messageType,messageParameter);
    QMap<QString,QString> structureContentMap;
    structureContentMap.insert("AllData",vysledek);
    switch(messageType)
    {

    case Vdv301Enumerations::RemoteControlOk:
        remoteControlService2_3CZ1_0.setBodyContent("AllData",vysledek);
        remoteControlService2_3CZ1_0.updateStructureMap();
        break;
    case Vdv301Enumerations::RemoteControlError:
        remoteControlService2_3CZ1_0.setBodyContent("AllData",vysledek);
        remoteControlService2_3CZ1_0.updateStructureMap();
        break;
    case Vdv301Enumerations::RemoteControlDestinationRequest:
        remoteControlService2_3CZ1_0.postToSubscribers(structureContentMap);
        break;
    case Vdv301Enumerations::RemoteControlGetOnRequest:
        remoteControlService2_3CZ1_0.postToSubscribers(structureContentMap);
        break;
    case Vdv301Enumerations::RemoteControlStartRazzia:
        remoteControlService2_3CZ1_0.postToSubscribers(structureContentMap);
        break;
    case Vdv301Enumerations::RemoteControlStopRazzia:
        remoteControlService2_3CZ1_0.postToSubscribers(structureContentMap);
        break;
    }

}


void MainWindow::dumpSubscribersRcs2_3CZ1_0(QVector<Subscriber> adresy)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    dumpSubscribersToTable(adresy,ui->tableWidget_subscribers);
}

void MainWindow::dumpSubscribersToTable(QVector<Subscriber> adresy, QTableWidget* tabulka)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    tabulka->setRowCount(0);
    qCDebug(MainWindowLog)<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qCDebug(MainWindowLog)<<"vracim 0";
    }
    else
    {
        for (int i = 0;  i < adresy.count(); i++)
        {
            Subscriber odberatel=adresy.at(i);

            qint32 row;
            QTableWidgetItem *cell;
            row = tabulka->rowCount();
            tabulka->insertRow(row);
            cell = new QTableWidgetItem(odberatel.address.toString());
            tabulka->setItem(row, 0, cell);


            cell = new QTableWidgetItem(odberatel.structure);
            tabulka->setItem(row, 1, cell);
            tabulka->resizeColumnsToContents();
        }
        qCDebug(MainWindowLog)<<"vracim 1";
    }
}

void MainWindow::on_pushButton_ok_clicked()
{
    createMessage(Vdv301Enumerations::RemoteControlOk,"");
}


void MainWindow::on_pushButton_error_clicked()
{
    createMessage(Vdv301Enumerations::RemoteControlError,"");
}


void MainWindow::on_pushButton_destinationRequest_clicked()
{
    createMessage(Vdv301Enumerations::RemoteControlDestinationRequest,"");
}


void MainWindow::on_pushButton_getOnRequest_clicked()
{
    createMessage(Vdv301Enumerations::RemoteControlGetOnRequest,"");
}


void MainWindow::on_pushButton_startRazzia_clicked()
{
    createMessage(Vdv301Enumerations::RemoteControlStartRazzia,ui->lineEdit_vehicleNumber->text());
}


void MainWindow::on_pushButton_stopRazia_clicked()
{
    createMessage(Vdv301Enumerations::RemoteControlStopRazzia,ui->lineEdit_vehicleNumber->text());
}

QString MainWindow::textVerze()
{
    QDate datumKompilace=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime casKompilace=QTime::fromString(__TIME__,"hh:mm:ss");
    qCDebug(MainWindowLog)<<" date:"<<datumKompilace<<" time:"<<casKompilace;
    QString verze=datumKompilace.toString("yyyyMMdd")+"_"+casKompilace.toString("hhmm");
    return verze;
}

