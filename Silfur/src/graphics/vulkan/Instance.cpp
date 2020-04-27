#include "sfpch.hpp"
#include "Instance.hpp"

#include "utility/log/Log.hpp"
#include "graphics/vulkan/utils/ValidationLayers.hpp"
#include "graphics/vulkan/utils/Debug.hpp"

#include <GLFW/glfw3.h>

#include <sstream>

// #TODO-Zeth : Create necessary enum class for replace enum C style of Vulkan API for Instance class
// #TODO-Zeth : Think about parameters for create the instance

namespace Silfur
{
    namespace Vk
    {
        std::vector<const char*> getRequiredExtensions()
        {
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

            if (enableValidationLayers)
            {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return extensions;
        }

        bool checkRequiredExtensions(const std::vector<VkExtensionProperties>& p_VkExtensionsAvailable, const std::vector<const char*> p_RequiredExtensions)
        {
            for (const char* extensionName : p_RequiredExtensions)
            {
                bool extensionFound = false;

                for (const auto& vkExtension : p_VkExtensionsAvailable)
                {
                    if (strcmp(extensionName, vkExtension.extensionName) == 0)
                    {
                        extensionFound = true;
                        break;
                    }
                }

                if (!extensionFound)
                {
                    return false;
                }
            }

            SF_CORE_INFO(Vulkan, "Extensions requirements fulfilled.");

            return true;
        }

        void Instance::Create()
        {
            if (enableValidationLayers && !checkValidationLayerSupport())
            {
                SF_CORE_FATAL(Vulkan, 20, "Validation layers requested but not available!");
                std::exit(EXIT_FAILURE);
            }

            VkApplicationInfo appInfo = {};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Hello Triangle";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "Silfur Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);

            // #NOTE : vkEnumerateInstanceVersion function exists since Vulkan 1.1
            auto func = (PFN_vkEnumerateInstanceVersion) vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion");
            if (func != nullptr)
            {
                uint32_t supportedApiVersion;
                vkEnumerateInstanceVersion(&supportedApiVersion);

                appInfo.apiVersion = supportedApiVersion;
            }
            else
            {
                appInfo.apiVersion = VK_API_VERSION_1_0;
            }

            VkInstanceCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            uint32_t vkExtensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);
            std::vector<VkExtensionProperties> vkExtensions(vkExtensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensions.data());

            std::stringstream msg;
            msg << "Vulkan available extensions:\n";
            for (const auto& extension : vkExtensions)
            {
                msg << "\t" << extension.extensionName << "\n";
            }
            SF_CORE_INFO(Vulkan, msg.str());

            auto extensions = getRequiredExtensions();

            msg.str("");
            msg.clear();
            msg << "Required extensions:\n";
            for (const char* extensionName : extensions)
            {
                msg << "\t" << extensionName << "\n";
            }
            SF_CORE_INFO(Vulkan, msg.str());

            if (!checkRequiredExtensions(vkExtensions, extensions))
            {
                SF_CORE_FATAL(Vulkan, 21, "Missing an extension.");
                std::exit(EXIT_FAILURE);
            }

            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
            if (enableValidationLayers)
            {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();

                populateDebugMessengerCreateInfo(debugCreateInfo);
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
            }
            else
            {
                createInfo.enabledLayerCount = 0;
                createInfo.pNext = nullptr;
            }

            if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
            {
                SF_CORE_FATAL(Vulkan, 22, "Failed to create instance!");
                std::exit(EXIT_FAILURE);
            }

            setupDebugMessenger();
        }

        void Instance::Destroy()
        {
            if (enableValidationLayers)
            {
                DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
            }

            vkDestroyInstance(m_Instance, nullptr);
        }

        VkSurfaceKHR Instance::CreateSurface(const Window& p_window)
        {
            VkSurfaceKHR surface;

            if (glfwCreateWindowSurface(m_Instance, p_window, nullptr, &surface) != VK_SUCCESS)
            {
                SF_CORE_FATAL(Vulkan, 24, "Failed to create window surface!");
                std::exit(EXIT_FAILURE);
            }

            return surface;
        }

        void Instance::setupDebugMessenger()
        {
            if (!enableValidationLayers) return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
            {
                SF_CORE_FATAL(Vulkan, 23, "Failed to set up debug messenger!");
                std::exit(EXIT_FAILURE);
            }
        }
    }
}