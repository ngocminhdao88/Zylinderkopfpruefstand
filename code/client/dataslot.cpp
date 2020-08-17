#include "dataslot.h"
#include <QRandomGenerator>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <thread>
#include <future>
#include <algorithm>

DataSlot::DataSlot() :
    m_samples(DataSetEnum::SLOT_SIZE)
{
    m_pathOnDisk = getUniqueName(); // TODO: generate unique number for this Slot
}

DataSlot::DataSlot(const DataSlot &other) {
    m_samples = other.m_samples;
}

DataSlot::~DataSlot() {
}

void DataSlot::moveToDisk() {
    if (!m_inRam || m_flushing)
        return;

    m_flushing = true;

    // do write operation on different thread asynchronously
    std::async(std::launch::async, [this]{
        QFile m_file(m_pathOnDisk);
        if (m_file.open(QIODevice::WriteOnly)) {
            QDataStream out(&m_file);
            out << m_samples;
            m_file.close();

            m_inRam = false;
            m_flushing = false;
            m_samples.clear();
            m_samples.squeeze(); // release space in RAM
        }
    });

}

void DataSlot::removeFromDisk() {
    QFile::remove(m_pathOnDisk);
}

void DataSlot::setSample(int index, float value) {
    if (!m_inRam)
    m_samples[index] = value;
}

float DataSlot::getSample(int index) {
    if (!m_inRam)
        copyToRam();

    return m_samples[index];
}

float DataSlot::getMinimumInBlock() {
    if (!m_inRam)
        copyToRam();

    return *std::min_element(m_samples.begin(), m_samples.end());
}

float DataSlot::getMaximumInBlock() {
    if (!m_inRam)
        copyToRam();

    return *std::max_element(m_samples.begin(), m_samples.end());
}

bool DataSlot::isInRam() const {
    return m_inRam;
}

void DataSlot::copyToRam() {
    // do this operation in another thread async
    std::async(std::launch::async, [this] {
        QFile m_file(m_pathOnDisk);

        if (m_file.open(QIODevice::ReadOnly)) {
            QDataStream in(&m_file);
            in >> m_samples;
            m_file.close();

            m_inRam = true;
        }
    });
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

QVector<float>& DataSlot::getSamples() {
    return m_samples;
}
