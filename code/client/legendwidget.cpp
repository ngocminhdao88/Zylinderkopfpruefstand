#include "legendwidget.h"

LegendWidget::LegendWidget(QAbstractSeries *series, QWidget *parent) :
    QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);
}
