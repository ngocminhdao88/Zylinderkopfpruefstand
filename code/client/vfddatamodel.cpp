#include "vfddatamodel.h"

enum {
    ColumnCount = 6,
    RowCount = 1,
};

VFDDataModel::VFDDataModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int VFDDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return RowCount;
}

int VFDDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnCount;
}

QVariant VFDDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= RowCount || index.column() >= ColumnCount)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == ControlSpeedColumn)
            return m_vfdData.controlSpeed;
        if (index.column() == RampSpeedColumn)
            return m_vfdData.rampSpeed;
        if (index.column() == FeedbackSpeedColumn)
            return m_vfdData.feedbackSpeed;
        if (index.column() == DirectionColumn)
            return m_vfdData.turnDirection;
        if (index.column() == AccelerationColumn)
            return m_vfdData.acceleration;
        if (index.column() == DecelerationColumn)
            return m_vfdData.deceleration;
    }

    return QVariant();
}

QVariant VFDDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == ControlSpeedColumn)
            return "ControlSpeed";
        if (section == RampSpeedColumn)
            return "RampSpeed";
        if (section == FeedbackSpeedColumn)
            return "FeedbackSpeed";
        if (section == DirectionColumn)
            return "TurnDirection";
        if (section == AccelerationColumn)
            return "Acceleration";
        if (section == DecelerationColumn)
            return "Deceleration";
    }

    return QVariant();
}

bool VFDDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= RowCount || index.column() >= ColumnCount)
        return false;

    if (role != Qt::EditRole)
        return false;

    const int col = index.column();

    if (col == ControlSpeedColumn)
        m_vfdData.controlSpeed = value.toDouble();
    if (col == RampSpeedColumn)
        m_vfdData.rampSpeed = value.toDouble();
    if (col == FeedbackSpeedColumn)
        m_vfdData.feedbackSpeed = value.toDouble();
    if (col == DirectionColumn)
        m_vfdData.turnDirection = value.toDouble();
    if (col == AccelerationColumn)
        m_vfdData.acceleration = value.toDouble();
    if (col == DecelerationColumn)
        m_vfdData.deceleration = value.toDouble();

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags VFDDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

const VFDData_t VFDDataModel::getVFDData() const
{
    return m_vfdData;
}
