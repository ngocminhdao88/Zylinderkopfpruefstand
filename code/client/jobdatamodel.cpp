#include "jobdatamodel.h"

enum {
    RowCount = 1,
    ColumnCount = 5,

    JobNumberColumn = 0,
    JobDescriptionColumn = 1,
    PartNameColumn = 2,
    PartNumberColumn = 3,
    CustomerColumn = 4,
};

JobDataModel::JobDataModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int JobDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return RowCount;
}

int JobDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnCount;
}

QVariant JobDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= RowCount || index.column() >= ColumnCount)
        return QVariant();

    int col = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (col == JobNumberColumn)
            return jobData.jobNumber;
        if (col == JobDescriptionColumn)
            return jobData.jobDescription;
        if (col == PartNameColumn)
            return jobData.partName;
        if (col == PartNumberColumn)
            return jobData.partNumber;
        if (col == CustomerColumn)
            return jobData.customer;
    }

    return QVariant();

}

QVariant JobDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == JobNumberColumn)
            return "Job Number";
        if (section == JobDescriptionColumn)
            return "Job Description";
        if (section == PartNameColumn)
            return "Part Name";
        if (section == PartNumberColumn)
            return "Part Number";
        if (section == CustomerColumn)
            return "Customer";
    }

    return QVariant();
}

bool JobDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() > RowCount || index.column() >= ColumnCount)
        return false;

    if (role != Qt::EditRole)
        return false;

    const int col = index.column();

    if (col == JobNumberColumn)
        jobData.jobNumber = value.toString();
    if (col == JobDescriptionColumn)
        jobData.jobDescription = value.toString();
    if (col == PartNameColumn)
        jobData.partName = value.toString();
    if (col == PartNumberColumn)
        jobData.partNumber = value.toString();
    if (col == CustomerColumn)
        jobData.customer = value.toString();

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags JobDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
