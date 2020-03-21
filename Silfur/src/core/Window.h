#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "VideoMode.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#if defined(CreateWindow)
    #undef CreateWindow
#endif

namespace Silfur
{
    class Window
    {
    public:
        Window() = delete;
        Window(VideoMode p_mode, const wchar_t* p_title);
        ~Window() = default;

        void ProcessEvents();

    protected:
        static LRESULT CALLBACK HandleMessages(HWND p_hWnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);

    private:
        void Create(VideoMode p_mode, const wchar_t* p_title);
        void Shutdown();

    public:
        HWND HWnd;
        bool IsClosed;
    };
}

#endif // WINDOW_H
