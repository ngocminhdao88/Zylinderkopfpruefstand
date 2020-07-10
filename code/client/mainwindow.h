#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vfdsettingsdialog.h"
#include "vfddatamodel.h"
#include "jobdatamodel.h"
#include "abstractvfd.h"

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

private slots:
    /**
     * @brief Connect to the VFD device
     */
    void onConnectButtonClicked();

    /**
     * @brief Handle the statusChanged signal from a VFD device
     */
    void onVfdStatusChanged(QString status);

private:
    /*
     * @brief Setup the actions
     */
    void initActions();

    /*
     * @brief Setup Unico VFD
     */
    void initVfdDevice();

    /*
     * @brief Setup a model hodling job data
     */
    void initJobDataModel();

    /*
     * @brief Setup a pacemaker
     */
    void initPacemaker();


private:
    Ui::MainWindow *ui = 0;
    VfdSettingsDialog *vfdSettingsDialog = 0;
    QModbusReply *lastRequest = 0;
    QModbusClient *modbusDevice = 0;

    VFDDataModel *vfdDataModel = 0;
    JobDataModel *jobDataModel = 0;
    AbstractVFD *m_vfdDevice = 0;

    QTimer * pacemaker = 0;
};
#endif // MAINWINDOW_H
