VULKAN_SDK_FOUND = false
VULKAN_FOUND = false

function checkVulkanDynamicLibWin32()
	local vulkanlib = os.findlib("vulkan-1")
	
	if (vulkanlib) then
		VULKAN_FOUND = true
		print("Vulkan found on the system")
		print("Dynamic linking is possible")
	else
		print("Vulkan not found")
		print("You can try to link statically with the provide lib in Vulkan SDK")
		print("Use function : linkVulkanStatic() against your project in the premake script file")
	end
end

function GetVulkanPath()
	local vulkanSDKPath = os.getenv("VULKAN_SDK")
	
	if (vulkanSDKPath) then
		if (VULKAN_SDK_FOUND == false) then
			VULKAN_SDK_FOUND = true
			print ("Vulkan SDK found on your system")
		end
		
		return vulkanSDKPath:gsub("\\", "/")
	else
		print ("Vulkan SDK not found on your system. Maybe you forgot to install it ?")
		return ""
	end
end

function includeVulkanSDKWin32()
	local vulkanSDKPath = GetVulkanPath()
	
	if (vulkanSDKPath) then
		includedirs { vulkanSDKPath:gsub("\\", "/") .. "/Include" }
	end
end

function linkVulkanStaticWin32()
	local vulkanSDKPath = GetVulkanPath()
	
	if (vulkanSDKPath) then
		libdirs { vulkanSDKPath:gsub("\\", "/") .. "/Lib" }
	end
	
	links { "vulkan-1" }
end