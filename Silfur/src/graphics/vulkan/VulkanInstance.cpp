#include "sfpch.hpp"
#include "VulkanInstance.hpp"

#include <SDL2/SDL_vulkan.h>

namespace Silfur
{
    VulkanInstance::VulkanInstance(RendererProperties properties)
    {
        Create(properties);
    }

    VulkanInstance::~VulkanInstance()
    {
        vkDestroyInstance(m_InstanceVk, nullptr);
    }

    void VulkanInstance::Create(RendererProperties properties)
    {
        SF_CORE_TRACE(Vulkan, "Init Vulkan Instance");

        if (properties.EnableValidationLayers && !CheckValidationLayersSupport())
        {
            SF_CORE_FATAL(Vulkan, 20, "Vulkan validation layers requested but not available!");
        }

        auto extensions = GetRequiredExtensions(properties);
        auto appInfos = PopulateAppInfos(properties);

        CreateInstanceInfos createInstanceInfos
        {
            appInfos,
            properties,
            extensions
        };
        auto createInfos = PopulateCreateInfos(createInstanceInfos);

        if (vkCreateInstance(&createInfos, nullptr, &m_InstanceVk) != VK_SUCCESS)
        {
            SF_CORE_FATAL(Vulkan, 24, "Can't create Vulkan Instance!");
        }
    }

    bool VulkanInstance::CheckValidationLayersSupport()
    {
        u32 count;
        vkEnumerateInstanceLayerProperties(&count, nullptr);

        std::vector<VkLayerProperties> availableLayers(count);
        vkEnumerateInstanceLayerProperties(&count, availableLayers.data());

        for (const char* layerName : m_ValidationLayers)
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

        return true;
    }

    std::vector<const char*> VulkanInstance::GetRequiredExtensions(RendererProperties properties)
    {
        u32 count;
        if (!SDL_Vulkan_GetInstanceExtensions(properties.Window, &count, nullptr))
        {
            SF_CORE_FATAL(Vulkan, 21, "Can't get the count of Vulkan required extensions for SDL2!");
        }

        std::vector<const char*> extensions(count);

        if (!SDL_Vulkan_GetInstanceExtensions(properties.Window, &count, extensions.data()))
        {
            SF_CORE_FATAL(Vulkan, 22, "Can't get Vulkan required extensions for SDL2!");
        }

        auto availableExtensions = GetAvailableExtensions();

        for (const auto& extensionName : extensions)
        {
            bool extensionFound = false;

            for (const auto& extensionProperties : availableExtensions)
            {
                if (strcmp(extensionName, extensionProperties.extensionName) == 0)
                {
                    extensionFound = true;
                    break;
                }
            }

            if (!extensionFound)
            {
                SF_CORE_FATAL(Vulkan, 23, "Can't find vulkan extension {}!", extensionName);
            }
        }

        SF_CORE_TRACE(Vulkan, "All necessary extensions found!");

        return extensions;
    }

    std::vector<VkExtensionProperties> VulkanInstance::GetAvailableExtensions()
    {
        u32 availableExtensionsCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);

        SF_CORE_TRACE(Vulkan, "{} extensions supported!", availableExtensionsCount);

        std::vector<VkExtensionProperties> availableExtensions(availableExtensionsCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, availableExtensions.data());

        SF_CORE_TRACE(Vulkan, "Vulkan extensions available :");
        for (const auto& availableExtension : availableExtensions)
        {
            SF_CORE_TRACE(Vulkan, "- {}", availableExtension.extensionName);
        }

        return availableExtensions;
    }

    VkInstanceCreateInfo VulkanInstance::PopulateCreateInfos(CreateInstanceInfos createInstanceInfos)
    {
        VkInstanceCreateInfo createInfos{};
        createInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfos.pApplicationInfo = &createInstanceInfos.AppInfos;
        createInfos.enabledExtensionCount = static_cast<u32>(createInstanceInfos.Extensions.size());
        createInfos.ppEnabledExtensionNames = createInstanceInfos.Extensions.data();
        createInfos.enabledLayerCount = 0;

        if (createInstanceInfos.RendererProperties.EnableValidationLayers)
        {
            createInfos.enabledLayerCount = static_cast<u32>(m_ValidationLayers.size());
            createInfos.ppEnabledLayerNames = m_ValidationLayers.data();
        }

        return createInfos;
    }

    VkApplicationInfo VulkanInstance::PopulateAppInfos(RendererProperties properties)
    {
        VkApplicationInfo appInfos{};
        appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfos.pApplicationName = properties.ApplicationName.c_str();
        appInfos.applicationVersion = VK_MAKE_API_VERSION(
            0,
            properties.ApplicationVersion.Major,
            properties.ApplicationVersion.Minor,
            properties.ApplicationVersion.Patch
        );
        appInfos.pEngineName = properties.EngineName.c_str();
        appInfos.engineVersion = VK_MAKE_API_VERSION(
            0,
            properties.EngineVersion.Major,
            properties.EngineVersion.Minor,
            properties.EngineVersion.Patch
        );
        appInfos.apiVersion = VK_API_VERSION_1_3;

        return appInfos;
    }
}
