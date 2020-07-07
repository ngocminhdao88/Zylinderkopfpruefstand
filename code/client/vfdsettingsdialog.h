#ifndef VFDSETTINGSDIALOG_H
#define VFDSETTINGSDIALOG_H

#include <QObject>
#include <QDialog>
#include <QSerialPort>
//#include <QtSerialBus/qtserialbusglobal.h>

QT_BEGIN_NAMESPACE

namespace Ui {
class VfdSettingsDialog;
}
QT_END_NAMESPACE

/*
 * \brief The VfdSettingsDialog class
 * \details Holding vfd's settings
 */
class VfdSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
        int responseTime = 1000;
        int numberOfRetries = 3;
    };

    VfdSettingsDialog(QWidget *parent = nullptr);
    ~VfdSettingsDialog();

    /*
     * Return the vfd's settings
     *
     * These are Modbus settings, which needed to connect to the Unico VFD
     * @return Settings User's settings for VFD
     */
    Settings settings() const;

private:
    Settings m_settings;
    Ui::VfdSettingsDialog *ui;
};

#endif // VFDSETTINGSDIALOG_H
