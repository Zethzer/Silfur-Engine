#include "sfpch.hpp"
#include "Application.hpp"

#include "core/events/EventHandler.hpp"
#include "core/events/WindowEvent.hpp"

#include <chrono>

// See line 43
#if defined(SF_DEBUG) && defined(_WIN32)
    #include <winnls.h>
    #include <wincon.h>
#endif

namespace Silfur
{
    Application* Application::s_Instance = nullptr;

    Application::Application(int argc, char** argv) :
        m_AppName("Hello Silfur"),
        m_AppVersion({1, 0, 0})
    {
        Create(argc, argv);
    }

    Application::Application(int argc, char** argv, const std::string& appName, const Version& appVersion) :
        m_AppName(appName),
        m_AppVersion(appVersion)
    {
        Create(argc, argv);
    }

    Application::~Application()
    {
        m_Window.reset();
    }

    void Application::Create(int argc, char** argv)
    {
#if defined(SF_DEBUG) && defined(_WIN32)
        // Source : https://stackoverflow.com/questions/2492077/output-unicode-strings-in-windows-console-app
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif

        s_Instance = this;

        // TODO : Resolution from client app
        m_Window = CreateScope<Window>(VideoMode(800,600), m_AppName);

        SF_CORE_TRACE(Init, "Application {} created!", m_AppName);
    }

    void Application::Run()
    {
        OnInitialize();

        while (!m_Window->IsClosed)
        {
            m_Window->ProcessEvents();

            if (!m_Window->IsMinimized)
            {
                float time = (float)m_Window->GetTicks();
                float timestep = (time - m_LastFrameTime) / 1000.0f;
                m_LastFrameTime = time;

                /*
                 * TODO Conditional sleep if FPS are too high :
                 *    - Test with a limit of 1000 FPS
                 *  Or don't use mailbox presentation mode during
                 *  development and use FIFO instead
                 */

                OnUpdate(timestep);
            }
        }
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
