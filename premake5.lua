include "scripts/FindVulkan.lua"

checkVulkanDynamicLibWin32()

IncludeDir = {}
IncludeDir["GLFW"] = "Silfur/vendor/GLFW/include"
IncludeDir["glm"] = "Silfur/vendor/glm"
IncludeDir["spdlog"] = "Silfur/vendor/spdlog/include"
IncludeDir["stb"] = "Silfur/vendor/stb"
IncludeDir["portableSnippets"] = "Silfur/vendor/portable-snippets"
IncludeDir["tinyobjloader"] = "Silfur/vendor/tinyobjloader"

workspace "Silfur Engine"
	architecture "x86_64"
	characterset "Default"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Development"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
	removefiles
	{
		"**.spv"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Silfur/vendor/GLFW"
group ""

group "Tools"
	project "CompileShaders"
		location "tools"
		kind "Utility"
		files
		{
			"%{prj.location}/../**.vert",
			"%{prj.location}/../**.frag",
			"%{prj.location}/../**.tesc",
			"%{prj.location}/../**.tese",
			"%{prj.location}/../**.geom",
			"%{prj.location}/../**.comp"
		}
		
		local vulkanPath = GetVulkanPath()
		local glslCompiler = ""
		local buildoutputcommand = "%{file.directory}/%{file.name}.spv"
		if (VULKAN_SDK_FOUND) then
			glslCompiler = vulkanPath .. '/bin/glslangValidator'
		end
		
		filter "files:**/*"
			buildmessage "Compiling %{file.name}..."
			buildcommands(glslCompiler .. ' -V -o "%{file.directory}%{file.name}.spv" "%{file.relpath}"')
			buildoutputs (buildoutputcommand:gsub("\\", "/"))
group ""

project "Silfur"
	location "Silfur"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sfpch.hpp"
	pchsource "Silfur/src/sfpch.cpp"

	files
	{
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.inl",
		"%{prj.location}/src/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",
		"%{prj.location}/**.vert",
		"%{prj.location}/**.frag",
		"%{prj.location}/**.tesc",
		"%{prj.location}/**.tese",
		"%{prj.location}/**.geom",
		"%{prj.location}/**.comp"
	}

	defines
	{
		"SF_CORE",
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.portableSnippets}",
		"%{IncludeDir.tinyobjloader}"
	}
	
	includeVulkanSDKWin32()

	filter "system:windows"
		systemversion "latest"
		defines "_WIN32"
		
	filter "action:vs2019"
		disablewarnings
		{
			"6323", -- https://docs.microsoft.com/en-US/cpp/code-quality/c6323?view=vs-2019
			"6385", -- https://docs.microsoft.com/en-US/cpp/code-quality/c6385?view=vs-2019
			"6387", -- https://docs.microsoft.com/en-US/cpp/code-quality/c6387?view=vs-2019
			"26812", -- https://docs.microsoft.com/en-US/cpp/code-quality/c26812?view=vs-2019
			"26495", -- https://docs.microsoft.com/en-US/cpp/code-quality/c26495?view=vs-2019
			"26451" -- https://docs.microsoft.com/en-US/cpp/code-quality/c26451?view=vs-2019
		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"SF_NDEBUG",
			"_NDEBUG"
		}
		runtime "Release"
		optimize "Full"

	filter "configurations:Development"
		defines "SF_DEBUG"
		runtime "Debug"
		optimize "Debug"

project "Sandbox"
	location "examples/Sandbox"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.inl",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/**.vert",
		"%{prj.location}/**.frag",
		"%{prj.location}/**.tesc",
		"%{prj.location}/**.tese",
		"%{prj.location}/**.geom",
		"%{prj.location}/**.comp"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.portableSnippets}",
		"%{IncludeDir.tinyobjloader}",
		"Silfur/src"
	}
	
	includeVulkanSDKWin32()

	links
	{
		"Silfur",
		"GLFW",
		"CompileShaders"
	}
	
	linkVulkanStaticWin32()

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		kind "ConsoleApp"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Development"
		kind "ConsoleApp"
		defines "_DEBUG"
		runtime "Debug"
		optimize "Debug"

	filter "configurations:Release"
		kind "WindowedApp"
		defines "_NDEBUG"
		runtime "Release"
		optimize "Full"