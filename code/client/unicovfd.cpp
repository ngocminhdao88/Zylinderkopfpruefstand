#include <QDebug>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QModbusDevice>

#include "global.h"
#include "unicovfd.h"
#include "vfddatamodel.h"
#include "vfdsettingsdialog.h"

enum {
    MaxSpeed = 7000, //[RPM]
    DeviceID = 1,
    MaxRampRate = 1000, //[RPM/s]

    //VFD holding registers
    SpeedRegister = 84,
    FeedbackSpeedRegister = 222,
    DirectionRegister = 427,
    AccelerationRegister = 86,
    DecelerationRegister = 87,
};

UnicoVFD::UnicoVFD(QAbstractItemModel *model, QTimer *pacemaker, QObject *parent) :
    AbstractVFD(parent),
    m_settingDialog(new VfdSettingsDialog()),
    m_speedRamp(new RampGenerator(this))
{
    initDevice();
    setModel(model);
    setPacemaker(pacemaker);
}

UnicoVFD::~UnicoVFD() {
    if (m_modbusDevice) m_modbusDevice->disconnectDevice();
    delete m_modbusDevice;
    m_modbusDevice = 0;

    delete m_settingDialog;
    m_settingDialog = 0;
}

void UnicoVFD::setModel(QAbstractItemModel *model) {
    if (!model) return;

    m_vfdModel = model;

    connect(m_vfdModel, &QAbstractItemModel::dataChanged,
            this, &UnicoVFD::onModelDataChanged);
}

void UnicoVFD::setPacemaker(QTimer *pacemaker) {
    if (!pacemaker) return;

    m_paceMaker = pacemaker;

    connect(m_paceMaker, &QTimer::timeout, this, &UnicoVFD::onUpdateRequest);
}

void UnicoVFD::setSpeed(double speed) {
    if (!m_modbusDevice)
        return;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return;

    if (speed > MaxSpeed)
        return;

    int speedFixPoint = speed * 10;

    QModbusDataUnit data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                           SpeedRegister,
                                           QVector<quint16>() << speedFixPoint);

    if (auto *reply = m_modbusDevice->sendWriteRequest(data, DeviceID)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &UnicoVFD::onReadReady);
        } else {
            //broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        //error when sending write request. Do something about that
    }
}

void UnicoVFD::setDirection(double dir) {
    if (!m_modbusDevice) return;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState) return;

    //guarding input. dir should be 0, 1 or 2
    if (dir > 2) return;

    QModbusDataUnit data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                           DirectionRegister,
                                           QVector<quint16>() << dir);
    if (auto *reply = m_modbusDevice->sendWriteRequest(data, DeviceID)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &UnicoVFD::onReadReady);
        } else {
            //broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        //error when sending write request. Do something about that
    }
}

void UnicoVFD::setRampDownRate(double rate) {
    Q_UNUSED(rate)
}

void UnicoVFD::setRampUpRate(double rate) {
    Q_UNUSED(rate)
}

double UnicoVFD::getSpeed() {
    if (!m_modbusDevice)
        return -1;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return -1;

    QModbusDataUnit data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                           FeedbackSpeedRegister,
                                           1);

    if (auto *reply = m_modbusDevice->sendReadRequest(data, DeviceID)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &UnicoVFD::onReadReady);
        } else {
            //broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        //error when sending read request. Do something about that
    }

    // return some thing here
    return 0;
}

bool UnicoVFD::connectDevice() {
    if (!m_modbusDevice) return false;

    //setup connection params if device is not connected
    if (m_modbusDevice->state() != QModbusDevice::ConnectedState) {
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                             m_settingDialog->settings().portName);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                             m_settingDialog->settings().parity);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                             m_settingDialog->settings().baud);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                             m_settingDialog->settings().dataBits);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                             m_settingDialog->settings().stopBits);
        m_modbusDevice->setTimeout(m_settingDialog->settings().responseTime);
        m_modbusDevice->setNumberOfRetries(m_settingDialog->settings().numberOfRetries);

        //try to connect to device
        if (!m_modbusDevice->connectDevice()) {
            emit statusChanged("Connection failed: " + m_modbusDevice->errorString());
            return false;
        } else {
            emit statusChanged("Connected to device on " + m_settingDialog->settings().portName);
            return true;
        }
    // disconnect the device if it was already connected
    } else {
        // stop the VFD first before disconnect it
        setSpeed(0);
        setDirection(0);

        m_modbusDevice->disconnectDevice();
        emit statusChanged("Disconnected to device on " + m_settingDialog->settings().portName);
        return false;
    }
}

void UnicoVFD::configDevice() {
    if (m_settingDialog) m_settingDialog->show();
}

void UnicoVFD::initDevice() {
    if (m_modbusDevice) {
        m_modbusDevice->disconnectDevice();
        delete m_modbusDevice;
        m_modbusDevice = 0;
    }

    m_modbusDevice = new QModbusRtuSerialMaster(this);

    // emit error when creating modbus device
    if (!m_modbusDevice) {
        // disable connection button
        // show error message
    } else {
        connect(m_modbusDevice, &QModbusClient::stateChanged, [this](int state) {
            m_isConnected = (state != QModbusDevice::UnconnectedState);
        });
    }
}

bool UnicoVFD::isConnected() {
    return m_isConnected;
}

void UnicoVFD::onReadReady() {
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        //No error -> parse the reply
        const QModbusDataUnit unit = reply->result();
        for (int i = 0, total = int(unit.valueCount()); i < total; i++) {
            if (unit.startAddress() == FeedbackSpeedRegister) {
                double rawValue = unit.value(0);
                if (m_vfdModel) {
                    //get motor's turn direction
                    QModelIndex directionIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, static_cast<int>(VFDDataColumn::Direction));
                    uint direction = m_vfdModel->data(directionIndex).toUInt();

                    //parse feedback speed and update the data model
                    double feedbackSpeed = getFeedbackSpeed(rawValue, direction);
                    QModelIndex feedbackSpeedIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, static_cast<int>(VFDDataColumn::FeedbackSpeed));
                    m_vfdModel->setData(feedbackSpeedIndex, feedbackSpeed);
                }
            }
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError) {
        emit statusChanged(reply->errorString());
    }
    else {
        emit statusChanged(reply->errorString());
    }

    reply->deleteLater();
}

void UnicoVFD::onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    Q_UNUSED(bottomRight)

    if (!topLeft.isValid()) return;
    if (!m_speedRamp) return;

    int col = topLeft.column();
    double data = topLeft.data(Qt::DisplayRole).toDouble();

    switch (col) {
    case static_cast<int>(VFDDataColumn::ControlSpeed):
        m_speedRamp->setTargetValue(data);
        break;
    case static_cast<int>(VFDDataColumn::Direction):
        if (data == 0) {
            m_speedRamp->reset();
            m_speedRamp->setEnable(false);
        } else {
            m_speedRamp->setEnable(true);
        }
        break;
    case static_cast<int>(VFDDataColumn::Acceleration):
        m_speedRamp->setRampUpRate(normalizeRampRate(data));
        break;
    case static_cast<int>(VFDDataColumn::Deceleration):
        m_speedRamp->setRampDownRate(normalizeRampRate(data));
        break;
    }
}

double UnicoVFD::normalizeRampRate(double rate) {
    if (!m_paceMaker) return 1;
    double pacemakerRate = m_paceMaker->interval();
    return rate * pacemakerRate / 1000;
}

double UnicoVFD::getFeedbackSpeed(double fbSpeed, uint direction) {
    double result = -1;

    if (direction == 0)
        result = -1;

    if (direction == 1)
        result = fbSpeed / 10;

    if (direction == 2)
        result = (fbSpeed - 65536) / 10; //2^16 = 65536

    return result;
}

void UnicoVFD::onUpdateRequest() {
    if (!m_speedRamp) return;
    if (!m_vfdModel) return;

    if (!isConnected()) {
        m_speedRamp->reset();
        return;
    }

    m_speedRamp->calculateRamp();

    //update model
    QModelIndex rampIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, static_cast<int>(VFDDataColumn::RampSpeed));
    m_vfdModel->setData(rampIndex, m_speedRamp->output());

    setSpeed(m_speedRamp->output());
    getSpeed();

    //update feedback speed in model is in onReadyRead slot

    //setDirection
    QModelIndex directionIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, static_cast<int>(VFDDataColumn::Direction));
    double direction = m_vfdModel->data(directionIndex).toDouble();
    setDirection(direction);
}
