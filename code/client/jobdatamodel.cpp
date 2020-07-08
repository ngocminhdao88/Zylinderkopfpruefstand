#include "global.h"
#include "jobdatamodel.h"

JobDataModel::JobDataModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int JobDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(JobDataEnum::RowCount);
}

int JobDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(JobDataEnum::ColumnCount);
}

QVariant JobDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= static_cast<int>(JobDataEnum::RowCount)
            || index.column() >= static_cast<int>(JobDataEnum::ColumnCount))
        return QVariant();

    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == static_cast<int>(JobDataEnum::JobNumber))
            return m_jobData.jobNumber;
        if (col == static_cast<int>(JobDataEnum::JobDescription))
            return m_jobData.jobDescription;
        if (col == static_cast<int>(JobDataEnum::PartName))
            return m_jobData.partName;
        if (col == static_cast<int>(JobDataEnum::PartNumber))
            return m_jobData.partNumber;
        if (col == static_cast<int>(JobDataEnum::Customer))
            return m_jobData.customer;
    }

    return QVariant();

}

QVariant JobDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == static_cast<int>(JobDataEnum::JobNumber))
            return "Job Number";
        if (section == static_cast<int>(JobDataEnum::JobDescription))
            return "Job Description";
        if (section == static_cast<int>(JobDataEnum::PartName))
            return "Part Name";
        if (section == static_cast<int>(JobDataEnum::PartNumber))
            return "Part Number";
        if (section == static_cast<int>(JobDataEnum::Customer))
            return "Customer";
    }

    return QVariant();
}

bool JobDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()
            || index.row() > static_cast<int>(JobDataEnum::RowCount)
            || index.column() >= static_cast<int>(JobDataEnum::ColumnCount))
        return false;

    if (role != Qt::EditRole)
        return false;

    const int col = index.column();

    if (col == static_cast<int>(JobDataEnum::JobNumber))
        m_jobData.jobNumber = value.toString();
    if (col == static_cast<int>(JobDataEnum::JobDescription))
        m_jobData.jobDescription = value.toString();
    if (col == static_cast<int>(JobDataEnum::PartName))
        m_jobData.partName = value.toString();
    if (col == static_cast<int>(JobDataEnum::PartNumber))
        m_jobData.partNumber = value.toString();
    if (col == static_cast<int>(JobDataEnum::Customer))
        m_jobData.customer = value.toString();

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags JobDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
