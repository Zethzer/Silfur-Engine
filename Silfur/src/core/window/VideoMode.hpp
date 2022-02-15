#pragma once

#include "defines.hpp"

namespace Silfur
{
    class VideoMode
    {
    public:
        VideoMode();
        VideoMode(uint32_t p_width, uint32_t p_height);
        ~VideoMode() = default;

    public:
        uint32_t Width;
        uint32_t Height;
    };
}
