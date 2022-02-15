#include "sfpch.hpp"
#include "Application.hpp"

#include "core/events/EventHandler.hpp"

// See line 43
#if defined(SF_DEBUG) && defined(_WIN32)
    #include <winnls.h>
    #include <wincon.h>
#endif

namespace Silfur
{
    Application* Application::s_Instance = nullptr;

    Application::Application() :
        m_AppName("Hello Silfur"),
        m_AppVersion({1, 0, 0})
    {
        Create();
    }

    Application::Application(std::string p_appName, const Version& p_appVersion) :
        m_AppName(std::move(p_appName)),
        m_AppVersion(p_appVersion)
    {
        Create();
    }

    Application::~Application()
    {
        m_Window.reset();
    }

    void Application::Create()
    {
#if defined(SF_DEBUG) && defined(_WIN32)
        // Source : https://stackoverflow.com/questions/2492077/output-unicode-strings-in-windows-console-app
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
        Log::Init();
        s_Instance = this;
    }

    Window& Application::CreateWindow(VideoMode p_mode, const std::string& p_title, bool p_isRenderWindow)
    {
        m_Window = CreateScope<Window>(p_mode, p_title);

        return *m_Window;
    }

    bool Application::Run()
    {
        /*
         * TODO Conditional sleep if FPS are too high :
         *    - Test with a limit of 1000 FPS
         *  Or don't use mailbox presentation mode during
         *  development and use FIFO instead
         */
        m_Window->ProcessEvents();

        return !m_Window->IsClosed;
    }

    void Application::Shutdown()
    {
        m_Window->Shutdown();
    }

    void* Application::GetSystemWindowHandle()
    {
        return m_Window->WindowSystemHandle();
    }
}
