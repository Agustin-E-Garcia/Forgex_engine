#pragma once
#if _WIN32
	#if GRAPHICS_DLL
		#define GRAPHICS_API __declspec(dllexport)
	#else
		#define GRAPHICS_API __declspec(dllimport)
	#endif
#else
	#define GRAPHICS_API
#endif
