#pragma once
#ifdef _WIN32
	#ifdef ASSETS_DLL
		#define ASSETS_API __declspec(dllexport)
	#else
		#define ASSETS_API __declspec(dllimport)
	#endif
#else
	#define ASSETS_API
#endif