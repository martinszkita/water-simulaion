#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QObject>


class Arduino : public QObject
{
    Q_OBJECT
    QSerialPort * serial_port = nullptr;
public:
    Arduino(QObject * parent = nullptr);
    ~Arduino();

private slots:
    void handleReadyRead();
};

#endif // ARDUINO_H
