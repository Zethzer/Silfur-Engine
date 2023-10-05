#pragma once

#include "defines.hpp"

#include "core/window/Window.hpp"
#include "../RendererProperties.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
    class VulkanInstance
    {
    public:
        struct CreateInstanceInfos
        {
            const VkApplicationInfo& AppInfos;
            const RendererProperties& RendererProperties;
            const std::vector<const char*>& Extensions;
        };

    public:
        VulkanInstance() = delete;
        VulkanInstance(const Window& window, const RendererProperties& properties);
        ~VulkanInstance();

        VulkanInstance(const VulkanInstance&) = delete;
        VulkanInstance(VulkanInstance&&) = delete;
        VulkanInstance& operator=(const VulkanInstance&) = delete;
        VulkanInstance& operator=(VulkanInstance&&) = delete;

        inline operator VkInstance() const noexcept { return m_Instance; };

    private:
        void Create(const Window& window, const RendererProperties& properties);
        void SetupDebugMessenger(const RendererProperties& properties);

        bool CheckValidationLayersSupport();
        std::vector<const char*> GetRequiredExtensions(const Window& window, const RendererProperties& properties);
        std::vector<VkExtensionProperties> GetAvailableExtensions();

        void PopulateCreateInfos(const CreateInstanceInfos& createInstanceInfos,
            VkInstanceCreateInfo& createInfos,
            VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfos);
        void PopulateAppInfos(const RendererProperties& properties, VkApplicationInfo& appInfos);
        void PopulateDebugMessengerCreateInfos(VkDebugUtilsMessengerCreateInfoEXT& createInfos);

        VkResult CreateDebugUtilsMessengerEXT(
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator);
        void DestroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator);

        static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );

    private:
        VkInstance m_Instance = nullptr;
        
        const std::vector<const char*> m_ValidationLayers {
            "VK_LAYER_KHRONOS_validation"
        };

        VkDebugUtilsMessengerEXT m_DebugMessenger = nullptr;
    };
}
