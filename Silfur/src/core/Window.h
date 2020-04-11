#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "VideoMode.h"

struct GLFWwindow;

namespace Silfur
{
    class Window
    {
    public:
        Window() = delete;
        Window(VideoMode p_mode, const wchar_t* p_title);
        ~Window();

        void ProcessEvents();

    private:
        void Create(VideoMode p_mode, const wchar_t* p_title);
        void Shutdown();

    public:
        GLFWwindow* WinHandle {};
        bool IsClosed = false;
    };
}

#endif // WINDOW_H
