#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vfdsettingsdialog.h"
#include "vfddatamodel.h"
#include "jobdatamodel.h"
#include "abstractvfd.h"
#include "testprofiledata.h"

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

    /**
     * @brief Handle the signal testStepChanged from TestSequencer
     */
    void onTestStepChanged(TestProfileData testStep);

private:
    Ui::MainWindow *ui = 0;

    VFDDataModel *m_vfdDataModel = 0;
    JobDataModel *m_jobDataModel = 0;
    AbstractVFD *m_vfdDevice = 0;

    QTimer *m_pacemaker = 0;
};
#endif // MAINWINDOW_H
