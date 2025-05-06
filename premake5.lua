workspace "Forgex_Engine"
	architecture "x64"
	configurations { "Debug", "Release" }
	language "C++"
	cppdialect "C++20"
	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	includedirs { "Modules/Debug/Include" }
	buildoptions { "/utf-8" }

    project "Debug_Module"
        location "Modules/Debug"
        kind "SharedLib"
        files { "Modules/Debug/**.cpp", "Modules/Debug/**.h" }
        defines { "DEBUG_DLL" }
        includedirs { "ExternalLibraries/Spdlog/include" }

	project "Core_Module"
		location "Modules/Core"
		kind "SharedLib"
		files { "Modules/Core/**.cpp", "Modules/Core/**.h" }
		links { "Graphics_Module", "Scene_Module", "Math_Module", "Debug_Module", "UI_Module" }
		defines { "CORE_DLL" }
		includedirs{
		    "Modules/Graphics/Include",
		    "Modules/Scene/Include",
		    "Modules/Math/Include",
		    "Modules/UI/Include"
		}
	
	project "Graphics_Module"
    	location "Modules/Graphics"
    	kind "SharedLib"
    	files { "Modules/Graphics/**.cpp", "Modules/Graphics/**.h" }
    	links { "Math_Module", "Debug_Module" }
    	defines { "GRAPHICS_DLL" }
    	includedirs {
    	    "Modules/Math/Include",
    	    "ExternalLibraries/GLEW/glew-2.1.0/include", 
    	    "ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/include",
    	    "ExternalLibraries/STB_Image"
    	}
    	libdirs {
        	"ExternalLibraries/GLEW/glew-2.1.0/lib/Release/x64",
    	    "ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/lib-vc2017" 
    	}
    	links { "glew32.lib", "glfw3.lib", "opengl32.lib" }
    	
    project "Scene_Module"
       	location "Modules/Scene"
       	kind "SharedLib"
       	files { "Modules/Scene/**.cpp", "Modules/Scene/**.h" }
       	links { "Math_Module", "Debug_Module" }
       	defines { "SCENE_DLL" }
       	includedirs{ "Modules/Math/Include" }
	
    project "Math_Module"
       	location "Modules/Math"
       	kind "SharedLib"
       	files { "Modules/Math/**.cpp", "Modules/Math/**.h" }
       	defines { "MATH_DLL" }
       	includedirs { "ExternalLibraries/GLM" }
    
    project "UI_Module"
       	location "Modules/UI"
       	kind "SharedLib"
       	files { "Modules/UI/**.cpp", "Modules/UI/**.h" }
       	links { "Debug_Module", "ImGui" }
       	defines { "UI_DLL" }
       	includedirs { "ExternalLibraries/ImGui" }
        libdirs { "ExternalLibraries/ImGui/bin" }

	
    project "Assets_Module"
       	location "Modules/Assets"
       	kind "SharedLib"
       	files { "Modules/Assets/**.cpp", "Modules/Assets/**.h" }
       	links { "Debug_Module" }
       	defines { "ASSETS_DLL" }
       	libdirs { }
       	links {	}
       	
    project "Forgex_Editor"
        location "Editor"
        kind "ConsoleApp"
        files { "Editor/**.cpp", "Editor/**.h" }
        links { "Core_Module", "Debug_Module" }
        includedirs { "Modules/Core/Include" }
        postbuildcommands { 
        "{COPYFILE} %[Build/Bin/Core_Module/%{cfg.longname}/Core_Module.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYFILE} %[Build/Bin/Debug_Module/%{cfg.longname}/Debug_Module.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYFILE} %[Build/Bin/Graphics_Module/%{cfg.longname}/Graphics_Module.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYFILE} %[Build/Bin/Math_Module/%{cfg.longname}/Math_Module.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYFILE} %[Build/Bin/Scene_Module/%{cfg.longname}/Scene_Module.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYFILE} %[Build/Bin/UI_Module/%{cfg.longname}/UI_Module.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYFILE} %[ExternalLibraries/GLEW/glew-2.1.0/bin/Release/x64/glew32.dll] %[Build/Bin/%{prj.name}/%{cfg.longname}]",
        "{COPYDIR} %[Editor/Resources] %[Build/Bin/%{prj.name}/%{cfg.longname}/Resources]"
        }

    project "ImGui"
		location "ExternalLibraries/ImGui"
		kind "StaticLib"
		language "C++"

        includedirs { "ExternalLibraries/ImGui" }

		links {
			"opengl32.lib"
		}

		targetdir("ExternalLibraries/ImGui/bin")

		files { 
			"ExternalLibraries/ImGui/*.cpp", "ExternalLibraries/ImGui/*.h",
			"ExternalLibraries/ImGui/backends/imgui_impl_opengl3.h", "ExternalLibraries/ImGui/backends/imgui_impl_opengl3.cpp",
			"ExternalLibraries/ImGui/misc/cpp/imgui_stdlib.cpp",
			"ExternalLibraries/ImGui/misc/cpp/imgui_stdlib.h"
		}