#include "global.h"
#include "vfddatamodel.h"

VFDDataModel::VFDDataModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int VFDDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int VFDDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return TestProfileEnum::COLUMN_COUNT;
}

QVariant VFDDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= 1 || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case TestProfileEnum::SPEED_COL:
            return m_vfdData.getSpeed();
        case TestProfileEnum::FB_SPEED_COL:
            return m_vfdData.getFbSpeed();
        case TestProfileEnum::DIRECTION_COL:
            return m_vfdData.getDirection();
        default:
            break;
        }
    }
    return QVariant();
}

QVariant VFDDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case TestProfileEnum::SPEED_COL:
            return "Speed";
        case TestProfileEnum::FB_SPEED_COL:
            return "FeedbackSpeed";
        case TestProfileEnum::DIRECTION_COL:
            return "Direction";
        default:
            break;
        }
    }
    return QVariant();
}

bool VFDDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        switch (index.column()) {
        case TestProfileEnum::SPEED_COL:
            m_vfdData.setSpeed(value.toInt());
            break;
        case TestProfileEnum::FB_SPEED_COL:
            m_vfdData.setFeedbackSpeed(value.toInt());
            break;
        case TestProfileEnum::DIRECTION_COL:
            m_vfdData.setDirection(value.toInt());
            break;
        default:
            return false;
        }
        emit dataChanged(index, index);

        return true;
    }
    return false;
}

Qt::ItemFlags VFDDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

TestProfileData VFDDataModel::getVFDData() const
{
    return m_vfdData;
}
