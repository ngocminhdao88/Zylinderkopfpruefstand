#ifndef ABSTRACTVFD_H
#define ABSTRACTVFD_H

#include <QObject>

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
};

#endif // ABSTRACTVFD_H
