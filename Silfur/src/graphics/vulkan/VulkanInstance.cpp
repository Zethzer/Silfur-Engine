#include "sfpch.hpp"
#include "VulkanInstance.hpp"

#include <SDL2/SDL_vulkan.h>

namespace Silfur
{
    VulkanInstance::VulkanInstance(const Window& window, const RendererProperties& properties)
    {
        Create(window, properties);
    }

    VulkanInstance::~VulkanInstance()
    {
        DestroyDebugUtilsMessengerEXT(nullptr);
        vkDestroyInstance(m_Instance, nullptr);
    }

    void VulkanInstance::Create(const Window& window, const RendererProperties& properties)
    {
        SF_CORE_TRACE(Vulkan, "Init Vulkan Instance");

        if (properties.EnableValidationLayers && !CheckValidationLayersSupport())
        {
            SF_CORE_FATAL(Vulkan, 20, "Vulkan validation layers requested but not available!");
        }

        auto extensions = GetRequiredExtensions(window, properties);
        VkApplicationInfo appInfos;
        PopulateAppInfos(properties, appInfos);

        CreateInstanceInfos createInstanceInfos
        {
            appInfos,
            properties,
            extensions
        };
        VkInstanceCreateInfo createInfos;
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfos;
        PopulateCreateInfos(createInstanceInfos, createInfos, debugCreateInfos);

        if (vkCreateInstance(&createInfos, nullptr, &m_Instance) != VK_SUCCESS)
        {
            SF_CORE_FATAL(Vulkan, 24, "Can't create Vulkan Instance!");
        }

        SetupDebugMessenger(properties);
    }

    void VulkanInstance::SetupDebugMessenger(const RendererProperties& properties)
    {
        if (!properties.EnableValidationLayers)
        {
            return;
        }

        VkDebugUtilsMessengerCreateInfoEXT createInfos;
        PopulateDebugMessengerCreateInfos(createInfos);

        if (CreateDebugUtilsMessengerEXT(
            &createInfos,
            nullptr
        ) != VK_SUCCESS)
        {
            SF_CORE_FATAL(Vulkan, 25, "Failed to set up Vulkan debug messenger!");
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

    std::vector<const char*> VulkanInstance::GetRequiredExtensions(const Window& window, const RendererProperties& properties)
    {
        u32 count;
        if (!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        {
            SF_CORE_FATAL(Vulkan, 21, "Can't get the count of Vulkan required extensions for SDL2!");
        }

        std::vector<const char*> extensions(count);

        if (!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data()))
        {
            SF_CORE_FATAL(Vulkan, 22, "Can't get Vulkan required extensions for SDL2!");
        }

        if (properties.EnableValidationLayers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
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

    void VulkanInstance::PopulateCreateInfos(const CreateInstanceInfos& createInstanceInfos,
        VkInstanceCreateInfo& createInfos,
        VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfos)
    {
        createInfos = {};
        createInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfos.pApplicationInfo = &createInstanceInfos.AppInfos;
        createInfos.enabledExtensionCount = static_cast<u32>(createInstanceInfos.Extensions.size());
        createInfos.ppEnabledExtensionNames = createInstanceInfos.Extensions.data();

        if (createInstanceInfos.RendererProperties.EnableValidationLayers)
        {
            createInfos.enabledLayerCount = static_cast<u32>(m_ValidationLayers.size());
            createInfos.ppEnabledLayerNames = m_ValidationLayers.data();

            PopulateDebugMessengerCreateInfos(debugCreateInfos);
            createInfos.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfos;
        }
    }

    void VulkanInstance::PopulateAppInfos(const RendererProperties& properties, VkApplicationInfo& appInfos)
    {
        appInfos = {};
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
    }

    void VulkanInstance::PopulateDebugMessengerCreateInfos(VkDebugUtilsMessengerCreateInfoEXT& createInfos)
    {
        createInfos = {};
        createInfos.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfos.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfos.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
            | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
        createInfos.pfnUserCallback = VulkanDebugCallback;
    }

    VkResult VulkanInstance::CreateDebugUtilsMessengerEXT(
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            return func(m_Instance, pCreateInfo, pAllocator, &m_DebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void VulkanInstance::DestroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            func(m_Instance, m_DebugMessenger, pAllocator);
        }
        else
        {
            SF_CORE_ERROR(Vulkan, 3, "VK_DEBUG_UTILS_EXTENSION is not present! Failed to load vkDestroyDebugUtilsMessengerEXT function!");
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstance::VulkanDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        std::stringstream debugMessage;
        auto callbackMessage = pCallbackData->pMessage;

        switch (messageType)
        {
            case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
                debugMessage << "[General] {}";
                break;
            case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
                debugMessage << "[Validation] {}";
                break;
            case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
                debugMessage << "[Performance] {}";
                break;
            default:
                break;
        }

        switch (messageSeverity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                SF_CORE_DEBUG(Vulkan, fmt::runtime(debugMessage.str()), callbackMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                SF_CORE_INFO(Vulkan, fmt::runtime(debugMessage.str()), callbackMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                SF_CORE_WARNING(Vulkan, fmt::runtime(debugMessage.str()), callbackMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                SF_CORE_ERROR(Vulkan, 2, fmt::runtime(debugMessage.str()), callbackMessage);
                break;
            default:
                break;
        }

        return VK_FALSE;
    }
}
