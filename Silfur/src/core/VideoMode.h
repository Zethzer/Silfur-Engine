#pragma once

#ifndef VIDEO_MODE_H
#define VIDEO_MODE_H

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

#endif // VIDEO_MODE_H
