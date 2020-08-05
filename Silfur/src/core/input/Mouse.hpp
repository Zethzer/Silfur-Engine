#pragma once

#ifndef __SILFUR_CORE_MOUSE_CODES_HPP__
#define __SILFUR_CORE_MOUSE_CODES_HPP__

#include <sstream>

namespace Silfur
{
    enum class MouseButton
    {
        Left = 0,
        Right,
        Middle,
        X1,
        X2,

        Max = X2
    };

    inline std::ostream& operator<<(std::ostream& p_os, MouseButton p_mouseCode)
    {
        p_os << static_cast<int32_t>(p_mouseCode);
        return p_os;
    }
}

#endif // __SILFUR_CORE_MOUSE_CODES_HPP__
