#pragma once

#include "defines.hpp"
#include "../RendererProperties.hpp"

#include "VulkanInstance.hpp"

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

        void Update();
    private:
        void Init(RendererProperties properties);

    private:
        Scope<VulkanInstance> m_Instance = nullptr;
        const Window& m_Window;

    };
}
