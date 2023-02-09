#include "sfpch.hpp"
#include "VideoMode.hpp"

namespace Silfur
{
    VideoMode::VideoMode() :
        Width(0),
        Height(0)
    {
    }

    VideoMode::VideoMode(uint32_t width, uint32_t height) :
        Width(width),
        Height(height)
    {
    }
}
