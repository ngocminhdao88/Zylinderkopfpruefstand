#ifndef RAMPGENERATOR_H
#define RAMPGENERATOR_H

#include <QObject>

class RampGenerator : public QObject
{
    Q_OBJECT
public:
    explicit RampGenerator(QObject *parent = nullptr);

    /*
     * Enable the ramp generator
     *
     * The ramp generator will only calculate new output data if it is enabled
     * @param enable Enable the ramp generator.
     */
    void setEnable(bool enable);

    /*
     * Indicate that the ramp output has reached the target value
     *
     * @return bool
     */
    bool isValueReached();

    /*
     * Ramp generator output
     *
     * @return double Calculated ramp value
     */
    double output();

public slots:
    /**
     * Calculating the ramp
     *
     * A slot to force this ramp generator to calculate a new value
     */
    void calculateRamp();

    /**
     * Set the ramp target value
     *
     * This is the maximal number this ramp can generate
     */
    void setTargetValue(double target);

    /**
     * Set the ramp up rate
     *
     * This sets how fast the ramp reaches its target value
     * when the current output is less than wanted output.
     */
    void setRampUpRate(double rate);

    /**
     * Set the ramp down rate
     *
     * This sets how fast the ramp reaches its target value
     * when the current output is greater than wanted output.
     */
    void setRampDownRate(double rate);

    /**
     * Set the ramp start value
     *
     * This the default output value of the ramp when it first started
     */
    void setStartValue(double rate);

signals:
    /**
     * Signal outputChanged
     *
     * This signal will be emited when the ramp generates a new value
     * @param newValue This is the new ramp output value
     */
    void outputChanged(double newValue);

    /*
     * Signal valueReached
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
