#include "sfpch.h"
#include "Window.h"

namespace Silfur
{
    Window::Window(VideoMode p_mode, const wchar_t* p_title) :
        WinHandle(nullptr),
        IsClosed(true)
    {
        Create(p_mode, p_title);
    }

    void Window::ProcessEvents()
    {
        glfwPollEvents();
    }

    void Window::Create(VideoMode p_mode, const wchar_t* p_title)
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        WinHandle = glfwCreateWindow(p_mode.Width, p_mode.Height, "Learning Vulkan", nullptr, nullptr);
        glfwSetWindowUserPointer(WinHandle, this);
        glfwSetFramebufferSizeCallback(WinHandle, [](GLFWwindow* p_Window, int p_Width, int p_Height) {
            auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_Window));
            window->m_FrameBufferResized = true;
        });
    }

    void Window::Shutdown()
    {
        IsClosed = true;
    }
}
