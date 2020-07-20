#include "testsequencer.h"
#include "ui_testsequencer.h"
#include <QDebug>

TestSequencer::TestSequencer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSequencer)
{
    ui->setupUi(this);

    m_stepTimer = new QTimer(this);
    m_stepTimer->setSingleShot(true);

    m_testProfileDataModel = new TestProfileModel(this);
    m_testProfileDataModel->insertRows(0, 3);
    ui->testProfileTableView->setModel(m_testProfileDataModel);

    // Buttons SIGNAL-SLOT
    connect(ui->loadButton, &QPushButton::clicked, this, &TestSequencer::onLoadButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &TestSequencer::onSaveButtonClicked);
    connect(ui->plotButton, &QPushButton::clicked, this, &TestSequencer::onPlotButtonClicked);
    connect(ui->nextButton, &QPushButton::clicked, this, &TestSequencer::onNextButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &TestSequencer::onPauseButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &TestSequencer::onStartButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &TestSequencer::onStopButtonClicked);
}

TestSequencer::~TestSequencer() {
    delete ui;
}

void TestSequencer::onLoadButtonClicked() {
    qDebug() << "load button clicked";
}

void TestSequencer::onSaveButtonClicked() {
    qDebug() << "save button clicked";
}

void TestSequencer::onPlotButtonClicked() {
    qDebug() << "plot button clicked";
}

void TestSequencer::onNextButtonClicked() {
    qDebug() << "next button clicked";
}

void TestSequencer::onPauseButtonClicked() {
    qDebug() << "pause button clicked";
}

void TestSequencer::onStartButtonClicked() {
    qDebug() << "start button clicked";
}

void TestSequencer::onStopButtonClicked() {
    qDebug() << "stop button clicked";
}

void TestSequencer::onStepTimerTimeout() {
    qDebug() << "step duration time out";
}
