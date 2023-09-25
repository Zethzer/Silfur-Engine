#include "sfpch.hpp"
#include "RendererVk.hpp"

#include "InstanceVk.hpp"

namespace Silfur
{
    RendererVk::RendererVk(RendererProperties properties)
    {
        Init(properties);
    }

    RendererVk::~RendererVk()
    {
        m_Instance.reset();
    }

    void RendererVk::Init(RendererProperties properties)
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        SF_CORE_TRACE(Vulkan, "{} extensions supported!", extensionCount);

        m_Instance = CreateScope<InstanceVk>(properties);
    }

    void RendererVk::Update()
    {
    }
}
