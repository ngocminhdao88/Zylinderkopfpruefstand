#ifndef JOBDATAMODEL_H
#define JOBDATAMODEL_H

#include <QAbstractTableModel>


/**
 * @brief The JobDataModel class holds all information about the test job
 */
class JobDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    /**
      * @brief A JobData type
      */
    struct TestJob {
        QString jobNumber;
        QString jobDescription;
        QString partName;
        QString partNumber;
        QString customer;
    };

    /**
     * @brief Default constructor
     * @param parent - A QObject, which owns this
     */
    JobDataModel(QObject *parent = 0);

    /**
     * @brief Override rowCount function in QAbstractTableModel
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

private:
    TestJob m_jobData;
};

#endif // JOBDATAMODEL_H
