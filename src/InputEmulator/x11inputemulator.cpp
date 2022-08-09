#include "x11inputemulator.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
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

unsigned long convertKey(InputEmulatorTypes::Key key, Display* display, bool& ok)
{
    if (!display)
    {
        ok = false;
        std::cerr << "Display not opened" << std::endl;
        return 0;
    }

    ok = true;

    switch (key)
    {
    case InputEmulatorTypes::Key::Key_Unknown:
        break;

    case InputEmulatorTypes::Key::Key_0:
    case InputEmulatorTypes::Key::Key_1:
    case InputEmulatorTypes::Key::Key_2:
    case InputEmulatorTypes::Key::Key_3:
    case InputEmulatorTypes::Key::Key_4:
    case InputEmulatorTypes::Key::Key_5:
    case InputEmulatorTypes::Key::Key_6:
    case InputEmulatorTypes::Key::Key_7:
    case InputEmulatorTypes::Key::Key_8:
    case InputEmulatorTypes::Key::Key_9:
    case InputEmulatorTypes::Key::Key_A:
    case InputEmulatorTypes::Key::Key_B:
    case InputEmulatorTypes::Key::Key_C:
    case InputEmulatorTypes::Key::Key_D:
    case InputEmulatorTypes::Key::Key_E:
    case InputEmulatorTypes::Key::Key_F:
    case InputEmulatorTypes::Key::Key_G:
    case InputEmulatorTypes::Key::Key_H:
    case InputEmulatorTypes::Key::Key_I:
    case InputEmulatorTypes::Key::Key_J:
    case InputEmulatorTypes::Key::Key_K:
    case InputEmulatorTypes::Key::Key_L:
    case InputEmulatorTypes::Key::Key_M:
    case InputEmulatorTypes::Key::Key_N:
    case InputEmulatorTypes::Key::Key_O:
    case InputEmulatorTypes::Key::Key_P:
    case InputEmulatorTypes::Key::Key_Q:
    case InputEmulatorTypes::Key::Key_R:
    case InputEmulatorTypes::Key::Key_S:
    case InputEmulatorTypes::Key::Key_T:
    case InputEmulatorTypes::Key::Key_U:
    case InputEmulatorTypes::Key::Key_V:
    case InputEmulatorTypes::Key::Key_W:
    case InputEmulatorTypes::Key::Key_X:
    case InputEmulatorTypes::Key::Key_Y:
    case InputEmulatorTypes::Key::Key_Z:
        return XKeysymToKeycode(display, (KeySym)key);

    case InputEmulatorTypes::Key::Key_F1:
    case InputEmulatorTypes::Key::Key_F2:
    case InputEmulatorTypes::Key::Key_F3:
    case InputEmulatorTypes::Key::Key_F4:
    case InputEmulatorTypes::Key::Key_F5:
    case InputEmulatorTypes::Key::Key_F6:
    case InputEmulatorTypes::Key::Key_F7:
    case InputEmulatorTypes::Key::Key_F8:
    case InputEmulatorTypes::Key::Key_F9:
    case InputEmulatorTypes::Key::Key_F10:
    case InputEmulatorTypes::Key::Key_F11:
    case InputEmulatorTypes::Key::Key_F12:
        break;

    case InputEmulatorTypes::Key::Key_Left: return XKeysymToKeycode(display, XK_Left);
    case InputEmulatorTypes::Key::Key_Up: return XKeysymToKeycode(display, XK_Up);
    case InputEmulatorTypes::Key::Key_Right: return XKeysymToKeycode(display, XK_Right);
    case InputEmulatorTypes::Key::Key_Down: return XKeysymToKeycode(display, XK_Down);

    case InputEmulatorTypes::Key::Key_Home:
        break;
    case InputEmulatorTypes::Key::Key_End:
        break;
    case InputEmulatorTypes::Key::Key_PageUp:
        break;
    case InputEmulatorTypes::Key::Key_PageDown:
        break;
    case InputEmulatorTypes::Key::Key_CapsLock:
        break;
    case InputEmulatorTypes::Key::Key_NumLock:
        break;
    case InputEmulatorTypes::Key::Key_ScrollLock:
        break;
    case InputEmulatorTypes::Key::Key_LShift:
        break;
    case InputEmulatorTypes::Key::Key_RShift:
        break;
    case InputEmulatorTypes::Key::Key_LControl:
        break;
    case InputEmulatorTypes::Key::Key_RControl:
        break;
    case InputEmulatorTypes::Key::Key_LAlt:
        break;
    case InputEmulatorTypes::Key::Key_RAlt:
        break;
    case InputEmulatorTypes::Key::Key_Meta:
        break;
    case InputEmulatorTypes::Key::Key_Escape:
        break;
    case InputEmulatorTypes::Key::Key_Tab:
        break;
    case InputEmulatorTypes::Key::Key_Backspace:
        break;
    case InputEmulatorTypes::Key::Key_Enter:
        break;
    case InputEmulatorTypes::Key::Key_Insert:
        break;
    case InputEmulatorTypes::Key::Key_Delete:
        break;
    case InputEmulatorTypes::Key::Key_Pause:
        break;
    case InputEmulatorTypes::Key::Key_Space: return XKeysymToKeycode(display, XK_space);
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
        std::cerr << "Failed to convert mouse button" << std::endl;
        return;
    }

    const int ret = XTestFakeButtonEvent((Display*)display, button, down, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }
}

bool X11inputemulator::isMouseWheelSpeedAvailable() const
{
    return false;
}

void X11inputemulator::emulateMouseWheelClick(InputEmulatorTypes::MouseWheelClick x, InputEmulatorTypes::MouseWheelClick y)
{
    if (!display)
    {
        std::cerr << "Display not opened" << std::endl;
        return;
    }

    int button = 0;

    switch (y)
    {
    case InputEmulatorTypes::MouseWheelClick::NotClicked:
        break;
    case InputEmulatorTypes::MouseWheelClick::Positive:
        button = Button5;
        break;
    case InputEmulatorTypes::MouseWheelClick::Negative:
        button = Button4;
        break;
    }

    int ret = XTestFakeButtonEvent((Display*)display, button, true, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }

    ret = XTestFakeButtonEvent((Display*)display, button, false, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }

    if (x != InputEmulatorTypes::MouseWheelClick::NotClicked)
    {
        std::cerr << "Not implemented" << std::endl;
    }
}

bool X11inputemulator::isHorizontalScrollAvailable() const
{
    return false;
}

void X11inputemulator::emulateMouseWheelSpeed(double, double)
{
    std::cerr << "Not implemented" << std::endl;
}

void X11inputemulator::emulateMouseMoveRelative(int64_t dx, int64_t dy)
{
    if (!display)
    {
        std::cerr << "Display not opened" << std::endl;
        return;
    }

    const int ret = XTestFakeRelativeMotionEvent((Display*)display, dx, dy, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }
}

void X11inputemulator::emulateMouseMoveAbsolute(int64_t x, int64_t y)
{
    if (!display)
    {
        std::cerr << "Display not opened" << std::endl;
        return;
    }

    const int ret = XTestFakeMotionEvent((Display*)display, -1, x, y, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }
}

void X11inputemulator::emulateKeyboard(InputEmulatorTypes::Key key_, bool down)
{
    if (!display)
    {
        std::cerr << "Display not opened" << std::endl;
        return;
    }

    bool ok = false;
    const auto key = convertKey(key_, (Display*)display, ok);
    if (!ok)
    {
        std::cerr << "Failed to convert key" << std::endl;
        return;
    }

    const int ret = XTestFakeKeyEvent((Display*)display, key, down, CurrentTime);
    XFlush((Display*)display);
    if (ret != 1)
    {
        std::cerr << "XTestFakeButtonEvent error " << ret << std::endl;
    }
}
