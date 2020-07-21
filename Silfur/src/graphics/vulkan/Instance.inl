#pragma once

#ifndef __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__
#define __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__

namespace Silfur
{
    namespace Vk
    {
        inline Instance::operator VkInstance() const noexcept
        {
            return m_Instance;
        }
    }
}

#endif // __SILFUR_GRAPHICS_VULKAN_INSTANCE_INL__
