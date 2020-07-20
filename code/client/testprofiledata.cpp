#include "testprofiledata.h"

TestProfileData::TestProfileData(int duration, int speed, int direction, QString comment) :
    m_duration(duration),
    m_speed(speed),
    m_direction(direction),
    m_comment(comment)
{

}

TestProfileData::TestProfileData(const TestProfileData &another) {
    m_duration = another.getDuration();
    m_speed = another.getSpeed();
    m_direction = another.getDuration();
    m_comment = another.getComment();
}

int TestProfileData::getDuration() const {
    return m_duration;
}

int TestProfileData::getSpeed() const {
    return m_speed;
}

int TestProfileData::getDirection() const {
    return m_direction;
}

QString TestProfileData::getComment() const {
    return m_comment;
}

void TestProfileData::setDuration(int duration) {
    if (duration != m_duration)
        m_duration = duration;
}

void TestProfileData::setSpeed(int speed) {
    if (speed != m_speed)
        m_speed = speed;
}

void TestProfileData::setDirection(int direction) {
    if (direction != m_direction)
        m_direction = direction;
}

void TestProfileData::setComment(QString comment) {
    if (comment != m_comment)
        m_comment = comment;
}
