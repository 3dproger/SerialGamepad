#ifndef INPUTEMULATOR_H
#define INPUTEMULATOR_H

#include "inputemulatortypes.h"
#include "abstractplatforminputemulator.h"

class InputEmulator
{
public:
    InputEmulator();
    ~InputEmulator();

    void emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down);
    void emulateMouseWheelSpeed(double x, double y);
    bool isMouseWheelSpeedAvailable() const;
    void emulateMouseWheelClick(InputEmulatorTypes::MouseWheelClick x, InputEmulatorTypes::MouseWheelClick y);
    void emulateMouseMoveRelative(int64_t dx, int64_t dy);
    void emulateMouseMoveAbsolute(int64_t x, int64_t y);
    bool isHorizontalScrollAvailable() const;
    void emulateKeyboard(InputEmulatorTypes::Key key, bool down);

private:
    AbstractPlatformInputEmulator& platform;
};

#endif // INPUTEMULATOR_H
