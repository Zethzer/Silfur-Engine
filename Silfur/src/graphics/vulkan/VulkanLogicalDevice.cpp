#include "sfpch.hpp"
#include "VulkanLogicalDevice.hpp"

namespace Silfur
{
    VulkanLogicalDevice::VulkanLogicalDevice(const Window& window, const RendererProperties& properties)
        : m_Window(window), m_RendererProperties(properties)
    {
        CreateInstance();
        CreatePhysicalDevice();
        CreateLogicalDevice();
    }

    VulkanLogicalDevice::~VulkanLogicalDevice()
    {
        vkDestroyDevice(m_Device, nullptr);
    }

    void VulkanLogicalDevice::CreateInstance()
    {
        m_Instance = CreateScope<VulkanInstance>(m_Window, m_RendererProperties);
    }

    void VulkanLogicalDevice::CreatePhysicalDevice()
    {
        m_PhysicalDevice = CreateScope<VulkanPhysicalDevice>(*m_Instance);
    }

    void VulkanLogicalDevice::CreateLogicalDevice()
    {
        auto indices = m_PhysicalDevice->GetQueueFamilyIndices();

        VkDeviceQueueCreateInfo queueCreateInfos{};
        float queuePriority = 1.0f;
        queueCreateInfos.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfos.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfos.queueCount = 1;
        queueCreateInfos.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures physicalDeviceFeatures{};

        VkDeviceCreateInfo createInfos{};
        createInfos.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfos.pQueueCreateInfos = &queueCreateInfos;
        createInfos.queueCreateInfoCount = 1;

        createInfos.pEnabledFeatures = &physicalDeviceFeatures;

        createInfos.enabledExtensionCount = 0;
        // https://registry.khronos.org/vulkan/specs/1.0/html/vkspec.html#extendingvulkan-layers-devicelayerdeprecation
        createInfos.enabledLayerCount = 0;
        createInfos.ppEnabledLayerNames = nullptr;

        if (vkCreateDevice(*m_PhysicalDevice, &createInfos, nullptr, &m_Device) != VK_SUCCESS)
        {
            SF_CORE_FATAL(Vulkan, 28, "Can't create Vulkan logical device!");
        }

        vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
    }
}
