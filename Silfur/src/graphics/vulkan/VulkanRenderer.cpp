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
        m_Instance.reset();
    }

    void VulkanRenderer::Init(RendererProperties properties)
    {
        m_Instance = CreateScope<VulkanInstance>(m_Window, properties);
        m_PhysicalDevice = CreateScope<VulkanPhysicalDevice>(*m_Instance);
    }

    void VulkanRenderer::Update()
    {
    }
}
