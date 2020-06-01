#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_EXTENSIONS_INL__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_EXTENSIONS_INL__

#include "graphics/vulkan/utils/Extensions.hpp"
#include "graphics/vulkan/utils/ValidationLayers.hpp"
#include "utility/log/Log.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Silfur
{
    namespace Vk
    {
        inline std::vector<const char*> getRequiredExtensions()
        {
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

            if (enableValidationLayers)
            {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return extensions;
        }

        inline bool checkRequiredExtensions(const std::vector<VkExtensionProperties>& p_VkExtensionsAvailable, const std::vector<const char*> p_RequiredExtensions)
        {
            for (const char* extensionName : p_RequiredExtensions)
            {
                bool extensionFound = false;

                for (const auto& vkExtension : p_VkExtensionsAvailable)
                {
                    if (strcmp(extensionName, vkExtension.extensionName) == 0)
                    {
                        extensionFound = true;
                        break;
                    }
                }

                if (!extensionFound)
                {
                    return false;
                }
            }

            SF_CORE_INFO(Vulkan, "Extensions requirements fulfilled.");

            return true;
        }
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_EXTENSIONS_HPP__
