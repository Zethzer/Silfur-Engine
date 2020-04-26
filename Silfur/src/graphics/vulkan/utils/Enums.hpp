#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_ENUMS_HPP__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_ENUMS_HPP__

#include <vulkan/vulkan.h>

namespace Silfur
{
    namespace Vk
    {
        enum class DebugUtilsMessageSeverity : VkDebugUtilsMessageSeverityFlagsEXT
        {
            VERBOSE = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
            INFO = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
            WARNING = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
            ERROR = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
        } DebugUtilsMessageSeverity;

        enum class VkDebugUtilsMessageType : VkDebugUtilsMessageTypeFlagsEXT
        {
            GENERAL = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
            VALIDATION = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
            PERFORMANCE = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
        } VkDebugUtilsMessageType;
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_ENUMS_HPP__
