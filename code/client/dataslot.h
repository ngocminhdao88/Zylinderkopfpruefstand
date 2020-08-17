#ifndef DATASLOT_H
#define DATASLOT_H

#include "global.h"
#include <QString>
#include <QVector>
#include <atomic>

/**
 * @brief Samples are sotred in an arry of Slots.
 *
 * Each Slot contains 1M values and may be flushed to disk if RAM runs low.
 * Slots are further divided into "blocks" that cache min/max values.
 */
class DataSlot
{
public:
    /**
     * @brief Default constructor
     */
    DataSlot();

    /**
     * @brief Copy constructor
     */
    DataSlot(const DataSlot &other);

    /**
      * @brief Default destructor
      */

    ~DataSlot();

    /**
     * @brief Flush the data in rame to disk
     */
    void moveToDisk();

    /**
     * @brief Remove cached data from disk
     */
    void removeFromDisk();

    /**
     * @brief Set a sample in this slot at index to value
     */
    void setSample(int index, float value);

    /**
     * @brief Get a sample from this slot at index
     */
    float getSample(int index);

    /**
     * @brief Get a minimum value in this block
     */
    float getMinimumInBlock();

    /**
     * @brief Get a maximum value in this block
     */
    float getMaximumInBlock();

    /**
     * @brief isInRam
     * @return true if DataSlot is in RAM, false if they are on disk
     */
    bool isInRam() const;

    /**
     * @return All samples in this slot
     */
    QVector<float>& getSamples();

private:
    /**
     * @brief Read cached data on disk into RAM
     */
    void copyToRam();

    /**
     * @brief Generate a unique name to cache this Slots data on disk
     */
    QString getUniqueName();


private:
    QString m_pathOnDisk;

    std::atomic<bool> m_inRam  {false};
    std::atomic<bool> m_flushing {false};

    QVector<float> m_samples;
};

#endif // DATASLOT_H
