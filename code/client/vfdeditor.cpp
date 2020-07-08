#include "global.h"
#include "vfdeditor.h"
#include "ui_vfdeditor.h"

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

    mapper->addMapping(ui->controlSpeedSpinbox, static_cast<int>(VFDDataColumn::ControlSpeed));
    //mapper->addMapping(ui->rampSpeedSpinbox, RampSpeedColumn);
    mapper->addMapping(ui->feedbackSpeedSpinbox, static_cast<int>(VFDDataColumn::FeedbackSpeed));
    mapper->addMapping(ui->directionSpinbox, static_cast<int>(VFDDataColumn::Direction));
    mapper->addMapping(ui->rampUpRateSpinbox, static_cast<int>(VFDDataColumn::Acceleration));
    mapper->addMapping(ui->rampDownRateSpinbox, static_cast<int>(VFDDataColumn::Deceleration));

    mapper->toLast();
}
