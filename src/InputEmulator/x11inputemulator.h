#ifndef X11INPUTEMULATOR_H
#define X11INPUTEMULATOR_H

#include "abstractplatforminputemulator.h"

class X11inputemulator : public AbstractPlatformInputEmulator
{
public:
    X11inputemulator();
    ~X11inputemulator();
    void emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down) override;
    void emulateMouseWheelSpeed(double x, double y) override;
    bool isMouseWheelSpeedAvailable() const override;
    void emulateMouseWheelClick(InputEmulatorTypes::MouseWheelClick x, InputEmulatorTypes::MouseWheelClick y) override;
    bool isHorizontalScrollAvailable() const override;
    void emulateMouseMoveRelative(int64_t dx, int64_t dy) override;
    void emulateMouseMoveAbsolute(int64_t x, int64_t y) override;
    void emulateKeyboard(InputEmulatorTypes::Key key, bool down) override;

private:
    void* display = nullptr;
};

#endif // X11INPUTEMULATOR_H
