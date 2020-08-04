#ifndef DATASET_H
#define DATASET_H

#include <QObject>
#include <QColor>

/**
 * @brief The DataSet class defines all of the details about one CSV column or
 * Binary packet field, stores all of its samples and provide  several ways to
 * get the samples
 */
class DataSet : public QObject
{
    Q_OBJECT
public:
    DataSet();

private:
    int location;
    // TODO: binary field processor
    QString name;
    QColor color;
    float glColor[4];
    QString unit;
    float convertionFactorA;
    float convertionFactorB;
    float convertionFactor;

    bool isBitfield;
    // TODO: private member for bitfield
};

#endif // DATASET_H
