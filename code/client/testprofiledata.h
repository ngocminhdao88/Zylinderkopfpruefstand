#ifndef TESTPROFILEDATA_H
#define TESTPROFILEDATA_H

#include <QString>
#include <QTextStream>

class TestProfileData {
public:
    /**
     * @brief Default constructor
     */
    TestProfileData();

    /**
     * @brief Constructor
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
     * @brief Construct a test profile data from a csv line
     */
    void fromCSVLine(QString line);

    /**
     * @brief Get the steps duration
     */
    int getDuration() const;

    /**
     * @brief Get motors speed in this step
     */
    int getSpeed() const;

    int getFbSpeed() const;
    int getAcceleration() const;
    int getDeceleration() const;

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
    void setSpeed(int speed);
    void setFeedbackSpeed(int speed);
    void setAcceleration(int acc);
    void setDeceleration(int dec);

    /**
     * @brief Set motors direction for this step
     */
    void setDirection(int m_direction);

    /**
     * @brief Set users comment for this step
     */
    void setComment(QString m_comment);

    QString toString();

private:
    int m_duration;
    int m_speed;
    int m_feedback_speed;
    int m_direction;
    int m_acceleration;
    int m_deceleration;
    QString m_comment;
};

#endif // TESTPROFILEDATA_H
