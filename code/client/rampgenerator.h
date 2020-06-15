#ifndef RAMPGENERATOR_H
#define RAMPGENERATOR_H

#include <QObject>

class RampGenerator : public QObject
{
    Q_OBJECT
public:
    explicit RampGenerator(QObject *parent = nullptr);

    /*
     * @brief Enable the ramp generator to run
     */
    void setEnable(bool enable);

    /*
     * @brief Ramp output has reached the target value
     */
    bool isValueReached();

    /*
     * @brief Ramp generator output
     */
    double output();

public slots:
    /*
     * @brief Calculating the ramp
     */
    void calculateRamp();

    /*
     * @brief Set the ramp target value
     */
    void setTargetValue(double target);

    /*
     * @brief Set the ramp up rate
     */
    void setRampUpRate(double rate);

    /*
     * @brief Set the ramp down rate
     */
    void setRampDownRate(double rate);

    /*
     * @brief Set the ramp start value
     */
    void setStartValue(double rate);

signals:
    /*
     * @brief Signal when output has changed from last value
     */
    void outputChanged(double newValue);
    /*
     * @brief Signal when output has reached the target value
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
