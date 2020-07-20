#ifndef TESTSEQUENCER_H
#define TESTSEQUENCER_H

#include <QObject>
#include <QWidget>
#include <QStateMachine>
#include "testprofilemodel.h"
#include <QTimer>
#include <QElapsedTimer>

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

    void onIdleStateEntered();
    void onIdleStateExited();
    void onRunStateEntered();
    void onParseStateEntered();
    void onParseStateExited();
    void onStopStateEntered();
    void onPauseStateEntered();
    void onPauseStateExited();
    void onEndLoopEntered();
    void onEndLoopExited();

    /**
     * @brief Update the test status
     */
    void updateStatus(const QString &status);

    /**
     * @brief Update the loop counter
     */
    void updateLoopCount(const int count);

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
