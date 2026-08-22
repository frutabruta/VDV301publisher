#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../remotecontrolservice.h"
#include "../xmlremotecontrolservice2_3cz1_0.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    RemoteControlService remoteControlService2_3CZ1_0;
    XmlRemoteControlService2_3CZ1_0 xmlGen;

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_error_clicked();

    void on_pushButton_destinationRequest_clicked();

    void on_pushButton_getOnRequest_clicked();

    void on_pushButton_startRazzia_clicked();

    void on_pushButton_stopRazia_clicked();

private:
    Ui::MainWindow *ui;
    void createMessage(Vdv301Enumerations::RemoteControlMessageTypeEnumeration messageType, QString messageParameter);
};
#endif // MAINWINDOW_H
