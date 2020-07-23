#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unicovfd.h"
#include "global.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initPacemaker();
    initVfdDevice();
    initJobDataModel();
    initActions();

    //SIGNALS -> SLOTS
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
    connect(m_vfdDevice, &AbstractVFD::statusChanged, this, &MainWindow::onVfdStatusChanged);
    connect(m_pacemaker, &QTimer::timeout, m_vfdDevice, &AbstractVFD::onUpdateRequest);

    connect(ui->testSequencer, &TestSequencer::testStepChanged, this, &MainWindow::onTestStepChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initActions() {
    if (m_vfdDevice) {
        connect(ui->actionVfdSetting, &QAction::triggered, m_vfdDevice, &AbstractVFD::configDevice);
        connect(ui->actionConnect, &QAction::triggered, m_vfdDevice, &AbstractVFD::connectDevice);
        connect(ui->actionDisconnect, &QAction::triggered, m_vfdDevice, &AbstractVFD::connectDevice);
    }
}

void MainWindow::initVfdDevice()
{
    m_vfdDataModel = new VFDDataModel(this);
    ui->vfdEditor->setModel(m_vfdDataModel);

    m_vfdDevice = new UnicoVFD(this, m_vfdDataModel);
}

void MainWindow::initJobDataModel() {
}

void MainWindow::initPacemaker()
{
    m_pacemaker = new QTimer(this);
    m_pacemaker->setInterval(PACE_MAKER_RATE); //250ms
    m_pacemaker->start();
}

void MainWindow::onTestStepChanged(TestProfileData testStep) {
    QModelIndex speedIndex = m_vfdDataModel->index(0, TestProfileEnum::SPEED_COL);
    QModelIndex dirIndex = m_vfdDataModel->index(0, TestProfileEnum::DIRECTION_COL);

    m_vfdDataModel->setData(speedIndex, testStep.getSpeed());
    m_vfdDataModel->setData(dirIndex, testStep.getDirection());
}

void MainWindow::onVfdStatusChanged(QString status) {
    statusBar()->showMessage(status, 5000);
}

void MainWindow::onConnectButtonClicked() {
    if (!m_vfdDevice) return;

    m_vfdDevice->connectDevice();

    // Disable "connect" action and enable "disconnect" action the connection
    // between host pc and VFD device has established.
    ui->actionConnect->setEnabled(!m_vfdDevice->isConnected());
    ui->actionDisconnect->setEnabled(m_vfdDevice->isConnected());

    // Change the description of connect button depends on
    // the connection between host pc and vfd device
    if (m_vfdDevice->isConnected()) {
        ui->connectButton->setText("Disconnect");
    } else {
        ui->connectButton->setText("Connect");
    }
//    if (!modbusDevice)
//        return;

//    statusBar()->clearMessage();

//    //setup connection params if device is not connected
//    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
//        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
//                                             ui->portCombo->currentText());
//        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
//                                             vfdSettingsDialog->settings().parity);
//        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
//                                             vfdSettingsDialog->settings().baud);
//        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
//                                             vfdSettingsDialog->settings().dataBits);
//        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
//                                             vfdSettingsDialog->settings().stopBits);
//        modbusDevice->setTimeout(vfdSettingsDialog->settings().responseTime);
//        modbusDevice->setNumberOfRetries(vfdSettingsDialog->settings().numberOfRetries);

//        //try to connect to device
//        if (!modbusDevice->connectDevice()) {
//            statusBar()->showMessage("Connect failed: " + modbusDevice->errorString(), 5000);
//        } else {
//            statusBar()->showMessage("Connected to device on " + ui->portCombo->currentText());
//        }
//    } else {
//        modbusDevice->disconnectDevice();
//        statusBar()->showMessage("Disconnected to device on " + ui->portCombo->currentText());
//    }
}
