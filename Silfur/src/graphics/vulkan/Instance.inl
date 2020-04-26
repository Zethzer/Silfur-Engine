#pragma once

#ifndef VULKAN_INSTANCE_INL
#define VULKAN_INSTANCE_INL

#include "graphics/vulkan/Instance.h"
#include "utility/log/Log.h"

#include <GLFW/glfw3.h>

namespace Silfur
{
    namespace Vk
    {
        inline Instance::operator VkInstance() const noexcept
        {
            return m_Instance;
        }
    }
}

#endif // VULKAN_INSTANCE_INL
