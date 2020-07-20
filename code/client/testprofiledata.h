#ifndef TESTPROFILEDATA_H
#define TESTPROFILEDATA_H

#include <QString>

class TestProfileData {
public:
    /**
     * @brief Default constructor
     * @param step - Index number? in the whole test profile
     * @param duration - How long should this step run
     * @param speed - Motors speed
     * @param direction - Motors direction
     * @param comment - Users comment
     */
    TestProfileData(int duration, int speed, int direction, QString comment);

    /**
     * @brief Copy constructor
     * @param another
     */
    TestProfileData(const TestProfileData &another);

    /**
     * @brief Get the steps duration
     */
    int getDuration() const;

    /**
     * @brief Get motors speed in this step
     */
    int getSpeed() const;

    /**
     * @brief Get motors direction in this step
     */
    int getDirection() const;

    /**
     * @brief Get users comment in this step
     */
    QString getComment() const;

    /**
     * @brief Set the steps duration
     */
    void setDuration(int m_duration);

    /**
     * @brief Set the motors speed for this step
     */
    void setSpeed(int m_speed);

    /**
     * @brief Set motors direction for this step
     */
    void setDirection(int m_direction);

    /**
     * @brief Set users comment for this step
     */
    void setComment(QString m_comment);

private:
    int m_duration;
    int m_speed;
    int m_direction;
    QString m_comment;
};

#endif // TESTPROFILEDATA_H
