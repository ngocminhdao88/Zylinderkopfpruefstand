#include "dataset.h"
#include <QTime>

DataSet::DataSet(int location, QString name, QColor color, QString unit, float convertionFactorA, float convertionFactorB, QObject *parent) : QObject(parent),
    m_slots(DataSetEnum::SLOT_COUNT),
    m_timestamps(DataSetEnum::SLOT_COUNT)
{
    m_sampleCount = 0;
    m_location = location;
    m_name = name;
    m_color = color;
    m_glColor = {float(color.red())/255, float(color.green())/255, float(color.blue())/255, 1};
    m_unit = unit;
    m_convertionFactorA = convertionFactorA;
    m_convertionFactorB = convertionFactorB;
    m_convertionFactor = convertionFactorB / convertionFactorA;
    m_isBitfield = false;
}

void DataSet::setNameColorUnit(QString name, QColor color, QString unit) {
    m_name = name;
    m_color = color;
    m_glColor = {float(color.red())/255, float(color.green())/255, float(color.blue())/255, 1};
    m_unit = unit;
}

QString DataSet::getName() {
    return m_name;
}

float DataSet::getSample(int index) {
    int slotNumber = index / DataSetEnum::SLOT_SIZE;
    int slotIndex = index % DataSetEnum::SLOT_SIZE;

    return m_slots[slotNumber].getValue(slotIndex);
}

QVector<float> DataSet::getSamples(int startIndex, int endIndex) {
    int sampleCount = endIndex - startIndex + 1;
    QVector<float> samples(sampleCount);

    for (int i = 0; i < sampleCount; i++) {
        samples[i] = getSample(i + startIndex);
    }

    return samples;
}

void DataSet::add(float value) {
    value *= m_convertionFactor;
    int currentSize = getSampleCount();
    int slotNumber = currentSize / DataSetEnum::SLOT_SIZE;
    int slotIndex = currentSize % DataSetEnum::SLOT_SIZE;

    if (slotIndex == 0)
        m_slots[slotNumber].setValue(slotIndex, value);
}

int DataSet::getSampleCount() {
    return m_sampleCount;
}

void DataSet::incrementSampleCount() {
    int currentSize = getSampleCount();
    int slotNumber = currentSize / DataSetEnum::SLOT_SIZE;
    int slotIndex = currentSize % DataSetEnum::SLOT_SIZE;

    flushIfNecessary();
//    m_timestamps[slotNumber].setValue(slotIndex, QTime::currentTime());
}

void DataSet::flushIfNecessary() {
}
