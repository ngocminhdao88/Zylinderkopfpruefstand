#ifndef JOBEDITOR_H
#define JOBEDITOR_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>

namespace Ui {
class JobEditor;
}

class JobEditor : public QWidget
{
    Q_OBJECT

public:
    explicit JobEditor(QWidget *parent = nullptr);
    ~JobEditor();

    void setModel(QAbstractItemModel *model);
private:
    Ui::JobEditor *ui;
    QDataWidgetMapper *mapper = nullptr;
};

#endif // JOBEDITOR_H
