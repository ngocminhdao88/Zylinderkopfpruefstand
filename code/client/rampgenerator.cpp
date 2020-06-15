#include "rampgenerator.h"

RampGenerator::RampGenerator(QObject *parent) : QObject(parent)
{

}

void RampGenerator::setEnable(bool enable)
{
    if (m_enable != enable)
        m_enable = enable;
}

bool RampGenerator::isValueReached()
{
    return m_valueReached;
}

void RampGenerator::calculateRamp()
{
    //only run the ramp calculation if it's enabled
    if (!m_enable)
        return;

    m_valueReached = false;

    //first run -> set output to initiate value
    if (m_firstRun) {
        m_firstRun = false;
        m_lastOuput = m_startValue;

        return;
    }

    if (m_lastOuput < m_targetValue) {
        //ramp up
        if (m_lastOuput + m_rampUpRate >= m_targetValue) {
            //cap the ouput at target value
            m_lastOuput = m_targetValue;

            m_valueReached = true;
        } else {
            m_lastOuput += m_rampUpRate;
        }
    } else {
        //ramp down
        if (m_lastOuput - m_rampDownRate <= m_targetValue) {
            //cap the ouput at target value
            m_lastOuput = m_targetValue;

            m_valueReached = true;
        } else {
            m_lastOuput -= m_rampDownRate;
        }
    }

    if (m_valueReached)
        emit valueReached();
}

void RampGenerator::setTargetValue(double target)
{
    if (m_targetValue != target)
        m_targetValue = target;
}

void RampGenerator::setRampUpRate(double rate)
{
    if (rate < 0)
        return;

    if (m_rampUpRate != rate)
        m_rampUpRate = rate;
}

void RampGenerator::setRampDownRate(double rate)
{
    if (rate < 0)
        return;

    if (m_rampDownRate != rate)
        m_rampDownRate = rate;
}

void RampGenerator::setStartValue(double value)
{
    if (m_startValue != value)
        m_startValue = value;
}

double RampGenerator::output()
{
    return m_lastOuput;
}
