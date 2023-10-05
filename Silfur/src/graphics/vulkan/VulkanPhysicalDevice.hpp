#pragma once

#include "defines.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
    class VulkanInstance;

    struct QueueFamilyIndices
    {
        std::optional<uint32> graphicsFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice() = delete;
        VulkanPhysicalDevice(const VulkanInstance& instance);
        ~VulkanPhysicalDevice() = default;

        VulkanPhysicalDevice(const VulkanPhysicalDevice&) = delete;
        VulkanPhysicalDevice(const VulkanPhysicalDevice&&) = delete;
        VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice&) = delete;
        VulkanPhysicalDevice& operator=(VulkanPhysicalDevice&&) = delete;

    private:
        void PickPhysicalDevice(const VulkanInstance& instance);
        bool IsDeviceSuitable(VkPhysicalDevice device);
        void LogDeviceInformations();
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    private:
        VkPhysicalDevice m_PhysicalDevice = nullptr;
    };
}
