#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include <QTimer>
#include <QModbusClient>
#include <QAbstractItemModel>
#include "vfdsettingsdialog.h"

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
    UnicoVFD(QObject *parent = 0, QAbstractItemModel *model = 0);

    /**
      * @brief Default destructor
      */
    ~UnicoVFD() override;

    /**
     * @brief Set the vfd data model for this VFD
     *
     * @param model A model holds all data of the VFD
     */
    void setModel(QAbstractItemModel *model);

    /**
     * @brief Set VFD speed
     *
     * @param speed Wanted motor speed
     */
    void setSpeed(int speed) override;

    /**
     * @brief Set the motor turn direction
     *
     * @param dir Motor's turn direction. 0 -> STOP, 1 -> CCW and 2 -> CW.
     */
    void setDirection(int dir) override;

    void setRampUpRate(int rate) override;
    void setRampDownRate(int rate) override;

    /**
     * @brief Get the motor's speed from VFD reading
     *
     * @return Motor's speed
     */
    int getSpeed() override;

    /**
     * @brief Connect to the Unico VFD using Serial Modbus
     */
    bool connectDevice() override;

    /**
     * @brief Configure the Unico VFD device
     *
     * User can change the serial Modbus parameters, which used to connect to
     * this Unico VFD. There are also some basic VFDs parameters like maximal
     * speed or acceleration.
     */
    void configDevice() override;

    /**
     * @brief Initiate the VFD device
     *
     * Create a serial modbus client object to handle the communication
     * between host pc and the vfd device
     */
    void initDevice() override;

    /**
     * @brief Indicate if the host pc is connected to the VFD device
     * @return bool
     */
    bool isConnected() override;

public slots:
    /**
     * @brief Handle VFD update request
     *
     * The pacemaker timer (in mainwindow) timeout signal will trigger this slot.
     * The speed ramp output will be calculated and sent to VFD. The motor speed will
     * be readed from VFD and motors direction.
     */
    void onUpdateRequest() override;

private slots:
    /**
     * @brief Handles the replies from Modbus device
     */
    void onReadReady();

    /**
     * @brief Handle the dataChanged signal from data model
     *
     * Update the new ramp setpoint, ramp rate and direction for VFD
     * @param topLeft Models starting range with new data
     * @param bottomRight Models ending range with new data
     */
    void onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    /**
     * @brief Scale the ramps rate value to the pacemaker update clock
     *
     * @param rate Users desired ramp rate
     * @return double Scaled ramp rate with pacemaker update clock
     */
    int normalizeRampRate(int rate);

    /**
     * @brief Parsing the feedback speed from VFD
     *
     * @param fbSpeed Raw speed feedback from the VFD
     * @param direction Motors turn direction
     */
    int getFeedbackSpeed(int fbSpeed, int direction);

private:
    QModbusClient * m_modbusDevice = 0;
    QAbstractItemModel * m_vfdModel = 0;
    VfdSettingsDialog *m_settingDialog = 0;
    RampGenerator * m_speedRamp = 0;
    bool m_isConnected = false;
};

#endif // UNICOVFD_H
