#include "serialgamepad.h"
#include <QSet>
#include <QDebug>
#include <QSerialPortInfo>

SerialGamepad::SerialGamepad(int baudRate_, QObject *parent)
    : QObject{parent}
    , baudRate(baudRate_)
{
    timerUpdatePorts.setInterval(1000);
    connect(&timerUpdatePorts, &QTimer::timeout, this, &SerialGamepad::updatePorts);
    timerUpdatePorts.start();
    updatePorts();
}

bool SerialGamepad::isButtonDown(int button) const
{
    if (button < 0)
    {
        return false;
    }

    if (button < buttonsDown.count())
    {
        return buttonsDown[button];
    }

    return false;
}

bool SerialGamepad::isButtonDownNow(int button) const
{
    if (button < 0)
    {
        return false;
    }

    if (button < buttonsDownNow.count())
    {
        return buttonsDownNow[button];
    }

    return false;
}

bool SerialGamepad::isButtonUpNow(int button) const
{
    if (button < 0)
    {
        return false;
    }

    if (button < buttonsUpNow.count())
    {
        return buttonsUpNow[button];
    }

    return false;
}

void SerialGamepad::updatePorts()
{
    const QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo& info : infos)
    {
        const QString name = info.portName();

        if (!connections.contains(name))
        {
            QSerialPort* port = new QSerialPort(name, this);
            port->setBaudRate(baudRate);
            if (port->open(QIODevice::OpenModeFlag::ReadOnly))
            {
                qDebug() << "Serial port" << port->portName() << port->baudRate() << "opened";

                connect(port, &QSerialPort::readyRead, this, &SerialGamepad::onReadyRead);

                connections.insert(name, port);
            }
            else
            {
                qWarning() << "Failed to open serial port" << name;
                port->deleteLater();
            }
        }
    }

    const QStringList names = connections.keys();

    for (int i = 0; i < names.count(); ++i)
    {
        const QString name = names[i];
        QSerialPort* serial = connections.value(name);
        if (!serial)
        {
            qWarning() << "!serial";
            continue;
        }

        if (!serial->isOpen())
        {
            qDebug() << "Serial port" << name << "close";
            connections.remove(name);
            delete serial;
        }
    }
}

void SerialGamepad::onReadyRead()
{
    QSerialPort* serial = qobject_cast<QSerialPort*>(sender());
    if (!serial)
    {
        qWarning() << "!serial";
        return;
    }

    while (serial->canReadLine())
    {
        const QByteArray line = serial->readLine().trimmed();
        for (const char& c : line)
        {
            if (c != '0' && c != '1')
            {
                qDebug() << "not valid line";
                return;
            }
        }

        QVector<bool> currentButtons;
        for (const char& c : line)
        {
            if (c == '1')
            {
                currentButtons.append(true);
            }
            else
            {
                currentButtons.append(false);
            }
        }

        if (currentButtons != buttonsDown)
        {
            for (int i = 0; i < currentButtons.count(); ++i)
            {
                const bool currentDown = currentButtons[i];
                bool prevDown = false;
                if (i < buttonsDown.count())
                {
                    prevDown = buttonsDown[i];
                }

                if (currentDown && !prevDown)
                {
                    buttonsDownNow.append(true);
                    buttonsUpNow.append(false);
                }
                else if (!currentDown && prevDown)
                {
                    buttonsDownNow.append(false);
                    buttonsUpNow.append(true);
                }
                else
                {
                    buttonsDownNow.append(false);
                    buttonsUpNow.append(false);
                }
            }

            buttonsDown = currentButtons;

            emit buttonsChanged();

            buttonsDownNow.clear();
            buttonsUpNow.clear();
        }
    }
}
