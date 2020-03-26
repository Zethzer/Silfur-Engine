#include "sfpch.h"
#include "Window.h"

namespace Silfur
{
    Window::Window(VideoMode p_mode, const wchar_t* p_title) :
        HWnd(nullptr),
        IsClosed(true)
    {
        Create(p_mode, p_title);
    }

    void Window::ProcessEvents()
    {
    }

    void Window::Create(VideoMode p_mode, const wchar_t* p_title)
    {
    }

    void Window::Shutdown()
    {
        IsClosed = true;
    }
}
