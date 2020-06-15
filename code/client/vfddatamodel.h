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

struct VFDData
{
    double controlSpeed;
    double rampSpeed;
    double feedbackSpeed;
    double turnDirection;
    double acceleration;
    double deceleration;
};

enum {
    ControlSpeedColumn = 0,
    RampSpeedColumn = 1,
    FeedbackSpeedColumn = 2,
    DirectionColumn = 3,
    AccelerationColumn = 4,
    DecelerationColumn = 5,
};

class VFDDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    VFDDataModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /*
     * @brief Get the whole vfd data
     */
    const VFDData getVFDData() const;

signals:
    void updateViewport();

private:
    struct VFDData vfdData;
};

#endif // VFDDATAMODEL_H
