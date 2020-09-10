#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_INL__
#define __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_INL__

#include <sstream>

namespace Silfur
{
    namespace Vk
    {
        inline VkResult CreateDebugUtilsMessengerEXT(VkInstance p_instance, const VkDebugUtilsMessengerCreateInfoEXT* p_pCreateInfo,
            const VkAllocationCallbacks* p_pAllocator, VkDebugUtilsMessengerEXT* p_pDebugMessenger)
        {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(p_instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                return func(p_instance, p_pCreateInfo, p_pAllocator, p_pDebugMessenger);
            }
            else
            {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        inline void DestroyDebugUtilsMessengerEXT(VkInstance p_instance,
            VkDebugUtilsMessengerEXT p_debugMessenger,
            const VkAllocationCallbacks* p_pAllocator)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(p_instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                func(p_instance, p_debugMessenger, p_pAllocator);
            }
        }

        inline void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& p_createInfo)
        {
            p_createInfo = {};
            p_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            p_createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            p_createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            p_createInfo.pfnUserCallback = DebugCallback;
            p_createInfo.pUserData = nullptr;
        }

        inline void DisplayMessage(VkDebugUtilsMessageSeverityFlagBitsEXT p_messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT p_messageType, const char* p_message)
        {
            std::stringstream msg;

            switch (p_messageType)
            {
                case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
                    msg << "[General] {}";
                break;
                case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
                    msg << "[Validation] {}";
                break;
                case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
                    msg << "[Performance] {}";
                break;
                default: break;
            }

            switch (p_messageSeverity)
            {
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                    SF_CORE_DEBUG(Vulkan, msg.str(), p_message);
                break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                    SF_CORE_WARNING(Vulkan, msg.str(), p_message);
                break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                    SF_CORE_ERROR(Vulkan, msg.str(), p_message);
                break;
                default:
                break;
            }
        }
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_INL__
