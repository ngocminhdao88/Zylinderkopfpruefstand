#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vfdsettingsdialog.h"
#include "vfddatamodel.h"
#include "jobdatamodel.h"
#include "unicovfd.h"

#include <QModbusRtuSerialMaster>
#include <QStatusBar>
#include <QSerialPortInfo>
#include <QModbusReply>
#include <QModbusClient>
#include <QModbusDataUnit>
#include <QDataWidgetMapper>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class VfdSettingsDialog;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /*
     * @brief Rescan the avaiable com ports on the computer
     */
    void refreshPort();

    /*
     * @brief Called when modbus device changes state
     */
    void onModbusStateChanged(int state);

    /*
     * @brief Called when user clicks on "Connect" button
     */
    void onConnectButtonClicked();


private slots:

private:
    /*
     * @brief Setup the actions
     */
    void initActions();

    /*
     * @brief Setup the modbus device
     * @detail Initiate the modbus device and setup SIGNAL-SLOT connection
     */
    void initModbusDevice();

    /*
     * @brief Setup Unico VFD
     */
    void initUnicoVFD();

    /*
     * @brief Setup a model hodling job data
     */
    void initJobDataModel();

    /*
     * @brief Setup a pacemaker
     */
    void initPacemaker();


private:
    Ui::MainWindow *ui;
    VfdSettingsDialog *vfdSettingsDialog = nullptr;
    QModbusReply *lastRequest = nullptr;
    QModbusClient *modbusDevice = nullptr;

    VFDDataModel *vfdDataModel;
    JobDataModel *jobDataModel;
    UnicoVFD *unicoVfd;

    QTimer * pacemaker;
};
#endif // MAINWINDOW_H
