#include "sfpch.h"
#include "Application.h"

namespace Silfur
{
    Application::Application()
    {
        Log::Init();
    }

    Application::~Application()
    {
        m_Renderer.reset();
        m_Window.reset();
    }

    void Application::CreateRenderWindow(VideoMode p_mode, const wchar_t* p_title)
    {
        m_Window = CreateScope<Window>(p_mode, p_title);
        m_Renderer = CreateScope<Renderer>(*m_Window);
    }

    bool Application::Run()
    {
        /*
         * #TODO (Zeth) : Conditional sleep if FPS are too high :
         *    - Test with a limit of 1000 FPS
         * Or don't use mailbox presentation mode during
         * development and use FIFO instead
         */
        m_Window->ProcessEvents();

        m_Renderer->drawFrame();

        if (m_Window->IsClosed)
        {
            return false;
        }

        return true;
    }

    void* Application::GetSystemWindowHandle()
    {
        return nullptr;
    }
}
