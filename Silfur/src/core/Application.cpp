#include "sfpch.hpp"
#include "Application.hpp"

namespace Silfur
{
    Application::Application() :
        m_AppName("Hello Silfur"),
        m_AppVersion({1, 0, 0})
    {
        Create();
    }

    Application::Application(std::string p_appName, Version p_appVersion) :
        m_AppName(std::move(p_appName)),
        m_AppVersion(std::move(p_appVersion))
    {
        Create();
    }

    Application::~Application()
    {
        m_Renderer.reset();
        m_Window.reset();
    }

    void Application::Create()
    {
        Log::Init();
    }

    void Application::CreateRenderWindow(VideoMode p_mode, const char* p_title)
    {
        m_Window = CreateScope<Window>(p_mode, p_title);
        m_Renderer = CreateScope<Renderer>(*m_Window, m_AppName, m_AppVersion);
    }

    bool Application::Run()
    {
        /*
         * #TODO-Zeth : Conditional sleep if FPS are too high :
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
