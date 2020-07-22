#ifndef TESTPROFILEMODEL_H
#define TESTPROFILEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "testprofiledata.h"

/**
 * @brief The TestProfileDataModel class holds the information about the test profile
 */
class TestProfileModel : public QAbstractTableModel {
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent - A QObject, which owns this
     */
    TestProfileModel(QObject *parent = 0);

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

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    /**
     * @brief Get the whole test profile with all the steps
     *
     * @return A const reference of QVector<TestProfileData>
     *
     * The const after getTestProfile() function means, that this function
     * does not modify member variables of the class
     */
    const QVector<TestProfileData>& getTestProfile() const;
private:
    QVector<TestProfileData> m_testProfile;
};

#endif // TESTPROFILEMODEL_H
