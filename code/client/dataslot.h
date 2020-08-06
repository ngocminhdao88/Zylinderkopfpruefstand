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
    DataSlot();

    DataSlot(const DataSlot &other);

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
     * @brief Set the DataSet at index to value
     */
    void setValue(int index, float value);

    /**
     * @brief Get a value from DataSet at index
     */
    float getValue(int index);

    /**
     * @brief Get a minimum value from a block index
     */
    float getMinimumInBlock(int blockIndex);

    /**
     * @brief Get a maximum value from a block index
     */
    float getMaximumInBlock(int blockIndex);

    /**
     * @brief isInRam
     * @return true if DataSlot is in RAM, false if they are on disk
     */
    bool isInRam() const;

    /**
     * @return A reference to values vector
     */
    QVector<float>& getValues();

    /**
     * @return A reference to minimalValueInBlock vector
     */
    QVector<float>& getMininumValueBlock();

    /**
     * @return A reference to maximalValueInBlock vector
     */
    QVector<float>& getMaximumValueBlock();

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
    QString m_pathOnDisk; // TODO: reimplement toString method for this class

    std::atomic<bool> m_inRam  {false};
    std::atomic<bool> m_flushing {false};

    QVector<float> m_values;
//    float values[DataSetEnum::SLOT_SIZE];
    QVector<float> m_minimumValueInBlock;
//    float minimumValueInBlock[DataSetEnum::SLOT_SIZE / DataSetEnum::BLOCK_SIZE];
    QVector<float> m_maximumValueInBlock;
//    float maximumValueInBlock[DataSetEnum::SLOT_SIZE / DataSetEnum::BLOCK_SIZE];

};

#endif // DATASLOT_H
