#ifndef JOBDATAMODEL_H
#define JOBDATAMODEL_H

#include <QAbstractTableModel>

struct JobData
{
    QString jobNumber;
    QString jobDescription;
    QString partName;
    QString partNumber;
    QString customer;
};

class JobDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    JobDataModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    struct JobData jobData;
};

#endif // JOBDATAMODEL_H
