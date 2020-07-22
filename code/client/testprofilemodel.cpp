#include "testprofilemodel.h"
#include <QVariant>
#include <Qt>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "global.h"

TestProfileModel::TestProfileModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int TestProfileModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_testProfile.size();
}

int TestProfileModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : TestProfileEnum::COLUMN_COUNT;
}

QVariant TestProfileModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_testProfile.size() || index.row() < 0)
        return QVariant();

    TestProfileData currentStep = m_testProfile.at(index.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case TestProfileEnum::DURATION_COL:
            return currentStep.getDuration();
        case TestProfileEnum::SPEED_COL:
            return currentStep.getSpeed();
        case TestProfileEnum::DIRECTION_COL:
            return currentStep.getDirection();
        case TestProfileEnum::COMMENT_COL:
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
        case TestProfileEnum::DURATION_COL:
            return "Duration";
        case TestProfileEnum::SPEED_COL:
            return "Speed";
        case TestProfileEnum::DIRECTION_COL:
            return "Direction";
        case TestProfileEnum::COMMENT_COL:
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
        case TestProfileEnum::DURATION_COL:
            currentStep.setDuration(value.toInt());
            break;
        case TestProfileEnum::SPEED_COL:
            currentStep.setSpeed(value.toInt());
            break;
        case TestProfileEnum::DIRECTION_COL:
            currentStep.setDirection(value.toInt());
            break;
        case TestProfileEnum::COMMENT_COL:
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
        m_testProfile.insert(position, TestProfileData(1, 0, 1, "Replace me"));

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

void TestProfileModel::readCSV(const QString &filePath) {
    QFile file(filePath);
    QString line;

    beginResetModel();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_testProfile.clear();
        QTextStream stream(&file);

        line = stream.readLine(); // Ignore the header in csv file
        while (!stream.atEnd()) {
            line = stream.readLine();
            TestProfileData data;
            data.fromCSVLine(line);
            m_testProfile.insert(m_testProfile.size(), data);
        }
    }
    endResetModel();
    file.close();
}

void TestProfileModel::writeCSV(const QString &filePath) {
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        QString header("Duration, Speed, FbSpeed, Direction, Comment");
        stream << header << '\n';

        for (TestProfileData data: m_testProfile) {
            stream << data.toString() << '\n';
        }

    }
    file.close();
}
