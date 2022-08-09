#ifndef X11INPUTEMULATOR_H
#define X11INPUTEMULATOR_H

#include "abstractplatforminputemulator.h"

class X11inputemulator : public AbstractPlatformInputEmulator
{
public:
    X11inputemulator();
    ~X11inputemulator();
    void emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down) override;
    void emulateMouseWheel(double x, double y) override;
    void emulateMouseMoveDelta(int64_t dx, int64_t dy) override;
    void emulateMouseMoveToCoord(int64_t x, int64_t y) override;
    bool isHorizontalScrollAvailable() const override;
    void emulateKeyboard(InputEmulatorTypes::Key key, bool down) override;

private:
    void* display = nullptr;
};

#endif // X11INPUTEMULATOR_H
