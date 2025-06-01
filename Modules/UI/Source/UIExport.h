#pragma once
#if _WIN32
	#if UI_DLL
		#define UI_API __declspec(dllexport)
	#else
		#define UI_API __declspec(dllimport)
	#endif
#else
	#define UI_API
#endif

