#ifndef VFDEDITOR_H
#define VFDEDITOR_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>
#include "vfddatamodel.h"

namespace Ui {
class VFDEditor;
}

class VFDEditor : public QWidget
{
    Q_OBJECT

public:
    explicit VFDEditor(QWidget *parent = nullptr);
    ~VFDEditor();

    /*
     * @brief Mapping model data to view widget
     */
    void setModel(QAbstractItemModel *model);

private:
    Ui::VFDEditor *ui = nullptr;
    QDataWidgetMapper *mapper = nullptr;
    QAbstractItemModel *m_model = nullptr;
};

#endif // VFDEDITOR_H
