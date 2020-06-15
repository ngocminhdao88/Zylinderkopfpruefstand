#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vfdSettingsDialog = new VfdSettingsDialog(this);

    initActions();
    initPacemaker();
    refreshPort();
    initModbusDevice();
    initUnicoVFD();
    initJobDataModel();

    //SIGNALS -> SLOTS
    connect(ui->portButton, &QPushButton::clicked, this, &MainWindow::refreshPort);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
}

MainWindow::~MainWindow()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;
    modbusDevice = nullptr;

    delete ui;
}

void MainWindow::refreshPort()
{
    ui->portCombo->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (QSerialPortInfo port: ports)
    {
        ui->portCombo->addItem(port.portName());
    }
}


void MainWindow::initActions() {

    connect(ui->actionVfdSetting, &QAction::triggered, vfdSettingsDialog, &QDialog::show);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::onConnectButtonClicked);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::onConnectButtonClicked);
}

void MainWindow::initModbusDevice()
{
    if (modbusDevice) {
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    modbusDevice = new QModbusRtuSerialMaster(this);

    //SIGNALS -> SLOTS
    //show modbus dev error on statusbar
    connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
        statusBar()->showMessage(modbusDevice->errorString(), 5000);
    });

    //show error when initiate modbus device
    if (!modbusDevice) {
        ui->connectButton->setDisabled(true);
        statusBar()->showMessage("Could not create Modbus master.");
    }
    else {
        connect(modbusDevice, &QModbusClient::stateChanged,
                this, &MainWindow::onModbusStateChanged);
    }
}

void MainWindow::initUnicoVFD()
{
    vfdDataModel = new VFDDataModel(this);
    ui->vfdEditor->setModel(vfdDataModel);

    unicoVfd = new UnicoVFD(modbusDevice, vfdDataModel, pacemaker, this);
}

void MainWindow::initJobDataModel()
{
    jobDataModel = new JobDataModel(this);
    ui->jobEditor->setModel(jobDataModel);

    ui->tableView->setModel(jobDataModel);
    ui->tableView_2->setModel(vfdDataModel);
}

void MainWindow::initPacemaker()
{
    pacemaker = new QTimer(this);
    pacemaker->setInterval(250); //250ms
    pacemaker->start();
}

void MainWindow::onModbusStateChanged(int state)
{
    bool connected = (state != QModbusDevice::UnconnectedState);
    ui->actionConnect->setEnabled(!connected);
    ui->actionDisconnect->setEnabled(connected);

    if (state == QModbusDevice::UnconnectedState)
        ui->connectButton->setText("Connect");
    else if (state == QModbusDevice::ConnectedState)
        ui->connectButton->setText("Disconnect");
}

void MainWindow::onConnectButtonClicked()
{
    if (!modbusDevice)
        return;

    statusBar()->clearMessage();

    //setup connection params if device is not connected
    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                             ui->portCombo->currentText());
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                             vfdSettingsDialog->settings().parity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                             vfdSettingsDialog->settings().baud);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                             vfdSettingsDialog->settings().dataBits);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                             vfdSettingsDialog->settings().stopBits);
        modbusDevice->setTimeout(vfdSettingsDialog->settings().responseTime);
        modbusDevice->setNumberOfRetries(vfdSettingsDialog->settings().numberOfRetries);

        //try to connect to device
        if (!modbusDevice->connectDevice()) {
            statusBar()->showMessage("Connect failed: " + modbusDevice->errorString(), 5000);
        } else {
            statusBar()->showMessage("Connected to device on " + ui->portCombo->currentText());
        }
    } else {
        modbusDevice->disconnectDevice();
        statusBar()->showMessage("Disconnected to device on " + ui->portCombo->currentText());
    }
}
