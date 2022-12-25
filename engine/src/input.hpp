#pragma once
#include "input.h"
#include "type_traits.h"
#include <GLFW/glfw3.h>

namespace engine {
template<typename T>
requires in_type_list_v<T, MouseButton, ButtonAction, Key>
    T glfw2input(int input)
noexcept {
    if constexpr (same_as<T, MouseButton>::value) {
        switch (input) {
        case GLFW_MOUSE_BUTTON_1: {
            return MouseButton::Button_1;
        }
        case GLFW_MOUSE_BUTTON_2: {
            return MouseButton::Button_2;
        }
        case GLFW_MOUSE_BUTTON_3: {
            return MouseButton::Button_3;
        }
        case GLFW_MOUSE_BUTTON_4: {
            return MouseButton::Button_4;
        }
        case GLFW_MOUSE_BUTTON_5: {
            return MouseButton::Button_5;
        }
        case GLFW_MOUSE_BUTTON_6: {
            return MouseButton::Button_6;
        }
        case GLFW_MOUSE_BUTTON_7: {
            return MouseButton::Button_7;
        }
        case GLFW_MOUSE_BUTTON_8: {
            return MouseButton::Button_8;
        }
        }
    }
    if constexpr (same_as<T, ButtonAction>::value) {
        switch (input) {
        case GLFW_RELEASE: {
            return ButtonAction::Release;
        }
        case GLFW_PRESS: {
            return ButtonAction::Press;
        }
        case GLFW_REPEAT: {
            return ButtonAction::Repeat;
        }
        }
    }
    if constexpr (same_as<T, Key>::value) {
        switch (input) {
        case GLFW_KEY_SPACE: {
            return Key::Space;
        }
        case GLFW_KEY_APOSTROPHE: {
            return Key::Apostrophe;
        }
        case GLFW_KEY_COMMA: {
            return Key::Comma;
        }
        case GLFW_KEY_MINUS: {
            return Key::Minus;
        }
        case GLFW_KEY_PERIOD: {
            return Key::Preiod;
        }
        case GLFW_KEY_SLASH: {
            return Key::Slash;
        }
        case GLFW_KEY_0: {
            return Key::Key_0;
        }
        case GLFW_KEY_1: {
            return Key::Key_1;
        }
        case GLFW_KEY_2: {
            return Key::Key_2;
        }
        case GLFW_KEY_3: {
            return Key::Key_3;
        }
        case GLFW_KEY_4: {
            return Key::Key_4;
        }
        case GLFW_KEY_5: {
            return Key::Key_5;
        }
        case GLFW_KEY_6: {
            return Key::Key_6;
        }
        case GLFW_KEY_7: {
            return Key::Key_7;
        }
        case GLFW_KEY_8: {
            return Key::Key_8;
        }
        case GLFW_KEY_9: {
            return Key::Key_9;
        }
        case GLFW_KEY_SEMICOLON: {
            return Key::Semicolon;
        }
        case GLFW_KEY_EQUAL: {
            return Key::Equal;
        }
        case GLFW_KEY_A: {
            return Key::Key_A;
        }
        case GLFW_KEY_B: {
            return Key::Key_B;
        }
        case GLFW_KEY_C: {
            return Key::Key_C;
        }
        case GLFW_KEY_D: {
            return Key::Key_D;
        }
        case GLFW_KEY_E: {
            return Key::Key_E;
        }
        case GLFW_KEY_F: {
            return Key::Key_F;
        }
        case GLFW_KEY_G: {
            return Key::Key_G;
        }
        case GLFW_KEY_H: {
            return Key::Key_H;
        }
        case GLFW_KEY_I: {
            return Key::Key_I;
        }
        case GLFW_KEY_J: {
            return Key::Key_J;
        }
        case GLFW_KEY_K: {
            return Key::Key_K;
        }
        case GLFW_KEY_L: {
            return Key::Key_L;
        }
        case GLFW_KEY_M: {
            return Key::Key_M;
        }
        case GLFW_KEY_N: {
            return Key::Key_N;
        }
        case GLFW_KEY_O: {
            return Key::Key_O;
        }
        case GLFW_KEY_P: {
            return Key::Key_P;
        }
        case GLFW_KEY_Q: {
            return Key::Key_Q;
        }
        case GLFW_KEY_R: {
            return Key::Key_R;
        }
        case GLFW_KEY_S: {
            return Key::Key_S;
        }
        case GLFW_KEY_T: {
            return Key::Key_T;
        }
        case GLFW_KEY_U: {
            return Key::Key_U;
        }
        case GLFW_KEY_V: {
            return Key::Key_V;
        }
        case GLFW_KEY_W: {
            return Key::Key_W;
        }
        case GLFW_KEY_X: {
            return Key::Key_X;
        }
        case GLFW_KEY_Y: {
            return Key::Key_Y;
        }
        case GLFW_KEY_Z: {
            return Key::Key_Z;
        }
        case GLFW_KEY_LEFT_BRACKET: {
            return Key::LeftBracket;
        }
        case GLFW_KEY_BACKSLASH: {
            return Key::Backslash;
        }
        case GLFW_KEY_RIGHT_BRACKET: {
            return Key::RightBracket;
        }
        case GLFW_KEY_GRAVE_ACCENT: {
            return Key::GraveAccent;
        }
        case GLFW_KEY_WORLD_1: {
            return Key::World_1;
        }
        case GLFW_KEY_WORLD_2: {
            return Key::World_2;
        }
        case GLFW_KEY_ESCAPE: {
            return Key::Escape;
        }
        case GLFW_KEY_ENTER: {
            return Key::Enter;
        }
        case GLFW_KEY_TAB: {
            return Key::Tab;
        }
        case GLFW_KEY_BACKSPACE: {
            return Key::Backspace;
        }
        case GLFW_KEY_INSERT: {
            return Key::Insert;
        }
        case GLFW_KEY_DELETE: {
            return Key::Delete;
        }
        case GLFW_KEY_RIGHT: {
            return Key::Right;
        }
        case GLFW_KEY_LEFT: {
            return Key::Left;
        }
        case GLFW_KEY_DOWN: {
            return Key::Down;
        }
        case GLFW_KEY_UP: {
            return Key::Up;
        }
        case GLFW_KEY_PAGE_UP: {
            return Key::PageUp;
        }
        case GLFW_KEY_PAGE_DOWN: {
            return Key::PageDown;
        }
        case GLFW_KEY_HOME: {
            return Key::Home;
        }
        case GLFW_KEY_END: {
            return Key::End;
        }
        case GLFW_KEY_CAPS_LOCK: {
            return Key::CapsLock;
        }
        case GLFW_KEY_SCROLL_LOCK: {
            return Key::ScrollLock;
        }
        case GLFW_KEY_NUM_LOCK: {
            return Key::NumLock;
        }
        case GLFW_KEY_PRINT_SCREEN: {
            return Key::PrintScreen;
        }
        case GLFW_KEY_PAUSE: {
            return Key::Pause;
        }
        case GLFW_KEY_F1: {
            return Key::F1;
        }
        case GLFW_KEY_F2: {
            return Key::F2;
        }
        case GLFW_KEY_F3: {
            return Key::F3;
        }
        case GLFW_KEY_F4: {
            return Key::F4;
        }
        case GLFW_KEY_F5: {
            return Key::F5;
        }
        case GLFW_KEY_F6: {
            return Key::F6;
        }
        case GLFW_KEY_F7: {
            return Key::F7;
        }
        case GLFW_KEY_F8: {
            return Key::F8;
        }
        case GLFW_KEY_F9: {
            return Key::F9;
        }
        case GLFW_KEY_F10: {
            return Key::F10;
        }
        case GLFW_KEY_F11: {
            return Key::F11;
        }
        case GLFW_KEY_F12: {
            return Key::F12;
        }
        case GLFW_KEY_F13: {
            return Key::F13;
        }
        case GLFW_KEY_F14: {
            return Key::F14;
        }
        case GLFW_KEY_F15: {
            return Key::F15;
        }
        case GLFW_KEY_F16: {
            return Key::F16;
        }
        case GLFW_KEY_F17: {
            return Key::F17;
        }
        case GLFW_KEY_F18: {
            return Key::F18;
        }
        case GLFW_KEY_F19: {
            return Key::F19;
        }
        case GLFW_KEY_F20: {
            return Key::F20;
        }
        case GLFW_KEY_F21: {
            return Key::F21;
        }
        case GLFW_KEY_F22: {
            return Key::F22;
        }
        case GLFW_KEY_F23: {
            return Key::F23;
        }
        case GLFW_KEY_F24: {
            return Key::F24;
        }
        case GLFW_KEY_F25: {
            return Key::F25;
        }
        case GLFW_KEY_KP_0: {
            return Key::KP_0;
        }
        case GLFW_KEY_KP_1: {
            return Key::KP_1;
        }
        case GLFW_KEY_KP_2: {
            return Key::KP_2;
        }
        case GLFW_KEY_KP_3: {
            return Key::KP_3;
        }
        case GLFW_KEY_KP_4: {
            return Key::KP_4;
        }
        case GLFW_KEY_KP_5: {
            return Key::KP_5;
        }
        case GLFW_KEY_KP_6: {
            return Key::KP_6;
        }
        case GLFW_KEY_KP_7: {
            return Key::KP_7;
        }
        case GLFW_KEY_KP_8: {
            return Key::KP_8;
        }
        case GLFW_KEY_KP_9: {
            return Key::KP_9;
        }
        case GLFW_KEY_KP_DECIMAL: {
            return Key::KP_Decimal;
        }
        case GLFW_KEY_KP_DIVIDE: {
            return Key::KP_Divide;
        }
        case GLFW_KEY_KP_MULTIPLY: {
            return Key::KP_Multiply;
        }
        case GLFW_KEY_KP_SUBTRACT: {
            return Key::KP_Subtract;
        }
        case GLFW_KEY_KP_ADD: {
            return Key::KP_Add;
        }
        case GLFW_KEY_KP_ENTER: {
            return Key::KP_Enter;
        }
        case GLFW_KEY_KP_EQUAL: {
            return Key::KP_Equal;
        }
        case GLFW_KEY_LEFT_SHIFT: {
            return Key::LeftShift;
        }
        case GLFW_KEY_LEFT_CONTROL: {
            return Key::LeftControl;
        }
        case GLFW_KEY_LEFT_ALT: {
            return Key::LeftAlt;
        }
        case GLFW_KEY_LEFT_SUPER: {
            return Key::LeftSuper;
        }
        case GLFW_KEY_RIGHT_SHIFT: {
            return Key::RightShift;
        }
        case GLFW_KEY_RIGHT_CONTROL: {
            return Key::RightControl;
        }
        case GLFW_KEY_RIGHT_ALT: {
            return Key::RightAlt;
        }
        case GLFW_KEY_RIGHT_SUPER: {
            return Key::RightSuper;
        }
        case GLFW_KEY_MENU: {
            return Key::Menu;
        }
        // case GLFW_KEY_LAST: {
        //     return Key::Key_Last;
        // }
        default: {
            return Key::Unknown;
        }
        }
    }
}
} // namespace engine