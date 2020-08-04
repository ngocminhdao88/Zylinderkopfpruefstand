#ifndef DATASLOT_H
#define DATASLOT_H

#include <QObject>
#include "global.h"

/**
 * @brief Samples are sotred in an arry of Slots.
 *
 * Each Slot contains 1M values and may be flushed to disk if RAM runs low.
 * Slots are further divided into "blocks" that cache min/max values.
 */
class DataSlot : public QObject
{
    Q_OBJECT
public:
    explicit DataSlot(QObject *parent = 0);

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

private:
    /**
     * @brief Read cached data on disk into RAM
     */
    void copyToRam();

    /**
     * @brief Generate a unique name to cache this Slots data on disk
     */
    QString getUniqueName();

signals:

private:
    QString pathOnDisk; // TODO: reimplement toString method for this class
    bool inRam = true; // data is in RAM
    bool flushing = false; // data is currently flushing to disk

    float values[DataSetEnum::SLOT_SIZE];
    float minimumValueInBlock[DataSetEnum::SLOT_SIZE / DataSetEnum::BLOCK_SIZE];
    float maximumValueInBlock[DataSetEnum::SLOT_SIZE / DataSetEnum::BLOCK_SIZE];

};

#endif // DATASLOT_H
