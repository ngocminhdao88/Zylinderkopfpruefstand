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

/**
 * @brief Display a window. It shows all settings for VFD
 */
class VfdSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
      * @brief A Setting data type. It holds the settings data for VFD
      */
    typedef struct {
        QString portName = "";
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
        int responseTime = 1000;
        int numberOfRetries = 3;
    } Setting_t;

    /**
     * @brief Default constructor
     * @param parent - A QObject parent, which owns this
     */
    VfdSettingsDialog(QWidget *parent = 0);

    /**
     * @brief Default deconstructor
     */
    ~VfdSettingsDialog();

    /**
     * @brief Return the vfd's settings
     *
     * These are Modbus settings, which used to connect to the Unico VFD
     * @return Setting_t
     */
    Setting_t settings() const;

private:
    Setting_t m_settings;
    Ui::VfdSettingsDialog *ui;
};

#endif // VFDSETTINGSDIALOG_H
