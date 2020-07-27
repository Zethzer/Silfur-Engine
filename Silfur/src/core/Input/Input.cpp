#include "sfpch.hpp"
#include "Input.hpp"

#include "core/Application.hpp"

#include <GLFW/glfw3.h>

namespace Silfur
{

    bool Input::IsKeyPressed(KeyCode p_key)
    {
        GLFWwindow* win = Application::Get().GetWindow().WindowHandle();
        int state = glfwGetKey(win, static_cast<int>(p_key));

        return state == GLFW_PRESS;
    }

    const char* Input::GetKeyName(KeyCode p_key)
    {
        return glfwGetKeyName(static_cast<int>(p_key), glfwGetKeyScancode(static_cast<int>(p_key)));
    }
}
