#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include <QTimer>
#include <QModbusClient>
#include <QAbstractItemModel>

#include "abstractvfd.h"
#include "rampgenerator.h"

class UnicoVFD : public AbstractVFD
{
    Q_OBJECT

public:
    UnicoVFD(QModbusClient *modbusDevice = 0,
             QAbstractItemModel *model = 0,
             QTimer *pacemaker = 0,
             QObject *parent = 0);

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
     * @param pacemaker A clock which shows how often vfds data are updated
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
     *
     * Update the new motors control speed and turn direction
     */
    void onUpdateRequest();

private slots:
    /**
     * Handles the replies from Modbus device
     */
    void onReadReady();

    /**
     * Handle the dataChanged signal from data model
     *
     * Update the new target ramp value, ramp rate for VFD
     * @param topLeft Models starting range with new data
     * @param bottomRight Models ending range with new data
     */
    void onModelDataChanged(QModelIndex topLeft, QModelIndex bottomRight);

private:
    /**
     * Scale the ramps rate value to the pacemaker update clock
     *
     * @param rate Users desired ramp rate
     * @return double Scaled ramp rate with pacemaker update clock
     */
    double normalizeRampRate(double rate);

    /**
     * Parsing the feedback speed from VFD
     *
     * @param fbSpeed Raw speed feedback from the VFD
     * @param direction Motors turn direction
     */
    double getFeedbackSpeed(double fbSpeed, uint direction);

private:
    QModbusClient * m_modbusDevice = 0;
    QAbstractItemModel * m_vfdModel = 0;

    RampGenerator * m_speedRamp = 0;
    QTimer * m_paceMaker = 0;
};

#endif // UNICOVFD_H
