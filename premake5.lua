workspace "Voxel_Engine"
	architecture "x64"
	configurations { "Debug", "Release" }
	buildoptions "/MDd"

	language "C++"
	cppdialect "C++17"

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")

	includedirs {
		"ExternalLibraries/Spdlog/spdlog-1.14.1/include",
		"ExternalLibraries/STB_Image"
	}

	project "Engine_Core"
		location "Core"
		kind "SharedLib"
		files { "Core/**.cpp", "Core/**.h" }
		defines { "ENGINE_DLL" }

		includedirs {
			"ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/include",
			"ExternalLibraries/GLEW/glew-2.2.0/include",
			"ExternalLibraries/GLM"
		}

		libdirs {
			"ExternalLibraries/GLEW/glew-2.2.0/lib/Release/x64",
			"ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/lib-vc2017"
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