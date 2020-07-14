#ifndef TESTSEQUENCER_H
#define TESTSEQUENCER_H

#include <QObject>
#include <QWidget>
#include "testprofilemodel.h"

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

private:
    Ui::TestSequencer *ui = 0;
    TestProfileModel *m_testProfileDataModel = 0;
};

#endif // TESTSEQUENCER_H
