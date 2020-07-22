#include "testprofiledata.h"
#include "global.h"
#include <QStringList>

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

void TestProfileData::fromCSVLine(QString csvLine) {
    if (csvLine.length() > 0) {
        QStringList params = csvLine.split(',');
        if (params.size() < 5)
            return;

        m_duration = params.at(TestProfileEnum::DURATION_COL).toInt();
        m_speed = params.at(TestProfileEnum::SPEED_COL).toInt();
        m_direction = params.at(TestProfileEnum::DIRECTION_COL).toInt();
        m_comment = params.at(TestProfileEnum::COMMENT_COL);
    }
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

QString TestProfileData::toString() {
    return QString("%1, %2, -, %3, %4")
            .arg(m_duration)
            .arg(m_speed)
            .arg(m_direction)
            .arg(m_comment);
}
