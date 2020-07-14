#include "testsequencer.h"
#include "ui_testsequencer.h"

TestSequencer::TestSequencer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSequencer)
{
    ui->setupUi(this);

    m_testProfileDataModel = new TestProfileModel(this);
    ui->testProfileTableView->setModel(m_testProfileDataModel);
}

TestSequencer::~TestSequencer() {
    delete ui;
}
