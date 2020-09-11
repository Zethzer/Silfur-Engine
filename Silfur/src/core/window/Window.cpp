#include "sfpch.hpp"
#include "Window.hpp"

#include "utility/log/Log.hpp"
#include "core/events/WindowEvent.hpp"
#include "core/events/KeyEvent.hpp"
#include "core/events/MouseEvent.hpp"
#include "core/input/Helper.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_syswm.h>
#include <imgui_impl_sdl.h>

namespace Silfur
{
    Window::Window(VideoMode p_mode, const char* p_title) :
        m_WinHandle(nullptr),
        IsClosed(false)
    {
        Create(p_mode, p_title);
        EventHandler::Get().AddSystemListener<WindowCloseEvent>(SF_BIND_MEMBER_FN(OnWindowClose));
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
        EventHandler::Get().Dispatch();
    }

    void Window::Create(VideoMode p_mode, const char* p_title)
    {
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            SF_CORE_FATAL(Window_l, 10, "Failed to init SDL : {}", SDL_GetError());
        }

        m_WinHandle = SDL_CreateWindow(p_title ,SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   p_mode.Width,
                                   p_mode.Height,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
        if(!m_WinHandle)
        {
            SF_CORE_FATAL(Window_l, 11, "Failed to create the window: {}", SDL_GetError());
        }

        // Set handle callback for SDL
        SDL_AddEventWatch(HandleEvent, this);
    }

    void Window::Shutdown()
    {
        WindowCloseEvent event;
        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowCloseEvent>(event), true);
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

    int CAPICALL Window::HandleEvent(void* p_userdata, SDL_Event* p_event)
    {
        ImGuiIO io = ImGui::GetIO();

        ImGui_ImplSDL2_ProcessEvent(p_event);

        switch(p_event->type)
        {
            case SDL_WINDOWEVENT:
                switch(p_event->window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE: {
                        WindowCloseEvent event;
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowCloseEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_MOVED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.x = p_event->window.data1;
                        windowEventInfo.y = p_event->window.data2;

                        WindowMovedEvent event(windowEventInfo);
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowMovedEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.width = p_event->window.data1;
                        windowEventInfo.height = p_event->window.data2;

                        WindowSizeChangedEvent event(windowEventInfo);
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowSizeChangedEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_RESIZED: {
                        WindowEventInfo windowEventInfo;
                        windowEventInfo.width = p_event->window.data1;
                        windowEventInfo.height = p_event->window.data2;

                        WindowResizedEvent event(windowEventInfo);
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowResizedEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_ENTER: {
                        WindowEnterEvent event;
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowEnterEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_LEAVE: {
                        WindowLeaveEvent event;
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowLeaveEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED: {
                        WindowFocusGainedEvent event;
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowFocusGainedEvent>(event), true);
                    }
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST: {
                        WindowFocusLostEvent event;
                        EventHandler::Get().PushSystemEvent(CreateUniqueRef<WindowFocusLostEvent>(event), true);
                    }
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYDOWN: {
                if (io.WantCaptureKeyboard)
                {
                    return 0;
                }

                KeyInfo keyInfo;
                keyInfo.vKey = SDLHelper::FromSDL(p_event->key.keysym.sym);
                keyInfo.scancode = SDLHelper::FromSDL(p_event->key.keysym.scancode);
                keyInfo.repeated = p_event->key.repeat != 0;
                keyInfo.alt = (p_event->key.keysym.mod & KMOD_ALT) != 0;
                keyInfo.control = (p_event->key.keysym.mod & KMOD_CTRL) != 0;
                keyInfo.shift = (p_event->key.keysym.mod & KMOD_SHIFT) != 0;
                keyInfo.system = (p_event->key.keysym.mod & KMOD_GUI) != 0;

                KeyPressedEvent event(keyInfo);
                EventHandler::Get().PushSystemEvent(CreateUniqueRef<KeyPressedEvent>(event), true);
            }
                break;
            case SDL_KEYUP: {
                if (io.WantCaptureKeyboard)
                {
                    return 0;
                }

                KeyInfo keyInfo;
                keyInfo.vKey = SDLHelper::FromSDL(p_event->key.keysym.sym);
                keyInfo.scancode = SDLHelper::FromSDL(p_event->key.keysym.scancode);
                keyInfo.repeated = p_event->key.repeat != 0;
                keyInfo.alt = (p_event->key.keysym.mod & KMOD_ALT) != 0;
                keyInfo.control = (p_event->key.keysym.mod & KMOD_CTRL) != 0;
                keyInfo.shift = (p_event->key.keysym.mod & KMOD_SHIFT) != 0;
                keyInfo.system = (p_event->key.keysym.mod & KMOD_GUI) != 0;

                KeyReleasedEvent event(keyInfo);
                EventHandler::Get().PushSystemEvent(CreateUniqueRef<KeyReleasedEvent>(event), true);
            }
                break;

            case SDL_MOUSEBUTTONDOWN: {
                if (io.WantCaptureMouse)
                {
                    return 0;
                }

                MouseButtonDownInfo info;
                info.button = SDLHelper::FromSDL(p_event->button.button);
                info.x = p_event->button.x;
                info.y = p_event->button.y;

                MouseButtonDownEvent event(info);
                EventHandler::Get().PushSystemEvent(CreateUniqueRef<MouseButtonDownEvent>(event), true);
            }
                break;
            case SDL_MOUSEBUTTONUP: {
                if (io.WantCaptureMouse)
                {
                    return 0;
                }

                MouseButtonUpInfo info;
                info.button = SDLHelper::FromSDL(p_event->button.button);
                info.x = p_event->button.x;
                info.y = p_event->button.y;

                MouseButtonUpEvent event(info);
                EventHandler::Get().PushSystemEvent(CreateUniqueRef<MouseButtonUpEvent>(event), true);
            }
                break;
            case SDL_MOUSEMOTION: {
                if (io.WantCaptureMouse)
                {
                    return 0;
                }

                MouseMotionInfo info;
                info.x = p_event->motion.x;
                info.y = p_event->motion.y;
                info.xRelative = p_event->motion.xrel;
                info.yRelative = p_event->motion.yrel;

                MouseMotionEvent event(info);
                EventHandler::Get().PushSystemEvent(CreateUniqueRef<MouseMotionEvent>(event), true);
            }
                break;
            case SDL_MOUSEWHEEL: {
                if (io.WantCaptureMouse)
                {
                    return 0;
                }

                MouseWheelInfo info;
                info.x = p_event->wheel.x;
                info.y = p_event->wheel.y;
                info.direction = p_event->wheel.direction;

                MouseWheelEvent event(info);
                EventHandler::Get().PushSystemEvent(CreateUniqueRef<MouseWheelEvent>(event), true);
            }
                break;
            default:
                break;
        }

        return 0;
    }

    void Window::OnWindowClose(SystemEvent &p_event)
    {
        IsClosed = true;
    }
}
