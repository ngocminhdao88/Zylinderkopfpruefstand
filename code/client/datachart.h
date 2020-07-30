#ifndef DATACHART_H
#define DATACHART_H

#include <QWidget>
#include <QTableView>
#include <QListWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DataChart : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     */
    explicit DataChart(QWidget *parent = nullptr);

    /**
      * @brief Default destructor
      */
    ~DataChart();

signals:

private:
    /**
     * @brief Setup the Ui components
     */
    void setupUi();

    /**
     * @brief Configure chart 1
     */
    void chart1_config();

    /**
     * @brief Configure chart 2
     */
    void chart2_config();

private:
    QTableView *m_tableView = 0;
    QListWidget *m_chart1Legend = 0;
    QListWidget *m_chart2Legend = 0;

    QChart *m_chart1 = 0;
    QChart *m_chart2 = 0;

    QLineSeries *m_series1 = 0;
    QLineSeries *m_series2 = 0;
};


#endif // DATACHART_H
