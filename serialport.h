#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>

class SerialPort : public QObject
{
    Q_OBJECT
    QSerialPort * serial_port = nullptr;
public:
    SerialPort(QObject * parent = nullptr);
    ~SerialPort();
signals:
    void dataReceived(const QByteArray &data);
private slots:
    void handleReadyRead();
};

#endif // SERIALPORT_H
