#pragma once

#include "defines.hpp"
#include "../RendererProperties.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
    class RendererVk
    {
    public:
        RendererVk() = delete;
        RendererVk(RendererProperties properties);
        ~RendererVk();

        RendererVk(const RendererVk&) = delete;
        RendererVk(RendererVk&&) = delete;

        void Update();
    private:
        void Init(RendererProperties properties);
    };
}
