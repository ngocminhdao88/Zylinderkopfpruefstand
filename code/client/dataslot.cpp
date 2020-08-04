#include "dataslot.h"
#include <QRandomGenerator>
#include <QFileInfo>
#include <QDir>

DataSlot::DataSlot(QObject *parent) : QObject(parent)
{
    pathOnDisk = getUniqueName(); // TODO: generate unique number for this Slot
}

void DataSlot::moveToDisk() {
    if (!inRam || flushing)
        return;

    flushing = true;

    // TODO: flush data to disk using a worker thread
    // Write values, minimumValueInBlock and maximumValueInBlock array to disk
    // After the flushing the clear the data, set inRam and flushing flag to false
}

void DataSlot::removeFromDisk() {
}

void DataSlot::setValue(int index, float value) {
    if (!inRam)
        copyToRam();

    values[index] = value;

    int blockNumber = index / DataSetEnum::BLOCK_SIZE;

    if (index % DataSetEnum::BLOCK_SIZE == 0) {
        // new block -> min = max = value
        minimumValueInBlock[blockNumber] = value;
        maximumValueInBlock[blockNumber] = value;
    } else {
        // update min / max if needed
        if (value < minimumValueInBlock[blockNumber])
            minimumValueInBlock[blockNumber] = value;

        if (value > maximumValueInBlock[blockNumber])
            maximumValueInBlock[blockNumber] = value;
    }
}

float DataSlot::getValue(int index) {
    if (!inRam)
        copyToRam();

    return values[index];
}

float DataSlot::getMinimumInBlock(int blockIndex) {
    if (!inRam)
        copyToRam();

    return minimumValueInBlock[blockIndex];
}

float DataSlot::getMaximumInBlock(int blockIndex) {
    if (!inRam)
        copyToRam();

    return maximumValueInBlock[blockIndex];
}

void DataSlot::copyToRam() {
    // TODO: read cached data from disk into RAM
    // set the inRam flag for this slot to true
}

QString DataSlot::getUniqueName() {
    bool nameFound = false;
    QString uniqueName;

    while (!nameFound) {
        quint32 uniqueNumber = QRandomGenerator::global()->generate();
        QFileInfo fi(QDir("cached"), QString::number(uniqueNumber));

        if (!fi.exists()) {
            uniqueName = fi.absolutePath();
            nameFound = true;
        }
    }
    return uniqueName;
}
