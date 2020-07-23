#ifndef TESTPROFILEPROXYMODEL_H
#define TESTPROFILEPROXYMODEL_H

#include <QObject>
#include <QIdentityProxyModel>

/**
 * @brief Proxy model of test profile data model
 *
 * This model will do some data processing, so we can plot it
 */
class TestProfileProxyModel : public QIdentityProxyModel {
    Q_OBJECT
public:
    TestProfileProxyModel(QObject *parent = 0);

    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent) const override;

private:
};

#endif // TESTPROFILEPROXYMODEL_H
