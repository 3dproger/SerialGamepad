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
    void emulateMouseWheel(double x, double y);
    void emulateMouseMoveDelta(int64_t dx, int64_t dy);
    void emulateMouseMoveToCoord(int64_t x, int64_t y);
    bool isHorizontalScrollAvailable() const;
    void emulateKeyboard(InputEmulatorTypes::Key key, bool down);

private:
    AbstractPlatformInputEmulator& platform;
};

#endif // INPUTEMULATOR_H
