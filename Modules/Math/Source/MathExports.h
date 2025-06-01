#pragma once
#if _WIN32
	#if MATH_DLL
		#define MATH_API __declspec(dllexport)
	#else
		#define MATH_API __declspec(dllimport)
	#endif
#else
	#define MATH_API
#endif
