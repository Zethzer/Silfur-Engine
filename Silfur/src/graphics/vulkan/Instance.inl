#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__
#define __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__

#include "graphics/vulkan/debug/ValidationLayers.hpp"
#include "utility/log/Log.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Silfur
{
    namespace Vk
    {
        inline Instance::operator VkInstance() const noexcept
        {
            return m_Instance;
        }

        inline std::vector<const char*> Instance::getRequiredExtensions()
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

        inline bool Instance::checkRequiredExtensions(const std::vector<VkExtensionProperties>& p_vkExtensionsAvailable, const std::vector<const char*>& p_requiredExtensions)
        {
            for (const char* extensionName : p_requiredExtensions)
            {
                bool extensionFound = false;

                for (const auto& vkExtension : p_vkExtensionsAvailable)
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

#endif // __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__
