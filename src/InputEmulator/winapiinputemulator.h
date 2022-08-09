#ifndef WINAPIINPUTEMULATOR_H
#define WINAPIINPUTEMULATOR_H

#include "abstractplatforminputemulator.h"

class WinApiInputEmulator : public AbstractPlatformInputEmulator
{
public:
    void emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down) override;
    void emulateMouseWheel(double x, double y) override;
    void emulateMouseMoveRelative(int64_t dx, int64_t dy) override;
    void emulateMouseMoveAbsolute(int64_t x, int64_t y) override;
    bool isHorizontalScrollAvailable() const override;
    void emulateKeyboard(InputEmulatorTypes::Key key, bool down) override;
};

#endif // WINAPIINPUTEMULATOR_H
