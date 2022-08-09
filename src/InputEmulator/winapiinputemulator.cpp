#include "winapiinputemulator.h"
#include "inputemulatortypes.h"
#include "targetver.h"
#include <windows.h>
#include <winuser.h>
#include <iostream>

namespace
{

void printError(DWORD error)
{
    // https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror

    if (error == 0)
    {
        std::cerr << "No winapi error" << std::endl;
    }

    LPWSTR messageBuffer = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, NULL);
    if (!messageBuffer)
    {
        std::cerr << "Winapi error:" << error << ", but failed to get error string" << std::endl;
        return;
    }

    std::cerr << "Error" << error << ": " << messageBuffer << std::endl;

    LocalFree(messageBuffer);
}

DWORD convertMouseButton(InputEmulatorTypes::MouseButton button, bool down, bool& ok)
{
    ok = false;

    switch (button)
    {
    case InputEmulatorTypes::MouseButton::MouseButton_Left:
        ok = true;
        return down ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;

    case InputEmulatorTypes::MouseButton::MouseButton_Middle:
        ok = true;
        return down ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP;

    case InputEmulatorTypes::MouseButton::MouseButton_Right:
        ok = true;
        return down ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;

    default:
        break;
    }

    return 0;
}

BYTE convertKey(InputEmulatorTypes::Key key, BYTE& s, bool& ok)
{
    s = 0;
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
        return (BYTE)key;

    case InputEmulatorTypes::Key::Key_F1: return VK_F1;
    case InputEmulatorTypes::Key::Key_F2: return VK_F2;
    case InputEmulatorTypes::Key::Key_F3: return VK_F3;
    case InputEmulatorTypes::Key::Key_F4: return VK_F4;
    case InputEmulatorTypes::Key::Key_F5: return VK_F5;
    case InputEmulatorTypes::Key::Key_F6: return VK_F6;
    case InputEmulatorTypes::Key::Key_F7: return VK_F7;
    case InputEmulatorTypes::Key::Key_F8: return VK_F8;
    case InputEmulatorTypes::Key::Key_F9: return VK_F9;
    case InputEmulatorTypes::Key::Key_F10: return VK_F10;
    case InputEmulatorTypes::Key::Key_F11: return VK_F11;
    case InputEmulatorTypes::Key::Key_F12: return VK_F12;

    case InputEmulatorTypes::Key::Key_Left: return VK_LEFT;
    case InputEmulatorTypes::Key::Key_Up: return VK_UP;
    case InputEmulatorTypes::Key::Key_Right: return VK_RIGHT;
    case InputEmulatorTypes::Key::Key_Down: return VK_DOWN;

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
    case InputEmulatorTypes::Key::Key_Space: return VK_SPACE;
    }

    ok = false;
    return 0;
}

}

void WinApiInputEmulator::emulateMouseButton(InputEmulatorTypes::MouseButton button, bool down)
{
    POINT pos;
    if (!GetCursorPos(&pos))
    {
        printError(GetLastError());
    }

    bool ok = false;
    const DWORD dwFlags = convertMouseButton(button, down, ok);
    if (!ok)
    {
        std::cerr << "Failed to conver int mouse button to winapi mouse button" << std::endl;
        return;
    }

    mouse_event(dwFlags, pos.x, pos.y, 0, 0);
}

void WinApiInputEmulator::emulateMouseWheel(double x, double y)
{
    POINT pos;
    if (!GetCursorPos(&pos))
    {
        printError(GetLastError());
    }

#if defined(MOUSEEVENTF_HWHEEL)
    mouse_event(MOUSEEVENTF_HWHEEL, pos.x, pos.y, DWORD(WHEEL_DELTA * x), 0);
#endif

    mouse_event(MOUSEEVENTF_WHEEL, pos.x, pos.y, DWORD(-WHEEL_DELTA * y), 0);
}

void WinApiInputEmulator::emulateMouseMoveRelative(int64_t dx, int64_t dy)
{
    POINT p;
    if (!GetCursorPos(&p))
    {
        std::cerr << "Failed to get cursor position" << std::endl;
        printError(GetLastError());
        return;
    }

    p.x += dx;
    p.y += dy;

    if (!SetCursorPos(p.x, p.y))
    {
        std::cerr << "Failed to set cursor position" << std::endl;
        printError(GetLastError());
    }
}

void WinApiInputEmulator::emulateMouseMoveAbsolute(int64_t x, int64_t y)
{
    if (!SetCursorPos(x, y))
    {
        std::cerr << "Failed to set cursor position" << std::endl;
        printError(GetLastError());
    }
}

bool WinApiInputEmulator::isHorizontalScrollAvailable() const
{
#if defined(MOUSEEVENTF_HWHEEL)
    return true;
#else
    return false;
#endif
}

void WinApiInputEmulator::emulateKeyboard(InputEmulatorTypes::Key key, bool down)
{
    BYTE bScan = 0;
    bool ok = false;
    BYTE bVk = convertKey(key, bScan, ok);

    if (ok)
    {
        keybd_event(bVk, bScan, down ? (KEYEVENTF_EXTENDEDKEY | 0) : (KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP), 0);
    }
    else
    {
        std::cerr << "Failed to covert key" << std::endl;
    }
}
