#pragma once
#include <imgui.h>
#include <ForgexGraphics.h>

namespace Forgex::Editor::UI::Utils
{
    inline ImGuiKey ForgexKeyToImGuiKey(int glfwKey)
    {
        switch (glfwKey)
        {
            case KEYCODE_TAB:           return ImGuiKey_Tab;
            case KEYCODE_LEFT:          return ImGuiKey_LeftArrow;
            case KEYCODE_RIGHT:         return ImGuiKey_RightArrow;
            case KEYCODE_UP:            return ImGuiKey_UpArrow;
            case KEYCODE_DOWN:          return ImGuiKey_DownArrow;
            case KEYCODE_PAGE_UP:       return ImGuiKey_PageUp;
            case KEYCODE_PAGE_DOWN:     return ImGuiKey_PageDown;
            case KEYCODE_HOME:          return ImGuiKey_Home;
            case KEYCODE_END:           return ImGuiKey_End;
            case KEYCODE_INSERT:        return ImGuiKey_Insert;
            case KEYCODE_DELETE:        return ImGuiKey_Delete;
            case KEYCODE_BACKSPACE:     return ImGuiKey_Backspace;
            case KEYCODE_SPACE:         return ImGuiKey_Space;
            case KEYCODE_ENTER:         return ImGuiKey_Enter;
            case KEYCODE_ESCAPE:        return ImGuiKey_Escape;
            case KEYCODE_APOSTROPHE:    return ImGuiKey_Apostrophe;
            case KEYCODE_COMMA:         return ImGuiKey_Comma;
            case KEYCODE_MINUS:         return ImGuiKey_Minus;
            case KEYCODE_PERIOD:        return ImGuiKey_Period;
            case KEYCODE_SLASH:         return ImGuiKey_Slash;
            case KEYCODE_SEMICOLON:     return ImGuiKey_Semicolon;
            case KEYCODE_EQUAL:         return ImGuiKey_Equal;
            case KEYCODE_LEFT_BRACKET:  return ImGuiKey_LeftBracket;
            case KEYCODE_BACKSLASH:     return ImGuiKey_Backslash;
            case KEYCODE_RIGHT_BRACKET: return ImGuiKey_RightBracket;
            case KEYCODE_GRAVE_ACCENT:  return ImGuiKey_GraveAccent;
            case KEYCODE_CAPS_LOCK:     return ImGuiKey_CapsLock;
            case KEYCODE_SCROLL_LOCK:   return ImGuiKey_ScrollLock;
            case KEYCODE_NUM_LOCK:      return ImGuiKey_NumLock;
            case KEYCODE_PRINT_SCREEN:  return ImGuiKey_PrintScreen;
            case KEYCODE_PAUSE:         return ImGuiKey_Pause;
            case KEYCODE_LEFT_SHIFT:    return ImGuiKey_LeftShift;
            case KEYCODE_LEFT_CONTROL:  return ImGuiKey_LeftCtrl;
            case KEYCODE_LEFT_ALT:      return ImGuiKey_LeftAlt;
            case KEYCODE_LEFT_SUPER:    return ImGuiKey_LeftSuper;
            case KEYCODE_RIGHT_SHIFT:   return ImGuiKey_RightShift;
            case KEYCODE_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
            case KEYCODE_RIGHT_ALT:     return ImGuiKey_RightAlt;
            case KEYCODE_RIGHT_SUPER:   return ImGuiKey_RightSuper;
            case KEYCODE_MENU:          return ImGuiKey_Menu;
            case KEYCODE_0:             return ImGuiKey_0;
            case KEYCODE_1:             return ImGuiKey_1;
            case KEYCODE_2:             return ImGuiKey_2;
            case KEYCODE_3:             return ImGuiKey_3;
            case KEYCODE_4:             return ImGuiKey_4;
            case KEYCODE_5:             return ImGuiKey_5;
            case KEYCODE_6:             return ImGuiKey_6;
            case KEYCODE_7:             return ImGuiKey_7;
            case KEYCODE_8:             return ImGuiKey_8;
            case KEYCODE_9:             return ImGuiKey_9;
            case KEYCODE_A:             return ImGuiKey_A;
            case KEYCODE_B:             return ImGuiKey_B;
            case KEYCODE_C:             return ImGuiKey_C;
            case KEYCODE_D:             return ImGuiKey_D;
            case KEYCODE_E:             return ImGuiKey_E;
            case KEYCODE_F:             return ImGuiKey_F;
            case KEYCODE_G:             return ImGuiKey_G;
            case KEYCODE_H:             return ImGuiKey_H;
            case KEYCODE_I:             return ImGuiKey_I;
            case KEYCODE_J:             return ImGuiKey_J;
            case KEYCODE_K:             return ImGuiKey_K;
            case KEYCODE_L:             return ImGuiKey_L;
            case KEYCODE_M:             return ImGuiKey_M;
            case KEYCODE_N:             return ImGuiKey_N;
            case KEYCODE_O:             return ImGuiKey_O;
            case KEYCODE_P:             return ImGuiKey_P;
            case KEYCODE_Q:             return ImGuiKey_Q;
            case KEYCODE_R:             return ImGuiKey_R;
            case KEYCODE_S:             return ImGuiKey_S;
            case KEYCODE_T:             return ImGuiKey_T;
            case KEYCODE_U:             return ImGuiKey_U;
            case KEYCODE_V:             return ImGuiKey_V;
            case KEYCODE_W:             return ImGuiKey_W;
            case KEYCODE_X:             return ImGuiKey_X;
            case KEYCODE_Y:             return ImGuiKey_Y;
            case KEYCODE_Z:             return ImGuiKey_Z;
            case KEYCODE_F1:            return ImGuiKey_F1;
            case KEYCODE_F2:            return ImGuiKey_F2;
            case KEYCODE_F3:            return ImGuiKey_F3;
            case KEYCODE_F4:            return ImGuiKey_F4;
            case KEYCODE_F5:            return ImGuiKey_F5;
            case KEYCODE_F6:            return ImGuiKey_F6;
            case KEYCODE_F7:            return ImGuiKey_F7;
            case KEYCODE_F8:            return ImGuiKey_F8;
            case KEYCODE_F9:            return ImGuiKey_F9;
            case KEYCODE_F10:           return ImGuiKey_F10;
            case KEYCODE_F11:           return ImGuiKey_F11;
            case KEYCODE_F12:           return ImGuiKey_F12;
            case KEYCODE_F13:           return ImGuiKey_F13;
            case KEYCODE_F14:           return ImGuiKey_F14;
            case KEYCODE_F15:           return ImGuiKey_F15;
            case KEYCODE_F16:           return ImGuiKey_F16;
            case KEYCODE_F17:           return ImGuiKey_F17;
            case KEYCODE_F18:           return ImGuiKey_F18;
            case KEYCODE_F19:           return ImGuiKey_F19;
            case KEYCODE_F20:           return ImGuiKey_F20;
            case KEYCODE_F21:           return ImGuiKey_F21;
            case KEYCODE_F22:           return ImGuiKey_F22;
            case KEYCODE_F23:           return ImGuiKey_F23;
            case KEYCODE_F24:           return ImGuiKey_F24;
            case KEYCODE_KP_0:          return ImGuiKey_Keypad0;
            case KEYCODE_KP_1:          return ImGuiKey_Keypad1;
            case KEYCODE_KP_2:          return ImGuiKey_Keypad2;
            case KEYCODE_KP_3:          return ImGuiKey_Keypad3;
            case KEYCODE_KP_4:          return ImGuiKey_Keypad4;
            case KEYCODE_KP_5:          return ImGuiKey_Keypad5;
            case KEYCODE_KP_6:          return ImGuiKey_Keypad6;
            case KEYCODE_KP_7:          return ImGuiKey_Keypad7;
            case KEYCODE_KP_8:          return ImGuiKey_Keypad8;
            case KEYCODE_KP_9:          return ImGuiKey_Keypad9;
            case KEYCODE_KP_DECIMAL:    return ImGuiKey_KeypadDecimal;
            case KEYCODE_KP_DIVIDE:     return ImGuiKey_KeypadDivide;
            case KEYCODE_KP_MULTIPLY:   return ImGuiKey_KeypadMultiply;
            case KEYCODE_KP_SUBTRACT:   return ImGuiKey_KeypadSubtract;
            case KEYCODE_KP_ADD:        return ImGuiKey_KeypadAdd;
            case KEYCODE_KP_ENTER:      return ImGuiKey_KeypadEnter;
            case KEYCODE_KP_EQUAL:      return ImGuiKey_KeypadEqual;
            case KEYCODE_WORLD_1:
            case KEYCODE_WORLD_2:       return ImGuiKey_Oem102;
            default:                     return ImGuiKey_None;
        }
    }
}
