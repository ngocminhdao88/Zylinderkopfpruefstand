/*
 * This model holds the data from the VFD:
 * - Control speed (RPM/m)
 * - Feedback speed (readonly)
 * - Turn direction (0:stop, 1:cw, 2:ccw)
 * - Acceleration (sec to reach max speed)
 * - Deceleration (sec to reach 0 from max speed)
 *
 * In manual mode, these data will be mapped to according widgets on GUI.
 * In automatic mode, these data will be sended from a TestProfile parser.
 * It is also possible to show these data on a chart.
 */

#ifndef VFDDATAMODEL_H
#define VFDDATAMODEL_H

#include <QAbstractItemModel>

enum  VFDDataColumn {
    ControlSpeedColumn = 0,
    RampSpeedColumn = 1,
    FeedbackSpeedColumn = 2,
    DirectionColumn = 3,
    AccelerationColumn = 4,
    DecelerationColumn = 5,
};

/**
 * @brief Holds all VFDs data like speed, ramp, turn direction etc...
 */
class VFDDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
      * @brief A VFDData type
      */
    typedef struct {
        double controlSpeed;
        double rampSpeed;
        double feedbackSpeed;
        double turnDirection;
        double acceleration;
        double deceleration;
    } VFDData_t;

    /**
     * @brief Default constructor
     *
     * @param parent - A QObject parent, which owns this class
     */
    VFDDataModel(QObject *parent = 0);

    /**
     * @brief Override the rowCount function in QAbstractTableModel
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Override columnCount function in QAbstractTableModel
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Override data function in QAbstractTableModel
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Override headerData function in QAbstractTableModel
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * @brief Override setData function in QAbstractTableModel
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /**
     * @brief Override flags function in QAbstractTableModel
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief Get the whole VFDs data
     *
     * @return VFDData
     */
    const VFDData_t getVFDData() const;

private:
    VFDData_t m_vfdData;
};

#endif // VFDDATAMODEL_H
