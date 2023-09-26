#pragma once

#include "defines.hpp"
#include "../RendererProperties.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
    class VulkanInstance
    {
    public:
        struct CreateInstanceInfos
        {
            VkApplicationInfo& AppInfos;
            RendererProperties RendererProperties;
            std::vector<const char*>& Extensions;
        };

    public:
        VulkanInstance() = delete;
        VulkanInstance(RendererProperties properties);
        ~VulkanInstance();

        VulkanInstance(const VulkanInstance&) = delete;
        VulkanInstance(VulkanInstance&&) = delete;

    private:
        void Create(RendererProperties properties);

        bool CheckValidationLayersSupport();
        std::vector<const char*> GetRequiredExtensions(RendererProperties properties);
        std::vector<VkExtensionProperties> GetAvailableExtensions();

        VkInstanceCreateInfo PopulateCreateInfos(CreateInstanceInfos createInstanceInfos);
        VkApplicationInfo PopulateAppInfos(RendererProperties properties);

    private:
        VkInstance m_InstanceVk = nullptr;
        const std::vector<const char*> m_ValidationLayers {
            "VK_LAYER_KHRONOS_validation"
        };
    };
}
