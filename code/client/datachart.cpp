#include "datachart.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLabel>

#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

#include <QDebug>

DataChart::DataChart(QWidget *parent) :
    QWidget(parent),
    m_tableView(new QTableView),
    m_chart1Legend(new QListWidget),
    m_chart2Legend(new QListWidget),
    m_chart1(new QChart),
    m_chart2(new QChart),
    m_series1(new QLineSeries),
    m_series2(new QLineSeries)
{
    setupUi();
}

DataChart::~DataChart() {
    delete m_tableView;
    delete m_chart1;
    delete m_chart2;
    delete m_chart1Legend;
    delete m_chart2Legend;
//    delete m_series1; // deleted with mchart1
//    delete m_series2; // deleted with mchart2
}

void DataChart::setupUi() {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QChartView *chartView = new QChartView(m_chart1, this);
    chartView->setMinimumSize(400, 300);
    chartView->setRenderHint(QPainter::Antialiasing);
    m_chart1->addSeries(m_series1);
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    m_chart1->addAxis(axisX, Qt::AlignBottom);
    m_series1->attachAxis(axisX);
    m_chart1->addAxis(axisY, Qt::AlignLeft);
    m_series1->attachAxis(axisY);
    m_chart1->legend()->hide();
    m_chart1->setTitle("Chart 1");

    QVBoxLayout *vLayout2 = new QVBoxLayout();

    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QPushButton *button = new QPushButton("Config", this);
    connect(button, &QPushButton::clicked, this, &DataChart::chart1_config);
    vLayout->addWidget(button);
    vLayout->addWidget(m_chart1Legend);
    hLayout->addWidget(chartView);
    hLayout->addLayout(vLayout);

    vLayout2->addLayout(hLayout);

    chartView = new QChartView(m_chart2, this);
    chartView->setMinimumSize(400, 300);
    chartView->setRenderHint(QPainter::Antialiasing);
    m_chart2->addSeries(m_series2);
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    m_chart2->addAxis(axisX, Qt::AlignBottom);
    m_series2->attachAxis(axisX);
    m_chart2->addAxis(axisY, Qt::AlignLeft);
    m_series2->attachAxis(axisY);
    m_chart2->legend()->hide();
    m_chart2->setTitle("Chart 2");

    hLayout = new QHBoxLayout();
    vLayout = new QVBoxLayout();
    button = new QPushButton("Config", this);
    connect(button, &QPushButton::clicked, this, &DataChart::chart2_config);
    vLayout->addWidget(button);
    vLayout->addWidget(m_chart2Legend);
    hLayout->addWidget(chartView);
    hLayout->addLayout(vLayout);

    vLayout2->addLayout(hLayout);

    mainLayout->addWidget(m_tableView);
    mainLayout->addLayout(vLayout2);

    setLayout(mainLayout);
}

void DataChart::chart1_config() {
    qDebug() << "chart 1 config";
}

void DataChart::chart2_config() {
    qDebug() << "chart 2 config";
}
