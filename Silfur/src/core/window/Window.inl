#pragma once

namespace Silfur
{
    inline SDL_Window* Window::WindowHandle() const noexcept
    {
        return m_WinHandle;
    }
}
