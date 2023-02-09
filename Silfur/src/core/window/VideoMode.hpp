#pragma once

#include "defines.hpp"

namespace Silfur
{
    class VideoMode
    {
    public:
        VideoMode();
        VideoMode(uint32_t width, uint32_t height);
        ~VideoMode() = default;

    public:
        uint32_t Width;
        uint32_t Height;
    };
}
