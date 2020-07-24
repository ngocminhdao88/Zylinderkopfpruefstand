#include "global.h"
#include "jobdatamodel.h"

JobDataModel::JobDataModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int JobDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return JobDataEnum::ROW_COUNT;
}

int JobDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return JobDataEnum::COLUMN_COUNT;
}

QVariant JobDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= JobDataEnum::ROW_COUNT)
        return QVariant();

    if (index.column() < 0 || index.column() >= JobDataEnum::COLUMN_COUNT)
        return QVariant();


    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case JobDataEnum::JOB_NUMBER_COL:
            return m_jobData.jobNumber;
        case JobDataEnum::JOB_DESCRIPTION_COL:
            return m_jobData.jobDescription;
        case JobDataEnum::PART_NAME_COL:
            return m_jobData.partName;
        case JobDataEnum::PART_NUMBER_COL:
            return m_jobData.partNumber;
        case JobDataEnum::CUSTOMER_COL:
            return m_jobData.customer;
        default:
            break;
        }
    }

    return QVariant();

}

QVariant JobDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case JobDataEnum::JOB_NUMBER_COL:
            return "Job Number";
        case JobDataEnum::JOB_DESCRIPTION_COL:
            return "Job Description";
        case JobDataEnum::PART_NAME_COL:
            return "Part Name";
        case JobDataEnum::PART_NUMBER_COL:
            return "Part Number";
        case JobDataEnum::CUSTOMER_COL:
            return "Customer";
        default:
            break;
        }
    }

    return QVariant();
}

bool JobDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return  false;

    if (index.row() < 0 || index.row() > JobDataEnum::ROW_COUNT)
        return false;

    if (index.column() < 0 || index.column() > JobDataEnum::COLUMN_COUNT)
        return false;

    if (role != Qt::EditRole)
        return false;

    switch (index.column()) {
    case JobDataEnum::JOB_NUMBER_COL:
        m_jobData.jobNumber = value.toString();
        break;
    case JobDataEnum::JOB_DESCRIPTION_COL:
        m_jobData.jobDescription = value.toString();
        break;
    case JobDataEnum::PART_NAME_COL:
        m_jobData.partName = value.toString();
        break;
    case JobDataEnum::PART_NUMBER_COL:
        m_jobData.partNumber = value.toString();
        break;
    case JobDataEnum::CUSTOMER_COL:
        m_jobData.customer = value.toString();
        break;
    default:
        return false;
    }

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags JobDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
