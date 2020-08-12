#pragma once

#ifndef __SILFUR_CORE_APPLICATION_HPP__
#define __SILFUR_CORE_APPLICATION_HPP__

#include "Base.hpp"
#include "utility/log/Log.hpp"
#include "window/Window.hpp"
#include "graphics/RendererVulkan.hpp"

// Because of <spdlog/logger.h> in Log.hpp
#ifdef CreateWindow
    #undef CreateWindow
#endif

namespace Silfur
{
    class Event;

    class Application
    {
    public:
        Application();
        Application(std::string p_appName, const Version& p_appVersion);
        ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;

        Window& CreateWindow(VideoMode p_mode, const char *p_title, bool p_isRenderWindow = true);
        bool Run();
        void Shutdown();

        static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }
        void* GetSystemWindowHandle();

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;
    private:
        void Create();

    private:
        static Application* s_Instance;

        Scope<Window> m_Window = nullptr;
        Scope<Renderer> m_Renderer = nullptr;
        std::string m_AppName {};
        Version m_AppVersion {};
    };
}

#endif // __SILFUR_CORE_APPLICATION_HPP__
