#include "unicovfd.h"

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

UnicoVFD::UnicoVFD(QModbusClient *modbusDevice, QAbstractItemModel *model, QTimer *pacemaker, QObject *parent) :
    QObject(parent),
    m_modbusDevice(modbusDevice),
    m_speedRamp(new RampGenerator(this))
{
    setModel(model);
    setPacemaker(pacemaker);
    m_speedRamp->setEnable(true);
}

UnicoVFD::~UnicoVFD()
{
}

void UnicoVFD::setDevice(QModbusClient *device)
{
    m_modbusDevice = device;
}

void UnicoVFD::setModel(QAbstractItemModel *model)
{
    if (!model)
        return;

    m_vfdModel = model;

    connect(m_vfdModel, &QAbstractItemModel::dataChanged,
            this, &UnicoVFD::onModelDataChanged);
}

void UnicoVFD::setPacemaker(QTimer *pacemaker)
{
    m_paceMaker = pacemaker;

    if (m_paceMaker) {
        connect(m_paceMaker, &QTimer::timeout, this, &UnicoVFD::onUpdateRequest);
    }
}

void UnicoVFD::setSpeed(double speed)
{
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

void UnicoVFD::setDirection(double dir)
{
    if (!m_modbusDevice)
        return;

    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
        return;

    //guarding input. dir should be 0, 1 or 2
    if (dir > 2)
        return;

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

void UnicoVFD::setRampDownRate(double rate)
{
    Q_UNUSED(rate)
}

void UnicoVFD::setRampUpRate(double rate)
{
    Q_UNUSED(rate)
}

double UnicoVFD::getSpeed()
{
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

void UnicoVFD::onReadReady()
{
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
                    QModelIndex dirIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, DirectionColumn);
                    uint direction = m_vfdModel->data(dirIndex).toUInt();

                    //parse feedback speed and update the data model
                    double feedbackSpeed = getFeedbackSpeed(rawValue, direction);
                    QModelIndex feedbackSpeedIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, FeedbackSpeedColumn);
                    m_vfdModel->setData(feedbackSpeedIndex, feedbackSpeed);
                }
            }
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError) {
        //Protocol error -> do something about that
    }
    else {
        //Read respone error -> do something about that
    }

    reply->deleteLater();
}

void UnicoVFD::onModelDataChanged(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_UNUSED(bottomRight)

    if (!topLeft.isValid())
        return;

    int col = topLeft.column();
    double data = topLeft.data(Qt::DisplayRole).toDouble();

    switch (col) {
    case ControlSpeedColumn:
        m_speedRamp->setTargetValue(data);
        break;
    case AccelerationColumn:
        //send acceleration request
        m_speedRamp->setRampUpRate(normalizeRate(data));
        break;
    case DecelerationColumn:
        //send deceleration request
        m_speedRamp->setRampDownRate(normalizeRate(data));
        break;
    }
}

double UnicoVFD::normalizeRate(double rate)
{
    double pacemakerRate = m_paceMaker->interval();
    return rate * pacemakerRate / 1000;
}

double UnicoVFD::getFeedbackSpeed(double fb, uint direction)
{
    double result = -1;

    if (direction == 0)
        result = -1;

    if (direction == 1)
        result = fb / 10;

    if (direction == 2)
        result = (fb - 65536) / 10; //2^16 = 65536

    return result;
}

void UnicoVFD::onUpdateRequest()
{
    //calculate speed ramp
    m_speedRamp->calculateRamp();
    //update model
    QModelIndex rampIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, RampSpeedColumn);
    m_vfdModel->setData(rampIndex, m_speedRamp->output());
    //send ramp speed request
    setSpeed(m_speedRamp->output());
    //send get speed request
    getSpeed();
    //update feedback speed in model is in onReadyRead slot
    //setDirection
    QModelIndex directionIndex = m_vfdModel->index(m_vfdModel->rowCount() - 1, DirectionColumn);
    double direction = m_vfdModel->data(directionIndex).toDouble();
    setDirection(direction);
}
