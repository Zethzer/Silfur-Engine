#include "sfpch.hpp"
#include "Window.hpp"

#include "core/events/EventManager.hpp"
#include "core/events/KeyEvent.hpp"

#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#else
    /* Unknown compiler/platform */
    #error "Unknown platform!"
#endif
#include <GLFW/glfw3native.h>

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
        glfwDestroyWindow(m_WinHandle);
        glfwTerminate();
    }

    void Window::ProcessEvents()
    {
        if (glfwWindowShouldClose(m_WinHandle))
        {
            Shutdown();
        }

        glfwPollEvents();
        EventManager::Dispatch();
    }

    void Window::Create(VideoMode p_mode, const char* p_title)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_WinHandle = glfwCreateWindow(p_mode.Width, p_mode.Height, p_title, nullptr, nullptr);
        glfwSetWindowUserPointer(m_WinHandle, this);

        // Set GLFW callbacks
        glfwSetKeyCallback(m_WinHandle, [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
        {
            Window& win = *(Window*)glfwGetWindowUserPointer(p_window);

            switch (p_action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(p_key), 0);
                    EventManager::PushEvent(CreateScope<KeyPressedEvent>(event));
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(static_cast<KeyCode>(p_key));
                    EventManager::PushEvent(CreateScope<KeyReleasedEvent>(event));
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(p_key), 1);
                    EventManager::PushEvent(CreateScope<KeyPressedEvent>(event));
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetCharCallback(m_WinHandle, [](GLFWwindow* p_window, unsigned int p_codePoint)
        {
            Window& win = *(Window*)glfwGetWindowUserPointer(p_window);

            KeyTypedEvent event(p_codePoint);
            EventManager::PushEvent(CreateScope<KeyTypedEvent>(event));
        });
    }

    void Window::Shutdown()
    {
        IsClosed = true;
    }

    void* Window::WindowSystemHandle() const noexcept
    {
        #ifdef _WIN32
            return glfwGetWin32Window(m_WinHandle);
        #else
            /* Unknown compiler/platform */
            #error "Unknown platform!"
        #endif
    }
}
