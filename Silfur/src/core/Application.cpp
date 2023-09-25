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

    Application::Application(ApplicationProperties properties) :
        m_Properties(properties)
    {
        Create(properties);
    }

    Application::~Application()
    {
        m_Renderer.reset();
        m_Window.reset();
    }

    void Application::Create(ApplicationProperties properties)
    {
#if defined(SF_DEBUG) && defined(_WIN32)
        // Source : https://stackoverflow.com/questions/2492077/output-unicode-strings-in-windows-console-app
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif

        s_Instance = this;

        m_Window = CreateScope<Window>(VideoMode(properties.Width,properties.Height), properties.Name);

        SF_CORE_TRACE(Init, "Application {} created!", properties.Name);

        RendererProperties rendererProps;
        rendererProps.Window = m_Window->WindowHandle();
        rendererProps.ApplicationName = properties.Name;
        rendererProps.ApplicationVersion = properties.Version;

        m_Renderer = CreateScope<RendererVk>(rendererProps);
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
