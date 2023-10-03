#pragma once

#include "defines.hpp"
#include "../RendererProperties.hpp"

#include "VulkanInstance.hpp"
#include "VulkanPhysicalDevice.hpp"

namespace Silfur
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer() = delete;
        VulkanRenderer(const Window& window, RendererProperties properties);
        ~VulkanRenderer();

        VulkanRenderer(const VulkanRenderer&) = delete;
        VulkanRenderer(VulkanRenderer&&) = delete;
        VulkanRenderer& operator=(const VulkanRenderer&) = delete;
        VulkanRenderer& operator=(VulkanRenderer&&) = delete;

        void Update();

    private:
        void Init(RendererProperties properties);

    private:
        Scope<VulkanInstance> m_Instance = nullptr;
        Scope<VulkanPhysicalDevice> m_PhysicalDevice = nullptr;
        
        const Window& m_Window;

    };
}
