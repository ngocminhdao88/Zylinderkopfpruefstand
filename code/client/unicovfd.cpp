#include <QDebug>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QModbusDevice>

#include "global.h"
#include "unicovfd.h"
#include "vfddatamodel.h"
#include "vfdsettingsdialog.h"

UnicoVFD::UnicoVFD(QObject *parent, QAbstractItemModel *model) :
    AbstractVFD(parent),
    m_settingDialog(new VfdSettingsDialog()),
    m_speedRamp(new RampGenerator(this))
{
    initDevice();
    setModel(model);

    m_speedRamp->setRampUpRate(100);
    m_speedRamp->setRampDownRate(100);
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

void UnicoVFD::setSpeed(int speed) {
    if (!m_modbusDevice)
        return;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return;

    if (speed > UnicoDataEnum::MAX_SPEED)
        return;

    int speedFixPoint = speed * 10;

    QModbusDataUnit data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                           UnicoDataEnum::SPEED_R,
                                           QVector<quint16>() << speedFixPoint);

    if (auto *reply = m_modbusDevice->sendWriteRequest(data, UnicoDataEnum::DEV_ID)) {
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

void UnicoVFD::setDirection(int dir) {
    if (!m_modbusDevice) return;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState) return;

    //guarding input. dir should be 0, 1 or 2
    if (dir > 2) return;

    QModbusDataUnit data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                           UnicoDataEnum::DIR_R,
                                           QVector<quint16>() << dir);
    if (auto *reply = m_modbusDevice->sendWriteRequest(data, UnicoDataEnum::DEV_ID)) {
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

void UnicoVFD::setRampDownRate(int rate) {
    if (m_speedRamp)
        m_speedRamp->setRampDownRate(rate);
}

void UnicoVFD::setRampUpRate(int rate) {
    if (m_speedRamp)
        m_speedRamp->setRampUpRate(rate);
}

int UnicoVFD::getSpeed() {
    if (!m_modbusDevice)
        return -1;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return -1;

    QModbusDataUnit data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                           UnicoDataEnum::FB_SPEED_R,
                                           1);

    if (auto *reply = m_modbusDevice->sendReadRequest(data, UnicoDataEnum::DEV_ID)) {
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
    if (m_settingDialog)
        m_settingDialog->show();
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
            if (unit.startAddress() == UnicoDataEnum::FB_SPEED_R) {
                int rawValue = unit.value(0);
                if (m_vfdModel) {
                    //get motor's turn direction
                    QModelIndex directionIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, TestProfileEnum::DIRECTION_COL);
                    uint direction = m_vfdModel->data(directionIndex).toUInt();

                    //parse feedback speed and update the data model
                    int feedbackSpeed = getFeedbackSpeed(rawValue, direction);
                    QModelIndex feedbackSpeedIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, TestProfileEnum::FB_SPEED_COL);
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
    if (!topLeft.isValid() || !bottomRight.isValid())
        return;
    if (!m_speedRamp)
        return;

    int col = topLeft.column();
    int data = topLeft.data(Qt::DisplayRole).toInt();

    switch (col) {
    case TestProfileEnum::SPEED_COL:
        m_speedRamp->setTargetValue(data);
        break;
    case TestProfileEnum::DIRECTION_COL:
        if (data == 0) {
            m_speedRamp->reset();
            m_speedRamp->setEnable(false);
        } else {
            m_speedRamp->setEnable(true);
        }
        break;
    }
}

int UnicoVFD::normalizeRampRate(int rate) {
    return rate * PACE_MAKER_RATE / 1000;
}

int UnicoVFD::getFeedbackSpeed(int fbSpeed, int direction) {
     int result = -1;

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
    setSpeed(m_speedRamp->output());
    getSpeed();

    //setDirection
    QModelIndex directionIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, TestProfileEnum::DIRECTION_COL);
    int direction = m_vfdModel->data(directionIndex).toInt();
    setDirection(direction);
}
