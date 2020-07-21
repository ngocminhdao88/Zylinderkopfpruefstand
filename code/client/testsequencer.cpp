#include "testsequencer.h"
#include "ui_testsequencer.h"
#include <QDebug>
#include <QState>
#include <QCursor>
#include <QFileDialog>
#include <QFileInfo>
#include "testprofiledata.h"

TestSequencer::TestSequencer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSequencer)
{
    ui->setupUi(this);

    m_stepTimer = new QTimer(this);
    m_stepTimer->setSingleShot(true);

    initStateMachine();

    m_testProfileDataModel = new TestProfileModel(this);
    m_testProfileDataModel->insertRows(0, 5);
    ui->testProfileTableView->setModel(m_testProfileDataModel);

    // Buttons SIGNAL-SLOT
    connect(ui->loadButton, &QPushButton::clicked, this, &TestSequencer::onLoadButtonClicked);
    connect(ui->plotButton, &QPushButton::clicked, this, &TestSequencer::onPlotButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &TestSequencer::onSaveButtonClicked);
//    connect(ui->startButton, &QPushButton::clicked, this, &TestSequencer::onStartButtonClicked);
//    connect(ui->nextButton, &QPushButton::clicked, this, &TestSequencer::onNextButtonClicked);
//    connect(ui->pauseButton, &QPushButton::clicked, this, &TestSequencer::onPauseButtonClicked);
//    connect(ui->stopButton, &QPushButton::clicked, this, &TestSequencer::onStopButtonClicked);
}

TestSequencer::~TestSequencer() {
    delete ui;
}

QTimer *TestSequencer::getTimer() {
    return m_stepTimer;
}

void TestSequencer::onLoadButtonClicked() {
    QString testProfileName = QFileDialog::getOpenFileName(this, "Open test profile",
                                                           ".",
                                                           "Test Profile (*.csv)");

    if (testProfileName.length() > 0) {

        QFileInfo fi(testProfileName);
        ui->profileNameLabel->setText(fi.fileName());
    }
}

void TestSequencer::onPlotButtonClicked() {
}

void TestSequencer::onSaveButtonClicked() {
}

//void TestSequencer::onStartButtonClicked() {
//}

//void TestSequencer::onNextButtonClicked() {
//}

//void TestSequencer::onPauseButtonClicked() {
//}

//void TestSequencer::onStopButtonClicked() {
//}

void TestSequencer::initStateMachine() {
    // Creating states
    QState *idleState = new QState();
    QState *runState = new QState();
    QState *parseState = new QState();
    QState *stopState = new QState();
    QState *endLoopState = new QState();
    QState *pauseState = new QState();

    // Simple state transitions whene button clicked
    idleState->addTransition(ui->startButton, &QAbstractButton::clicked, runState);
    runState->addTransition(ui->stopButton, &QAbstractButton::clicked, stopState);
    runState->addTransition(ui->nextButton, &QAbstractButton::clicked, parseState);
    runState->addTransition(ui->pauseButton, &QAbstractButton::clicked, pauseState);
    pauseState->addTransition(ui->pauseButton, &QAbstractButton::clicked, runState);

    // Go back immediately from parse state to run state
    parseState->addTransition(runState);

    // Go back immediately from parse state to run state
    stopState->addTransition(idleState);

    // Transtion from run state to parse state at timer timeout signal
    runState->addTransition(m_stepTimer, &QTimer::timeout, parseState);

    // Transition from run state to endloop state when one test loop has been done
    runState->addTransition(this, &TestSequencer::testLoopEnded, endLoopState);

    // Transition from endloop state to run state when current loop count < total loops
    endLoopState->addTransition(this, &TestSequencer::testRestart, runState);

    // Transition from endloop state to stop state when the test is done
    endLoopState->addTransition(this, &TestSequencer::testEnded, stopState);

    // SIGNAL-SLOT
    connect(idleState, &QState::entered, this, &TestSequencer::onIdleStateEntered);
    connect(idleState, &QState::exited, this, &TestSequencer::onIdleStateExited);

    connect(runState, &QState::entered, this, &TestSequencer::onRunStateEntered);

    connect(parseState, &QState::entered, this, &TestSequencer::onParseStateEntered);
    connect(parseState, &QState::exited, this, &TestSequencer::onParseStateExited);

    connect(stopState, &QState::entered, this, &TestSequencer::onStopStateEntered);

    connect(pauseState, &QState::entered, this, &TestSequencer::onPauseStateEntered);
    connect(pauseState, &QState::exited, this, &TestSequencer::onPauseStateExited);

    connect(endLoopState, &QState::entered, this, &TestSequencer::onEndLoopEntered);
    connect(endLoopState, &QState::exited, this, &TestSequencer::onEndLoopExited);

    // Loading states into machine
    m_machine.addState(idleState);
    m_machine.addState(runState);
    m_machine.addState(parseState);
    m_machine.addState(stopState);
    m_machine.addState(endLoopState);
    m_machine.addState(pauseState);

    // Start the machine
    m_machine.setInitialState(idleState);
    m_machine.start();
}

void TestSequencer::onIdleStateEntered() {
    // Update the status to Idle and enable the total loop spinbox
    updateTestStatus("Idle");
    ui->loopSpinBox->setEnabled(true);
}

void TestSequencer::onIdleStateExited() {
    // Arm the parse timer to 1s, so the state will automatically
    // transition from run -> parse on first run
    m_stepTimer->setInterval(1000);
    m_stepTimer->start();

    updateTestLoopCount(0);
}

void TestSequencer::onRunStateEntered() {
    // Update the status to Run and disable the total loop spinbox
    updateTestStatus("Run");
    ui->loopSpinBox->setEnabled(false);

//    qDebug() << QString("stepindex %1").arg(m_stepIndex);
    if (m_stepIndex >= m_testProfileDataModel->rowCount())
        emit testLoopEnded();
}

void TestSequencer::onParseStateEntered() {
    // Update the status to Parse and parse the current step in test profile
    updateTestStatus("Parse");

    TestProfileData testStep = m_testProfileDataModel->getTestProfile().at(m_stepIndex);

    // Rearm the step timer
    m_stepTimer->setInterval(testStep.getDuration() * 1000);
    m_stepTimer->start();

    updateTestProgress();
}

void TestSequencer::onParseStateExited() {
    m_stepIndex++;
}

void TestSequencer::onStopStateEntered() {
    // Update the status to Stop and reset all the test sequencer counter
    updateTestStatus("Stop");
}

void TestSequencer::onPauseStateEntered() {
    ui->pauseButton->setText("Resume");

    // Update the status to Pause and take a snap shot of current step run time
    updateTestStatus("Pause");

    // Calculate the time left for current step
    m_stepTimeLeft = m_stepTimer->interval() - m_stepTimer->remainingTime();

    // Disarm the step timer
    m_stepTimer->stop();
}

void TestSequencer::onPauseStateExited() {
    ui->pauseButton->setText("Pause");

    // Resume the test from previous pause
    m_stepTimer->setInterval(m_stepTimeLeft);
    m_stepTimer->start();
}

void TestSequencer::onEndLoopEntered() {
    // Update the status to Endloop
    updateTestStatus("Endloop");

    m_stepIndex = 0;
    updateTestLoopCount(++m_loopIndex);

    ui->loopLabel->setNum(m_loopIndex);

    if (m_loopIndex >= ui->loopSpinBox->value()) {
        emit testEnded();
    } else {
        emit testRestart();
    }
}

void TestSequencer::onEndLoopExited() {
    // Do something about this
}

void TestSequencer::updateTestStatus(const QString &status) {
    QString currentStatus = ui->statusEdit->text();
    ui->statusEdit->setText(status + ", " + currentStatus);

    // Scroll the line edit to left most position
    ui->statusEdit->setCursorPosition(0);
}

void TestSequencer::updateTestLoopCount(const int count) {
    m_loopIndex = count;
    ui->loopLabel->setNum(count);
}

void TestSequencer::updateTestProgress() {
    int finishedSteps = m_testProfileDataModel->rowCount() * m_loopIndex + m_stepIndex + 1;
    int totalSteps = m_testProfileDataModel->rowCount() * ui->loopSpinBox->value();

    ui->progressLabel->setText(QString("%1/%2").arg(finishedSteps).arg(totalSteps));
}
