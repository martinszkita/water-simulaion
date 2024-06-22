#include "arduino.h"

Arduino::Arduino(QObject *parent) : QObject(parent), serial_port(new QSerialPort(this)){
    serial_port->setPortName("/dev/ttyUSB0");
    serial_port->setBaudRate(QSerialPort::Baud9600);
    serial_port->setDataBits(QSerialPort::Data8);
    serial_port->setParity(QSerialPort::NoParity);
    serial_port->setStopBits(QSerialPort::OneStop);
    serial_port->setFlowControl(QSerialPort::NoFlowControl);

    connect(serial_port, &QSerialPort::readyRead, this, &Arduino::handleReadyRead);

    if (serial_port->open(QIODevice::ReadOnly)) {
        qDebug() << "Serial port opened successfully.";
    } else {
        qDebug() << "Failed to open serial port!";
    }
}

Arduino::~Arduino() {
    serial_port->close();
}
void Arduino::handleReadyRead()
{
    QByteArray data = serial_port->readAll();
    qDebug() << "Data received:" << data;
}
