#pragma once
#ifdef _WIN32
	#ifdef ENGINE_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#define ENGINE_API
#endif