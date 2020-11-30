workspace "MatzeLib"
	architecture "x64"
	startproject "MatzeLib"

	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "ThirdParty"
	include "MatzeLib/ThirdParty/GLFW"
	include "MatzeLib/ThirdParty/Glad"
	include "MatzeLib/ThirdParty/imgui"
group ""

project "MatzeLib"
	location "MatzeLib"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"MatzeLib/src/**.h",
		"MatzeLib/src/**.cpp"
	}
	includedirs { 
		"MatzeLib/src",
		"MatzeLib/ThirdParty/GLFW/include",
		"MatzeLib/ThirdParty/Glad/include",
		"MatzeLib/ThirdParty/imgui",
		"MatzeLib/ThirdParty/glm",
		"MatzeLib/ThirdParty/stb_image"
	}

	links { "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	filter "configurations:Release"
		optimize "On"