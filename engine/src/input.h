#pragma once
#include "concepts.h"

namespace engine {
enum class MouseButton;
enum class ButtonAction;
enum class Key;

// a function to convert input from glfw's format to engine's.
template<typename T>
requires in_type_list_v<T, MouseButton, ButtonAction, Key>
    T glfw2input(int input)
noexcept;

enum class MouseButton {
    Left        = 0,
    Right       = 1,
    Middle      = 2,
    Button_Last = 7,
    Button_1    = Left,
    Button_2    = Right,
    Button_3    = Middle,
    Button_4,
    Button_5,
    Button_6,
    Button_7,
    Button_8 = Button_Last
};

enum class ButtonAction { // this enum is used for both mouse and keyboard
    Release = 0,
    Press   = 1,
    Repeat  = 2 // the key was held down until it repeated
};

enum class Key {
    /* The unknown key */
    Unknown = -1,
    /* Printable keys */
    Space        = 32,
    Apostrophe   = 39, /* ' */
    Comma        = 44, /* , */
    Minus        = 45, /* - */
    Preiod       = 46, /* . */
    Slash        = 47, /* / */
    Key_0        = 48,
    Key_1        = 49,
    Key_2        = 50,
    Key_3        = 51,
    Key_4        = 52,
    Key_5        = 53,
    Key_6        = 54,
    Key_7        = 55,
    Key_8        = 56,
    Key_9        = 57,
    Semicolon    = 59, /* ; */
    Equal        = 61, /* = */
    Key_A        = 65,
    Key_B        = 66,
    Key_C        = 67,
    Key_D        = 68,
    Key_E        = 69,
    Key_F        = 70,
    Key_G        = 71,
    Key_H        = 72,
    Key_I        = 73,
    Key_J        = 74,
    Key_K        = 75,
    Key_L        = 76,
    Key_M        = 77,
    Key_N        = 78,
    Key_O        = 79,
    Key_P        = 80,
    Key_Q        = 81,
    Key_R        = 82,
    Key_S        = 83,
    Key_T        = 84,
    Key_U        = 85,
    Key_V        = 86,
    Key_W        = 87,
    Key_X        = 88,
    Key_Y        = 89,
    Key_Z        = 90,
    LeftBracket  = 91,  /* [ */
    Backslash    = 92,  /* \ */
    RightBracket = 93,  /* ] */
    GraveAccent  = 96,  /* ` */
    World_1      = 161, /* non-US #1 */
    World_2      = 162, /* non-US #2 */
    /* Function keys */
    Escape       = 256,
    Enter        = 257,
    Tab          = 258,
    Backspace    = 259,
    Insert       = 260,
    Delete       = 261,
    Right        = 262,
    Left         = 263,
    Down         = 264,
    Up           = 265,
    PageUp       = 266,
    PageDown     = 267,
    Home         = 268,
    End          = 269,
    CapsLock     = 280,
    ScrollLock   = 281,
    NumLock      = 282,
    PrintScreen  = 283,
    Pause        = 284,
    F1           = 290,
    F2           = 291,
    F3           = 292,
    F4           = 293,
    F5           = 294,
    F6           = 295,
    F7           = 296,
    F8           = 297,
    F9           = 298,
    F10          = 299,
    F11          = 300,
    F12          = 301,
    F13          = 302,
    F14          = 303,
    F15          = 304,
    F16          = 305,
    F17          = 306,
    F18          = 307,
    F19          = 308,
    F20          = 309,
    F21          = 310,
    F22          = 311,
    F23          = 312,
    F24          = 313,
    F25          = 314,
    KP_0         = 320,
    KP_1         = 321,
    KP_2         = 322,
    KP_3         = 323,
    KP_4         = 324,
    KP_5         = 325,
    KP_6         = 326,
    KP_7         = 327,
    KP_8         = 328,
    KP_9         = 329,
    KP_Decimal   = 330,
    KP_Divide    = 331,
    KP_Multiply  = 332,
    KP_Subtract  = 333,
    KP_Add       = 334,
    KP_Enter     = 335,
    KP_Equal     = 336,
    LeftShift    = 340,
    LeftControl  = 341,
    LeftAlt      = 342,
    LeftSuper    = 343,
    RightShift   = 344,
    RightControl = 345,
    RightAlt     = 346,
    RightSuper   = 347,
    Menu         = 348,

    Key_Last = Menu

};

class Modifier {
public:
    Modifier(unsigned int mods);

public:
    bool shift() const;
    bool control() const;
    bool alt() const;
    bool super() const;
    bool capsLock() const;
    bool numLock() const;

protected:
    unsigned int flags;
};
} // namespace engine

#include "input.hpp"