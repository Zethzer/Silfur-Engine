#include "sfpch.hpp"
#include "InstanceVk.hpp"

#include <SDL2/SDL_vulkan.h>

namespace Silfur
{
    InstanceVk::InstanceVk(RendererProperties properties)
    {
        Create(properties);
    }

    InstanceVk::~InstanceVk()
    {
        vkDestroyInstance(m_InstanceVk, nullptr);
    }

    void InstanceVk::Create(RendererProperties properties)
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

        unsigned int count;
        if (!SDL_Vulkan_GetInstanceExtensions(properties.Window, &count, nullptr))
        {
            SF_CORE_FATAL(Vulkan, 20, "Can't get the count of Vulkan required extensions for SDL2!");
        }

        std::vector<const char*> extensions;
        extensions.resize(count);

        if (!SDL_Vulkan_GetInstanceExtensions(properties.Window, &count, extensions.data()))
        {
            SF_CORE_FATAL(Vulkan, 21, "Can't get Vulkan required extensions for SDL2!");
        }

        VkInstanceCreateInfo createInfos{};
        createInfos.pApplicationInfo = &appInfos;
        createInfos.enabledExtensionCount = count;
        createInfos.ppEnabledExtensionNames = extensions.data();

        if (vkCreateInstance(&createInfos, nullptr, &m_InstanceVk) != VK_SUCCESS)
        {
            SF_CORE_FATAL(Vulkan, 22, "Can't create Vulkan Instance!");
        }
    }
}
