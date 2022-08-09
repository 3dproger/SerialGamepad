#ifndef INPUTEMULATORTYPES_H
#define INPUTEMULATORTYPES_H

namespace InputEmulatorTypes
{

enum class GamepadStdButton {
    Unknown,

    Left,
    Right,
    Up,
    Down,

    A,
    B,
    X,
    Y,

    L1,
    L2,
    L3,
    R1,
    R2,
    R3,

    Select,
    Start,
    Center,
    Guide,
};

enum class MouseButton {
    MouseButton_Unknown,

    MouseButton_Left,
    MouseButton_Middle,
    MouseButton_Right,
};

enum class MouseWheelClick {
    NotClicked,
    Positive,
    Negative
};

enum class Key {
    Key_Unknown,

    Key_0 = 48,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,

    Key_A = 65,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,

    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,
    Key_F11,
    Key_F12,

    Key_Left,
    Key_Up,
    Key_Right,
    Key_Down,

    Key_Home,
    Key_End,
    Key_PageUp,
    Key_PageDown,

    Key_CapsLock,
    Key_NumLock,
    Key_ScrollLock,

    Key_LShift,
    Key_RShift,
    Key_LControl,
    Key_RControl,
    Key_LAlt,
    Key_RAlt,

    Key_Meta,
    Key_Escape,
    Key_Tab,
    Key_Backspace,
    Key_Enter,
    Key_Insert,
    Key_Delete,
    Key_Pause,

    Key_Space = 20,
};

}


#endif // INPUTEMULATORTYPES_H
