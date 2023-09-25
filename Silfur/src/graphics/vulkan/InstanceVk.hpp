#pragma once

#include "defines.hpp"
#include "../RendererProperties.hpp"

#include <vulkan/vulkan.h>

namespace Silfur
{
	class InstanceVk
	{
	public:
		InstanceVk() = delete;
		InstanceVk(RendererProperties properties);
		~InstanceVk();

		InstanceVk(const InstanceVk&) = delete;
		InstanceVk(InstanceVk&&) = delete;

	private:
		void Create(RendererProperties properties);

	private:
		VkInstance m_InstanceVk = nullptr;
	};
}
