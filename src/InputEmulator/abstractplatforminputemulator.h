#ifndef ABSTRACTPLATFORMINPUTEMULATOR_H
#define ABSTRACTPLATFORMINPUTEMULATOR_H

#include "inputemulatortypes.h"
#include <stdint.h>

class AbstractPlatformInputEmulator
{
public:
    virtual ~AbstractPlatformInputEmulator(){}

    virtual void emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down) = 0;
    virtual void emulateMouseWheel(double x, double y) = 0;
    virtual void emulateMouseMoveRelative(int64_t dx, int64_t dy) = 0;
    virtual void emulateMouseMoveAbsolute(int64_t x, int64_t y) = 0;
    virtual bool isHorizontalScrollAvailable() const = 0;
    virtual void emulateKeyboard(InputEmulatorTypes::Key key, bool down) = 0;
};

#endif // ABSTRACTPLATFORMINPUTEMULATOR_H
