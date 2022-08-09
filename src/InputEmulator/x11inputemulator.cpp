#include "x11inputemulator.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <iostream>

namespace
{

unsigned int convertMouseButton(InputEmulatorTypes::MouseButton button, bool& ok)
{
    ok = true;

    switch (button)
    {
    case InputEmulatorTypes::MouseButton::MouseButton_Left: return Button1;
    case InputEmulatorTypes::MouseButton::MouseButton_Middle: return Button2;
    case InputEmulatorTypes::MouseButton::MouseButton_Right: return Button3;
    case InputEmulatorTypes::MouseButton::MouseButton_Unknown: break;
    }

    ok = false;
    return 0;
}

}

X11inputemulator::X11inputemulator()
{
    display = XOpenDisplay(nullptr);
    if (!display)
    {
        std::cerr << "Failed to open display" << std::endl;
    }
}

X11inputemulator::~X11inputemulator()
{
    if (display)
    {
        XCloseDisplay((Display*)display);
        display = nullptr;
    }
}

void X11inputemulator::emulateMouseButton(InputEmulatorTypes::MouseButton button_, bool down)
{
    if (!display)
    {
        std::cerr << "Display not opened" << std::endl;
        return;
    }

    bool ok = false;
    const auto button = convertMouseButton(button_, ok);
    if (!ok)
    {
        std::cerr << "Failed to convert int mouse button to x11 mouse button" << std::endl;
        return;
    }

    const int ret = XTestFakeButtonEvent((Display*)display, button, down, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }
}

void X11inputemulator::emulateMouseWheel(double x, double y)
{
    std::cerr << "Not implemented" << std::endl;
}

void X11inputemulator::emulateMouseMoveRelative(int64_t dx, int64_t dy)
{
    std::cerr << "Not implemented" << std::endl;
}

void X11inputemulator::emulateMouseMoveAbsolute(int64_t x, int64_t y)
{
    std::cerr << "Not implemented" << std::endl;
}

bool X11inputemulator::isHorizontalScrollAvailable() const
{
    return false;
}

void X11inputemulator::emulateKeyboard(InputEmulatorTypes::Key key, bool down)
{
    std::cerr << "Not implemented" << std::endl;
}
