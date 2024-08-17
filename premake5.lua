workspace "Voxel_Engine"
	architecture "x64"
	configurations { "Debug", "Release" }

	includedirs { "ExternalLibraries" }
	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")

	project "Engine_Core"
		location "Core"
		kind "SharedLib"
		language "C++"
		files { "Core/**.cpp", "Core/**.h" }
		defines { "ENGINE_DLL" }
	
	project "Engine_Application"
		location "App"
		kind "ConsoleApp"
		language "C++"
		files { "App/**.cpp", "App/**.h" }
		includedirs { "Core" }
		links { "Engine_Core" }
		postbuildcommands { "{COPYFILE} %[Build/Bin/Engine_Core/%{cfg.longname}/Engine_Core.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]" }