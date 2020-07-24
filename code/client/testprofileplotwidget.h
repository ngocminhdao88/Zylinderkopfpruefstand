#ifndef TESTPROFILEPLOTWIDGET_H
#define TESTPROFILEPLOTWIDGET_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class TestProfilePlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestProfilePlotWidget(QWidget *parent = nullptr);

    ~TestProfilePlotWidget();

    /**
     * @brief Plot all points on the chart
     */
    void plot(QVector<QPointF> points);

signals:

private:
    QChart *m_chart = 0;
    QLineSeries *m_series = 0;
};

#endif // TESTPROFILEPLOTWIDGET_H
