#ifndef RAMPGENERATOR_H
#define RAMPGENERATOR_H

#include <QObject>

/**
 * @brief The RampGenerator class ramps the output slowly to the target value
 *
 * @author Ngoc Minh Dao
 * @date July 2020
 */
class RampGenerator : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     *
     * @param parent - A QOject parent
     */
    RampGenerator(QObject *parent = 0);

    /**
     * @brief Default destructor
     */
    ~RampGenerator();

    /**
     * @brief Enable the ramp generator
     *
     * The ramp generator will only calculate new output data if it is enabled
     * @param enable Enable the ramp generator.
     */
    void setEnable(bool enable);

    /**
     * @brief Indicate that the ramp output has reached the target value
     *
     * @return bool
     */
    bool isValueReached();

    /**
     * @brief Ramp generator output
     *
     * @return double Calculated ramp value
     */
    double output();

    /**
     * @brief Reset the ramp to it initiate value
     */
    void reset();

public slots:
    /**
     * @brief Calculating the ramp
     *
     * This function force this ramp generator to calculate a new value.
     * If it is the first time the ramp generator run then the output is
     * equal the start value.
     * If the ramps output is less than the target value (ramp up) then the
     *  new output will be last ouput + ramp up rate.
     * If the ramps output is greater than the target value (ramp down) then the
     * new output will be last ouput - ramp down rate.
     * The ramps output will be capped at target value.
     */
    void calculateRamp();

    /**
     * @brief Set the ramp target value
     *
     * The ramps output will be capped at this target value.
     * @param target - Target value of the ramp generator
     */
    void setTargetValue(double target);

    /**
     * @brief Set the ramp up rate
     *
     * This sets how fast the ramp reaches its target value
     * when the current output is less than wanted output.
     */
    void setRampUpRate(double rate);

    /**
     * @brief Set the ramp down rate
     *
     * This sets how fast the ramp reaches its target value
     * when the current output is greater than wanted output.
     */
    void setRampDownRate(double rate);

    /**
     * @brief Set the ramp start value
     *
     * Set the initiate output value of the ramp when it first started
     */
    void setStartValue(double rate);

signals:
    /**
     * @brief Signal outputChanged
     *
     * This signal will be emitted when the ramp generates a new value
     * @param newValue This is the new ramp output value
     */
    void outputChanged(double newValue);

    /**
     * @brief Signal valueReached
     *
     * This signal will be emited when the ramp output
     * has reached its target value
     */
    void valueReached();

private:
    bool m_firstRun = true;
    double m_lastOuput = 0;
    double m_startValue = 0;
    double m_targetValue = 0;
    double m_rampUpRate = 1; //[unit/s]
    double m_rampDownRate = 1; //[unit/s]
    bool m_valueReached = false;
    bool m_enable = false;
};

#endif // RAMPGENERATOR_H
