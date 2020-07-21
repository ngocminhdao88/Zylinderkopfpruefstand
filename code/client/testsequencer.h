#ifndef TESTSEQUENCER_H
#define TESTSEQUENCER_H

#include <QObject>
#include <QWidget>
#include <QStateMachine>
#include "testprofilemodel.h"
#include <QTimer>

namespace Ui {
class TestSequencer;
}

class TestSequencer : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Default constructor
     */
    TestSequencer(QWidget *parent = 0);

    /**
      * @brief Default destructor
      */

    ~TestSequencer();

    /**
     * @brief Get the timer of this test sequencer
     */
    QTimer *getTimer();

public slots:
    void onLoadButtonClicked();
    void onPlotButtonClicked();
    void onSaveButtonClicked();
//    void onStartButtonClicked();
//    void onNextButtonClicked();
//    void onPauseButtonClicked();
//    void onStopButtonClicked();

private:
    /**
     * @brief Setup the state machine for parsing test profile
     */
    void initStateMachine();

    /**
     * @brief Slot for entered signal of idle state
     */
    void onIdleStateEntered();

    /**
     * @brief Slot for exited signal of idle state
     */
    void onIdleStateExited();

    /**
     * @brief Slot for entered signal of run state
     */
    void onRunStateEntered();

    /**
     * @brief Slot for entered signal of parse state
     */
    void onParseStateEntered();

    /**
     * @brief Slot for exited signal of parse state
     */
    void onParseStateExited();

    /**
     * @brief Slot for entered signal of stop state
     */
    void onStopStateEntered();

    /**
     * @brief Slot for entered signal of pause state
     */
    void onPauseStateEntered();

    /**
     * @brief Slot for exited signal of pause state
     */
    void onPauseStateExited();

    /**
     * @brief Slot for entered signal of endloop state
     */
    void onEndLoopEntered();

    /**
     * @brief Slot for exited signal of endloop state
     */
    void onEndLoopExited();

    /**
     * @brief Update the test status
     */
    void updateTestStatus(const QString &status);

    /**
     * @brief Update the loop counter
     */
    void updateTestLoopCount(const int count);

    /**
     * @brief Update the tests progress
     */
    void updateTestProgress();

signals:
    /**
     * @brief loopEnded Signaling current test loop has ended
     */
    void testLoopEnded();

    /**
     * @brief testEnded Signaling the whole test has ended
     */
    void testEnded();

    /**
     * @brief reRun Signaling the test loop has to be done one more time
     */
    void testRestart();

private:
    Ui::TestSequencer *ui = 0;
    TestProfileModel *m_testProfileDataModel = 0;
    QStateMachine m_machine;
    QTimer *m_stepTimer = 0;
    int m_loopIndex = 0;
    int m_stepIndex = 0;
    int m_stepTimeLeft;
};

#endif // TESTSEQUENCER_H
