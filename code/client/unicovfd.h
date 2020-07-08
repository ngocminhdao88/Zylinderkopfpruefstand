#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include <QTimer>
#include <QModbusClient>
#include <QAbstractItemModel>

#include "abstractvfd.h"
#include "rampgenerator.h"

/**
 * @brief The UnicoVFD class helps the software to talk to the Unico S1100 VFD
 * using Modbus
 *
 * @author Ngoc Minh Dao
 */
class UnicoVFD : public AbstractVFD
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor
     * @param modbusDevice - A serial device connected to the Unico VFD
     * @param model - A VFD data model
     * @param pacemaker - A clock/timer, which determines how often data are sended to VFD
     * @param parent - A QObject, which owns this
     */
    UnicoVFD(QModbusClient *modbusDevice = 0,
             QAbstractItemModel *model = 0,
             QTimer *pacemaker = 0,
             QObject *parent = 0);

    /**
      * @brief Default destructor
      */
    ~UnicoVFD() override;

    /**
     * @brief Set the serial modbus device for this VFD
     *
     * @param device A modbus device, which is used to connect to the VFD
     */
    void setDevice(QModbusClient *device);

    /**
     * @brief Set the vfd data model for this VFD
     *
     * @param model A model holds all data of the VFD
     */
    void setModel(QAbstractItemModel *model);

    /**
     * @brief Set the pacemaker (update clock) for this VFD
     *
     * @param pacemaker A clock which shows how often vfds data are updated
     */
    void setPacemaker(QTimer *pacemaker);

    /**
     * @brief Set VFD speed
     *
     * @param speed Wanted motor speed
     */
    void setSpeed(double speed) override;

    /**
     * @brief Set the motor turn direction
     *
     * @param dir Motor's turn direction. 0 -> STOP, 1 -> CCW and 2 -> CW.
     */
    void setDirection(double dir) override;

    void setRampUpRate(double rate) override;
    void setRampDownRate(double rate) override;

    /**
     * @brief Get the motor's speed from VFD reading
     *
     * @return Motor's speed
     */
    double getSpeed() override;

public slots:
    /**
     * @brief Handle update request from mainwindow
     *
     * Update the new motors control speed and turn direction
     */
    void onUpdateRequest();

private slots:
    /**
     * @brief Handles the replies from Modbus device
     */
    void onReadReady();

    /**
     * @brief Handle the dataChanged signal from data model
     *
     * Update the new target ramp value, ramp rate for VFD
     * @param topLeft Models starting range with new data
     * @param bottomRight Models ending range with new data
     */
    void onModelDataChanged(QModelIndex topLeft, QModelIndex bottomRight);

private:
    /**
     * @brief Scale the ramps rate value to the pacemaker update clock
     *
     * @param rate Users desired ramp rate
     * @return double Scaled ramp rate with pacemaker update clock
     */
    double normalizeRampRate(double rate);

    /**
     * @brief Parsing the feedback speed from VFD
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
