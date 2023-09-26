#include "sfpch.hpp"
#include "VulkanRenderer.hpp"

namespace Silfur
{
    VulkanRenderer::VulkanRenderer(RendererProperties properties)
    {
        Init(properties);
    }

    VulkanRenderer::~VulkanRenderer()
    {
        m_Instance.reset();
    }

    void VulkanRenderer::Init(RendererProperties properties)
    {
        m_Instance = CreateScope<VulkanInstance>(properties);
    }

    void VulkanRenderer::Update()
    {
    }
}
