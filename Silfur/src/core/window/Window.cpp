#include "sfpch.hpp"
#include "Window.hpp"

#include "utility/log/Log.hpp"
#include "core/events/EventManager.hpp"
#include "core/events/KeyEvent.hpp"
#include "core/input/Helper.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

namespace Silfur
{
    Window::Window(VideoMode p_mode, const char* p_title) :
        m_WinHandle(nullptr),
        IsClosed(false)
    {
        Create(p_mode, p_title);
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
        EventManager::Dispatch();
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
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
        if(!m_WinHandle)
        {
            SF_CORE_FATAL(Window_l, 11, "Faild to create the window: {}", SDL_GetError());
        }

        // Set handle callback for SDL
        SDL_AddEventWatch(HandleEvent, this);
    }

    void Window::Shutdown()
    {
        IsClosed = true;
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

    int SDLCALL Window::HandleEvent(void *p_userdata, SDL_Event *p_event)
    {
        auto window = static_cast<Window*>(p_userdata);

        switch(p_event->type)
        {
            case SDL_WINDOWEVENT:
                switch(p_event->window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        window->Shutdown();
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYDOWN: {
                KeyInfo keyInfo;
                keyInfo.vKey = SDLHelper::FromSDL(p_event->key.keysym.sym);
                keyInfo.scancode = SDLHelper::FromSDL(p_event->key.keysym.scancode);
                keyInfo.repeated = p_event->key.repeat != 0;
                keyInfo.alt = (p_event->key.keysym.mod & KMOD_ALT) != 0;
                keyInfo.control = (p_event->key.keysym.mod & KMOD_CTRL) != 0;
                keyInfo.shift = (p_event->key.keysym.mod & KMOD_SHIFT) != 0;
                keyInfo.system = (p_event->key.keysym.mod & KMOD_GUI) != 0;

                KeyPressedEvent event(keyInfo);
                EventManager::PushEvent(CreateScope<KeyPressedEvent>(event));
            }
                break;
            case SDL_KEYUP: {
                KeyInfo keyInfo;
                keyInfo.vKey = SDLHelper::FromSDL(p_event->key.keysym.sym);
                keyInfo.scancode = SDLHelper::FromSDL(p_event->key.keysym.scancode);
                keyInfo.repeated = p_event->key.repeat != 0;
                keyInfo.alt = (p_event->key.keysym.mod & KMOD_ALT) != 0;
                keyInfo.control = (p_event->key.keysym.mod & KMOD_CTRL) != 0;
                keyInfo.shift = (p_event->key.keysym.mod & KMOD_SHIFT) != 0;
                keyInfo.system = (p_event->key.keysym.mod & KMOD_GUI) != 0;

                KeyReleasedEvent event(keyInfo);
                EventManager::PushEvent(CreateScope<KeyReleasedEvent>(event));
            }
                break;
            default:
                break;
        }

        return 0;
    }
}
