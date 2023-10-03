#include "sfpch.hpp"
#include "VulkanPhysicalDevice.hpp"

#include "VulkanInstance.hpp"

namespace Silfur
{
    VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanInstance& instance)
    {
        PickPhysicalDevice(instance);
    }

    void VulkanPhysicalDevice::PickPhysicalDevice(const VulkanInstance& instance)
    {
        uint32 deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            SF_CORE_FATAL(Vulkan, 26, "Can't find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        // NOTE : Function not very generic
        // It's just pick the first discrete gpu found on the computer
        for (const auto& device : devices)
        {
            if (IsDeviceSuitable(device))
            {
                m_PhysicalDevice = device;
                break;
            }
        }

        if (m_PhysicalDevice == nullptr)
        {
            SF_CORE_FATAL(Vulkan, 27, "Failed to find a suitable GPU!");
        }

        LogDeviceInformations();
    }

    bool VulkanPhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProps;
        vkGetPhysicalDeviceProperties(device, &deviceProps);

        if (deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            return true;
        }

        return false;
    }

    void VulkanPhysicalDevice::LogDeviceInformations()
    {
        VkPhysicalDeviceProperties deviceProps;
        vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProps);

        std::stringstream driverVersionStr;
        driverVersionStr << "Driver Version: ";

        // Nvidia
        if (deviceProps.vendorID == 4318)
        {
            driverVersionStr << std::string(fmt::format("{0}.{1}.{2}.{3}",
                ((uint32)(deviceProps.driverVersion >> 22U)) & 0x3FFU,
                ((uint32)(deviceProps.driverVersion >> 14U)) & 0x0FFU,
                ((uint32)(deviceProps.driverVersion >> 6U)) & 0x0FFU,
                ((uint32)deviceProps.driverVersion) & 0x003FU
            ));
        }
        else
        {
            driverVersionStr << std::string(fmt::format("{0}.{1}.{2}.{3}",
                VK_API_VERSION_MAJOR(deviceProps.driverVersion),
                VK_API_VERSION_MINOR(deviceProps.driverVersion),
                VK_API_VERSION_PATCH(deviceProps.driverVersion),
                VK_API_VERSION_VARIANT(deviceProps.driverVersion)
            ));
        }

        SF_CORE_INFO(Vulkan, "Using GPU : {0} - Vulkan API Version: {1}.{2}.{3} - {4}",
            deviceProps.deviceName,
            VK_API_VERSION_MAJOR(deviceProps.apiVersion),
            VK_API_VERSION_MINOR(deviceProps.apiVersion),
            VK_API_VERSION_PATCH(deviceProps.apiVersion),
            driverVersionStr.str()
        );
    }
}
