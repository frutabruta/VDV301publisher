#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , remoteControlService2_3CZ1_0 ("RemoteControlService","_ibisip_http._tcp",47485,"2.3CZ1.0","_ropid_vdv301tester")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    remoteControlService2_3CZ1_0.slotStartServer();


   // qDebug().noquote()<<xmlGen.AllData2_3CZ1_0gen(document,RemoteControlStartRazzia,"8866");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createMessage(RemoteControlMessageType messageType, QString messageParameter)
{
    qDebug() <<  Q_FUNC_INFO;

    QDomDocument document;

    QString vysledek=xmlGen.AllData2_3CZ1_0gen(document,messageType,messageParameter);
    remoteControlService2_3CZ1_0.setBodyContent("AllData",vysledek);
    remoteControlService2_3CZ1_0.updateStructureMap();

}

void MainWindow::on_pushButton_ok_clicked()
{
    createMessage(RemoteControlOk,"");
}


void MainWindow::on_pushButton_error_clicked()
{
    createMessage(RemoteControlError,"");
}


void MainWindow::on_pushButton_destinationRequest_clicked()
{
    createMessage(RemoteControlDestinationRequest,"");
}


void MainWindow::on_pushButton_getOnRequest_clicked()
{
    createMessage(RemoteControlGetOnRequest,"");
}


void MainWindow::on_pushButton_startRazzia_clicked()
{
    createMessage(RemoteControlStartRazzia,ui->lineEdit_vehicleNumber->text());
}


void MainWindow::on_pushButton_stopRazia_clicked()
{
    createMessage(RemoteControlStopRazzia,ui->lineEdit_vehicleNumber->text());
}

