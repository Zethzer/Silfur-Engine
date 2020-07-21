#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_HPP__ 
#define __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_HPP__

#include <vulkan/vulkan.h>

namespace Silfur
{
    namespace Vk
    {
        inline VkResult CreateDebugUtilsMessengerEXT(VkInstance p_instance, const VkDebugUtilsMessengerCreateInfoEXT* p_pCreateInfo,
            const VkAllocationCallbacks* p_pAllocator, VkDebugUtilsMessengerEXT* p_pDebugMessenger);
        inline void DestroyDebugUtilsMessengerEXT(VkInstance p_instance, VkDebugUtilsMessengerEXT p_debugMessenger,
            const VkAllocationCallbacks* p_pAllocator);
        inline void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& p_createInfo);
        inline void displayMessage(VkDebugUtilsMessageSeverityFlagBitsEXT p_messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT p_messageType,
            const char* p_message);

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT p_messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT p_messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* p_pCallbackData,
            void* p_pUserData)
        {
            displayMessage(p_messageSeverity, p_messageType, p_pCallbackData->pMessage);

            return VK_FALSE;
        }
    }
}

#include "Debug.inl"

#endif // __SILFUR_GRAPHICS_VULKAN_UTILS_DEBUG_HPP__
