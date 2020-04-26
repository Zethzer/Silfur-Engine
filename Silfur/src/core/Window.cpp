#include "sfpch.hpp"
#include "Window.hpp"

#include <GLFW/glfw3.h>

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
    }

    void Window::Create(VideoMode p_mode, const char* p_title)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_WinHandle = glfwCreateWindow(p_mode.Width, p_mode.Height, p_title, nullptr, nullptr);
        glfwSetWindowUserPointer(m_WinHandle, this);
    }

    void Window::Shutdown()
    {
        IsClosed = true;
    }
}
