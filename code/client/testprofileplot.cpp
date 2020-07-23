#include "testprofileplot.h"
#include "ui_testprofileplot.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QVXYModelMapper>
#include <QVBoxLayout>
#include "global.h"
#include <QTableView>

TestProfilePlot::TestProfilePlot(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::TestProfilePlot)
{
    ui->setupUi(this);

}

TestProfilePlot::~TestProfilePlot() {
    delete ui;
}

void TestProfilePlot::setModel(QAbstractItemModel *model) {
    if (model)
        m_model = model;

    initChart();
}

void TestProfilePlot::initChart() {
//    QtCharts::QLineSeries *series = new QtCharts::QLineSeries(this);
////    *series << QPoint(11, 1) << QPoint(13, 3) << QPoint(17, 6) << QPoint(18, 3) << QPoint(20, 2);
//    QtCharts::QVXYModelMapper *mapper = new QtCharts::QVXYModelMapper(this);
//    mapper->setModel(m_model);
//    mapper->setSeries(series);
//    mapper->setXColumn(5);
//    mapper->setYColumn(1);

//    QtCharts::QChart *chart = new QtCharts::QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    chart->createDefaultAxes();
//    chart->axisX()->setRange(0, 1000);
//    chart->axisY()->setRange(0, 1000);
//    chart->setTitle("Test Profile");
//    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, this);
//    chartView->setRenderHint(QPainter::Antialiasing);

//    QVBoxLayout *mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(chartView);

//    setWindowTitle("Test Profile");
//    setLayout(mainLayout);



    QTableView *tableView = new QTableView(this);
    tableView->setModel(m_model);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);
}
