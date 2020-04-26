#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_HPP__ 
#define __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_HPP__

#include <vulkan/vulkan.h>

namespace Silfur
{
    namespace Vk
    {
        VkResult CreateDebugUtilsMessengerEXT(VkInstance p_instance,
            const VkDebugUtilsMessengerCreateInfoEXT* p_pCreateInfo,
            const VkAllocationCallbacks* p_pAllocator,
            VkDebugUtilsMessengerEXT* p_pDebugMessenger)
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

        void DestroyDebugUtilsMessengerEXT(VkInstance p_instance,
            VkDebugUtilsMessengerEXT p_debugMessenger,
            const VkAllocationCallbacks* p_pAllocator)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(p_instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                func(p_instance, p_debugMessenger, p_pAllocator);
            }
        }

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT p_MessageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT p_MessageType,
            const VkDebugUtilsMessengerCallbackDataEXT* p_pCallbackData,
            void* p_pUserData)
        {
            std::cerr << "Validation layer: " << p_pCallbackData->pMessage << std::endl;

            return VK_FALSE;
        }

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& p_createInfo)
        {
            p_createInfo = {};
            p_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            p_createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            p_createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            p_createInfo.pfnUserCallback = debugCallback;
            p_createInfo.pUserData = nullptr; // Optional
        }
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_HPP__
