#pragma once

#ifndef __SILFUR_CORE_APPLICATION_HPP__
#define __SILFUR_CORE_APPLICATION_HPP__

#include "utility/log/Log.hpp"
#include "core/Core.hpp"
#include "core/Window.hpp"
#include "graphics/RendererVulkan.hpp"

namespace Silfur
{
    class Application
    {
    public:
        Application();
        ~Application();

        void CreateRenderWindow(VideoMode p_mode, const char* p_title);
        bool Run();

        void* GetSystemWindowHandle();

    private:
        WindowPtr m_Window = nullptr;
        Scope<Renderer> m_Renderer = nullptr;
    };
}

#endif // __SILFUR_CORE_APPLICATION_HPP__
