#include "testprofilemodel.h"
#include <QVariant>
#include <Qt>

TestProfileModel::TestProfileModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int TestProfileModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_testProfile.size();
}

int TestProfileModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 4;
}

QVariant TestProfileModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_testProfile.size() || index.row() < 0)
        return QVariant();

    TestProfileData currentStep = m_testProfile.at(index.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return currentStep.getDuration();
        case 1:
            return currentStep.getSpeed();
        case 2:
            return currentStep.getDirection();
        case 3:
            return currentStep.getComment();
        default:
            break;
        }
    }
    return QVariant();
}

QVariant TestProfileModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "Duration [s]";
        case 1:
            return "Speed [1/min]";
        case 2:
            return "Direction";
        case 3:
            return "Comment";
        default:
            break;
        }
    } else {
        // rown number
        return section;
    }

    return QVariant();
}

bool TestProfileModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {

        const int row = index.row();

        TestProfileData currentStep = m_testProfile.at(row);

        switch (index.column()) {
        case 0:
            currentStep.setDuration(value.toInt());
            break;
        case 1:
            currentStep.setSpeed(value.toInt());
            break;
        case 2:
            currentStep.setDirection(value.toInt());
            break;
        case 3:
            currentStep.setComment(value.toString());
            break;
        default:
            return false;
        }
        m_testProfile.replace(row, currentStep);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }
    return false;
}

Qt::ItemFlags TestProfileModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TestProfileModel::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_testProfile.insert(position, TestProfileData(1, 0, 0, "Replace me"));

    endInsertRows();
    return true;
}

bool TestProfileModel::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_testProfile.removeAt(position);

    endRemoveRows();
    return true;
}

const QVector<TestProfileData> &TestProfileModel::getTestProfile() const {
    return m_testProfile;
}
