#pragma once

#ifndef __SILFUR_CORE_KEY_CODES_HPP__
#define __SILFUR_CORE_KEY_CODES_HPP__

#include <sstream>

namespace Silfur
{
    // According to the documentation of GLFW, this is US layout keyboard
    typedef enum class KeyCode : uint16_t
    {
        // From glfw3.h
        Space               = 32,
        Apostrophe          = 39, /* ' */
        Comma               = 44, /* , */
        Minus               = 45, /* - */
        Period              = 46, /* . */
        Slash               = 47, /* / */

        D0                  = 48, /* 0 */
        D1                  = 49, /* 1 */
        D2                  = 50, /* 2 */
        D3                  = 51, /* 3 */
        D4                  = 52, /* 4 */
        D5                  = 53, /* 5 */
        D6                  = 54, /* 6 */
        D7                  = 55, /* 7 */
        D8                  = 56, /* 8 */
        D9                  = 57, /* 9 */

        Semicolon           = 59, /* ; */
        Equal               = 61, /* = */

        A                   = 65,
        B                   = 66,
        C                   = 67,
        D                   = 68,
        E                   = 69,
        F                   = 70,
        G                   = 71,
        H                   = 72,
        I                   = 73,
        J                   = 74,
        K                   = 75,
        L                   = 76,
        M                   = 77,
        N                   = 78,
        O                   = 79,
        P                   = 80,
        Q                   = 81,
        R                   = 82,
        S                   = 83,
        T                   = 84,
        U                   = 85,
        V                   = 86,
        W                   = 87,
        X                   = 88,
        Y                   = 89,
        Z                   = 90,

        LeftBracket         = 91,  /* [ */
        Backslash           = 92,  /* \ */
        RightBracket        = 93,  /* ] */
        GraveAccent         = 96,  /* ` */

        World1              = 161, /* non-US #1 */
        World2              = 162, /* non-US #2 */

        /* Function keys */
        Escape              = 256,
        Enter               = 257,
        Tab                 = 258,
        Backspace           = 259,
        Insert              = 260,
        Delete              = 261,
        Right               = 262,
        Left                = 263,
        Down                = 264,
        Up                  = 265,
        PageUp              = 266,
        PageDown            = 267,
        Home                = 268,
        End                 = 269,
        CapsLock            = 280,
        ScrollLock          = 281,
        NumLock             = 282,
        PrintScreen         = 283,
        Pause               = 284,
        F1                  = 290,
        F2                  = 291,
        F3                  = 292,
        F4                  = 293,
        F5                  = 294,
        F6                  = 295,
        F7                  = 296,
        F8                  = 297,
        F9                  = 298,
        F10                 = 299,
        F11                 = 300,
        F12                 = 301,
        F13                 = 302,
        F14                 = 303,
        F15                 = 304,
        F16                 = 305,
        F17                 = 306,
        F18                 = 307,
        F19                 = 308,
        F20                 = 309,
        F21                 = 310,
        F22                 = 311,
        F23                 = 312,
        F24                 = 313,
        F25                 = 314,

        /* Keypad */
        KP0                 = 320,
        KP1                 = 321,
        KP2                 = 322,
        KP3                 = 323,
        KP4                 = 324,
        KP5                 = 325,
        KP6                 = 326,
        KP7                 = 327,
        KP8                 = 328,
        KP9                 = 329,
        KPDecimal           = 330,
        KPDivide            = 331,
        KPMultiply          = 332,
        KPSubtract          = 333,
        KPAdd               = 334,
        KPEnter             = 335,
        KPEqual             = 336,

        LeftShift           = 340,
        LeftControl         = 341,
        LeftAlt             = 342,
        LeftSuper           = 343,
        RightShift          = 344,
        RightControl        = 345,
        RightAlt            = 346,
        RightSuper          = 347,
        Menu                = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
}

// From glfw3.h
#define SF_KEY_SPACE           ::Silfur::Key::Space
#define SF_KEY_APOSTROPHE      ::Silfur::Key::Apostrophe    /* ' */
#define SF_KEY_COMMA           ::Silfur::Key::Comma         /* , */
#define SF_KEY_MINUS           ::Silfur::Key::Minus         /* - */
#define SF_KEY_PERIOD          ::Silfur::Key::Period        /* . */
#define SF_KEY_SLASH           ::Silfur::Key::Slash         /* / */
#define SF_KEY_0               ::Silfur::Key::D0
#define SF_KEY_1               ::Silfur::Key::D1
#define SF_KEY_2               ::Silfur::Key::D2
#define SF_KEY_3               ::Silfur::Key::D3
#define SF_KEY_4               ::Silfur::Key::D4
#define SF_KEY_5               ::Silfur::Key::D5
#define SF_KEY_6               ::Silfur::Key::D6
#define SF_KEY_7               ::Silfur::Key::D7
#define SF_KEY_8               ::Silfur::Key::D8
#define SF_KEY_9               ::Silfur::Key::D9
#define SF_KEY_SEMICOLON       ::Silfur::Key::Semicolon     /* ; */
#define SF_KEY_EQUAL           ::Silfur::Key::Equal         /* = */
#define SF_KEY_A               ::Silfur::Key::A
#define SF_KEY_B               ::Silfur::Key::B
#define SF_KEY_C               ::Silfur::Key::C
#define SF_KEY_D               ::Silfur::Key::D
#define SF_KEY_E               ::Silfur::Key::E
#define SF_KEY_F               ::Silfur::Key::F
#define SF_KEY_G               ::Silfur::Key::G
#define SF_KEY_H               ::Silfur::Key::H
#define SF_KEY_I               ::Silfur::Key::I
#define SF_KEY_J               ::Silfur::Key::J
#define SF_KEY_K               ::Silfur::Key::K
#define SF_KEY_L               ::Silfur::Key::L
#define SF_KEY_M               ::Silfur::Key::M
#define SF_KEY_N               ::Silfur::Key::N
#define SF_KEY_O               ::Silfur::Key::O
#define SF_KEY_P               ::Silfur::Key::P
#define SF_KEY_Q               ::Silfur::Key::Q
#define SF_KEY_R               ::Silfur::Key::R
#define SF_KEY_S               ::Silfur::Key::S
#define SF_KEY_T               ::Silfur::Key::T
#define SF_KEY_U               ::Silfur::Key::U
#define SF_KEY_V               ::Silfur::Key::V
#define SF_KEY_W               ::Silfur::Key::W
#define SF_KEY_X               ::Silfur::Key::X
#define SF_KEY_Y               ::Silfur::Key::Y
#define SF_KEY_Z               ::Silfur::Key::Z
#define SF_KEY_LEFT_BRACKET    ::Silfur::Key::LeftBracket   /* [ */
#define SF_KEY_BACKSLASH       ::Silfur::Key::Backslash     /* \ */
#define SF_KEY_RIGHT_BRACKET   ::Silfur::Key::RightBracket  /* ] */
#define SF_KEY_GRAVE_ACCENT    ::Silfur::Key::GraveAccent   /* ` */
#define SF_KEY_WORLD_1         ::Silfur::Key::World1        /* non-US #1 */
#define SF_KEY_WORLD_2         ::Silfur::Key::World2        /* non-US #2 */

/* Function keys */
#define SF_KEY_ESCAPE          ::Silfur::Key::Escape
#define SF_KEY_ENTER           ::Silfur::Key::Enter
#define SF_KEY_TAB             ::Silfur::Key::Tab
#define SF_KEY_BACKSPACE       ::Silfur::Key::Backspace
#define SF_KEY_INSERT          ::Silfur::Key::Insert
#define SF_KEY_DELETE          ::Silfur::Key::Delete
#define SF_KEY_RIGHT           ::Silfur::Key::Right
#define SF_KEY_LEFT            ::Silfur::Key::Left
#define SF_KEY_DOWN            ::Silfur::Key::Down
#define SF_KEY_UP              ::Silfur::Key::Up
#define SF_KEY_PAGE_UP         ::Silfur::Key::PageUp
#define SF_KEY_PAGE_DOWN       ::Silfur::Key::PageDown
#define SF_KEY_HOME            ::Silfur::Key::Home
#define SF_KEY_END             ::Silfur::Key::End
#define SF_KEY_CAPS_LOCK       ::Silfur::Key::CapsLock
#define SF_KEY_SCROLL_LOCK     ::Silfur::Key::ScrollLock
#define SF_KEY_NUM_LOCK        ::Silfur::Key::NumLock
#define SF_KEY_PRINT_SCREEN    ::Silfur::Key::PrintScreen
#define SF_KEY_PAUSE           ::Silfur::Key::Pause
#define SF_KEY_F1              ::Silfur::Key::F1
#define SF_KEY_F2              ::Silfur::Key::F2
#define SF_KEY_F3              ::Silfur::Key::F3
#define SF_KEY_F4              ::Silfur::Key::F4
#define SF_KEY_F5              ::Silfur::Key::F5
#define SF_KEY_F6              ::Silfur::Key::F6
#define SF_KEY_F7              ::Silfur::Key::F7
#define SF_KEY_F8              ::Silfur::Key::F8
#define SF_KEY_F9              ::Silfur::Key::F9
#define SF_KEY_F10             ::Silfur::Key::F10
#define SF_KEY_F11             ::Silfur::Key::F11
#define SF_KEY_F12             ::Silfur::Key::F12
#define SF_KEY_F13             ::Silfur::Key::F13
#define SF_KEY_F14             ::Silfur::Key::F14
#define SF_KEY_F15             ::Silfur::Key::F15
#define SF_KEY_F16             ::Silfur::Key::F16
#define SF_KEY_F17             ::Silfur::Key::F17
#define SF_KEY_F18             ::Silfur::Key::F18
#define SF_KEY_F19             ::Silfur::Key::F19
#define SF_KEY_F20             ::Silfur::Key::F20
#define SF_KEY_F21             ::Silfur::Key::F21
#define SF_KEY_F22             ::Silfur::Key::F22
#define SF_KEY_F23             ::Silfur::Key::F23
#define SF_KEY_F24             ::Silfur::Key::F24
#define SF_KEY_F25             ::Silfur::Key::F25

/* Keypad */
#define SF_KEY_KP_0            ::Silfur::Key::KP0
#define SF_KEY_KP_1            ::Silfur::Key::KP1
#define SF_KEY_KP_2            ::Silfur::Key::KP2
#define SF_KEY_KP_3            ::Silfur::Key::KP3
#define SF_KEY_KP_4            ::Silfur::Key::KP4
#define SF_KEY_KP_5            ::Silfur::Key::KP5
#define SF_KEY_KP_6            ::Silfur::Key::KP6
#define SF_KEY_KP_7            ::Silfur::Key::KP7
#define SF_KEY_KP_8            ::Silfur::Key::KP8
#define SF_KEY_KP_9            ::Silfur::Key::KP9
#define SF_KEY_KP_DECIMAL      ::Silfur::Key::KPDecimal
#define SF_KEY_KP_DIVIDE       ::Silfur::Key::KPDivide
#define SF_KEY_KP_MULTIPLY     ::Silfur::Key::KPMultiply
#define SF_KEY_KP_SUBTRACT     ::Silfur::Key::KPSubtract
#define SF_KEY_KP_ADD          ::Silfur::Key::KPAdd
#define SF_KEY_KP_ENTER        ::Silfur::Key::KPEnter
#define SF_KEY_KP_EQUAL        ::Silfur::Key::KPEqual

#define SF_KEY_LEFT_SHIFT      ::Silfur::Key::LeftShift
#define SF_KEY_LEFT_CONTROL    ::Silfur::Key::LeftControl
#define SF_KEY_LEFT_ALT        ::Silfur::Key::LeftAlt
#define SF_KEY_LEFT_SUPER      ::Silfur::Key::LeftSuper
#define SF_KEY_RIGHT_SHIFT     ::Silfur::Key::RightShift
#define SF_KEY_RIGHT_CONTROL   ::Silfur::Key::RightControl
#define SF_KEY_RIGHT_ALT       ::Silfur::Key::RightAlt
#define SF_KEY_RIGHT_SUPER     ::Silfur::Key::RightSuper
#define SF_KEY_MENU            ::Silfur::Key::Menu

#endif // __SILFUR_CORE_KEY_CODES_HPP__
