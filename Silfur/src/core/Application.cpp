#include "sfpch.hpp"
#include "Application.hpp"

#include "events/EventManager.hpp"

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
#if defined(SF_DEBUG) && defined(_WIN32)
        // Source : https://stackoverflow.com/questions/2492077/output-unicode-strings-in-windows-console-app
        // These functions are defined in Windows.h include with spdlog.h in Log.hpp
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
        Log::Init();
        EventManager::Init();

        // TEST
        EventManager::AddListener<KeyTypedEvent>(SF_BIND_FN(Application::PrintMessage));
    }

    void Application::CreateWindow(VideoMode p_mode, const char *p_title, bool p_isRenderWindow)
    {
        m_Window = CreateScope<Window>(p_mode, p_title);

        /*
         * TODO This is the main renderer which is create for the moment. Refactor this code
         *  for just create useful things for a render window
         */
        if (p_isRenderWindow)
        {
            m_Renderer = CreateScope<Renderer>(*m_Window, m_AppName, m_AppVersion);
        }
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

        m_Renderer->drawFrame();

        return !m_Window->IsClosed;
    }

    void* Application::GetSystemWindowHandle()
    {
        return m_Window->WindowSystemHandle();
    }

    void Application::PrintMessage(const Scope<Event>& p_event)
    {
        SF_CORE_DEBUG(Temp, "Event name: {} | {}", p_event->GetName(), p_event->ToString());
    }
}
