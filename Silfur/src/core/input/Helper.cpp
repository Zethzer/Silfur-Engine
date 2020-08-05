#include "sfpch.hpp"
#include "Helper.hpp"

#include "utility/log/Log.hpp"

namespace Silfur
{
    SDL_Scancode SfScanCodeToSDLScanCode[static_cast<std::size_t>(ScanCode::Max) + 1] = {
        SDL_SCANCODE_A,
        SDL_SCANCODE_B,
        SDL_SCANCODE_C,
        SDL_SCANCODE_D,
        SDL_SCANCODE_E,
        SDL_SCANCODE_F,
        SDL_SCANCODE_G,
        SDL_SCANCODE_H,
        SDL_SCANCODE_I,
        SDL_SCANCODE_J,
        SDL_SCANCODE_K,
        SDL_SCANCODE_L,
        SDL_SCANCODE_M,
        SDL_SCANCODE_N,
        SDL_SCANCODE_O,
        SDL_SCANCODE_P,
        SDL_SCANCODE_Q,
        SDL_SCANCODE_R,
        SDL_SCANCODE_S,
        SDL_SCANCODE_T,
        SDL_SCANCODE_U,
        SDL_SCANCODE_V,
        SDL_SCANCODE_W,
        SDL_SCANCODE_X,
        SDL_SCANCODE_Y,
        SDL_SCANCODE_Z,

        SDL_SCANCODE_SPACE,
        SDL_SCANCODE_APOSTROPHE,    /* ' */
        SDL_SCANCODE_COMMA,         /* , */
        SDL_SCANCODE_MINUS,         /* - */
        SDL_SCANCODE_PERIOD,        /* . */
        SDL_SCANCODE_SLASH,         /* / */

        SDL_SCANCODE_0, /* 0 */
        SDL_SCANCODE_1, /* 1 */
        SDL_SCANCODE_2, /* 2 */
        SDL_SCANCODE_3, /* 3 */
        SDL_SCANCODE_4, /* 4 */
        SDL_SCANCODE_5, /* 5 */
        SDL_SCANCODE_6, /* 6 */
        SDL_SCANCODE_7, /* 7 */
        SDL_SCANCODE_8, /* 8 */
        SDL_SCANCODE_9, /* 9 */

        SDL_SCANCODE_SEMICOLON,     /* ; */
        SDL_SCANCODE_EQUALS,        /* = */
        SDL_SCANCODE_LEFTBRACKET,   /* [ */
        SDL_SCANCODE_BACKSLASH,     /* \ */
        SDL_SCANCODE_RIGHTBRACKET,  /* ] */
        SDL_SCANCODE_GRAVE,         /* ` */

        /* Function keys */
        SDL_SCANCODE_ESCAPE,
        SDL_SCANCODE_RETURN,
        SDL_SCANCODE_TAB,
        SDL_SCANCODE_BACKSPACE,
        SDL_SCANCODE_INSERT,
        SDL_SCANCODE_DELETE,
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_UP,
        SDL_SCANCODE_PAGEUP,
        SDL_SCANCODE_PAGEDOWN,
        SDL_SCANCODE_HOME,
        SDL_SCANCODE_END,
        SDL_SCANCODE_CAPSLOCK,
        SDL_SCANCODE_SCROLLLOCK,
        SDL_SCANCODE_NUMLOCKCLEAR,
        SDL_SCANCODE_PRINTSCREEN,
        SDL_SCANCODE_PAUSE,
        SDL_SCANCODE_F1,
        SDL_SCANCODE_F2,
        SDL_SCANCODE_F3,
        SDL_SCANCODE_F4,
        SDL_SCANCODE_F5,
        SDL_SCANCODE_F6,
        SDL_SCANCODE_F7,
        SDL_SCANCODE_F8,
        SDL_SCANCODE_F9,
        SDL_SCANCODE_F10,
        SDL_SCANCODE_F11,
        SDL_SCANCODE_F12,
        SDL_SCANCODE_F13,
        SDL_SCANCODE_F14,
        SDL_SCANCODE_F15,
        SDL_SCANCODE_F16,
        SDL_SCANCODE_F17,
        SDL_SCANCODE_F18,
        SDL_SCANCODE_F19,
        SDL_SCANCODE_F20,
        SDL_SCANCODE_F21,
        SDL_SCANCODE_F22,
        SDL_SCANCODE_F23,
        SDL_SCANCODE_F24,

        /* Keypad */
        SDL_SCANCODE_KP_0,
        SDL_SCANCODE_KP_1,
        SDL_SCANCODE_KP_2,
        SDL_SCANCODE_KP_3,
        SDL_SCANCODE_KP_4,
        SDL_SCANCODE_KP_5,
        SDL_SCANCODE_KP_6,
        SDL_SCANCODE_KP_7,
        SDL_SCANCODE_KP_8,
        SDL_SCANCODE_KP_9,
        SDL_SCANCODE_KP_DECIMAL,
        SDL_SCANCODE_KP_DIVIDE,
        SDL_SCANCODE_KP_MULTIPLY,
        SDL_SCANCODE_KP_MINUS,
        SDL_SCANCODE_KP_PLUS,
        SDL_SCANCODE_KP_ENTER,

        SDL_SCANCODE_LSHIFT,
        SDL_SCANCODE_LCTRL,
        SDL_SCANCODE_LALT,
        SDL_SCANCODE_LGUI,
        SDL_SCANCODE_RSHIFT,
        SDL_SCANCODE_RCTRL,
        SDL_SCANCODE_RALT,
        SDL_SCANCODE_RGUI,
        SDL_SCANCODE_APPLICATION
    };

    SDL_Keycode SfKeycodeToSDLKeycode[static_cast<std::size_t>(VKey::Max) + 1] = {
        SDLK_a,
        SDLK_b,
        SDLK_c,
        SDLK_d,
        SDLK_e,
        SDLK_f,
        SDLK_g,
        SDLK_h,
        SDLK_i,
        SDLK_j,
        SDLK_k,
        SDLK_l,
        SDLK_m,
        SDLK_n,
        SDLK_o,
        SDLK_p,
        SDLK_q,
        SDLK_r,
        SDLK_s,
        SDLK_t,
        SDLK_u,
        SDLK_v,
        SDLK_w,
        SDLK_x,
        SDLK_y,
        SDLK_z,

        SDLK_SPACE,
        SDLK_QUOTE,     /* ' */
        SDLK_COMMA,     /* , */
        SDLK_MINUS,     /* - */
        SDLK_PERIOD,    /* . */
        SDLK_SLASH,     /* / */

        SDLK_0, /* 0 */
        SDLK_1, /* 1 */
        SDLK_2, /* 2 */
        SDLK_3, /* 3 */
        SDLK_4, /* 4 */
        SDLK_5, /* 5 */
        SDLK_6, /* 6 */
        SDLK_7, /* 7 */
        SDLK_8, /* 8 */
        SDLK_9, /* 9 */

        SDLK_SEMICOLON,     /* ; */
        SDLK_EQUALS,        /* = */
        SDLK_LEFTBRACKET,   /* [ */
        SDLK_BACKSLASH,     /* \ */
        SDLK_RIGHTBRACKET,  /* ] */
        SDLK_BACKQUOTE,     /* ` */

        /* Function keys */
        SDLK_ESCAPE,
        SDLK_RETURN,
        SDLK_TAB,
        SDLK_BACKSPACE,
        SDLK_INSERT,
        SDLK_DELETE,
        SDLK_RIGHT,
        SDLK_LEFT,
        SDLK_DOWN,
        SDLK_UP,
        SDLK_PAGEUP,
        SDLK_PAGEDOWN,
        SDLK_HOME,
        SDLK_END,
        SDLK_CAPSLOCK,
        SDLK_SCROLLLOCK,
        SDLK_NUMLOCKCLEAR,
        SDLK_PRINTSCREEN,
        SDLK_PAUSE,
        SDLK_F1,
        SDLK_F2,
        SDLK_F3,
        SDLK_F4,
        SDLK_F5,
        SDLK_F6,
        SDLK_F7,
        SDLK_F8,
        SDLK_F9,
        SDLK_F10,
        SDLK_F11,
        SDLK_F12,
        SDLK_F13,
        SDLK_F14,
        SDLK_F15,
        SDLK_F16,
        SDLK_F17,
        SDLK_F18,
        SDLK_F19,
        SDLK_F20,
        SDLK_F21,
        SDLK_F22,
        SDLK_F23,
        SDLK_F24,

        /* Keypad */
        SDLK_KP_0,
        SDLK_KP_1,
        SDLK_KP_2,
        SDLK_KP_3,
        SDLK_KP_4,
        SDLK_KP_5,
        SDLK_KP_6,
        SDLK_KP_7,
        SDLK_KP_8,
        SDLK_KP_9,
        SDLK_KP_DECIMAL,
        SDLK_KP_DIVIDE,
        SDLK_KP_MULTIPLY,
        SDLK_KP_MINUS,
        SDLK_KP_PLUS,
        SDLK_KP_ENTER,

        SDLK_LSHIFT,
        SDLK_LCTRL,
        SDLK_LALT,
        SDLK_LGUI,
        SDLK_RSHIFT,
        SDLK_RCTRL,
        SDLK_RALT,
        SDLK_RGUI,
        SDLK_APPLICATION
    };

    Silfur::VKey Silfur::SDLHelper::FromSDL(SDL_Keycode p_keycode)
    {
        switch(p_keycode)
        {
            case SDLK_a:            return VKey::A;
            case SDLK_b:            return VKey::B;
            case SDLK_c:            return VKey::C;
            case SDLK_d:            return VKey::D;
            case SDLK_e:            return VKey::E;
            case SDLK_f:            return VKey::F;
            case SDLK_g:            return VKey::G;
            case SDLK_h:            return VKey::H;
            case SDLK_i:            return VKey::I;
            case SDLK_j:            return VKey::J;
            case SDLK_k:            return VKey::K;
            case SDLK_l:            return VKey::L;
            case SDLK_m:            return VKey::M;
            case SDLK_n:            return VKey::N;
            case SDLK_o:            return VKey::O;
            case SDLK_p:            return VKey::P;
            case SDLK_q:            return VKey::Q;
            case SDLK_r:            return VKey::R;
            case SDLK_s:            return VKey::S;
            case SDLK_t:            return VKey::T;
            case SDLK_u:            return VKey::U;
            case SDLK_v:            return VKey::V;
            case SDLK_w:            return VKey::W;
            case SDLK_x:            return VKey::X;
            case SDLK_y:            return VKey::Y;
            case SDLK_z:            return VKey::Z;

            case SDLK_SPACE:        return VKey::Space;
            case SDLK_QUOTE:        return VKey::Apostrophe;
            case SDLK_COMMA:        return VKey::Comma;
            case SDLK_MINUS:        return VKey::Minus;
            case SDLK_PERIOD:       return VKey::Period;
            case SDLK_SLASH:        return VKey::Slash;

            case SDLK_0:            return VKey::D0;
            case SDLK_1:            return VKey::D1;
            case SDLK_2:            return VKey::D2;
            case SDLK_3:            return VKey::D3;
            case SDLK_4:            return VKey::D4;
            case SDLK_5:            return VKey::D5;
            case SDLK_6:            return VKey::D6;
            case SDLK_7:            return VKey::D7;
            case SDLK_8:            return VKey::D8;
            case SDLK_9:            return VKey::D9;

            case SDLK_SEMICOLON:    return VKey::Semicolon;
            case SDLK_EQUALS:       return VKey::Equal;
            case SDLK_LEFTBRACKET:  return VKey::LeftBracket;
            case SDLK_BACKSLASH:    return VKey::Backslash;
            case SDLK_RIGHTBRACKET: return VKey::RightBracket;
            case SDLK_BACKQUOTE:    return VKey::GraveAccent;

            case SDLK_ESCAPE:       return VKey::Escape;
            case SDLK_RETURN:       return VKey::Enter;
            case SDLK_TAB:          return VKey::Tab;
            case SDLK_BACKSPACE:    return VKey::Backspace;
            case SDLK_INSERT:       return VKey::Insert;
            case SDLK_DELETE:       return VKey::Delete;
            case SDLK_RIGHT:        return VKey::Right;
            case SDLK_LEFT:         return VKey::Left;
            case SDLK_DOWN:         return VKey::Down;
            case SDLK_UP:           return VKey::Up;
            case SDLK_PAGEUP:       return VKey::PageUp;
            case SDLK_PAGEDOWN:     return VKey::PageDown;
            case SDLK_HOME:         return VKey::Home;
            case SDLK_END:          return VKey::End;
            case SDLK_CAPSLOCK:     return VKey::CapsLock;
            case SDLK_SCROLLLOCK:   return VKey::ScrollLock;
            case SDLK_NUMLOCKCLEAR: return VKey::NumLock;
            case SDLK_PRINTSCREEN:  return VKey::PrintScreen;
            case SDLK_PAUSE:        return VKey::Pause;
            case SDLK_F1:           return VKey::F1;
            case SDLK_F2:           return VKey::F2;
            case SDLK_F3:           return VKey::F3;
            case SDLK_F4:           return VKey::F4;
            case SDLK_F5:           return VKey::F5;
            case SDLK_F6:           return VKey::F6;
            case SDLK_F7:           return VKey::F7;
            case SDLK_F8:           return VKey::F8;
            case SDLK_F9:           return VKey::F9;
            case SDLK_F10:          return VKey::F10;
            case SDLK_F11:          return VKey::F11;
            case SDLK_F12:          return VKey::F12;
            case SDLK_F13:          return VKey::F13;
            case SDLK_F14:          return VKey::F14;
            case SDLK_F15:          return VKey::F15;
            case SDLK_F16:          return VKey::F16;
            case SDLK_F17:          return VKey::F17;
            case SDLK_F18:          return VKey::F18;
            case SDLK_F19:          return VKey::F19;
            case SDLK_F20:          return VKey::F20;
            case SDLK_F21:          return VKey::F21;
            case SDLK_F22:          return VKey::F22;
            case SDLK_F23:          return VKey::F23;
            case SDLK_F24:          return VKey::F24;

            case SDLK_KP_0:         return VKey::KP0;
            case SDLK_KP_1:         return VKey::KP1;
            case SDLK_KP_2:         return VKey::KP2;
            case SDLK_KP_3:         return VKey::KP3;
            case SDLK_KP_4:         return VKey::KP4;
            case SDLK_KP_5:         return VKey::KP5;
            case SDLK_KP_6:         return VKey::KP6;
            case SDLK_KP_7:         return VKey::KP7;
            case SDLK_KP_8:         return VKey::KP8;
            case SDLK_KP_9:         return VKey::KP9;
            case SDLK_KP_DECIMAL:   return VKey::KPDecimal;
            case SDLK_KP_DIVIDE:    return VKey::KPDivide;
            case SDLK_KP_MULTIPLY:  return VKey::KPMultiply;
            case SDLK_KP_MINUS:     return VKey::KPSubtract;
            case SDLK_KP_PLUS:      return VKey::KPAdd;
            case SDLK_KP_ENTER:     return VKey::KPEnter;

            case SDLK_LSHIFT:       return VKey::LeftShift;
            case SDLK_LCTRL:        return VKey::LeftControl;
            case SDLK_LALT:         return VKey::LeftAlt;
            case SDLK_LGUI:         return VKey::LeftSuper;
            case SDLK_RSHIFT:       return VKey::RightShift;
            case SDLK_RCTRL:        return VKey::RightControl;
            case SDLK_RALT:         return VKey::RightAlt;
            case SDLK_RGUI:         return VKey::RightSuper;
            case SDLK_APPLICATION:  return VKey::Menu;

            default:                return VKey::Undefined;
        }
    }

    Silfur::ScanCode Silfur::SDLHelper::FromSDL(SDL_Scancode p_scancode)
    {
        switch(p_scancode)
        {
            case SDL_SCANCODE_A:            return ScanCode::A;
            case SDL_SCANCODE_B:            return ScanCode::B;
            case SDL_SCANCODE_C:            return ScanCode::C;
            case SDL_SCANCODE_D:            return ScanCode::D;
            case SDL_SCANCODE_E:            return ScanCode::E;
            case SDL_SCANCODE_F:            return ScanCode::F;
            case SDL_SCANCODE_G:            return ScanCode::G;
            case SDL_SCANCODE_H:            return ScanCode::H;
            case SDL_SCANCODE_I:            return ScanCode::I;
            case SDL_SCANCODE_J:            return ScanCode::J;
            case SDL_SCANCODE_K:            return ScanCode::K;
            case SDL_SCANCODE_L:            return ScanCode::L;
            case SDL_SCANCODE_M:            return ScanCode::M;
            case SDL_SCANCODE_N:            return ScanCode::N;
            case SDL_SCANCODE_O:            return ScanCode::O;
            case SDL_SCANCODE_P:            return ScanCode::P;
            case SDL_SCANCODE_Q:            return ScanCode::Q;
            case SDL_SCANCODE_R:            return ScanCode::R;
            case SDL_SCANCODE_S:            return ScanCode::S;
            case SDL_SCANCODE_T:            return ScanCode::T;
            case SDL_SCANCODE_U:            return ScanCode::U;
            case SDL_SCANCODE_V:            return ScanCode::V;
            case SDL_SCANCODE_W:            return ScanCode::W;
            case SDL_SCANCODE_X:            return ScanCode::X;
            case SDL_SCANCODE_Y:            return ScanCode::Y;
            case SDL_SCANCODE_Z:            return ScanCode::Z;

            case SDL_SCANCODE_SPACE:        return ScanCode::Space;
            case SDL_SCANCODE_APOSTROPHE:   return ScanCode::Apostrophe;
            case SDL_SCANCODE_COMMA:        return ScanCode::Comma;
            case SDL_SCANCODE_MINUS:        return ScanCode::Minus;
            case SDL_SCANCODE_PERIOD:       return ScanCode::Period;
            case SDL_SCANCODE_SLASH:        return ScanCode::Slash;

            case SDL_SCANCODE_0:            return ScanCode::D0;
            case SDL_SCANCODE_1:            return ScanCode::D1;
            case SDL_SCANCODE_2:            return ScanCode::D2;
            case SDL_SCANCODE_3:            return ScanCode::D3;
            case SDL_SCANCODE_4:            return ScanCode::D4;
            case SDL_SCANCODE_5:            return ScanCode::D5;
            case SDL_SCANCODE_6:            return ScanCode::D6;
            case SDL_SCANCODE_7:            return ScanCode::D7;
            case SDL_SCANCODE_8:            return ScanCode::D8;
            case SDL_SCANCODE_9:            return ScanCode::D9;

            case SDL_SCANCODE_SEMICOLON:    return ScanCode::Semicolon;
            case SDL_SCANCODE_EQUALS:       return ScanCode::Equal;
            case SDL_SCANCODE_LEFTBRACKET:  return ScanCode::LeftBracket;
            case SDL_SCANCODE_BACKSLASH:    return ScanCode::Backslash;
            case SDL_SCANCODE_RIGHTBRACKET: return ScanCode::RightBracket;
            case SDL_SCANCODE_GRAVE:        return ScanCode::GraveAccent;

            case SDL_SCANCODE_ESCAPE:       return ScanCode::Escape;
            case SDL_SCANCODE_RETURN:       return ScanCode::Enter;
            case SDL_SCANCODE_TAB:          return ScanCode::Tab;
            case SDL_SCANCODE_BACKSPACE:    return ScanCode::Backspace;
            case SDL_SCANCODE_INSERT:       return ScanCode::Insert;
            case SDL_SCANCODE_DELETE:       return ScanCode::Delete;
            case SDL_SCANCODE_RIGHT:        return ScanCode::Right;
            case SDL_SCANCODE_LEFT:         return ScanCode::Left;
            case SDL_SCANCODE_DOWN:         return ScanCode::Down;
            case SDL_SCANCODE_UP:           return ScanCode::Up;
            case SDL_SCANCODE_PAGEUP:       return ScanCode::PageUp;
            case SDL_SCANCODE_PAGEDOWN:     return ScanCode::PageDown;
            case SDL_SCANCODE_HOME:         return ScanCode::Home;
            case SDL_SCANCODE_END:          return ScanCode::End;
            case SDL_SCANCODE_CAPSLOCK:     return ScanCode::CapsLock;
            case SDL_SCANCODE_SCROLLLOCK:   return ScanCode::ScrollLock;
            case SDL_SCANCODE_NUMLOCKCLEAR: return ScanCode::NumLock;
            case SDL_SCANCODE_PRINTSCREEN:  return ScanCode::PrintScreen;
            case SDL_SCANCODE_PAUSE:        return ScanCode::Pause;
            case SDL_SCANCODE_F1:           return ScanCode::F1;
            case SDL_SCANCODE_F2:           return ScanCode::F2;
            case SDL_SCANCODE_F3:           return ScanCode::F3;
            case SDL_SCANCODE_F4:           return ScanCode::F4;
            case SDL_SCANCODE_F5:           return ScanCode::F5;
            case SDL_SCANCODE_F6:           return ScanCode::F6;
            case SDL_SCANCODE_F7:           return ScanCode::F7;
            case SDL_SCANCODE_F8:           return ScanCode::F8;
            case SDL_SCANCODE_F9:           return ScanCode::F9;
            case SDL_SCANCODE_F10:          return ScanCode::F10;
            case SDL_SCANCODE_F11:          return ScanCode::F11;
            case SDL_SCANCODE_F12:          return ScanCode::F12;
            case SDL_SCANCODE_F13:          return ScanCode::F13;
            case SDL_SCANCODE_F14:          return ScanCode::F14;
            case SDL_SCANCODE_F15:          return ScanCode::F15;
            case SDL_SCANCODE_F16:          return ScanCode::F16;
            case SDL_SCANCODE_F17:          return ScanCode::F17;
            case SDL_SCANCODE_F18:          return ScanCode::F18;
            case SDL_SCANCODE_F19:          return ScanCode::F19;
            case SDL_SCANCODE_F20:          return ScanCode::F20;
            case SDL_SCANCODE_F21:          return ScanCode::F21;
            case SDL_SCANCODE_F22:          return ScanCode::F22;
            case SDL_SCANCODE_F23:          return ScanCode::F23;
            case SDL_SCANCODE_F24:          return ScanCode::F24;

            case SDL_SCANCODE_KP_0:         return ScanCode::KP0;
            case SDL_SCANCODE_KP_1:         return ScanCode::KP1;
            case SDL_SCANCODE_KP_2:         return ScanCode::KP2;
            case SDL_SCANCODE_KP_3:         return ScanCode::KP3;
            case SDL_SCANCODE_KP_4:         return ScanCode::KP4;
            case SDL_SCANCODE_KP_5:         return ScanCode::KP5;
            case SDL_SCANCODE_KP_6:         return ScanCode::KP6;
            case SDL_SCANCODE_KP_7:         return ScanCode::KP7;
            case SDL_SCANCODE_KP_8:         return ScanCode::KP8;
            case SDL_SCANCODE_KP_9:         return ScanCode::KP9;
            case SDL_SCANCODE_KP_DECIMAL:   return ScanCode::KPDecimal;
            case SDL_SCANCODE_KP_DIVIDE:    return ScanCode::KPDivide;
            case SDL_SCANCODE_KP_MULTIPLY:  return ScanCode::KPMultiply;
            case SDL_SCANCODE_KP_MINUS:     return ScanCode::KPSubtract;
            case SDL_SCANCODE_KP_PLUS:      return ScanCode::KPAdd;
            case SDL_SCANCODE_KP_ENTER:     return ScanCode::KPEnter;

            case SDL_SCANCODE_LSHIFT:       return ScanCode::LeftShift;
            case SDL_SCANCODE_LCTRL:        return ScanCode::LeftControl;
            case SDL_SCANCODE_LALT:         return ScanCode::LeftAlt;
            case SDL_SCANCODE_LGUI:         return ScanCode::LeftSuper;
            case SDL_SCANCODE_RSHIFT:       return ScanCode::RightShift;
            case SDL_SCANCODE_RCTRL:        return ScanCode::RightControl;
            case SDL_SCANCODE_RALT:         return ScanCode::RightAlt;
            case SDL_SCANCODE_RGUI:         return ScanCode::RightSuper;
            case SDL_SCANCODE_APPLICATION:  return ScanCode::Menu;
            default:                        return ScanCode::Undefined;
        }
    }

    MouseButton SDLHelper::FromSDL(uint8_t p_sdlButton)
    {
        switch(p_sdlButton)
        {
            case SDL_BUTTON_LEFT:   return MouseButton::Left;
            case SDL_BUTTON_RIGHT:  return MouseButton::Right;
            case SDL_BUTTON_MIDDLE: return MouseButton::Middle;
            case SDL_BUTTON_X1:     return MouseButton::X1;
            case SDL_BUTTON_X2:     return MouseButton::X2;
            default:
                SF_CORE_INFO(Input, "Unknow mouse button.");
                return MouseButton::Left;
        }
    }

    SDL_Scancode SDLHelper::ToSDL(ScanCode p_scancode)
    {
        if (p_scancode == ScanCode::Undefined)
            return SDL_SCANCODE_UNKNOWN;

        return SfScanCodeToSDLScanCode[static_cast<std::size_t>(p_scancode)];
    }

    SDL_Keycode SDLHelper::ToSDL(VKey p_keycode)
    {
        if (p_keycode == VKey::Undefined)
            return SDLK_UNKNOWN;

        return SfKeycodeToSDLKeycode[static_cast<std::size_t >(p_keycode)];
    }
}
