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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Silfur/vendor/GLFW/include"
IncludeDir["vulkan"] = "$(VULKAN_SDK)/include" -- TODO : Check Linux compatibility
IncludeDir["spdlog"] = "Silfur/vendor/spdlog/include"
IncludeDir["portableSnippets"] = "Silfur/vendor/portable-snippets"

group "Dependencies"
	include "Silfur/vendor/GLFW"
	
group ""

project "Silfur"
	location "Silfur"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sfpch.h"
	pchsource "Silfur/src/sfpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
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
		"%{IncludeDir.vulkan}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.portableSnippets}",
	}
	
	links
	{
		"GLFW",
		"$(VULKAN_SDK)/lib/vulkan-1.lib" -- TODO : Check Linux compatibility
	}

	filter "system:windows"
		systemversion "latest"
		defines "_WIN32"

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
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.vulkan}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.portableSnippets}",
		"Silfur/src"
	}

	links
	{
		"Silfur"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		kind "ConsoleApp"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		kind "WindowedApp"
		defines "_NDEBUG"
		runtime "Release"
		optimize "Full"

	filter "configurations:Development"
		kind "ConsoleApp"
		defines "_DEBUG"
		runtime "Debug"
		optimize "Debug"