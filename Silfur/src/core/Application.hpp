#pragma once

#ifndef __SILFUR_CORE_APPLICATION_HPP__
#define __SILFUR_CORE_APPLICATION_HPP__

#include "utility/log/Log.hpp"
#include "Base.hpp"
#include "window/Window.hpp"
#include "graphics/RendererVulkan.hpp"

// Because of spdlog in Log.hpp
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

        void CreateWindow(VideoMode p_mode, const char *p_title, bool p_isRenderWindow = true);
        bool Run();
        void Shutdown();

        static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }
        void* GetSystemWindowHandle();

    private:
        void Create();

    private:
        static Application* s_Instance;

        WindowPtr m_Window = nullptr;
        Scope<Renderer> m_Renderer = nullptr;
        std::string m_AppName {};
        Version m_AppVersion {};
    };
}

#endif // __SILFUR_CORE_APPLICATION_HPP__
