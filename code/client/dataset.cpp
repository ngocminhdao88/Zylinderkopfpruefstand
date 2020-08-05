#include "dataset.h"
#include <QDateTime>

DataSet::DataSet(int location, QString name,
                 QColor color, QString unit,
                 float convertionFactorA, float convertionFactorB):
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

DataSet::~DataSet() {
}

DataSet::DataSet(const DataSet &other) {
    m_sampleCount = other.getSampleCount();
    m_location = other.getLocation();
    m_name = other.getName();
    m_color = other.getColor();
    m_glColor = {float(m_color.red())/255, float(m_color.green())/255, float(m_color.blue())/255, 1};
    m_unit = other.getUnit();
    m_convertionFactorA = other.getConvertionFactorA();
    m_convertionFactorB = other.getConvertionFactorB();
    m_convertionFactor = m_convertionFactorA / m_convertionFactorB;
    m_isBitfield = other.isBitfield();
}

void DataSet::setNameColorUnit(QString name, QColor color, QString unit) {
    m_name = name;
    m_color = color;
    m_glColor = {float(color.red())/255, float(color.green())/255, float(color.blue())/255, 1};
    m_unit = unit;
}

QString DataSet::getName() const {
    return m_name;
}

QColor DataSet::getColor() const {
    return m_color;
}

QString DataSet::getUnit() const {
    return m_unit;
}

QVector<float> DataSet::getGlColor() const {
    return m_glColor;
}

bool DataSet::isBitfield() const {
    return m_isBitfield;
}

float DataSet::getConvertionFactor() const {
    return m_convertionFactor;
}

float DataSet::getConvertionFactorA() const {
    return m_convertionFactorA;
}

float DataSet::getConvertionFactorB() const {
    return m_convertionFactorB;
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

int DataSet::getSampleCount() const {
    return m_sampleCount;
}

int DataSet::getLocation() const {
    return m_location;
}

void DataSet::incrementSampleCount() {
    int currentSize = getSampleCount();
    int slotNumber = currentSize / DataSetEnum::SLOT_SIZE;
    int slotIndex = currentSize % DataSetEnum::SLOT_SIZE;

    flushIfNecessary();
    QDateTime datetime;
    m_timestamps[slotNumber].setValue(slotIndex, datetime.toMSecsSinceEpoch());

    m_sampleCount++;
    // TODO: See DatasetsController.java
}

void DataSet::flushIfNecessary() {
}

long DataSet::getTimestamp(int sampleNumber) const
{

}
