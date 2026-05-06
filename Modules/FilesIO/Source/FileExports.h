#pragma once
#ifdef _WIN32
	#ifdef FILES_DLL
		#define FILES_API __declspec(dllexport)
	#else
		#define FILES_API __declspec(dllimport)
	#endif
#else
	#define FILES_API
#endif