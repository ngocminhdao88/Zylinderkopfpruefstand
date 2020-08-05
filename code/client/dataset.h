#ifndef DATASET_H
#define DATASET_H

#include <QObject>
#include <QColor>
#include "dataslot.h"

/**
 * @brief The DataSet class defines all of the details about one CSV column or
 * Binary packet field, stores all of its samples and provide  several ways to
 * get the samples
 */
class DataSet : public QObject
{
    Q_OBJECT
public:
    DataSet(int location, QString name,
            QColor color, QString unit,
            float convertionFactorA, float convertionFactorB,
            QObject *parent = 0);

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
    QString getName();

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
    int getSampleCount();

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


};

#endif // DATASET_H
