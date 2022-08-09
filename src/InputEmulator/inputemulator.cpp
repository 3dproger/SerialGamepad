#include "inputemulator.h"
#if defined(_WIN32) || defined(_WIN64)
#include "winapiinputemulator.h"
#elif defined(__unix__)
#include "x11inputemulator.h"
#endif

InputEmulator::InputEmulator()
#if defined(_WIN32) || defined(_WIN64)
    : platform(*new WinApiInputEmulator())
#elif defined(__unix__)
    : platform(*new X11inputemulator())
#endif
{

}

InputEmulator::~InputEmulator()
{
    delete &platform;
}

void InputEmulator::emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down)
{
    platform.emulateMouseButton(button, down);
}

void InputEmulator::emulateMouseWheel(double x, double y)
{
    platform.emulateMouseWheel(x, y);
}

void InputEmulator::emulateMouseMoveDelta(int64_t dx, int64_t dy)
{
    platform.emulateMouseMoveDelta(dx, dy);
}

void InputEmulator::emulateMouseMoveToCoord(int64_t x, int64_t y)
{
    platform.emulateMouseMoveToCoord(x, y);
}

bool InputEmulator::isHorizontalScrollAvailable() const
{
    return platform.isHorizontalScrollAvailable();
}

void InputEmulator::emulateKeyboard(InputEmulatorTypes::Key key, bool down)
{
    platform.emulateKeyboard(key, down);
}
