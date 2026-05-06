#pragma once
#ifdef _WIN32
	#ifdef DEBUG_DLL
		#define DEBUG_API __declspec(dllexport)
	#else
		#define DEBUG_API __declspec(dllimport)
	#endif
#else
	#define DEBUG_API
#endif