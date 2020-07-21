#include "global.h"
#include "vfdeditor.h"
#include "ui_vfdeditor.h"
#include "global.h"

VFDEditor::VFDEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VFDEditor)
{
    ui->setupUi(this);
}

VFDEditor::~VFDEditor()
{
    delete ui;
}

void VFDEditor::setModel(QAbstractItemModel *model)
{
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(ui->controlSpeedSpinbox, TestProfileEnum::SPEED_COL);
    mapper->addMapping(ui->feedbackSpeedSpinbox, TestProfileEnum::FB_SPEED_COL);
    mapper->addMapping(ui->directionSpinbox, TestProfileEnum::DIRECTION_COL);
    mapper->toLast();
}
