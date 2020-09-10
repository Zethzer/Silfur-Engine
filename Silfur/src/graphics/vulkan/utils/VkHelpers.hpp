#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_VKHELPERS_HPP__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_VKHELPERS_HPP__

#include "utility/log/Log.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
    namespace Vk
    {
        static void VkCheckResult(VkResult err)
        {
            if (err == VK_SUCCESS)
            {
                return;
            }

            SF_CORE_ERROR(Vulkan, "Error: VkResult = {0}\n", err);

            if (err < 0)
            {
                std::exit(EXIT_FAILURE);
            }

        }
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_VKHELPERS_HPP__
