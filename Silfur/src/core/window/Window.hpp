#pragma once

#include "defines.hpp"
#include "VideoMode.hpp"
#include "core/events/EventHandler.hpp"

struct SDL_Window;
union SDL_Event;

namespace Silfur
{
    class Event;
    class Window;

    class Window
    {
    public:
        Window() = delete;
        Window(VideoMode p_mode, const std::string& p_title);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;

        void ProcessEvents();
        void Shutdown();

        inline EventHandler& GetEventHandler() const { return *m_EventHandler; }

        inline operator SDL_Window*() const noexcept;
        inline SDL_Window* WindowHandle() const noexcept;
        void* WindowSystemHandle() const noexcept;

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
    private:
        void Create(VideoMode p_mode, const std::string& p_title);
        int static CAPICALL HandleEvent(void* p_userdata, SDL_Event* p_event);

        void OnWindowClose(Event& p_event);
    public:
        bool IsClosed = false;

    private:
        SDL_Window* m_WinHandle {};
        Scope<EventHandler> m_EventHandler {};
    };
}

#include "Window.inl"
