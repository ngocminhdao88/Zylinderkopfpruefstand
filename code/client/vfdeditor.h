#ifndef VFDEDITOR_H
#define VFDEDITOR_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>

namespace Ui {
class VFDEditor;
}

class VFDEditor : public QWidget
{
    Q_OBJECT

public:
    explicit VFDEditor(QWidget *parent = 0);
    ~VFDEditor();

    /*
     * @brief Mapping model data to view widget
     */
    void setModel(QAbstractItemModel *model);

private:
    Ui::VFDEditor *ui = 0;
    QDataWidgetMapper *mapper = 0;
    QAbstractItemModel *m_model = 0;
};

#endif // VFDEDITOR_H
