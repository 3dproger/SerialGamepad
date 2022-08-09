#ifndef SERIALGAMEPAD_H
#define SERIALGAMEPAD_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QSerialPort>

class SerialGamepad : public QObject
{
    Q_OBJECT
public:
    explicit SerialGamepad(int baudRate, QObject *parent = nullptr);
    bool isButtonDown(int button) const;
    bool isButtonDownNow(int button) const;
    bool isButtonUpNow(int button) const;
    int getButtonsCount() const { return buttonsDown.count(); }

signals:
    void buttonsChanged();

private slots:
    void updatePorts();
    void onReadyRead();

private:
    const int baudRate;
    QTimer timerUpdatePorts;
    QMap<QString, QSerialPort*> connections;
    QVector<bool> buttonsDown;
    QVector<bool> buttonsDownNow;
    QVector<bool> buttonsUpNow;
};

#endif // SERIALGAMEPAD_H
