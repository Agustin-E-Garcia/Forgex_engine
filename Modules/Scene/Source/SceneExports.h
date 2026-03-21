#pragma once
#ifdef _WIN32
	#ifdef SCENE_DLL
		#define SCENE_API __declspec(dllexport)
	#else
		#define SCENE_API __declspec(dllimport)
	#endif
#else
	#define SCENE_API
#endif
