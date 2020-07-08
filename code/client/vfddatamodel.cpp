#include "global.h"
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
        if (index.column() == static_cast<int>(VFDDataColumn::ControlSpeed))
            return m_vfdData.controlSpeed;
        if (index.column() == static_cast<int>(VFDDataColumn::RampSpeed))
            return m_vfdData.rampSpeed;
        if (index.column() == static_cast<int>(VFDDataColumn::FeedbackSpeed))
            return m_vfdData.feedbackSpeed;
        if (index.column() == static_cast<int>(VFDDataColumn::Direction))
            return m_vfdData.turnDirection;
        if (index.column() == static_cast<int>(VFDDataColumn::Acceleration))
            return m_vfdData.acceleration;
        if (index.column() == static_cast<int>(VFDDataColumn::Deceleration))
            return m_vfdData.deceleration;
    }

    return QVariant();
}

QVariant VFDDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == static_cast<int>(VFDDataColumn::ControlSpeed))
            return "ControlSpeed";
        if (section == static_cast<int>(VFDDataColumn::RampSpeed))
            return "RampSpeed";
        if (section == static_cast<int>(VFDDataColumn::FeedbackSpeed))
            return "FeedbackSpeed";
        if (section == static_cast<int>(VFDDataColumn::Direction))
            return "TurnDirection";
        if (section == static_cast<int>(VFDDataColumn::Acceleration))
            return "Acceleration";
        if (section == static_cast<int>(VFDDataColumn::Deceleration))
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

    if (col == static_cast<int>(VFDDataColumn::ControlSpeed))
        m_vfdData.controlSpeed = value.toDouble();
    if (col == static_cast<int>(VFDDataColumn::RampSpeed))
        m_vfdData.rampSpeed = value.toDouble();
    if (col == static_cast<int>(VFDDataColumn::FeedbackSpeed))
        m_vfdData.feedbackSpeed = value.toDouble();
    if (col == static_cast<int>(VFDDataColumn::Direction))
        m_vfdData.turnDirection = value.toDouble();
    if (col == static_cast<int>(VFDDataColumn::Acceleration))
        m_vfdData.acceleration = value.toDouble();
    if (col == static_cast<int>(VFDDataColumn::Deceleration))
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

VFDDataModel::VFDData_t VFDDataModel::getVFDData() const
{
    return m_vfdData;
}
