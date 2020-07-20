#ifndef TESTSEQUENCER_H
#define TESTSEQUENCER_H

#include <QObject>
#include <QWidget>
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

public slots:
    /**
     * @brief Load the test profile from an external source
     */
    void onLoadButtonClicked();

    /**
     * @brief Save the test profile to a file
     */
    void onSaveButtonClicked();

    /**
     * @brief Plot the test profile
     */
    void onPlotButtonClicked();

    /**
     * @brief Goto next step in step profile
     */
    void onNextButtonClicked();

    /**
     * @brief Pause the test profile on current step
     */
    void onPauseButtonClicked();

    /**
     * @brief Start the test profile
     */
    void onStartButtonClicked();

    /**
     * @brief Stop the test profile
     */
    void onStopButtonClicked();

    /**
     * @brief Handle the event when the step duration is over
     */
    void onStepTimerTimeout();

private:
    Ui::TestSequencer *ui = 0;
    TestProfileModel *m_testProfileDataModel = 0;
    int m_loopIndex = 0;
    int m_stepIndex = 0;
    QTimer *m_stepTimer = 0;
};

#endif // TESTSEQUENCER_H
