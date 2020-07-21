#include "rampgenerator.h"

RampGenerator::RampGenerator(QObject *parent) : QObject(parent) {
    setEnable(false); // disable the ramp generator by default
}

RampGenerator::~RampGenerator() {
}

void RampGenerator::reset() {
    m_lastOuput = m_startValue;
}

void RampGenerator::setEnable(bool enable) {
    if (m_enable != enable) m_enable = enable;
}

bool RampGenerator::isValueReached() {
    return m_valueReached;
}

void RampGenerator::calculateRamp() {
    //only calculate the ramp if it's enabled
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

void RampGenerator::setTargetValue(int target)
{
    if (m_targetValue != target)
        m_targetValue = target;
}

void RampGenerator::setRampUpRate(int rate)
{
    if (rate < 0)
        return;

    if (m_rampUpRate != rate)
        m_rampUpRate = rate;
}

void RampGenerator::setRampDownRate(int rate)
{
    if (rate < 0)
        return;

    if (m_rampDownRate != rate)
        m_rampDownRate = rate;
}

void RampGenerator::setStartValue(int value)
{
    if (m_startValue != value)
        m_startValue = value;
}

int RampGenerator::output()
{
    return m_lastOuput;
}
