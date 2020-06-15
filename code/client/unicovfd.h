#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QModbusClient>
#include <QModbusDataUnit>
#include <QAbstractItemModel>
#include "abstractvfd.h"
#include "vfddatamodel.h"
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

    /*
     * @brief Set the modbus device for this VFD
     */
    void setDevice(QModbusClient *device);

    /*
     * @brief Set the vfd data model
     */
    void setModel(QAbstractItemModel *model);

    /*
     * @brief Set the pacemaker for this VFD
     */
    void setPacemaker(QTimer * pacemaker);


    void setSpeed(double speed) override;
    void setDirection(double dir) override;
    void setRampUpRate(double rate) override;
    void setRampDownRate(double rate) override;
    double getSpeed() override;

public slots:
    /*
     * Handle update request from mainwindow
     */
    void onUpdateRequest();

private slots:
    /*
     * Handles the replies from Modbus device
     */
    void onReadReady();

    /*
     * Handle the dataChanged signal from data model
     */
    void onModelDataChanged(QModelIndex topLeft, QModelIndex bottomRight);

private:
    /*
     * @brief Scale the rate value to the pacemaker update rate
     */
    double normalizeRate(double rate);

    /*
     * @brief Parsing the feedback speed from VFD
     */
    double getFeedbackSpeed(double fb, uint direction);

private:
    QModbusClient * m_modbusDevice = nullptr;
    QAbstractItemModel * m_vfdModel = nullptr;

    RampGenerator * m_speedRamp = nullptr;
    QTimer * m_paceMaker = nullptr;
};

#endif // UNICOVFD_H
