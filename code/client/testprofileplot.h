#ifndef TESTPROFILEPLOT_H
#define TESTPROFILEPLOT_H

#include <QDialog>
#include <QObject>
#include <QAbstractItemModel>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui {
class TestProfilePlot;
}
QT_END_NAMESPACE

/**
 * @brief Display the test profile on a plot
 */
class TestProfilePlot : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     */
    TestProfilePlot(QWidget *parent = 0);

    /**
      * @brief Default destructor
     */
    ~TestProfilePlot();

    void setModel(QAbstractItemModel *model = 0);

private:
    void initChart();

private:
    Ui::TestProfilePlot *ui;
    QAbstractItemModel *m_model;
//    QtCharts::QValueAxis *m_axisX;
//    QtCharts::QValueAxis *m_axisY;
//    QtCharts::QLineSeries *m_serie;
};

#endif // TESTPROFILEPLOT_H
