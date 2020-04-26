#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__
#define __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__

#include "graphics/vulkan/Instance.hpp"
#include "utility/log/Log.hpp"

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

#endif // __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__
