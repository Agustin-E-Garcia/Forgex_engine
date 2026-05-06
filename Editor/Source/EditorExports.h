#pragma once
#ifdef _WIN32
	#ifdef EDITOR_DLL
		#define EDITOR_API __declspec(dllexport)
	#else
		#define EDITOR_API __declspec(dllimport)
	#endif
#else
	#define EDITOR_API
#endif