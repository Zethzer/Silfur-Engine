#include "sfpch.hpp"
#include "Window.hpp"

#include "utils/log/Log.hpp"
#include "core/events/WindowEvent.hpp"
#include "core/events/KeyEvent.hpp"
#include "core/events/MouseEvent.hpp"
#include "core/input/Helper.hpp"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_syswm.h>

namespace Silfur
{
    Window::Window(VideoMode mode, const std::string& title) :
        m_WinHandle(nullptr),
        IsClosed(false),
        IsMinimized(false)
    {
        SDL_SetMainReady();
        Create(mode, title);
        m_EventHandler = CreateScope<EventHandler>();
        m_EventHandler->AddListener<WindowCloseEvent>(SF_BIND_MEMBER_FN(OnWindowClose));
        m_EventHandler->AddListener<WindowResizedEvent>(SF_BIND_MEMBER_FN(OnWindowResized));
    }

    Window::~Window()
    {
        SDL_DelEventWatch(HandleEvent, this);
        SDL_DestroyWindow(m_WinHandle);
        SDL_Quit();
    }

    void Window::ProcessEvents()
    {
        SDL_PumpEvents();
        m_EventHandler->Dispatch();
    }

    void Window::Create(VideoMode mode, const std::string& title)
    {
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            SF_CORE_FATAL(Window_l, 10, "Failed to init SDL : {}", SDL_GetError());
        }

        m_WinHandle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   mode.Width,
                                   mode.Height,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
        if(!m_WinHandle)
        {
            SF_CORE_FATAL(Window_l, 11, "Failed to create the window: {}", SDL_GetError());
        }

        m_VideoMode = CreateScope<VideoMode>(mode);

        // Set handle callback for SDL
        SDL_AddEventWatch(HandleEvent, this);
    }

    void Window::Shutdown()
    {
        WindowCloseEvent event;
        m_EventHandler->PushEvent(CreateScope<WindowCloseEvent>(event));
    }

    uint64 Window::GetTicks()
    {
        return SDL_GetTicks64();
    }

    void* Window::WindowSystemHandle() const noexcept
    {
        SDL_SysWMinfo wMInfos;
        SDL_VERSION(&wMInfos.version);

        if (SDL_GetWindowWMInfo(m_WinHandle, &wMInfos) != SDL_TRUE)
        {
            SF_CORE_FATAL(Window_l, 12, "Failed to retrieve window manager informations: {}", SDL_GetError());
        }

        #ifdef _WIN32
            return wMInfos.info.win.window;
        #else
            /* Unknown compiler/platform */
            #error "Unknown platform!"
        #endif
    }

    int CAPICALL Window::HandleEvent(void* userdata, SDL_Event* SDLEvent)
    {
        auto window = static_cast<Window*>(userdata);

        switch(SDLEvent->type)
        {
            case SDL_WINDOWEVENT:
                switch(SDLEvent->window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE: {
                        WindowCloseEvent event;
                        window->m_EventHandler->PushEvent(CreateScope<WindowCloseEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_MOVED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.x = SDLEvent->window.data1;
                        windowEventInfo.y = SDLEvent->window.data2;

                        WindowMovedEvent event(windowEventInfo);
                        window->m_EventHandler->PushEvent(CreateScope<WindowMovedEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.width = SDLEvent->window.data1;
                        windowEventInfo.height = SDLEvent->window.data2;

                        WindowSizeChangedEvent event(windowEventInfo);
                        window->m_EventHandler->PushEvent(CreateScope<WindowSizeChangedEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_RESIZED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.width = SDLEvent->window.data1;
                        windowEventInfo.height = SDLEvent->window.data2;

                        WindowResizedEvent event(windowEventInfo);
                        window->m_EventHandler->PushEvent(CreateScope<WindowResizedEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_ENTER: {
                        WindowEnterEvent event;
                        window->m_EventHandler->PushEvent(CreateScope<WindowEnterEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_LEAVE: {
                        WindowLeaveEvent event;
                        window->m_EventHandler->PushEvent(CreateScope<WindowLeaveEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED: {
                        WindowFocusGainedEvent event;
                        window->m_EventHandler->PushEvent(CreateScope<WindowFocusGainedEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST: {
                        WindowFocusLostEvent event;
                        window->m_EventHandler->PushEvent(CreateScope<WindowFocusLostEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.width = SDLEvent->window.data1;
                        windowEventInfo.height = SDLEvent->window.data2;

                        WindowResizedEvent event(windowEventInfo);
                        window->m_EventHandler->PushEvent(CreateScope<WindowResizedEvent>(event));
                    }
                        break;
                    case SDL_WINDOWEVENT_RESTORED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.width = window->m_VideoMode->Width;
                        windowEventInfo.height = window->m_VideoMode->Height;

                        WindowResizedEvent event(windowEventInfo);
                        window->m_EventHandler->PushEvent(CreateScope<WindowResizedEvent>(event));
                    }
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYDOWN: {
                KeyInfo keyInfo;
                keyInfo.vKey = SDLHelper::FromSDL(SDLEvent->key.keysym.sym);
                keyInfo.scancode = SDLHelper::FromSDL(SDLEvent->key.keysym.scancode);
                keyInfo.repeated = SDLEvent->key.repeat != 0;
                keyInfo.alt = (SDLEvent->key.keysym.mod & KMOD_ALT) != 0;
                keyInfo.control = (SDLEvent->key.keysym.mod & KMOD_CTRL) != 0;
                keyInfo.shift = (SDLEvent->key.keysym.mod & KMOD_SHIFT) != 0;
                keyInfo.system = (SDLEvent->key.keysym.mod & KMOD_GUI) != 0;

                KeyPressedEvent event(keyInfo);
                window->m_EventHandler->PushEvent(CreateScope<KeyPressedEvent>(event));
            }
                break;
            case SDL_KEYUP: {
                KeyInfo keyInfo;
                keyInfo.vKey = SDLHelper::FromSDL(SDLEvent->key.keysym.sym);
                keyInfo.scancode = SDLHelper::FromSDL(SDLEvent->key.keysym.scancode);
                keyInfo.repeated = SDLEvent->key.repeat != 0;
                keyInfo.alt = (SDLEvent->key.keysym.mod & KMOD_ALT) != 0;
                keyInfo.control = (SDLEvent->key.keysym.mod & KMOD_CTRL) != 0;
                keyInfo.shift = (SDLEvent->key.keysym.mod & KMOD_SHIFT) != 0;
                keyInfo.system = (SDLEvent->key.keysym.mod & KMOD_GUI) != 0;

                KeyReleasedEvent event(keyInfo);
                window->m_EventHandler->PushEvent(CreateScope<KeyReleasedEvent>(event));
            }
                break;

            case SDL_MOUSEBUTTONDOWN: {
                MouseButtonDownInfo info;
                info.button = SDLHelper::FromSDL(SDLEvent->button.button);
                info.x = SDLEvent->button.x;
                info.y = SDLEvent->button.y;

                MouseButtonDownEvent event(info);
                window->m_EventHandler->PushEvent(CreateScope<MouseButtonDownEvent>(event));
            }
                break;
            case SDL_MOUSEBUTTONUP: {
                MouseButtonUpInfo info;
                info.button = SDLHelper::FromSDL(SDLEvent->button.button);
                info.x = SDLEvent->button.x;
                info.y = SDLEvent->button.y;

                MouseButtonUpEvent event(info);
                window->m_EventHandler->PushEvent(CreateScope<MouseButtonUpEvent>(event));
            }
                break;
            case SDL_MOUSEMOTION: {
                MouseMotionInfo info;
                info.x = SDLEvent->motion.x;
                info.y = SDLEvent->motion.y;
                info.xRelative = SDLEvent->motion.xrel;
                info.yRelative = SDLEvent->motion.yrel;

                MouseMotionEvent event(info);
                window->m_EventHandler->PushEvent(CreateScope<MouseMotionEvent>(event));
            }
                break;
            case SDL_MOUSEWHEEL: {
                MouseWheelInfo info;
                info.x = SDLEvent->wheel.x;
                info.y = SDLEvent->wheel.y;
                info.direction = SDLEvent->wheel.direction;

                MouseWheelEvent event(info);
                window->m_EventHandler->PushEvent(CreateScope<MouseWheelEvent>(event));
            }
                break;
            default:
                break;
        }

        return 0;
    }

    bool Window::OnWindowClose(Event& event)
    {
        IsClosed = true;
        return false;
    }

    bool Window::OnWindowResized(Event& event)
    {
        try
        {
            WindowResizedEvent* resizedEvent = dynamic_cast<WindowResizedEvent*>(&event);
            WindowEventInfo eventInfos = resizedEvent->GetInfos();

            if (eventInfos.width == 0 && eventInfos.height == 0)
            {
                IsMinimized = true;
                return false;
            }

            m_VideoMode->Width = eventInfos.width;
            m_VideoMode->Height = eventInfos.height;
            IsMinimized = false;

            return false;
        }
        catch (std::bad_cast b) {
            SF_CORE_ERROR(Window_l, 0, "Impossible to convert Event into WindowResizedEvent : {}", b.what());
            return true;
        }
    }
}
