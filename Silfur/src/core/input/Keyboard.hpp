#pragma once

#include <sstream>

#include "defines.hpp"

namespace Silfur
{
    enum class VKey
    {
        Undefined = -1,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Space,
        Apostrophe, /* ' */
        Comma,      /* , */
        Minus,      /* - */
        Period,     /* . */
        Slash,      /* / */

        D0, /* 0 */
        D1, /* 1 */
        D2, /* 2 */
        D3, /* 3 */
        D4, /* 4 */
        D5, /* 5 */
        D6, /* 6 */
        D7, /* 7 */
        D8, /* 8 */
        D9, /* 9 */

        Semicolon,      /* ; */
        Equal,          /* = */
        LeftBracket,    /* [ */
        Backslash,      /* \ */
        RightBracket,   /* ] */
        GraveAccent,   /* ` */

        /* Function keys */
                Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        /* Keypad */
                KP0,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,

        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,

        Max = Menu
    };

    enum class ScanCode
    {
        Undefined = -1,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Space,
        Apostrophe, /* ' */
        Comma,      /* , */
        Minus,      /* - */
        Period,     /* . */
        Slash,      /* / */

        D0, /* 0 */
        D1, /* 1 */
        D2, /* 2 */
        D3, /* 3 */
        D4, /* 4 */
        D5, /* 5 */
        D6, /* 6 */
        D7, /* 7 */
        D8, /* 8 */
        D9, /* 9 */

        Semicolon,      /* ; */
        Equal,          /* = */
        LeftBracket,    /* [ */
        Backslash,      /* \ */
        RightBracket,   /* ] */
        GraveAccent,   /* ` */

        /* Function keys */
                Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        /* Keypad */
                KP0,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,

        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,

        Max = Menu
    };

    inline std::ostream& operator<<(std::ostream& p_os, VKey p_keyCode)
    {
        p_os << static_cast<u32>(p_keyCode);
        return p_os;
    }

    inline std::ostream& operator<<(std::ostream& p_os, ScanCode p_scanCode)
    {
        p_os << static_cast<u32>(p_scanCode);
        return p_os;
    }
}
