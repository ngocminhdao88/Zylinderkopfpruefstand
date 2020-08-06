#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QColor>
#include <QVector>
#include "dataslot.h"

/**
 * @brief The DataSet class defines all of the details about one CSV column or
 * Binary packet field, stores all of its samples and provide  several ways to
 * get the samples
 */
class DataSet
{
public:
    DataSet(int location, QString name,
            QColor color, QString unit,
            float convertionFactorA, float convertionFactorB);

    ~DataSet();

    DataSet(const DataSet &other);

    /**
     * @brief Update the name, color and unit of this Dataset
     * @param name The new name
     * @param color The new color
     * @param unit The new unit
     */
    void setNameColorUnit(QString name, QColor color, QString unit);

    /**
     * @brief Return the name of this dataset
     */
    QString getName() const;

    /**
     * @brief Return color of this dataset
     */
    QColor getColor() const;

    /**
     * @brief Return unit description of this dataset
     */
    QString getUnit() const;

    /**
     * @brief Return GL color of this dataset
     */
    QVector<float> getGlColor() const;

    /**
     * @brief Return if this dataset represents a bitfield
     */
    bool isBitfield() const;

    /**
     * @brief Get convertion factor of this dataset
     */
    float getConvertionFactor() const;

    /**
     * @brief Get convertion factor A of this dataset
     */
    float getConvertionFactorA() const;

    /**
     * @brief Get convertion factor B of this dataset
     */
    float getConvertionFactorB() const;

    /**
     * @brief Gets on specific sample
     * @param index Which sample to get
     * @return The sample
     */
    float getSample(int index);

    /**
     * @brief Get a series of samples
     * @param startIndex Index of the first sample (inclusive)
     * @param endIndex Index of the last sample (inclusive)
     * @return The sample as QVector<float>
     */
    QVector<float> getSamples(int startIndex, int endIndex);

    /**
     * @brief Add new sample to dataset
     * @param value New sample
     */
    void add(float value);

    /**
     * @brief Get current number of samples stored in the dataset
     */
    int getSampleCount() const;

    /**
     * @brief Get location of this dataset
     */
    int getLocation() const;

    /**
     * @brief Increments the sample count
     *
     * Call this function after all datasets have recieved a new value
     */
    void incrementSampleCount();

    /**
     * @brief Flush the data to disk if the half of RAM is used
     */
    void flushIfNecessary();

    /**
     * @brief Gets the timestamp for one specific sample
     * @param sampleNumber Which sample to check
     * @return The corresponding UNIX timestamp
     */
    long getTimestamp(int sampleNumber);

    /**
     * @return The timestamp for sample number 0,
     * or 0 if there are no samples
     */
    long getFirstTimestamp();

    /**
     * @brief Removes a specific dataset
     * @return true on success, false if nothing existed there
     */
    bool removeDataset(int location);

    /**
     * @brief Prevents slots from being flushed to disk because they are
     * actively being used to draw charts
     *
     * @param minimumSampleNumber Minimum sample number shown on screen
     * @param maximumSampleNumberMaximum sample number shown on screen
     */
    void dontFlushRangeOnScreen(int minimumSampleNumber, int maximumSampleNumber);

private:
    int m_sampleCount;
    int m_location;
    // TODO: binary field processor
    QString m_name;
    QColor m_color;
    QVector<float> m_glColor; // curve color for GL plotting
    QString m_unit;
    float m_convertionFactorA;
    float m_convertionFactorB;
    float m_convertionFactor;

    bool m_isBitfield;
    // TODO: private member for bitfield

    QVector<DataSlot> m_slots;
    QVector<DataSlot> m_timestamps;

    long m_firstTimestamp = 0;

    // for keeping track of what slots not to flush to disk
    int m_minimumSampleNumberOnScreen = -1;
    int m_maximumSampleNumberOnScreen = -1;
};

#endif // DATASET_H
