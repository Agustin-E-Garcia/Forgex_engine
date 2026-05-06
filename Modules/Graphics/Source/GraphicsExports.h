#pragma once
#ifdef _WIN32
	#ifdef GRAPHICS_DLL
		#define GRAPHICS_API __declspec(dllexport)
	#else
		#define GRAPHICS_API __declspec(dllimport)
	#endif
#else
	#define GRAPHICS_API
#endif