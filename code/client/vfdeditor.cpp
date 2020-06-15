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

    mapper->addMapping(ui->controlSpeedSpinbox, ControlSpeedColumn);
    //mapper->addMapping(ui->rampSpeedSpinbox, RampSpeedColumn);
    mapper->addMapping(ui->feedbackSpeedSpinbox, FeedbackSpeedColumn);
    mapper->addMapping(ui->directionSpinbox, DirectionColumn);
    mapper->addMapping(ui->rampUpRateSpinbox, AccelerationColumn);
    mapper->addMapping(ui->rampDownRateSpinbox, DecelerationColumn);

    mapper->toLast();
}
