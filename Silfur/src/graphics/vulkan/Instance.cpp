#include "sfpch.hpp"
#include "Instance.hpp"

#include "utility/log/Log.hpp"
#include "graphics/vulkan/debug/ValidationLayers.hpp"
#include "graphics/vulkan/debug/Debug.hpp"

#include <vulkan/vulkan.h>
#include <SDL2/SDL_vulkan.h>

#include <sstream>

// #TODO Create necessary enum class for replace enum C style of Vulkan API for Instance class
// #TODO Think about parameters for create the instance

namespace Silfur
{
    namespace Vk
    {
        void Instance::Create(const std::string& p_appName, const Version& p_appVersion, const Window& p_window)
        {
            if (!CheckValidationLayerSupport() && enableValidationLayers)
            {
                SF_CORE_FATAL(Vulkan, 20, "Validation layers requested but not available!");
                std::exit(EXIT_FAILURE);
            }

            VkApplicationInfo appInfo = {};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = p_appName.c_str();
            appInfo.applicationVersion = VK_MAKE_VERSION(p_appVersion.major, p_appVersion.minor, p_appVersion.patch);
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

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
            auto requiredExtensions = GetRequiredExtensions(p_window);
            VkInstanceCreateInfo createInfo = CreateVkInstanceCreateInfo(appInfo, requiredExtensions, debugCreateInfo);

            if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
            {
                SF_CORE_FATAL(Vulkan, 22, "Failed to create instance!");
                std::exit(EXIT_FAILURE);
            }

            SF_CORE_INFO(Vulkan, "Create vulkan instance for application: {}, version {}.{}.{}", appInfo.pApplicationName,
                VK_VERSION_MAJOR(appInfo.applicationVersion), VK_VERSION_MINOR(appInfo.applicationVersion),
                VK_VERSION_PATCH(appInfo.applicationVersion));

            SetupDebugMessenger();
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

            if (SDL_Vulkan_CreateSurface(p_window, m_Instance, &surface) != SDL_TRUE)
            {
                SF_CORE_FATAL(Vulkan, 24, "Failed to create window surface!");
                std::exit(EXIT_FAILURE);
            }

            return surface;
        }

        VkInstanceCreateInfo Instance::CreateVkInstanceCreateInfo(const VkApplicationInfo& p_appInfo,
            const std::vector<const char*>& p_requiredExtensions,
            VkDebugUtilsMessengerCreateInfoEXT& p_debugCreateInfo)
        {
            VkInstanceCreateInfo createInfo;
            createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &p_appInfo;

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

            msg.str("");
            msg.clear();
            msg << "Required extensions:\n";
            for (const char* extensionName : p_requiredExtensions)
            {
                msg << "\t" << extensionName << "\n";
            }
            SF_CORE_INFO(Vulkan, msg.str());

            if (!CheckRequiredExtensions(vkExtensions, p_requiredExtensions))
            {
                SF_CORE_FATAL(Vulkan, 21, "Missing an extension.");
                std::exit(EXIT_FAILURE);
            }

            createInfo.enabledExtensionCount = static_cast<uint32_t>(p_requiredExtensions.size());
            createInfo.ppEnabledExtensionNames = p_requiredExtensions.data();

            
            if (enableValidationLayers)
            {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();

                PopulateDebugMessengerCreateInfo(p_debugCreateInfo);
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &p_debugCreateInfo;
            }
            else
            {
                createInfo.enabledLayerCount = 0;
                createInfo.pNext = nullptr;
            }

            return createInfo;
        }

        std::vector<const char*> Instance::GetRequiredExtensions(const Window& p_window)
        {
            uint32_t SDLExtensionsCount;
            SDL_Vulkan_GetInstanceExtensions(nullptr, &SDLExtensionsCount, nullptr);

            const char **SDLExtensions = static_cast<const char**>(malloc(sizeof(const char *) * SDLExtensionsCount));

            SDL_Vulkan_GetInstanceExtensions(nullptr, &SDLExtensionsCount, SDLExtensions);

            std::vector<const char*> extensions(SDLExtensions, SDLExtensions + SDLExtensionsCount);

            if (enableValidationLayers)
            {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return extensions;
        }

        bool Instance::CheckRequiredExtensions(const std::vector<VkExtensionProperties>& p_vkExtensionsAvailable, const std::vector<const char*>& p_requiredExtensions)
        {
            for (const char* extensionName : p_requiredExtensions)
            {
                bool extensionFound = false;

                for (const auto& vkExtension : p_vkExtensionsAvailable)
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

        void Instance::SetupDebugMessenger()
        {
            if (!enableValidationLayers) return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            PopulateDebugMessengerCreateInfo(createInfo);

            if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
            {
                SF_CORE_FATAL(Vulkan, 23, "Failed to set up debug messenger!");
                std::exit(EXIT_FAILURE);
            }
        }
    }
}
