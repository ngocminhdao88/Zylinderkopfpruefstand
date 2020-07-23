#include "testprofileplot.h"
#include "ui_testprofileplot.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QVBoxLayout>
#include "global.h"

TestProfilePlot::TestProfilePlot(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::TestProfilePlot)
{
    ui->setupUi(this);

    QtCharts::QLineSeries *series = new QtCharts::QLineSeries(this);
//    *series << QPoint(11, 1) << QPoint(13, 3) << QPoint(17, 6) << QPoint(18, 3) << QPoint(20, 2);
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Test Profile");
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

    setWindowTitle("Test Profile");
    setLayout(mainLayout);
}

TestProfilePlot::~TestProfilePlot() {
    delete ui;
}

void TestProfilePlot::setModel(QAbstractItemModel *model) {
    if (model)
        m_model = model;
}
