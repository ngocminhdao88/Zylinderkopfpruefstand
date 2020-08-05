#include "dataslot.h"
#include <QRandomGenerator>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDataStream>

DataSlot::DataSlot(QObject *parent) : QObject(parent),
    m_values(DataSetEnum::SLOT_SIZE),
    m_minimumValueInBlock(DataSetEnum::SLOT_SIZE / DataSetEnum::BLOCK_SIZE),
    m_maximumValueInBlock(DataSetEnum::SLOT_SIZE / DataSetEnum::BLOCK_SIZE)
{
    m_pathOnDisk = getUniqueName(); // TODO: generate unique number for this Slot
}

void DataSlot::moveToDisk() {
    if (!m_inRam || m_flushing)
        return;

    m_flushing = true;

    // TODO: do this operation on different thread
    QFile m_file(m_pathOnDisk);
    if (m_file.open(QIODevice::WriteOnly)) {
        QDataStream out(&m_file);
        out << m_values;
        out << m_minimumValueInBlock;
        out << m_maximumValueInBlock;
        m_file.close();

        m_inRam = false;
        m_flushing = false;
        m_values.clear();
        m_values.squeeze(); // release space in RAM
    }
}

void DataSlot::removeFromDisk() {
    QFile::remove(m_pathOnDisk);
}

void DataSlot::setValue(int index, float value) {
    if (!m_inRam)
        copyToRam();

    m_values[index] = value;

    int blockNumber = index / DataSetEnum::BLOCK_SIZE;

    if (index % DataSetEnum::BLOCK_SIZE == 0) {
        // new block -> min = max = value
        m_minimumValueInBlock[blockNumber] = value;
        m_maximumValueInBlock[blockNumber] = value;
    } else {
        // update min / max if needed
        if (value < m_minimumValueInBlock[blockNumber])
            m_minimumValueInBlock[blockNumber] = value;

        if (value > m_maximumValueInBlock[blockNumber])
            m_maximumValueInBlock[blockNumber] = value;
    }
}

float DataSlot::getValue(int index) {
    if (!m_inRam)
        copyToRam();

    return m_values[index];
}

float DataSlot::getMinimumInBlock(int blockIndex) {
    if (!m_inRam)
        copyToRam();

    return m_minimumValueInBlock[blockIndex];
}

float DataSlot::getMaximumInBlock(int blockIndex) {
    if (!m_inRam)
        copyToRam();

    return m_maximumValueInBlock[blockIndex];
}

void DataSlot::copyToRam() {
    QFile m_file(m_pathOnDisk);

    if (m_file.open(QIODevice::ReadOnly)) {
        QDataStream in(&m_file);
        in >> m_values;
        in >> m_minimumValueInBlock;
        in >> m_maximumValueInBlock;
        m_file.close();

        m_inRam = true;
    }
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
