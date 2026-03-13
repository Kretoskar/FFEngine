include "dependencies.lua"

workspace "FF"
	language "C++"
	cppdialect "C++20"
	architecture "x86_64"
	startproject "FFSandbox"
	configurations { "Debug", "Release" }

	filter { "configurations:Debug" }
		symbols "On"

	filter { "configurations:Release" }
		optimize "On"

	filter { }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FFCore"
	location "FFCore"
	kind "StaticLib"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
	
	includedirs
	{
		"%{prj.name}/include"
	}

	
	filter "configurations:Debug"
		defines "FF_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		defines "FF_RELEASE"
		runtime "Release"
		optimize "on"

project "FFVulkan"
	location "FFVulkan"
    kind "StaticLib"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

	includedirs
	{
		"%{prj.name}/include",
		"FFCore/include",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.GLFW}",
	}
	
	dependson { "FFCore" }

	filter { "system:windows" }
    	links { "OpenGL32" }
		
	filter {}
	
	filter "configurations:Debug"
		defines "FF_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		defines "FF_RELEASE"
		runtime "Release"
		optimize "on"

project "FFEngine"
	location "FFEngine"
    kind "StaticLib"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

	includedirs
	{
		"%{prj.name}/include",
		"FFCore/include",
		"FFVulkan/include",
		"%{IncludeDir.GLFW}",
	}
	
	dependson { "FFCore", "FFVulkan" }

	filter { "system:windows" }
    	links { "OpenGL32" }
		
	filter {}
	
	filter "configurations:Debug"
		defines "FF_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		defines "FF_RELEASE"
		runtime "Release"
		optimize "on"

project "FFSandbox"
	location "FFSandbox"
    kind "ConsoleApp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

	includedirs
	{
		"FFCore/include",
		"FFVulkan/include",
		"FFEngine/include",
		"FFSandbox/include",
	}

	
	libdirs
	{
		"%{LibraryDir.GLFW}",
	}


	links
	{
		"FFCore",
		"FFEngine",
		"FFVulkan",
		"glfw3",
	}
	
	libdirs
	{
		"%{LibraryDir.VulkanSDK}",
	}
	
	links(VulkanLinks.Common)

	filter "configurations:Debug"
		links(VulkanLinks.Debug)
	
	filter "configurations:Release"
		links(VulkanLinks.Release)
		
	filter {}
	
	filter "configurations:Debug"
		defines "FF_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		defines "FF_RELEASE"
		runtime "Release"
		optimize "on"
	
	dependson { "FFCore", "FFCore", "FFEngine" }