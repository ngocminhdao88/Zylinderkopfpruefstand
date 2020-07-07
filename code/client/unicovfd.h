#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include <QTimer>
#include <QModbusClient>
#include <QAbstractItemModel>

#include "abstractvfd.h"
#include "rampgenerator.h"

class UnicoVFD : public QObject, public AbstractVFD
{
    Q_OBJECT

public:
    UnicoVFD(QModbusClient *modbusDevice = nullptr,
             QAbstractItemModel *model = nullptr,
             QTimer *pacemaker = nullptr,
             QObject *parent = nullptr);

    ~UnicoVFD() override;

    /**
     * Set the modbus device for this VFD
     *
     * @param device A modbus device, which is used to connect to the VFD
     */
    void setDevice(QModbusClient *device);

    /**
     * Set the vfd data model
     *
     * @param model A model holds all data of the VFD
     */
    void setModel(QAbstractItemModel *model);

    /**
     * Set the pacemaker for this VFD
     *
     * @param pacemaker A clock which shows how often data are sended to VFD
     */
    void setPacemaker(QTimer *pacemaker);


    /**
     * Set VFD speed
     *
     * @param speed Wanted motor speed
     */
    void setSpeed(double speed) override;

    /**
     * Set the motor turn direction
     *
     * @param dir Motor's turn direction. 0 -> STOP, 1 -> CCW and 2 -> CW.
     */
    void setDirection(double dir) override;

    void setRampUpRate(double rate) override;
    void setRampDownRate(double rate) override;

    /**
     * Get the motor's speed using VFD reading
     *
     * @return Motor's speed
     */
    double getSpeed() override;

public slots:
    /**
     * Handle update request from mainwindow
     */
    void onUpdateRequest();

private slots:
    /**
     * Handles the replies from Modbus device
     */
    void onReadReady();

    /**
     * Handle the dataChanged signal from data model
     */
    void onModelDataChanged(QModelIndex topLeft, QModelIndex bottomRight);

private:
    /**
     * Scale the rate value to the pacemaker update rate
     */
    double normalizeRate(double rate);

    /**
     * Parsing the feedback speed from VFD
     */
    double getFeedbackSpeed(double fb, uint direction);

private:
    QModbusClient * m_modbusDevice = nullptr;
    QAbstractItemModel * m_vfdModel = nullptr;

    RampGenerator * m_speedRamp = nullptr;
    QTimer * m_paceMaker = nullptr;
};

#endif // UNICOVFD_H
