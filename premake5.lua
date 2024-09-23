workspace "Voxel_Engine"
	architecture "x64"
	configurations { "Debug", "Release" }
	buildoptions "/MDd"

	language "C++"
	cppdialect "C++17"

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")

	includedirs {
		"ExternalLibraries/Spdlog/spdlog-1.14.1/include",
		"ExternalLibraries/STB_Image",
		"ExternalLibraries/ImGUI",
		"ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/include",
		"ExternalLibraries/GLEW/glew-2.2.0/include",
		"ExternalLibraries/GLM",
	}

	project "Engine_Core"
		location "Core"
		kind "SharedLib"
		files { "Core/**.cpp", "Core/**.h" }
		links { "ImGui" }
		defines { "ENGINE_DLL" }

		libdirs {
			"ExternalLibraries/GLEW/glew-2.2.0/lib/Release/x64",
			"ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/lib-vc2017",
			"ExternalLibraries/ImGUI/imgui/bin"
		}

		links {
			"glew32.lib",
			"glfw3.lib",
			"opengl32.lib"
		}
	
	project "Engine_Application"
		location "App"
		kind "ConsoleApp"
		files { "App/**.cpp", "App/**.h" }
		includedirs { "Core" }
		links { "Engine_Core" }

		postbuildcommands { 
			"{COPYFILE} %[Build/Bin/Engine_Core/%{cfg.longname}/Engine_Core.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]", 
			"{COPYFILE} %[ExternalLibraries/GLEW/glew-2.2.0/bin/Release/x64/glew32.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
			"{COPYDIR} %[App/Resources] %[Build/Bin/%{prj.name}/%{cfg.longname}/Resources]"
		}

	project "ImGui"
		location "ExternalLibraries/ImGUI/imgui"
		kind "StaticLib"
		language "C++"

		links {
			"opengl32.lib"
		}

		targetdir("ExternalLibraries/ImGUI/imgui/bin")

		files { 
			"ExternalLibraries/ImGUI/imgui/*.cpp", "ExternalLibraries/ImGUI/imgui/*.h",
			"ExternalLibraries/ImGUI/imgui/backends/OpenGL/*.h", "ExternalLibraries/ImGUI/imgui/backends/OpenGL/*.cpp",
			"ExternalLibraries/ImGUI/imgui/misc/cpp/imgui_stdlib.cpp",
			"ExternalLibraries/ImGUI/imgui/misc/cpp/imgui_stdlib.h"
		}