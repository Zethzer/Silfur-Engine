#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/Core.h"

#include "Window.h"

namespace Silfur
{
    class Application
    {
    public:
        Application();
        ~Application();

        void CreateRenderWindow(VideoMode p_mode, const wchar_t* p_title);
        bool Run();

        void* GetSystemWindowHandle();

    private:
        Scope<Window> m_Window;
    };
}

#endif // APPLICATION_H