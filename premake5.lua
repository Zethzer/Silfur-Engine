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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Silfur/vendor/GLFW/include"
IncludeDir["vulkan"] = "$(VULKAN_SDK)/include" -- TODO : Check Linux compatibility
IncludeDir["glm"] = "Silfur/vendor/glm"
IncludeDir["spdlog"] = "Silfur/vendor/spdlog/include"
IncludeDir["stb"] = "Silfur/vendor/stb"
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
		"%{prj.location}/src/**.h",
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
		"%{IncludeDir.vulkan}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.portableSnippets}",
	}

	filter "system:windows"
		systemversion "latest"
		defines "_WIN32"
		prebuildcommands
		{
			"pushd ..\\scripts",
			"call CompileShaders.bat",
			"popd"
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
		"%{prj.location}/src/**.h",
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
		"%{IncludeDir.vulkan}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.portableSnippets}",
		"Silfur/src"
	}

	links
	{
		"Silfur",
		"GLFW",
		"$(VULKAN_SDK)/lib/vulkan-1.lib" -- TODO : Check Linux compatibility
	}

	filter "system:windows"
		systemversion "latest"
		prebuildcommands
		{
			"pushd ..\\..\\scripts",
			"call CompileShaders.bat",
			"popd"
		}
		
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