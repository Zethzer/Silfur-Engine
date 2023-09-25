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
    }

    void RendererVk::Init(RendererProperties properties)
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        SF_CORE_TRACE(Vulkan, "{} extensions supported!", extensionCount);

        auto instance = new InstanceVk(properties);
    }

    void RendererVk::Update()
    {
    }
}
