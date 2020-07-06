#ifndef ABSTRACTVFD_H
#define ABSTRACTVFD_H

class AbstractVFD
{
public:
    /*
     * @brief Set VFD speed
     */
    virtual void setSpeed(double speed) = 0;

    /*
     * @brief Set VFD turn direction
     */
    virtual void setDirection(double dir) = 0;

    /*
     * @brief Set VFD ramp rate
     */
    virtual void setRampUpRate(double rate) = 0;

    /*
     * @brief Set VFD ramp down rate
     */
    virtual void setRampDownRate(double rate) = 0;

    /*
     * @brief Get VFD speed
     */
    virtual double getSpeed() = 0;
};

#endif // ABSTRACTVFD_H
