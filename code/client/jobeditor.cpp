#include "jobeditor.h"
#include "ui_jobeditor.h"

JobEditor::JobEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JobEditor)
{
    ui->setupUi(this);
}

JobEditor::~JobEditor()
{
    delete ui;
}

void JobEditor::setModel(QAbstractItemModel *model)
{
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(ui->jobNumberEdit, 0);
    mapper->addMapping(ui->jobDescriptionEdit, 1);
    mapper->addMapping(ui->partNameEdit, 2);
    mapper->addMapping(ui->partNumberEdit, 3);
    mapper->addMapping(ui->customerEdit, 4);

    mapper->toLast();
}
