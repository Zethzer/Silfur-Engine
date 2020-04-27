#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_VALIDATION_LAYERS_INL__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_VALIDATION_LAYERS_INL__

#include "graphics/vulkan/utils/ValidationLayers.hpp"
#include "utility/log/Log.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace Silfur
{
    namespace Vk
    {
        inline bool checkValidationLayerSupport()
        {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            for (const char* layerName : validationLayers)
            {
                bool layerFound = false;

                for (const auto& layerProperties : availableLayers)
                {
                    if (strcmp(layerName, layerProperties.layerName) == 0)
                    {
                        layerFound = true;
                        break;
                    }
                }

                if (!layerFound)
                {
                    return false;
                }
            }

            SF_CORE_INFO(Vulkan, "Validation layers enabled.");

            return true;
        }
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_VALIDATION_LAYERS_INL__
