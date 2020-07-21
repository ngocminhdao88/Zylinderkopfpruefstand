#include "testprofiledata.h"

TestProfileData::TestProfileData() {
}

TestProfileData::TestProfileData(int duration, int speed, int direction, QString comment) :
    m_duration(duration),
    m_speed(speed),
    m_direction(direction),
    m_comment(comment)
{}

TestProfileData::TestProfileData(const TestProfileData &another) {
    m_duration = another.getDuration();
    m_speed = another.getSpeed();
    m_direction = another.getDirection();
    m_comment = another.getComment();
}

int TestProfileData::getDuration() const {
    return m_duration;
}

int TestProfileData::getSpeed() const {
    return m_speed;
}

int TestProfileData::getFbSpeed() const {
    return m_feedback_speed;
}

int TestProfileData::getAcceleration() const {
    return m_acceleration;
}

int TestProfileData::getDeceleration() const {
    return m_deceleration;
}

int TestProfileData::getDirection() const {
    return m_direction;
}

QString TestProfileData::getComment() const {
    return m_comment;
}

void TestProfileData::setDuration(int duration) {
    m_duration = duration;
}

void TestProfileData::setSpeed(int speed) {
    m_speed = speed;
}

void TestProfileData::setFeedbackSpeed(int speed) {
    m_feedback_speed = speed;
}

void TestProfileData::setAcceleration(int acc) {
    m_acceleration = acc;
}

void TestProfileData::setDeceleration(int dec) {
    m_deceleration = dec;
}

void TestProfileData::setDirection(int direction) {
    m_direction = direction;
}

void TestProfileData::setComment(QString comment) {
    m_comment = comment;
}
