#include "serialgamepad.h"
#include "inputemulator.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

void updateControll(SerialGamepad& gamepad, InputEmulator& emulator)
{
    if (gamepad.isButtonDownNow(0))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_Left, true);
    }

    if (gamepad.isButtonUpNow(0))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_Left, false);
    }

    if (gamepad.isButtonDownNow(1))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_Right, true);
    }

    if (gamepad.isButtonUpNow(1))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_Right, false);
    }

    if (gamepad.isButtonDownNow(2))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_S, true);
    }

    if (gamepad.isButtonUpNow(2))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_S, false);
    }

    if (gamepad.isButtonDownNow(3))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_A, true);
    }

    if (gamepad.isButtonUpNow(3))
    {
        emulator.emulateKeyboard(InputEmulatorTypes::Key::Key_A, false);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InputEmulator emulator;

    SerialGamepad gamepad(115200);
    QObject::connect(&gamepad, &SerialGamepad::buttonsChanged, [&gamepad, &emulator]() { updateControll(gamepad, emulator); });

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&gamepad, &emulator]() { updateControll(gamepad, emulator); });
    timer.start(16);

    return a.exec();
}
