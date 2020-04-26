#pragma once

#ifndef VALIDATION_LAYERS_H
#define VALIDATION_LAYERS_H

#include <array>

namespace Silfur
{
    namespace Vk
    {
        #ifdef _DEBUG
            constexpr bool enableValidationLayers = true;
        #else
            constexpr bool enableValidationLayers = false;
        #endif

        constexpr std::array<const char*, 1> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
    }
}

#endif // VALIDATION_LAYERS_H
