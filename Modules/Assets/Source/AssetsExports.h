#pragma once
#if _WIN32
	#if ASSETS_DLL
		#define ASSETS_API __declspec(dllexport)
	#else
		#define ASSETS_API __declspec(dllimport)
	#endif
#else
	#define ASSETS_API
#endif
