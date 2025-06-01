#pragma once
#if _WIN32
	#if DEBUG_DLL
		#define DEBUG_API __declspec(dllexport)
	#else
		#define DEBUG_API __declspec(dllimport)
	#endif
#else
	#define DEBUG_API
#endif
