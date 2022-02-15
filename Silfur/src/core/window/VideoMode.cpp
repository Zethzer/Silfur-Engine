#include "sfpch.hpp"
#include "VideoMode.hpp"

namespace Silfur
{
    VideoMode::VideoMode() :
        Width(0),
        Height(0)
    {
    }

    VideoMode::VideoMode(uint32_t p_width, uint32_t p_height) :
        Width(p_width),
        Height(p_height)
    {
    }
}
