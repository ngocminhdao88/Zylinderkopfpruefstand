#ifndef ABSTRACTVFD_H
#define ABSTRACTVFD_H

#include <QObject>
#include <QString>

/**
 * @brief The AbstractVFD class
 *
 * There are some virtual functions in this class, which must be implementd in its child
 */
class AbstractVFD : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the AbstractVFD class
     *
     * @param parent as QObject
     */
    explicit AbstractVFD(QObject *parent = 0) : QObject(parent) {};

    /**
     * @brief Set VFD speed
     */
     virtual void setSpeed(double speed) = 0;

    /**
     * @brief Set VFD turn direction
     */
     virtual void setDirection(double dir) = 0;

    /**
     * @brief Set VFD ramp rate
     */
     virtual void setRampUpRate(double rate) = 0;

    /**
     * @brief Set VFD ramp down rate
     */
     virtual void setRampDownRate(double rate) = 0;

    /**
     * @brief Get VFD speed
     */
     virtual double getSpeed() = 0;

    /**
     * @brief Connect to the VFD device
     */
    virtual bool connectDevice() = 0;

    /**
     * @brief Configure the VFD device
     */
    virtual void configDevice() = 0;

    /**
     * @brief Initiate the VFD device
     */
    virtual void initDevice() = 0;

    /**
     * @brief Indicate if the host pc is connected with the VFD device
     * @return bool
     */
    virtual bool isConnected() = 0;

signals:
    void errorOccured(QString errMsg);
    void statusChanged(QString status);
};

#endif // ABSTRACTVFD_H
