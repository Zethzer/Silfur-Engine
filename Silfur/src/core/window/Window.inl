#pragma once

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
