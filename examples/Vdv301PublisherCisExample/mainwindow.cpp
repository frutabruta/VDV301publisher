#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,customerInformationService2_2CZ1_0("CustomerInformationService","_ibisip_http._tcp",47480,"2.2CZ1.0")
{
    ui->setupUi(this);

    allConnects();
    customerInformationService2_2CZ1_0.slotStartServer();

    ui->label_serviceName->setText(customerInformationService2_2CZ1_0.mServiceName);
    ui->label_serviceVersion->setText(customerInformationService2_2CZ1_0.version());
    ui->label_port->setText(QString::number(customerInformationService2_2CZ1_0.portNumber()));
    ui->lineEdit_structure->setText(selectedStructure);
    ui->plainTextEdit_content->setPlainText(customerInformationService2_2CZ1_0.retrieveStructureContentMapValue(selectedStructure));
}

MainWindow::~MainWindow()
{
    customerInformationService2_2CZ1_0.outOfService();
    delete ui;
}


void MainWindow::allConnects()
{
    //  connect(&customerInformationService2_2CZ1_0,&HttpService::signalDumpSubscriberList,this,&MainWindow::dumpSubscribers2_2CZ);
    //  connect(&customerInformationService2_2CZ1_0,&HttpService::signalServicePublished,this,&MainWindow::slotVdv301ServiceStartResult);

    //   connect(&customerInformationService2_2CZ1_0,&CustomerInformationService::signalDumpSubscriberList,&testSubscribeServer,&TestOdberuServer::slotAktualizaceSubscriberu);
    //  connect(&customerInformationService2_2CZ1_0,&HttpService::signalReplyToPostReceived,&testSubscribeServer,&TestOdberuServer::slotVypisOdpovedServeru);

}




void MainWindow::on_pushButton_send_clicked()
{
    qDebug() <<  Q_FUNC_INFO;

    selectedStructure=ui->lineEdit_structure->text();
    QByteArray input=ui->plainTextEdit_content->toPlainText().toUtf8();

    customerInformationService2_2CZ1_0.setBodyContent(selectedStructure,input);

    //this doesn't update the server for now

    customerInformationService2_2CZ1_0.updateStructureMap();

}

