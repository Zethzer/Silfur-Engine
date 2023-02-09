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
        Window(VideoMode mode, const std::string& title);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;

        void ProcessEvents();
        void Shutdown();
        u64 GetTicks();

        inline EventHandler& GetEventHandler() const { return *m_EventHandler; }

        inline operator SDL_Window*() const noexcept;
        inline SDL_Window* WindowHandle() const noexcept;
        void* WindowSystemHandle() const noexcept;

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
    private:
        void Create(VideoMode mode, const std::string& title);
        int static CAPICALL HandleEvent(void* userdata, SDL_Event* event);

        bool OnWindowClose(Event& event);
    public:
        bool IsClosed = false;

    private:
        SDL_Window* m_WinHandle {};
        Scope<EventHandler> m_EventHandler {};
    };
}

#include "Window.inl"
