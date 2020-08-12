#include "dataset.h"
#include <QDateTime>
#include <algorithm>

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
    m_sampleCount = other.m_sampleCount;
    m_location = other.m_location;
    m_name = other.m_name;
    m_color = other.m_color;
    m_glColor = other.m_glColor;
    m_unit = other.m_unit;
    m_convertionFactorA = other.m_convertionFactorA;
    m_convertionFactorB = other.m_convertionFactorB;
    m_convertionFactor = other.m_convertionFactor;
    m_isBitfield = other.m_isBitfield;
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

void DataSet::addSample(float value) {
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
    // TODO: determine how much space is avaiable and how much is used
    // by the timestamps and datasets
    long maxHeapSize = 0; // TODO: logic
    long currentSize = 0;

    for (int i = 0; i < m_timestamps.size(); i++) {
        currentSize += DataSetEnum::SLOT_SIZE * 8; // float is 4 bytes, 4 for data + 4 for timestamps
    }
//    currentSize += (getDatasetsCount() / 2) * currentSize;

    if (currentSize > maxHeapSize / 2) {
        // figure out which slots NOT to flush
        int firstProtectedSlotA = m_minimumSampleNumberOnScreen / DataSetEnum::SLOT_SIZE;
        int lastProtectedSlotA = m_maximumSampleNumberOnScreen / DataSetEnum::SLOT_SIZE;

        for (int i = 0; i < m_timestamps.size(); i++) {
            // don't flush protected slots
            if (i >= firstProtectedSlotA && i <= lastProtectedSlotA)
                continue;

            // TODO: stop checking if we reached the end

            // move the unnecessary timestamps and datasets to disk
            if (m_timestamps[i].isInRam()) {
                m_timestamps[i].moveToDisk();

                //            for (int j = 0; i < getDatasetsCount(); j++)
                //                getDatasetByIndex(j).slots[i].moveToDisk();
            }
            // using map the keeps track of all datasets
        }
    }
}

long DataSet::getTimestamp(int sampleNumber) {
    if (sampleNumber < 0)
        return 0;

    int slotNumber = sampleNumber / DataSetEnum::SLOT_SIZE;
    int slotIndex = sampleNumber % DataSetEnum::SLOT_SIZE;

    return m_timestamps[slotNumber].getValue(slotIndex);
}

long DataSet::getFirstTimestamp() {
    return m_firstTimestamp;
}

bool DataSet::removeDataset(int location) {
}

void DataSet::dontFlushRangeOnScreen(int minimumSampleNumber, int maximumSampleNumber) {
    m_minimumSampleNumberOnScreen = minimumSampleNumber;
    m_maximumSampleNumberOnScreen = maximumSampleNumber;
}

float DataSet::getMinInRange(int firstSampleNumber, int lastSampleNumber) {
    QVector<float> samples = getSamples(firstSampleNumber, lastSampleNumber);

    return *std::min_element(samples.begin(), samples.end());
}

float DataSet::getMaxInRange(int firstSampleNumber, int lastSampleNumber) {
    auto samples_vec = getSamples(firstSampleNumber, lastSampleNumber);

    return *std::max_element(samples_vec.begin(), samples_vec.end());
}
