#pragma once

#ifndef __SILFUR_CORE_MOUSE_CODES_HPP__
#define __SILFUR_CORE_MOUSE_CODES_HPP__

#include <sstream>

namespace Silfur
{
    typedef enum class MouseCode : uint16_t
    {
        // From glfw3.h
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    } Mouse;

    inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
    {
        os << static_cast<int32_t>(mouseCode);
        return os;
    }
}

#define SF_MOUSE_BUTTON_0      ::Silfur::Mouse::Button0
#define SF_MOUSE_BUTTON_1      ::Silfur::Mouse::Button1
#define SF_MOUSE_BUTTON_2      ::Silfur::Mouse::Button2
#define SF_MOUSE_BUTTON_3      ::Silfur::Mouse::Button3
#define SF_MOUSE_BUTTON_4      ::Silfur::Mouse::Button4
#define SF_MOUSE_BUTTON_5      ::Silfur::Mouse::Button5
#define SF_MOUSE_BUTTON_6      ::Silfur::Mouse::Button6
#define SF_MOUSE_BUTTON_7      ::Silfur::Mouse::Button7
#define SF_MOUSE_BUTTON_LAST   ::Silfur::Mouse::ButtonLast
#define SF_MOUSE_BUTTON_LEFT   ::Silfur::Mouse::ButtonLeft
#define SF_MOUSE_BUTTON_RIGHT  ::Silfur::Mouse::ButtonRight
#define SF_MOUSE_BUTTON_MIDDLE ::Silfur::Mouse::ButtonMiddle

#endif // __SILFUR_CORE_MOUSE_CODES_HPP__
