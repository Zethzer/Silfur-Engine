#pragma once

#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#include "core/Window.h"

#include <vulkan/vulkan.h>

// #TODO (Zeth) : Handle physical device needs

namespace Silfur
{
    namespace Vk
    {
        class Instance
        {
        public:
            Instance() = default;
            ~Instance() = default;

            Instance(const Instance&) = delete;
            Instance(Instance&&) = delete;

            void Create();
            void Destroy();

            VkSurfaceKHR CreateSurface(const Window& p_window);

            Instance& operator=(const Instance&) = delete;
            Instance& operator=(Instance&&) = delete;

            inline operator VkInstance() const noexcept;
        private:
            void setupDebugMessenger();

        private:
            VkInstance m_Instance {};
            VkDebugUtilsMessengerEXT m_DebugMessenger {};
        };
    }
}

#include "graphics/vulkan/Instance.inl"

#endif // VULKAN_INSTANCE_H
