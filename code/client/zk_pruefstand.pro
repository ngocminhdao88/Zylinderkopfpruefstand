QT       += core gui
QT       += serialbus
QT       += widgets
QT       += serialport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    jobdatamodel.cpp \
    jobeditor.cpp \
    main.cpp \
    mainwindow.cpp \
    rampgenerator.cpp \
    testprofiledata.cpp \
    testprofilemodel.cpp \
    testsequencer.cpp \
    unicovfd.cpp \
    vfddatamodel.cpp \
    vfdeditor.cpp \
    vfdsettingsdialog.cpp

HEADERS += \
    abstractvfd.h \
    global.h \
    jobdatamodel.h \
    jobeditor.h \
    mainwindow.h \
    rampgenerator.h \
    testprofiledata.h \
    testprofilemodel.h \
    testsequencer.h \
    unicovfd.h \
    vfddatamodel.h \
    vfdeditor.h \
    vfdsettingsdialog.h

FORMS += \
    jobeditor.ui \
    mainwindow.ui \
    testsequencer.ui \
    vfdeditor.ui \
    vfdsettingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

#Build test
test {
    message(Test Build)
    QT += testlib
    TARGET = UnitTests

    SOURCES -= main.cpp #remove the main app

    SOURCES += \
        test/main.cpp \
        test/testrampgenerator.cpp \

    HEADERS += \
        test/testrampgenerator.h \

} else {
    message(Normal Build)
}
