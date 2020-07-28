#pragma once

#ifndef __SILFUR_CORE_WINDOW_WINDOW_INL__
#define __SILFUR_CORE_WINDOW_WINDOW_INL__

namespace Silfur
{
    inline SDL_Window* Window::WindowHandle() const noexcept
    {
        return m_WinHandle;
    }

    inline Window::operator SDL_Window*() const noexcept
    {
        return m_WinHandle;
    }
}

#endif // __SILFUR_CORE_WINDOW_WINDOW_INL__
