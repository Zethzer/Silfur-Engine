#pragma once

#ifndef __SILFUR_CORE_WINDOW_VIDEO_MODE_HPP__
#define __SILFUR_CORE_WINDOW_VIDEO_MODE_HPP__

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

#endif // __SILFUR_CORE_WINDOW_VIDEO_MODE_HPP__
