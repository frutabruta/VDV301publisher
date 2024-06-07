#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../httpservice.h"



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

private slots:
    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;

    HttpService customerInformationService2_2CZ1_0;

    QString selectedStructure="AllData";


    void allConnects();
};
#endif // MAINWINDOW_H
