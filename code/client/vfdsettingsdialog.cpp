#include "vfdsettingsdialog.h"
#include "ui_vfdsettingsdialog.h"
#include <QSerialPortInfo>

VfdSettingsDialog::VfdSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VfdSettingsDialog)
{
    ui->setupUi(this);

    //set up GUI with its default values
    ui->parityCombo->setCurrentIndex(0);
    ui->baudCombo->setCurrentText(QString::number(m_settings.baud));
    ui->dataBitsCombo->setCurrentText(QString::number(m_settings.dataBits));
    ui->stopBitsCombo->setCurrentText(QString::number(m_settings.stopBits));
    ui->timeoutSpinner->setValue(m_settings.responseTime);
    ui->retriesSpinner->setValue(m_settings.numberOfRetries);

    // refresh the serial port
    connect(ui->portButton, &QPushButton::clicked, [this] {
        ui->portCombo->clear();

        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for (QSerialPortInfo port: ports) {
            ui->portCombo->addItem(port.portName());
        }
    });

    // save the settings
    connect(ui->applyButton, &QPushButton::clicked, [this]() {
        m_settings.portName = ui->portCombo->currentText();
        m_settings.parity = ui->parityCombo->currentIndex();
        if (m_settings.parity > 0) m_settings.parity++;
        m_settings.baud = ui->baudCombo->currentText().toInt();
        m_settings.dataBits = ui->dataBitsCombo->currentText().toInt();
        m_settings.stopBits = ui->stopBitsCombo->currentText().toInt();
        m_settings.responseTime = ui->timeoutSpinner->value();
        m_settings.numberOfRetries = ui->retriesSpinner->value();

        hide();
    });
}

VfdSettingsDialog::~VfdSettingsDialog()
{
    delete ui;
}

VfdSettingsDialog::Setting_t VfdSettingsDialog::settings() const
{
    return m_settings;
}
