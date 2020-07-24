#include "testprofileplotwidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

#include <QVBoxLayout>
#include <QPolygonF>
#include <QRectF>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

TestProfilePlotWidget::TestProfilePlotWidget(QWidget *parent) :
    QWidget(parent),
    m_chart(new QChart),
    m_series(new QLineSeries)
{
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(800, 600);
    chartView->setRenderHint(QPainter::Antialiasing);
    m_chart->addSeries(m_series);
//    m_chart->setMargins(QMargins(10, 10, 10 , 10));

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 1000);
//    axisX->setLabelFormat("%d");
    axisX->setTitleText("Time [s]");
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 4000);
    axisY->setTitleText("Speed [1/min]");

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    m_chart->legend()->hide();
    m_chart->setTitle("Test Profile");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

    setWindowTitle("Test Profile Plot");
}

TestProfilePlotWidget::~TestProfilePlotWidget() {
}

void TestProfilePlotWidget::plot(QVector<QPointF> points) {
    m_series->replace(points);

    // Using bounding box to find max X and max Y
    QPolygonF poly(points);
    QRectF brect = poly.boundingRect();

    QList<QAbstractAxis *> axes = m_series->attachedAxes();
    axes[0]->setRange(0, brect.right()); // x axis
    axes[1]->setRange(0, brect.bottom()); // y axis
}
