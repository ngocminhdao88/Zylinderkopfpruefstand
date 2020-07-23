#include "testprofileproxymodel.h"
#include <Qt>
#include "global.h"
#include <QDebug>
#include <QModelIndex>

TestProfileProxyModel::TestProfileProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{ }

QVariant TestProfileProxyModel::data(const QModelIndex &proxyIndex, int role) const {
    int accumulationTimeColumn = columnCount(QModelIndex()) - 1;
    int accumulationTime = 0;

    if (proxyIndex.column() == accumulationTimeColumn && role == Qt::DisplayRole) {
        // Calculate the accumulation time til this step
        for (int i = 0; i < proxyIndex.row(); i++) {
            QModelIndex mIndex = index(i, TestProfileEnum::DURATION_COL);
            accumulationTime  = accumulationTime  + data(mIndex).toInt();
        }
        return accumulationTime ;
    }

    return QIdentityProxyModel::data(proxyIndex, role);
}

int TestProfileProxyModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    // new virtual column
    return sourceModel() ? (sourceModel()->columnCount() + 1) : 0;
}

QModelIndex TestProfileProxyModel::index(int row, int column, const QModelIndex &parent) const {
    // Create new index for new column
    if (column == columnCount(parent) - 1) {
        return createIndex(row, column);
    }

    // Just return the index from this proxymodel (same as source)
    return QIdentityProxyModel::index(row, column);
}
