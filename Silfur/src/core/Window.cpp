#include "sfpch.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace Silfur
{
    Window::Window(VideoMode p_mode, const wchar_t* p_title) :
        WinHandle(nullptr),
        IsClosed(false)
    {
        Create(p_mode, p_title);
    }

    Window::~Window()
    {
        glfwDestroyWindow(WinHandle);
        glfwTerminate();
    }

    void Window::ProcessEvents()
    {
        if (glfwWindowShouldClose(WinHandle))
        {
            Shutdown();
        }

        glfwPollEvents();
    }

    void Window::Create(VideoMode p_mode, const wchar_t* p_title)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        WinHandle = glfwCreateWindow(p_mode.Width, p_mode.Height, "Learning Vulkan", nullptr, nullptr);
        glfwSetWindowUserPointer(WinHandle, this);
    }

    void Window::Shutdown()
    {
        IsClosed = true;
    }
}
