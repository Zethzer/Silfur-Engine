#pragma once

#include <sstream>

#include "defines.hpp"

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
        p_os << static_cast<u32>(p_mouseCode);
        return p_os;
    }
}
