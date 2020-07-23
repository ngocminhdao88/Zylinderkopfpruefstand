#include "testprofileproxymodel.h"
#include <Qt>
#include "global.h"

TestProfileProxyModel::TestProfileProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{ }

QVariant TestProfileProxyModel::data(const QModelIndex &proxyIndex, int role) const {
    int timeAxeColumn = columnCount(QModelIndex()) - 1;
    int tempTime = 0;

    if (proxyIndex.column() == timeAxeColumn || role == Qt::DisplayRole) {
        // Calculate the total time til this step
        for (int i = 0; i < proxyIndex.row(); i++) {
            QModelIndex mIndex = index(i, TestProfileEnum::DURATION_COL);
            tempTime = tempTime + data(mIndex).toInt();
        }
        return tempTime;
    }

    return data(proxyIndex, role);
}

int TestProfileProxyModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    // new virtual column
    return sourceModel() ? (sourceModel()->columnCount() + 1) : 0;
}
