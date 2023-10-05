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

        inline QueueFamilyIndices GetQueueFamilyIndices() const { return m_QueueFamilyIndices; };

        inline operator VkPhysicalDevice() const noexcept { return m_PhysicalDevice; };

    private:
        void PickPhysicalDevice(const VulkanInstance& instance);
        bool IsDeviceSuitable(VkPhysicalDevice device);
        void LogDeviceInformations();
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    private:
        VkPhysicalDevice m_PhysicalDevice = nullptr;
        QueueFamilyIndices m_QueueFamilyIndices;
    };
}
