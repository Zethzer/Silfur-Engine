#include "sfpch.hpp"
#include "Window.hpp"

#ifdef SF_WINDOWS
    #include "platform/win32/Win32_Window.hpp"
#endif

namespace Silfur
{
    std::unique_ptr<Window> Window::Create(const std::string& p_title, int p_width, int p_height)
    {
#ifdef SF_WINDOWS
        return std::make_unique<Win32_Window>(p_title, p_width, p_height);
#endif
    }
}
