#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_VALIDATION_LAYERS_HPP__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_VALIDATION_LAYERS_HPP__

#include <array>

namespace Silfur
{
    namespace Vk
    {
        #ifdef SF_CONFIG_DEBUG
            constexpr bool enableValidationLayers = true;
        #else
            constexpr bool enableValidationLayers = false;
        #endif

        constexpr std::array<const char*, 1> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        inline bool checkValidationLayerSupport();
    }
}

#include "ValidationLayers.inl"

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_VALIDATION_LAYERS_HPP__
