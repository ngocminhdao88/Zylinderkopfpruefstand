#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include <QObject>
#include <QListWidget>
#include <QtCharts/QAbstractSeries>

QT_CHARTS_BEGIN_NAMESPACE
class QAbstractSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class LegendWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit LegendWidget(QAbstractSeries *series = 0, QWidget *parent = 0);
};

#endif // LEGENDWIDGET_H
