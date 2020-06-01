#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_EXTENSIONS_HPP__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_EXTENSIONS_HPP__

#include <vector>

namespace Silfur
{
    namespace Vk
    {
        inline std::vector<const char*> getRequiredExtensions();

        inline bool checkRequiredExtensions(const std::vector<VkExtensionProperties>& p_VkExtensionsAvailable, const std::vector<const char*> p_RequiredExtensions);
    }
}

#include "graphics/vulkan/utils/Extensions.inl"

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_EXTENSIONS_HPP__
