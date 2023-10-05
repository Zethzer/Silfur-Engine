#pragma once

#include "defines.hpp"

#include "core/window/Window.hpp"
#include "../RendererProperties.hpp"

#include "VulkanInstance.hpp"
#include "VulkanPhysicalDevice.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
    class VulkanLogicalDevice
    {
    public:
        VulkanLogicalDevice() = delete;
        VulkanLogicalDevice(const Window& window, const RendererProperties& properties);
        ~VulkanLogicalDevice();

        VulkanLogicalDevice(const VulkanLogicalDevice&) = delete;
        VulkanLogicalDevice(const VulkanLogicalDevice&&) = delete;
        VulkanLogicalDevice& operator=(const VulkanLogicalDevice&) = delete;
        VulkanLogicalDevice& operator=(VulkanLogicalDevice&&) = delete;

    private:
        void CreateInstance();
        void CreatePhysicalDevice();
        void CreateLogicalDevice();

    private:
        VkDevice m_Device;
        VkQueue m_GraphicsQueue;

        const Window& m_Window;
        const RendererProperties& m_RendererProperties;

        Scope<VulkanInstance> m_Instance;
        Scope<VulkanPhysicalDevice> m_PhysicalDevice;
    };
}
