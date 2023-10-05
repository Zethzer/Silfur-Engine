#include "sfpch.hpp"
#include "VulkanRenderer.hpp"

namespace Silfur
{
    VulkanRenderer::VulkanRenderer(const Window& window, RendererProperties properties)
        : m_Window(window)
    {
        Init(properties);
    }

    VulkanRenderer::~VulkanRenderer()
    {
        m_LogicalDevice.reset();
    }

    void VulkanRenderer::Init(RendererProperties properties)
    {
        m_LogicalDevice = CreateScope<VulkanLogicalDevice>(m_Window, properties);
    }

    void VulkanRenderer::Update()
    {
    }
}
