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

    inline std::ostream& operator<<(std::ostream& os, MouseButton mouseCode)
    {
        os << static_cast<uint32>(mouseCode);
        return os;
    }
}
