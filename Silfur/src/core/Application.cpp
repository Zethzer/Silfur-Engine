#include "sfpch.h"
#include "Application.h"

#include "utility/log/Log.h"

namespace Silfur
{
    Application::Application()
    {
        Log::Init();
    }

    Application::~Application()
    {
    }

    void Application::CreateRenderWindow(VideoMode p_mode, const wchar_t* p_title)
    {
        m_Window = CreateScope<Window>(p_mode, p_title);
    }

    bool Application::Run()
    {
        m_Window->ProcessEvents();

        if (m_Window->IsClosed)
        {
            return false;
        }

        return true;
    }

    void* Application::GetSystemWindowHandle()
    {
        return m_Window->WinHandle;
    }
}
